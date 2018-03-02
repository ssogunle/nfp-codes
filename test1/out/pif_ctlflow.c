/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#include <nfp/me.h>
#include "pif_common.h"

/****************************************
 * ingress_flow                         *
 ****************************************/

/* State transition functions */

static int handle_ingress_flow_in_tbl(__lmem uint32_t *parrep, __mem uint32_t *actbuf, unsigned int *actlen, int *state)
{
    __gpr int action_id, ret;
    int next_state = PIF_CTLFLOW_STATE_ingress_flow_DONE;

#ifdef PIF_DEBUG
    __debug_label("pif_ctlflow_state_ingress_flow_in_tbl");
#endif

    {
        struct pif_lookup_result result;
        result = pif_lookup(PIF_TABLE_ID_in_tbl, parrep, actbuf);
        action_id = result.action_id;
        *actlen = result.action_len;
    }

    next_state = PIF_CTLFLOW_STATE_ingress_flow_exit_control_flow; /* always */

    if (*actlen > 0) {
        ret = pif_action_execute(parrep, actbuf, *actlen);
        if (ret < 0)
            return -1;
    }

    *state = next_state;
    return 0;
}

/* Control flow entry point */

int pif_ctlflow_ingress_flow(int *start_state, __lmem uint32_t *parrep, __mem uint32_t *actbuf)
{
    __gpr unsigned int actlen, totlen = 0;
    __gpr int ret;
    int pif_ctlflow_state_ingress_flow = PIF_CTLFLOW_STATE_ingress_flow_in_tbl;

    while (pif_ctlflow_state_ingress_flow != PIF_CTLFLOW_STATE_ingress_flow_DONE) {
        PIF_DEBUG_SET_STATE(PIF_DEBUG_STATE_CONTROL, ((0 << 16) + pif_ctlflow_state_ingress_flow));
#ifdef PIF_DEBUG
        __debug_label("pif_ctlflow_state_ingress_flow");
#endif
        switch (pif_ctlflow_state_ingress_flow) {
        case PIF_CTLFLOW_STATE_ingress_flow_in_tbl:
            ret = handle_ingress_flow_in_tbl(parrep, actbuf + totlen, (unsigned int *)&actlen, (int *)&pif_ctlflow_state_ingress_flow);
            break;
        }
        totlen += actlen;
        if (ret < 0)
            return -totlen;
    }

    return totlen;
}

/* Empty control flow */
int pif_ctlflow_egress_flow(int *start_state, __lmem uint32_t *parrep, __mem uint32_t *actbuf)
{
    return 0;
}
