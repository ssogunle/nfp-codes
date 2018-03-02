/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_GLOBAL_H__
#define __PIF_GLOBAL_H__

#define PIF_GLOBAL_FLOWKEY_MAX_LW 1

void pif_global_metadata_init(__lmem uint32_t *parrep);

unsigned int pif_global_get_stdmd_egress_spec(__lmem uint32_t *parrep);
unsigned int pif_global_get_stdmd_egress_port(__lmem uint32_t *parrep);
void pif_global_set_stdmd_egress_port(__lmem uint32_t *parrep, unsigned int port_spec);
void pif_global_set_stdmd_instance_type(__lmem uint32_t *parrep, unsigned int instance_type);
void pif_global_set_stdmd_egress_instance(__lmem uint32_t *parrep, unsigned int egress_instance);

#endif /* __PIF_GLOBAL_H__ */
