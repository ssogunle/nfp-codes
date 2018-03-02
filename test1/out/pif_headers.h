/* Copyright (C) 2015-2016,  Netronome Systems, Inc.  All rights reserved. */

#ifndef __PIF_HEADERS_H__
#define __PIF_HEADERS_H__

/* Generated C source defining PIF headers, metadata and registers */
/* Warning: your edits to this file may be lost */

/*
 * Packet headers
 */

/* eth (14B) */
struct pif_header_eth {
    /* dst [32;16] */
    unsigned int __dst_0:32;
    /* dst [16;0] */
    unsigned int __dst_1:16;
    /* src [16;32] */
    unsigned int __src_0:16;
    /* src [32;0] */
    unsigned int __src_1:32;
    unsigned int ethype:16;
};

/* eth field accessor macros */
#define PIF_HEADER_GET_eth___dst___0(_hdr_p) ((((_hdr_p)->__dst_0 & 0xffff) << 16) | ((_hdr_p)->__dst_1)) /* eth.dst [32;0] */

#define PIF_HEADER_SET_eth___dst___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__dst_0 &= (unsigned)(0xffff0000); \
        (_hdr_p)->__dst_0 |= (unsigned)((((_val) >> 16) & 0xffff)); \
        (_hdr_p)->__dst_1 = (unsigned)(((_val))); \
    } while (0) /* eth.dst[32;0] */

#define PIF_HEADER_GET_eth___dst___1(_hdr_p) ((((_hdr_p)->__dst_0 >> 16) & 0xffff)) /* eth.dst [16;32] */

#define PIF_HEADER_SET_eth___dst___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->__dst_0 &= (unsigned)(0xffff); \
        (_hdr_p)->__dst_0 |= (unsigned)((((_val) & 0xffff) << 16)); \
    } while (0) /* eth.dst[16;32] */

#define PIF_HEADER_GET_eth___src___0(_hdr_p) (((_hdr_p)->__src_1)) /* eth.src [32;0] */

#define PIF_HEADER_SET_eth___src___0(_hdr_p, _val) \
    do { \
        (_hdr_p)->__src_1 = (unsigned)(((_val))); \
    } while (0) /* eth.src[32;0] */

#define PIF_HEADER_GET_eth___src___1(_hdr_p) (((_hdr_p)->__src_0)) /* eth.src [16;32] */

#define PIF_HEADER_SET_eth___src___1(_hdr_p, _val) \
    do { \
        (_hdr_p)->__src_0 = (unsigned)(((_val))); \
    } while (0) /* eth.src[16;32] */

#define PIF_HEADER_GET_eth___ethype(_hdr_p) (((_hdr_p)->ethype)) /* eth.ethype [16;0] */

#define PIF_HEADER_SET_eth___ethype(_hdr_p, _val) \
    do { \
        (_hdr_p)->ethype = (unsigned)(((_val))); \
    } while (0) /* eth.ethype[16;0] */


/*
 * Metadata
 */

/* standard_metadata (16B) */
struct pif_header_standard_metadata {
    unsigned int clone_spec:32;
    unsigned int egress_spec:16;
    unsigned int egress_port:16;
    unsigned int packet_length:14;
    unsigned int egress_instance:10;
    unsigned int instance_type:4;
    unsigned int _padding_0:4;
    unsigned int ingress_port:10;
    unsigned int _padding_1:22;
};

/* standard_metadata field accessor macros */
#define PIF_HEADER_GET_standard_metadata___clone_spec(_hdr_p) (((_hdr_p)->clone_spec)) /* standard_metadata.clone_spec [32;0] */

#define PIF_HEADER_SET_standard_metadata___clone_spec(_hdr_p, _val) \
    do { \
        (_hdr_p)->clone_spec = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.clone_spec[32;0] */

#define PIF_HEADER_GET_standard_metadata___egress_spec(_hdr_p) (((_hdr_p)->egress_spec)) /* standard_metadata.egress_spec [16;0] */

#define PIF_HEADER_SET_standard_metadata___egress_spec(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_spec = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_spec[16;0] */

#define PIF_HEADER_GET_standard_metadata___egress_port(_hdr_p) (((_hdr_p)->egress_port)) /* standard_metadata.egress_port [16;0] */

#define PIF_HEADER_SET_standard_metadata___egress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_port = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_port[16;0] */

#define PIF_HEADER_GET_standard_metadata___packet_length(_hdr_p) (((_hdr_p)->packet_length)) /* standard_metadata.packet_length [14;0] */

#define PIF_HEADER_SET_standard_metadata___packet_length(_hdr_p, _val) \
    do { \
        (_hdr_p)->packet_length = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.packet_length[14;0] */

#define PIF_HEADER_GET_standard_metadata___egress_instance(_hdr_p) (((_hdr_p)->egress_instance)) /* standard_metadata.egress_instance [10;0] */

#define PIF_HEADER_SET_standard_metadata___egress_instance(_hdr_p, _val) \
    do { \
        (_hdr_p)->egress_instance = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.egress_instance[10;0] */

#define PIF_HEADER_GET_standard_metadata___instance_type(_hdr_p) (((_hdr_p)->instance_type)) /* standard_metadata.instance_type [4;0] */

#define PIF_HEADER_SET_standard_metadata___instance_type(_hdr_p, _val) \
    do { \
        (_hdr_p)->instance_type = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.instance_type[4;0] */

#define PIF_HEADER_GET_standard_metadata____padding_0(_hdr_p) (((_hdr_p)->_padding_0)) /* standard_metadata._padding_0 [4;0] */

#define PIF_HEADER_SET_standard_metadata____padding_0(_hdr_p, _val) \
    do { \
        (_hdr_p)->_padding_0 = (unsigned)(((_val))); \
    } while (0) /* standard_metadata._padding_0[4;0] */

#define PIF_HEADER_GET_standard_metadata___ingress_port(_hdr_p) (((_hdr_p)->ingress_port)) /* standard_metadata.ingress_port [10;0] */

#define PIF_HEADER_SET_standard_metadata___ingress_port(_hdr_p, _val) \
    do { \
        (_hdr_p)->ingress_port = (unsigned)(((_val))); \
    } while (0) /* standard_metadata.ingress_port[10;0] */

#define PIF_HEADER_GET_standard_metadata____padding_1(_hdr_p) (((_hdr_p)->_padding_1)) /* standard_metadata._padding_1 [22;0] */

#define PIF_HEADER_SET_standard_metadata____padding_1(_hdr_p, _val) \
    do { \
        (_hdr_p)->_padding_1 = (unsigned)(((_val))); \
    } while (0) /* standard_metadata._padding_1[22;0] */



/*
 * Registers
 */

#endif /* __PIF_HEADERS_H__ */
