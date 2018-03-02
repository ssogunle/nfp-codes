/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp.h>
#include <nfp/me.h>
#include <pkt/pkt.h>
#include "nfd_user_cfg.h"
#include "pif_common.h"
#include "pif_pkt_mod_script.h"

__forceinline static int handle_tier_1(__lmem uint32_t *parrep, PIF_PKT_INFO_TYPE struct pif_pkt_info *pktinfo, int *pkt_byteoff, uint32_t pkt_min_off)
{
    __lmem struct pif_parrep_ctldata *ctldata = (__lmem struct pif_parrep_ctldata *)(parrep + PIF_PARREP_CTLDATA_OFF_LW);
    uint32_t orig_len = PIF_PARREP_T1_ORIG_LEN(ctldata);
    uint32_t curr_len = 0;

    if (!PIF_PARREP_T1_DIRTY(ctldata)) {
        *pkt_byteoff -= orig_len;
        if (*pkt_byteoff < 0)
            return -1;

        return 0;
    }

    if (PIF_PARREP_T1_VALID(ctldata)) {
        curr_len = PIF_PARREP_eth_LEN_B;
    }

    if (curr_len) {
        *pkt_byteoff -= curr_len;
        if (*pkt_byteoff < 0)
            return -1;

        pif_pkt_write_header(*pkt_byteoff,
                             parrep,
                             PIF_PARREP_T1_OFF_LW,
                             curr_len);
    }

    return 0;
}

__forceinline extern int pif_deparse(__lmem uint32_t *parrep, PIF_PKT_INFO_TYPE struct pif_pkt_info *pktinfo)
{
    __gpr uint32_t pkt_byteoff = pktinfo->pkt_pl_off;
    __gpr uint32_t pkt_min_off;

    /* Packet minimum offset depends on packet destination - NBI/PCIe */
    pkt_min_off = PIF_PKT_MIN_NBI_TX_OFFSET; /* apply the nbi min to nfd too */
    if (handle_tier_1(parrep, pktinfo, (uint32_t *)&pkt_byteoff, pkt_min_off) < 0)
        return -1;

    pkt_byteoff = PIF_PKT_SOP(pktinfo->pkt_buf, pktinfo->pkt_num);

    /* If packet offset more than maximum allowed for NBI, return error */
    if (pif_pkt_info_global.eg_port.type == PIF_PKT_SRC_NBI) {
        if (pkt_byteoff > PIF_PKT_MAX_NBI_TX_OFFSET)
            return -1;
    }
    if (pif_pkt_info_global.trunc_len != 0 && pif_pkt_info_global.trunc_len < pif_pkt_info_global.pkt_len)
        pif_pkt_info_global.pkt_len = pif_pkt_info_global.trunc_len;

    return pkt_byteoff;
}
