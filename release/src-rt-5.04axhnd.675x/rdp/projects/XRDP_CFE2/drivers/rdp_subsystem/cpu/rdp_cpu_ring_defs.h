/*
 * <:copyright-BRCM:2013:DUAL/GPL:standard
 * 
 *    Copyright (c) 2013 Broadcom 
 *    All Rights Reserved
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :> 
 */


#ifndef _RDP_CPU_RING_DEFS_H
#define _RDP_CPU_RING_DEFS_H

#include "access_macros.h"

#ifndef _BYTE_ORDER_LITTLE_ENDIAN_
typedef struct
{
    union {
        struct {
            uint32_t word0;
            uint32_t word1;
        };
        struct {
            uint32_t host_buffer_data_ptr_low; /* total 40 bits for address */
            uint32_t host_buffer_data_ptr_hi:8;
            uint32_t reserved0:7;
            uint32_t abs:1;
            uint32_t packet_length:14;
            uint32_t is_chksum_verified:1;
            uint32_t reserved2:1;
        } abs;
        struct {
            uint32_t fpm_idx:18;
            uint32_t reserved0:14;
            uint32_t reserved1:15;
            uint32_t abs:1;
            uint32_t packet_length:14;
            uint32_t is_chksum_verified:1;
            uint32_t reserved2:1;
        } fpm;
        struct {
            uint32_t bn0:18;
            uint32_t reserved0:14;
            uint32_t reserved1:15;
            uint32_t abs:1;
            uint32_t packet_length:14;
            uint32_t is_chksum_verified:1;
            uint32_t reserved2:1;
        } sbpm;
    };

    union {
        uint32_t word2;
        struct {
            uint32_t is_src_lan:1;
            uint32_t reserved7:1;
            uint32_t source_port:5;
            uint32_t wan_flow_id:12; /* WAN Flow / DSL flags */
            uint32_t data_offset:7;
            uint32_t reason:6;
        } wan;
        struct {
            uint32_t is_src_lan:1;
            uint32_t reserved7:1;
            uint32_t source_port:5; /* LAN */
            uint32_t reserved3:12;
            uint32_t data_offset:7;
            uint32_t reason:6;
        } lan;
        struct {
            uint32_t is_src_lan:1;
            uint32_t reserved7:1;
            uint32_t vport:5;
            uint32_t ssid:4;
            uint32_t reserved4:8;
            uint32_t data_offset:7;
            uint32_t reason:6;
        } cpu_vport; /* (e.g. WLAN) */
    };

    union {
        uint32_t word3;
        struct {
            uint16_t    is_exception:1;
            uint16_t    is_rx_offload:1;
            uint16_t    is_ucast:1;
            uint16_t    mcast_tx_prio:3;
            uint16_t    reserved5:10;
            union {
                uint16_t dst_ssid_vector; /* For WLAN multicast */
                uint16_t wl_metadata; /* For WLAN multicast */
                struct {
                    uint16_t reserved8:2;
                    uint16_t is_chain:1;
                    uint16_t tx_prio:3;
                    uint16_t reserved9:1;
                    uint16_t iq_prio:1;
                    uint16_t chain_id:8;
                } wl_nic;
                struct {
                    uint16_t reserved10:2;
                    uint16_t is_chain:1;
                    uint16_t tx_prio:3;
                    uint16_t flow_ring_idx:10;
                } wl_dongle;
                struct {
                    uint16_t reserved11:2;
                    uint16_t metadata_0:4; /* For WLAN: is_chain:1, tx_prio:3 */
                    uint16_t metadata_1:10; /* For WLAN NIC: rsv:1, iq_prio:1, chain_id:1; Dongle: flow_ring_idx:10 */
                } metadata;
#ifdef CONFIG_CPU_REDIRECT_MODE_SUPPORT
                struct {
                    uint16_t egress_queue:8;
                    uint16_t wan_flow:8;
                } cpu_redirect;
#endif
            };
        };
    };
}
CPU_RX_DESCRIPTOR;


#else
typedef struct
{
    union {
        struct {
            uint32_t word0;
            uint32_t word1;
        };
        struct {
            uint32_t host_buffer_data_ptr_low; /* total 40 bits for address */
            uint32_t reserved2:1;
            uint32_t is_chksum_verified:1;
            uint32_t packet_length:14;
            uint32_t abs:1;
            uint32_t reserved0:7;
            uint32_t host_buffer_data_ptr_hi:8;
        } abs;
        struct {
            uint32_t reserved0:14;
            uint32_t fpm_idx:18;
            uint32_t reserved2:1;
            uint32_t is_chksum_verified:1;
            uint32_t packet_length:14;
            uint32_t abs:1;
            uint32_t reserved1:15;
        } fpm;
        struct {
            uint32_t reserved0:14;
            uint32_t bn0:18;
            uint32_t reserved2:1;
            uint32_t is_chksum_verified:1;
            uint32_t packet_length:14;
            uint32_t abs:1;
            uint32_t reserved1:15;
        } sbpm;
    };
    union {
        uint32_t word2;
        struct {
            uint32_t reason:6;
            uint32_t data_offset:7;
            uint32_t wan_flow_id:12; /* WAN Flow / DSL flags */
            uint32_t source_port:5;
            uint32_t reserved7:1;
            uint32_t is_src_lan:1;
        } wan;
        struct {
            uint32_t reason:6;
            uint32_t data_offset:7;
            uint32_t reserved3:12;
            uint32_t source_port:5; /* LAN */
            uint32_t reserved7:1;
            uint32_t is_src_lan:1;
        } lan;
        struct {
            uint32_t reason:6;
            uint32_t data_offset:7;
            uint32_t reserved4:8;
            uint32_t ssid:4;
            uint32_t vport:5;
            uint32_t reserved7:1;
            uint32_t is_src_lan:1;
        } cpu_vport;
    };

    union {
        uint32_t word3;
        struct {
            union {
                uint16_t dst_ssid_vector; /* For WLAN multicast */
                uint16_t wl_metadata; /* For WLAN multicast */
                struct {
                    uint16_t metadata_1:10; /* For WLAN NIC: rsv:1, iq_prio:1, chain_id:1; Dongle: flow_ring_idx:10 */
                    uint16_t metadata_0:4; /* For WLAN: is_chain:1, tx_prio:3 */
                    uint16_t reserved11:2;
                } metadata;
                struct {
                    uint16_t flow_ring_idx:10;
                    uint16_t tx_prio:3;
                    uint16_t is_chain:1;
                    uint16_t reserved10:2;
                } wl_dongle;
                struct {
                    uint16_t chain_id:8;
                    uint16_t iq_prio:1;
                    uint16_t reserved9:1;
                    uint16_t tx_prio:3;
                    uint16_t is_chain:1;
                    uint16_t reserved8:2;
                } wl_nic;
#ifdef CONFIG_CPU_REDIRECT_MODE_SUPPORT
                struct {
                    uint16_t wan_flow:8;
                    uint16_t egress_queue:8;
                } cpu_redirect;
#endif
            };
            uint16_t    reserved5:10;
            uint16_t    mcast_tx_prio:3;
            uint16_t    is_ucast:1;
            uint16_t    is_rx_offload:1;
            uint16_t    is_exception:1;
        };
    };
}
CPU_RX_DESCRIPTOR;


#endif

#endif /*_RDP_CPU_RING_DEFS_H */
