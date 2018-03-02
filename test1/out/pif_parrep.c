/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include <hashmap.h>
#include "pif_common.h"


static __inline __gpr int handle_node_start(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_start");
#endif

    *(pstate) = PIF_PARREP_STATE_eth_parse;

    return hdrsz;
}


static __inline __gpr int handle_node_eth_parse(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktdataoff, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len, int *pstate)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    __gpr int hdrsz = 0;
    __lmem struct pif_header_eth *eth;

#ifdef PIF_DEBUG
    __debug_label("pif_parrep_state_eth_parse");
#endif

    eth = (__lmem struct pif_header_eth *) (lm_ptr + PIF_PARREP_eth_OFF_LW);

    mem2lmem_copy(pktdata + (pktdataoff + hdrsz),
                  lm_ptr,
                  PIF_PARREP_eth_OFF_LW,
                  PIF_PARREP_eth_LEN_LW);
    hdrsz += PIF_PARREP_eth_LEN_B;

    *(pstate) = PIF_PARREP_STATE_in_tbl;

    PIF_PARREP_SET_eth_VALID(prdata);
    PIF_PARREP_SET_T1_ORIG_LEN(prdata, hdrsz);

    return hdrsz;
}

extern __forceinline
pif_parrep_extract(__lmem uint32_t *lm_ptr, __mem uint8_t *pktdata, unsigned int pktlen, __lmem uint32_t *fk_ptr, __gpr uint32_t *fk_len)
{
    __lmem struct pif_parrep_ctldata *prdata = (__lmem struct pif_parrep_ctldata *)(lm_ptr + PIF_PARREP_CTLDATA_OFF_LW);
    PIF_PKT_INFO_TYPE struct pif_pkt_info *pkt_info = &pif_pkt_info_global;
    __gpr int exit_node = 0;
    __gpr int pif_parrep_state;
    __gpr int ret;
    __gpr int off = 0;
    int i;

    /* set state to graph entry node */
    pif_parrep_state = PIF_PARREP_STATE_start;

    /* First zero the parsed representation control data fields */
    for (i = 0; i < PIF_PARREP_CTLDATA_LEN_LW; i++)
        lm_ptr[PIF_PARREP_CTLDATA_OFF_LW + i] = 0;

    /* run through the states extracting as we go */
    while (pif_parrep_state != PIF_PARREP_STATE_DONE) {
        PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_PARSER, pif_parrep_state);
#ifdef PIF_DEBUG
        __debug_label("pif_parrep_state");
#endif
        switch (pif_parrep_state) {
        case PIF_PARREP_STATE_start:
            ret = handle_node_start(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        case PIF_PARREP_STATE_eth_parse:
            ret = handle_node_eth_parse(lm_ptr, pktdata, off, fk_ptr + *fk_len, fk_len, (int *) &pif_parrep_state);
            break;
        }
        if (ret < 0) {
            pkt_info->pkt_pl_off = off;
            return ret;
        }
        off += ret;
        if (off > pktlen) {
            pkt_info->pkt_pl_off = off;
            return -PIF_PARSE_ERROR_OUT_OF_PACKET;
        }
    }

#ifndef PIF_GLOBAL_FLOWCACHE_DISABLED
    for (i = 0; i < PIF_PARREP_CTLDATA_LEN_LW; i++)
        fk_ptr[i + *fk_len] = lm_ptr[PIF_PARREP_CTLDATA_OFF_LW + i];
    *fk_len += PIF_PARREP_CTLDATA_LEN_LW;
#endif /* !PIF_GLOBAL_FLOWCACHE_DISABLED */

    if (off > 1023) {
        pkt_info->pkt_pl_off = off;
        return -PIF_PARSE_ERROR_HEADER_TOO_LONG;
    }

    pkt_info->pkt_pl_off = off;
    PIF_PARREP_SET_VALID(prdata);
    return exit_node;
}

extern __forceinline int
pif_parrep_exceptions(__lmem uint32_t *parrep, int result)
{
    return -1; /* no exceptions, always fail */
}
