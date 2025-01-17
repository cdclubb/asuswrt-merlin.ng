/*
    <:copyright-BRCM:2013:DUAL/GPL:standard
    
       Copyright (c) 2013 Broadcom 
       All Rights Reserved
    
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License, version 2, as published by
    the Free Software Foundation (the "GPL").
    
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    
    
    A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
    writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
    
:>
*/

#ifndef _BL_LILAC_DRV_RUNNER_RDD_DEFS_H
#define _BL_LILAC_DRV_RUNNER_RDD_DEFS_H

#include "rdd_fw_defs.h"
#include "rdpa_types.h"
#include "rdpa_cpu_basic.h"
#include "rdd_data_structures_auto.h"

/* Dependency in rdd_wl4908_partial_legacy_conv.h */
typedef enum {
    rdd_egress_phy_eth_lan = 0,
    rdd_egress_phy_wlan,
    rdd_egress_phy_wan_start,
    rdd_egress_phy_eth_wan = rdd_egress_phy_wan_start,
    rdd_egress_phy_dsl,
    rdd_egress_phy_gpon = rdd_egress_phy_eth_wan,
    rdd_egress_phy_max   /* can only support 4 types */
} rdd_egress_phy_t;

#if defined(WL4908)
#include "rdd_wl4908_partial_legacy_conv.h"
#endif

/* Runner Device Driver Errors */
typedef enum
{
    BL_LILAC_RDD_OK                                                          = 0,
    BL_LILAC_RDD_ERROR_MALLOC_FAILED                                         = 10,
    BL_LILAC_RDD_ERROR_ILLEGAL_BRIDGE_PORT_ID                                = 11,
    BL_LILAC_RDD_ERROR_ILLEGAL_EMAC_ID                                       = 12,
    BL_LILAC_RDD_ERROR_ILLEGAL_QUEUE_ID                                      = 13,
    BL_LILAC_RDD_ERROR_ILLEGAL_WAN_CHANNEL_ID                                = 14,
    BL_LILAC_RDD_ERROR_ILLEGAL_RATE_CONTROLLER_ID                            = 15,
    BL_LILAC_RDD_ERROR_ILLEGAL_RATE_SHAPER_ID                                = 16,
    BL_LILAC_RDD_ERROR_ILLEGAL_POLICER_ID                                    = 17,
    BL_LILAC_RDD_ERROR_ILLEGAL_DIRECTION                                     = 18,
    BL_LILAC_RDD_ERROR_ILLEGAL_RUNNER_ID                                     = 19,
    BL_LILAC_RDD_ERROR_RATE_CONTROLLERS_POOL_OVERFLOW                        = 50,
    BL_LILAC_RDD_ERROR_RATE_CONTROLLER_NOT_CONFIGURED                        = 52,
    BL_LILAC_RDD_ERROR_RATE_SHAPER_NOT_CONFIGURED                            = 55,
    BL_LILAC_RDD_ERROR_GPON_TX_QUEUES_POOL_OVERFLOW                          = 70,
    BL_LILAC_RDD_ERROR_GPON_TX_QUEUE_NOT_CONFIGURED                          = 72,
    BL_LILAC_RDD_ERROR_GPON_TX_QUEUE_EMPTY                                   = 73,
    BL_LILAC_RDD_ERROR_CPU_RX_QUEUE_ILLEGAL                                  = 100,
    BL_LILAC_RDD_ERROR_CPU_RX_REASON_ILLEGAL                                 = 101,
    BL_LILAC_RDD_ERROR_CPU_RX_QUEUE_EMPTY                                    = 102,
    BL_LILAC_RDD_ERROR_CPU_RX_QUEUE_INVALID                                  = 103,
    BL_LILAC_RDD_ERROR_CPU_TX_QUEUE_FULL                                     = 120,
    BL_LILAC_RDD_ERROR_CPU_TX_NOT_ALLOWED                                    = 122,
    BL_LILAC_RDD_ERROR_PCI_TX_QUEUE_EMPTY                                    = 130,
    BL_LILAC_RDD_ERROR_PCI_QUEUE_THRESHOLD_TOO_SMALL                         = 131,
    BL_LILAC_RDD_ERROR_ADD_LOOKUP_ENTRY                                      = 150,
    BL_LILAC_RDD_ERROR_REMOVE_LOOKUP_ENTRY                                   = 151,
    BL_LILAC_RDD_ERROR_GET_LOOKUP_ENTRY                                      = 152,
    BL_LILAC_RDD_ERROR_LOOKUP_ENTRY_EXISTS                                   = 153,
    BL_LILAC_RDD_ERROR_HASH_TABLE_NO_EMPTY_ENTRY                             = 156,
    BL_LILAC_RDD_ERROR_HASH_TABLE_NO_MATCHING_KEY                            = 157,
    BL_LILAC_RDD_ERROR_ADD_LOOKUP_NO_EMPTY_ENTRY                             = 158,
    BL_LILAC_RDD_ERROR_ILLEGAL_MAC_ENTRY_ID                                  = 160,
    BL_LILAC_RDD_ERROR_GET_MAC_ENTRY                                         = 161,
    BL_LILAC_RDD_ERROR_MAC_ENTRY_EXISTS                                      = 162,
    BL_LILAC_RDD_ERROR_MAC_ENTRY_DOESNT_EXIST                                = 163,
    BL_LILAC_RDD_ERROR_ILLEGAL_ARP_ENTRY_ID                                  = 170,
    BL_LILAC_RDD_ERROR_ILLEGAL_IPTV_ENTRY_ID                                 = 175,
    BL_LILAC_RDD_ERROR_INGRESS_CLASSIFICATION_CFG_FULL                       = 180,
    BL_LILAC_RDD_ERROR_INGRESS_CLASSIFICATION_CFG_ILEGGAL_GROUP_SORT         = 181,
    BL_LILAC_RDD_ERROR_INGRESS_CLASSIFICATION_CFG_NOT_EXIST                  = 182,
    BL_LILAC_RDD_ERROR_INGRESS_CLASSIFICATION_CFG_KEY_TOO_LONG               = 183,
    BL_LILAC_RDD_ERROR_INGRESS_CLASSIFICATION_CFG_LONG_TABLE_FULL            = 184,
    BL_LILAC_RDD_ERROR_CAM_LOOKUP_TABLE_FULL                                 = 200,
    BL_LILAC_RDD_ERROR_CAM_LOOKUP_TABLE_EMPTY                                = 201,
    BL_LILAC_RDD_ERROR_CAM_LOOKUP_FAILED                                     = 202,
    BL_LILAC_RDD_ERROR_CAM_INSERTION_FAILED                                  = 203,
    BL_LILAC_RDD_ERROR_BPM_ALLOC_FAIL                                        = 230,
    BL_LILAC_RDD_ERROR_BPM_FREE_FAIL                                         = 231,
    BL_LILAC_RDD_ERROR_ILLEGAL_PBITS                                         = 300,
    BL_LILAC_RDD_ERROR_ILLEGAL_TRAFFIC_CLASS                                 = 301,
    BL_LILAC_RDD_ERROR_ILLEGAL_WAN_MAPPING_TABLE_INDEX                       = 302,
    BL_LILAC_RDD_ERROR_ILLEGAL_PBITS_TO_WAN_FLOW_MAPPING_TABLE               = 303,
    BL_LILAC_RDD_ERROR_ADD_CONTEXT_ENTRY                                     = 350,
    BL_LILAC_RDD_ERROR_CONTEXT_ENTRY_INVALID                                 = 351,
    BL_LILAC_RDD_ERROR_ILLEGAL_SUBNET_ID                                     = 360,
    BL_LILAC_RDD_ERROR_IPTV_TABLE_ENTRY_EXISTS                               = 400,
    BL_LILAC_RDD_ERROR_IPTV_FORWARDING_TABLE_FULL                            = 401,
    BL_LILAC_RDD_ERROR_IPTV_SRC_IP_COUNTER_NOT_ZERO                          = 402,
    BL_LILAC_RDD_ERROR_IPTV_WITH_SRC_IP_ANY_EXISTS                           = 403,
    BL_LILAC_RDD_ERROR_IPTV_TABLE_ENTRY_NOT_EXISTS                           = 404,
    BL_LILAC_RDD_ERROR_ILLEGAL_IPTV_TABLE_CACHE_SIZE                         = 405,
    BL_LILAC_RDD_ERROR_IPTV_SRC_IP_TABLE_FULL                                = 406,
    BL_LILAC_RDD_ERROR_IPTV_CONTEXT_TABLES_TABLE_FULL                        = 407,
    BL_LILAC_RDD_ERROR_DDR_CONTEXT_TABLE_TABLE_FULL                          = 408,
    BL_LILAC_RDD_ERROR_TIMER_TASK_TABLE_FULL                                 = 440,
    BL_LILAC_RDD_ERROR_TIMER_TASK_PERIOD                                     = 441,
    BL_LILAC_RDD_ERROR_NO_FREE_SKB                                           = 450,
    BL_LILAC_RDD_ERROR_1588_TX                                               = 451,
    BL_LILAC_RDD_ERROR_NO_FREE_GSODESC                                       = 452,
    BL_LILAC_RDD_ERROR_SPDSVC_RESOURCE_BUSY                                  = 453,
    BL_LILAC_RDD_ERROR_INGRESS_RATE_LIMITER_BUDGET_TOO_LARGE                 = 460,
    BL_LILAC_RDD_ERROR_INGRESS_RATE_LIMITER_FLOW_CONTROL_THRESHOLD_TOO_LARGE = 461,
    BL_LILAC_RDD_ERROR_GPON_SNIFFER_NULL_PD_PTR                              = 500,
    BL_LILAC_RDD_ERROR_SMC_PPS_SEND_LEN_LESS_THEN_3                          = 600,
    BL_LILAC_RDD_ERROR_SMC_INVALID_SEND_LENGTH                               = 601,
    BL_LILAC_RDD_ERROR_SMC_INVALID_RECEIVE_LENGTH                            = 602,
    BL_LILAC_RDD_ERROR_MTU_INVALID_LENGTH                                    = 603,
    BL_LILAC_RDD_ERROR_ILLEGAL_IPSEC_SA_DESC_TABLE_INDEX                     = 700,
    BL_LILAC_RDD_ERROR_IPSEC_AUTH_ALG_INVALID                                = 701,
    BL_LILAC_RDD_ERROR_IPSEC_CRYPT_ALG_INVALID                               = 702,
    BL_LILAC_RDD_ERROR_IPSEC_CRYPT_MECH_INVALID                              = 703,
    BL_LILAC_RDD_ERROR_IPSEC_CRYPT_NXTHDR_INVALID                            = 704,
    BL_LILAC_RDD_ERROR_IPHOST_TABLE_INDEX_INVALID                            = 705,
    BL_LILAC_RDD_ERROR_HOST_MAC_TABLE_INDEX_INVALID                          = 706,
}
BL_LILAC_RDD_ERROR_DTE;


#define BL_LILAC_RDD_IS_WAN_BRIDGE_PORT(__port)                         \
    ( (__port) == BL_LILAC_RDD_WAN0_BRIDGE_PORT || (__port) == BL_LILAC_RDD_WAN1_BRIDGE_PORT )
typedef enum
{
    BL_LILAC_RDD_WAN0_BRIDGE_PORT           = 0, /* DSL WAN */
    BL_LILAC_RDD_WAN1_BRIDGE_PORT           = 1, /* ETH WAN */
    BL_LILAC_RDD_LAN0_BRIDGE_PORT           = 2,
    BL_LILAC_RDD_LAN1_BRIDGE_PORT           = 3,
    BL_LILAC_RDD_LAN2_BRIDGE_PORT           = 4,
    BL_LILAC_RDD_LAN3_BRIDGE_PORT           = 5,
    BL_LILAC_RDD_LAN4_BRIDGE_PORT           = 6,
    BL_LILAC_RDD_LAN5_BRIDGE_PORT           = 7,
    BL_LILAC_RDD_LAN6_BRIDGE_PORT           = 8,
    BL_LILAC_RDD_LAN7_BRIDGE_PORT           = 9,
    BL_LILAC_RDD_VIRTUAL_BRIDGE_PORT        = 10, /* Used to represent switch IMP Port */
    BL_LILAC_RDD_ANY_BRIDGE_PORT            = 11, /* matches any port, used by Speed Service */
    BL_LILAC_RDD_CPU_BRIDGE_PORT            = 12,
    BL_LILAC_RDD_PCI_BRIDGE_PORT            = 13, /* must match DRV_BPM_SP_SPARE_1 */
    /* In DSL RDP platforms (63138/63148/4908) 14 and 15 are used to extend BL_LILAC_RDD_PCI_BRIDGE_PORT */
    /* to indicate BL_LILAC_RDD_PCI_BRIDGE_PORT + radio_idx in the flow lookup key. */
    /* See _ucast_prepare_rdd_ip_flow_params in rdpa_ucast for more information. */
    BL_LILAC_RDD_MAPPING_MAX_BRIDGE_PORT    = 15,
    BL_LILAC_RDD_WAN_QUASI_BRIDGE_PORT      = 15,
    BL_LILAC_RDD_WAN_ROUTER_PORT            = 17,
    BL_LILAC_RDD_WAN_IPTV_BRIDGE_PORT       = 18,
    BL_LILAC_RDD_MULTICAST_LAN0_BRIDGE_PORT = 0x10,
    BL_LILAC_RDD_MULTICAST_LAN1_BRIDGE_PORT = 0x20,
    BL_LILAC_RDD_MULTICAST_LAN2_BRIDGE_PORT = 0x40,
    BL_LILAC_RDD_MULTICAST_LAN3_BRIDGE_PORT = 0x80,
    BL_LILAC_RDD_MULTICAST_LAN4_BRIDGE_PORT = 0x100,
    BL_LILAC_RDD_MULTICAST_PCI_BRIDGE_PORT  = 0x200,
}
BL_LILAC_RDD_BRIDGE_PORT_DTE;

#define BL_LILAC_RDD_WAN_BRIDGE_PORT BL_LILAC_RDD_WAN0_BRIDGE_PORT

typedef enum
{
    BL_LILAC_RDD_WAN_PHYSICAL_PORT_GPON = 0,
    BL_LILAC_RDD_WAN_PHYSICAL_PORT_ETH4 = 1,
    BL_LILAC_RDD_WAN_PHYSICAL_PORT_ETH5 = 2,
    BL_LILAC_RDD_WAN_PHYSICAL_PORT_ETH0 = 3,
    BL_LILAC_RDD_WAN_PHYSICAL_PORT_EPON = 4,
    BL_LILAC_RDD_WAN_PHYSICAL_PORT_DSL  = 5,
}
BL_LILAC_RDD_WAN_PHYSICAL_PORT_DTE;


#if defined(WL4908)
#define BL_LILAC_RDD_EMAC_ID_START RDD_EMAC_FIRST
#define BL_LILAC_RDD_EMAC_ID_PCI RDD_EMAC_ID_WIFI
#define BL_LILAC_RDD_EMAC_ID_0 RDD_EMAC_ID_0
#define BL_LILAC_RDD_EMAC_ID_1 RDD_EMAC_ID_1
#define BL_LILAC_RDD_EMAC_ID_2 RDD_EMAC_ID_2
#define BL_LILAC_RDD_EMAC_ID_3 RDD_EMAC_ID_3
#define BL_LILAC_RDD_EMAC_ID_4 RDD_EMAC_ID_4
#define BL_LILAC_RDD_EMAC_ID_5 RDD_EMAC_ID_5
#define BL_LILAC_RDD_EMAC_ID_6 RDD_EMAC_ID_6
#define BL_LILAC_RDD_EMAC_ID_7 RDD_EMAC_ID_7
#define BL_LILAC_RDD_EMAC_ID_COUNT RDD_EMAC_ID_COUNT
typedef rdd_rdd_emac  BL_LILAC_RDD_EMAC_ID_DTE;
#else
typedef enum
{
    BL_LILAC_RDD_EMAC_ID_START = 0,
    BL_LILAC_RDD_EMAC_ID_PCI  = 0,
    BL_LILAC_RDD_EMAC_ID_0    = 1,
    BL_LILAC_RDD_EMAC_ID_1    = 2,
    BL_LILAC_RDD_EMAC_ID_2    = 3,
    BL_LILAC_RDD_EMAC_ID_3    = 4,
    BL_LILAC_RDD_EMAC_ID_4    = 5,
#if defined(DSL_63138) || defined(DSL_63148)
    BL_LILAC_RDD_EMAC_ID_5   = 6,
    BL_LILAC_RDD_EMAC_ID_6   = 7,
    BL_LILAC_RDD_EMAC_ID_7   = 8,
#endif
    BL_LILAC_RDD_EMAC_ID_COUNT   ,
}
BL_LILAC_RDD_EMAC_ID_DTE;
#endif

#define RDD_WAN0_VPORT       RDD_VPORT_ID_0
#define RDD_LAN0_VPORT       RDD_VPORT_ID_1
#define RDD_LAN1_VPORT       RDD_VPORT_ID_2
#define RDD_LAN2_VPORT       RDD_VPORT_ID_3
#define RDD_LAN3_VPORT       RDD_VPORT_ID_4
#define RDD_LAN4_VPORT       RDD_VPORT_ID_5
#define RDD_LAN5_VPORT       RDD_VPORT_ID_6
#define RDD_LAN6_VPORT       RDD_VPORT_ID_7
#if !defined(WL4908)
#define RDD_LAN_VPORT_LAST   RDD_LAN6_VPORT
#endif
#define RDD_WLAN0_VPORT      RDD_VPORT_ID_8

typedef rdd_rdd_emac rdd_emac_id_t;

typedef uint32_t rdd_emac_id_vector_t;

static inline rdd_emac_id_vector_t rdd_emac_id_to_vector(rdd_emac_id_t emac, bdmf_boolean is_iptv)
{
    return 1LL << emac;
}
#define RDD_EMAC_PORT_TO_VECTOR(rdd_emac_id, is_iptv) rdd_emac_id_to_vector(rdd_emac_id, is_iptv)

typedef enum
{
    RDD_WAN_CHANNEL_UNASSIGNED = -1,
    RDD_WAN_CHANNEL_0  = 0,
    RDD_WAN_CHANNEL_1  = 1,
    RDD_WAN_CHANNEL_2  = 2,
    RDD_WAN_CHANNEL_3  = 3,
    RDD_WAN_CHANNEL_4  = 4,
    RDD_WAN_CHANNEL_5  = 5,
    RDD_WAN_CHANNEL_6  = 6,
    RDD_WAN_CHANNEL_7  = 7,
    RDD_WAN_CHANNEL_8  = 8,
    RDD_WAN_CHANNEL_9  = 9,
    RDD_WAN_CHANNEL_10 = 10,
    RDD_WAN_CHANNEL_11 = 11,
    RDD_WAN_CHANNEL_12 = 12,
    RDD_WAN_CHANNEL_13 = 13,
    RDD_WAN_CHANNEL_14 = 14,
    RDD_WAN_CHANNEL_15 = 15,
    RDD_WAN_CHANNEL_16 = 16,
    RDD_WAN_CHANNEL_17 = 17,
    RDD_WAN_CHANNEL_18 = 18,
    RDD_WAN_CHANNEL_19 = 19,
    RDD_WAN_CHANNEL_20 = 20,
    RDD_WAN_CHANNEL_21 = 21,
    RDD_WAN_CHANNEL_22 = 22,
    RDD_WAN_CHANNEL_23 = 23,
    RDD_WAN_CHANNEL_24 = 24,
    RDD_WAN_CHANNEL_25 = 25,
    RDD_WAN_CHANNEL_26 = 26,
    RDD_WAN_CHANNEL_27 = 27,
    RDD_WAN_CHANNEL_28 = 28,
    RDD_WAN_CHANNEL_29 = 29,
    RDD_WAN_CHANNEL_30 = 30,
    RDD_WAN_CHANNEL_31 = 31,
    RDD_WAN_CHANNEL_32 = 32,
    RDD_WAN_CHANNEL_33 = 33,
    RDD_WAN_CHANNEL_34 = 34,
    RDD_WAN_CHANNEL_35 = 35,
    RDD_WAN_CHANNEL_36 = 36,
    RDD_WAN_CHANNEL_37 = 37,
    RDD_WAN_CHANNEL_38 = 38,
    RDD_WAN_CHANNEL_39 = 39,
}
RDD_WAN_CHANNEL_ID;

#define RDD_WAN0_CHANNEL_BASE               RDD_WAN_CHANNEL_1
#define RDD_WAN1_CHANNEL_BASE               RDD_WAN_CHANNEL_0

typedef enum
{
    BL_LILAC_RDD_RATE_CONTROLLER_UNASSIGNED = -1,
    BL_LILAC_RDD_RATE_CONTROLLER_0  = 0,
    BL_LILAC_RDD_RATE_CONTROLLER_1  = 1,
    BL_LILAC_RDD_RATE_CONTROLLER_2  = 2,
    BL_LILAC_RDD_RATE_CONTROLLER_3  = 3,
    BL_LILAC_RDD_RATE_CONTROLLER_4  = 4,
    BL_LILAC_RDD_RATE_CONTROLLER_5  = 5,
    BL_LILAC_RDD_RATE_CONTROLLER_6  = 6,
    BL_LILAC_RDD_RATE_CONTROLLER_7  = 7,
    BL_LILAC_RDD_RATE_CONTROLLER_8  = 8,
    BL_LILAC_RDD_RATE_CONTROLLER_9  = 9,
    BL_LILAC_RDD_RATE_CONTROLLER_10 = 10,
    BL_LILAC_RDD_RATE_CONTROLLER_11 = 11,
    BL_LILAC_RDD_RATE_CONTROLLER_12 = 12,
    BL_LILAC_RDD_RATE_CONTROLLER_13 = 13,
    BL_LILAC_RDD_RATE_CONTROLLER_14 = 14,
    BL_LILAC_RDD_RATE_CONTROLLER_15 = 15,
    BL_LILAC_RDD_RATE_CONTROLLER_16 = 16,
    BL_LILAC_RDD_RATE_CONTROLLER_17 = 17,
    BL_LILAC_RDD_RATE_CONTROLLER_18 = 18,
    BL_LILAC_RDD_RATE_CONTROLLER_19 = 19,
    BL_LILAC_RDD_RATE_CONTROLLER_20 = 20,
    BL_LILAC_RDD_RATE_CONTROLLER_21 = 21,
    BL_LILAC_RDD_RATE_CONTROLLER_22 = 22,
    BL_LILAC_RDD_RATE_CONTROLLER_23 = 23,
    BL_LILAC_RDD_RATE_CONTROLLER_24 = 24,
    BL_LILAC_RDD_RATE_CONTROLLER_25 = 25,
    BL_LILAC_RDD_RATE_CONTROLLER_26 = 26,
    BL_LILAC_RDD_RATE_CONTROLLER_27 = 27,
    BL_LILAC_RDD_RATE_CONTROLLER_28 = 28,
    BL_LILAC_RDD_RATE_CONTROLLER_29 = 29,
    BL_LILAC_RDD_RATE_CONTROLLER_30 = 30,
    BL_LILAC_RDD_RATE_CONTROLLER_31 = 31,
    BL_LILAC_RDD_RATE_CONTROLLER_32 = 32,
    BL_LILAC_RDD_RATE_CONTROLLER_33 = 33,
    BL_LILAC_RDD_RATE_CONTROLLER_34 = 34,
    BL_LILAC_RDD_RATE_CONTROLLER_35 = 35,
    BL_LILAC_RDD_RATE_CONTROLLER_36 = 36,
    BL_LILAC_RDD_RATE_CONTROLLER_37 = 37,
    BL_LILAC_RDD_RATE_CONTROLLER_38 = 38,
    BL_LILAC_RDD_RATE_CONTROLLER_39 = 39,
    BL_LILAC_RDD_RATE_CONTROLLER_40 = 40,
    BL_LILAC_RDD_RATE_CONTROLLER_41 = 41,
    BL_LILAC_RDD_RATE_CONTROLLER_42 = 42,
    BL_LILAC_RDD_RATE_CONTROLLER_43 = 43,
    BL_LILAC_RDD_RATE_CONTROLLER_44 = 44,
    BL_LILAC_RDD_RATE_CONTROLLER_45 = 45,
    BL_LILAC_RDD_RATE_CONTROLLER_46 = 46,
    BL_LILAC_RDD_RATE_CONTROLLER_47 = 47,
    BL_LILAC_RDD_RATE_CONTROLLER_48 = 48,
    BL_LILAC_RDD_RATE_CONTROLLER_49 = 49,
    BL_LILAC_RDD_RATE_CONTROLLER_50 = 50,
    BL_LILAC_RDD_RATE_CONTROLLER_51 = 51,
    BL_LILAC_RDD_RATE_CONTROLLER_52 = 52,
    BL_LILAC_RDD_RATE_CONTROLLER_53 = 53,
    BL_LILAC_RDD_RATE_CONTROLLER_54 = 54,
    BL_LILAC_RDD_RATE_CONTROLLER_55 = 55,
    BL_LILAC_RDD_RATE_CONTROLLER_56 = 56,
    BL_LILAC_RDD_RATE_CONTROLLER_57 = 57,
    BL_LILAC_RDD_RATE_CONTROLLER_58 = 58,
    BL_LILAC_RDD_RATE_CONTROLLER_59 = 59,
    BL_LILAC_RDD_RATE_CONTROLLER_60 = 60,
    BL_LILAC_RDD_RATE_CONTROLLER_61 = 61,
    BL_LILAC_RDD_RATE_CONTROLLER_62 = 62,
    BL_LILAC_RDD_RATE_CONTROLLER_63 = 63,
    BL_LILAC_RDD_RATE_CONTROLLER_64 = 64,
    BL_LILAC_RDD_RATE_CONTROLLER_65 = 65,
    BL_LILAC_RDD_RATE_CONTROLLER_66 = 66,
    BL_LILAC_RDD_RATE_CONTROLLER_67 = 67,
    BL_LILAC_RDD_RATE_CONTROLLER_68 = 68,
    BL_LILAC_RDD_RATE_CONTROLLER_69 = 69,
    BL_LILAC_RDD_RATE_CONTROLLER_70 = 70,
    BL_LILAC_RDD_RATE_CONTROLLER_71 = 71,
    BL_LILAC_RDD_RATE_CONTROLLER_72 = 72,
    BL_LILAC_RDD_RATE_CONTROLLER_73 = 73,
    BL_LILAC_RDD_RATE_CONTROLLER_74 = 74,
    BL_LILAC_RDD_RATE_CONTROLLER_75 = 75,
    BL_LILAC_RDD_RATE_CONTROLLER_76 = 76,
    BL_LILAC_RDD_RATE_CONTROLLER_77 = 77,
    BL_LILAC_RDD_RATE_CONTROLLER_78 = 78,
    BL_LILAC_RDD_RATE_CONTROLLER_79 = 79,
    BL_LILAC_RDD_RATE_CONTROLLER_80 = 80,
    BL_LILAC_RDD_RATE_CONTROLLER_81 = 81,
    BL_LILAC_RDD_RATE_CONTROLLER_82 = 82,
    BL_LILAC_RDD_RATE_CONTROLLER_83 = 83,
    BL_LILAC_RDD_RATE_CONTROLLER_84 = 84,
    BL_LILAC_RDD_RATE_CONTROLLER_85 = 85,
    BL_LILAC_RDD_RATE_CONTROLLER_86 = 86,
    BL_LILAC_RDD_RATE_CONTROLLER_87 = 87,
    BL_LILAC_RDD_RATE_CONTROLLER_88 = 88,
    BL_LILAC_RDD_RATE_CONTROLLER_89 = 89,
    BL_LILAC_RDD_RATE_CONTROLLER_90 = 90,
    BL_LILAC_RDD_RATE_CONTROLLER_91 = 91,
    BL_LILAC_RDD_RATE_CONTROLLER_92 = 92,
    BL_LILAC_RDD_RATE_CONTROLLER_93 = 93,
    BL_LILAC_RDD_RATE_CONTROLLER_94 = 94,
    BL_LILAC_RDD_RATE_CONTROLLER_95 = 95,
    BL_LILAC_RDD_RATE_CONTROLLER_96 = 96,
    BL_LILAC_RDD_RATE_CONTROLLER_97 = 97,
    BL_LILAC_RDD_RATE_CONTROLLER_98 = 98,
    BL_LILAC_RDD_RATE_CONTROLLER_99 = 99,
    BL_LILAC_RDD_RATE_CONTROLLER_100 = 100,
    BL_LILAC_RDD_RATE_CONTROLLER_101 = 101,
    BL_LILAC_RDD_RATE_CONTROLLER_102 = 102,
    BL_LILAC_RDD_RATE_CONTROLLER_103 = 103,
    BL_LILAC_RDD_RATE_CONTROLLER_104 = 104,
    BL_LILAC_RDD_RATE_CONTROLLER_105 = 105,
    BL_LILAC_RDD_RATE_CONTROLLER_106 = 106,
    BL_LILAC_RDD_RATE_CONTROLLER_107 = 107,
    BL_LILAC_RDD_RATE_CONTROLLER_108 = 108,
    BL_LILAC_RDD_RATE_CONTROLLER_109 = 109,
    BL_LILAC_RDD_RATE_CONTROLLER_110 = 110,
    BL_LILAC_RDD_RATE_CONTROLLER_111 = 111,
    BL_LILAC_RDD_RATE_CONTROLLER_112 = 112,
    BL_LILAC_RDD_RATE_CONTROLLER_113 = 113,
    BL_LILAC_RDD_RATE_CONTROLLER_114 = 114,
    BL_LILAC_RDD_RATE_CONTROLLER_115 = 115,
    BL_LILAC_RDD_RATE_CONTROLLER_116 = 116,
    BL_LILAC_RDD_RATE_CONTROLLER_117 = 117,
    BL_LILAC_RDD_RATE_CONTROLLER_118 = 118,
    BL_LILAC_RDD_RATE_CONTROLLER_119 = 119,
    BL_LILAC_RDD_RATE_CONTROLLER_120 = 120,
    BL_LILAC_RDD_RATE_CONTROLLER_121 = 121,
    BL_LILAC_RDD_RATE_CONTROLLER_122 = 122,
    BL_LILAC_RDD_RATE_CONTROLLER_123 = 123,
    BL_LILAC_RDD_RATE_CONTROLLER_124 = 124,
    BL_LILAC_RDD_RATE_CONTROLLER_125 = 125,
    BL_LILAC_RDD_RATE_CONTROLLER_126 = 126,
    BL_LILAC_RDD_RATE_CONTROLLER_127 = 127,
}
BL_LILAC_RDD_RATE_CONTROLLER_ID_DTE;


typedef enum
{
    BL_LILAC_RDD_QUEUE_0 = 0,
    BL_LILAC_RDD_QUEUE_1 = 1,
    BL_LILAC_RDD_QUEUE_2 = 2,
    BL_LILAC_RDD_QUEUE_3 = 3,
    BL_LILAC_RDD_QUEUE_4 = 4,
    BL_LILAC_RDD_QUEUE_5 = 5,
    BL_LILAC_RDD_QUEUE_6 = 6,
    BL_LILAC_RDD_QUEUE_7 = 7,
    BL_LILAC_RDD_QUEUE_LAST = 7,
}
BL_LILAC_RDD_QUEUE_ID_DTE;


typedef enum
{
    RDD_WAN_CHANNEL_SCHEDULE_PRIORITY     = 0,
    RDD_WAN_CHANNEL_SCHEDULE_RATE_CONTROL = 1,
}
RDD_WAN_CHANNEL_SCHEDULE;


typedef enum
{
    BL_LILAC_RDD_CPU_RX_QUEUE_0 = 0,
    BL_LILAC_RDD_CPU_RX_QUEUE_1 = 1,
    BL_LILAC_RDD_CPU_RX_QUEUE_2 = 2,
    BL_LILAC_RDD_CPU_RX_QUEUE_3 = 3,
    BL_LILAC_RDD_CPU_RX_QUEUE_4 = 4,
    BL_LILAC_RDD_CPU_RX_QUEUE_5 = 5,
    BL_LILAC_RDD_CPU_RX_QUEUE_6 = 6,
    BL_LILAC_RDD_CPU_RX_QUEUE_7 = 7,
}
BL_LILAC_RDD_CPU_RX_QUEUE_DTE;


typedef enum
{
    BL_LILAC_RDD_PCI_TX_QUEUE_0 = 8,
    BL_LILAC_RDD_PCI_TX_QUEUE_1 = 9,
    BL_LILAC_RDD_PCI_TX_QUEUE_2 = 10,
    BL_LILAC_RDD_PCI_TX_QUEUE_3 = 11,
}
BL_LILAC_RDD_PCI_TX_QUEUE_DTE;


typedef enum
{
    BL_LILAC_RDD_CPU_METER_0       = 0,
    BL_LILAC_RDD_CPU_METER_1       = 1,
    BL_LILAC_RDD_CPU_METER_2       = 2,
    BL_LILAC_RDD_CPU_METER_3       = 3,
    BL_LILAC_RDD_CPU_METER_4       = 4,
    BL_LILAC_RDD_CPU_METER_5       = 5,
    BL_LILAC_RDD_CPU_METER_6       = 6,
    BL_LILAC_RDD_CPU_METER_7       = 7,
    BL_LILAC_RDD_CPU_METER_8       = 8,
    BL_LILAC_RDD_CPU_METER_9       = 9,
    BL_LILAC_RDD_CPU_METER_10      = 10,
    BL_LILAC_RDD_CPU_METER_11      = 11,
    BL_LILAC_RDD_CPU_METER_12      = 12,
    BL_LILAC_RDD_CPU_METER_13      = 13,
    BL_LILAC_RDD_CPU_METER_14      = 14,
    BL_LILAC_RDD_CPU_METER_15      = 15,
    BL_LILAC_RDD_CPU_METER_DISABLE = 16,
}
BL_LILAC_RDD_CPU_METER_DTE;


typedef enum
{
    BL_LILAC_RDD_STATIC_MAC_ADDRESS = 0,
    BL_LILAC_RDD_BRIDGE_MAC_ADDRESS = 1,
}
BL_LILAC_RDD_MAC_ENTRY_TYPE_DTE;


typedef enum
{
    BL_LILAC_RDD_DISABLED = 0,
    BL_LILAC_RDD_ENABLED  = 1,
}
BL_LILAC_RDD_CONTROL_DTE;


typedef enum
{
    BL_LILAC_RDD_PPPOE_DISABLED = 0,
    BL_LILAC_RDD_PPPOE_ENABLED  = 1,
}
BL_LILAC_RDD_PPPOE_ENABLE_DTE;


typedef enum
{
    BL_LILAC_RDD_DUAL_STACK_LITE_DISABLED = 0,
    BL_LILAC_RDD_DUAL_STACK_LITE_ENABLED  = 1,
}
BL_LILAC_RDD_DUAL_STACK_LITE_ENABLE_DTE;


typedef enum
{
    BL_LILAC_RDD_IPV6_DISABLED = 0,
    BL_LILAC_RDD_IPV6_ENABLED  = 1,
}
BL_LILAC_RDD_IPV6_ENABLE_DTE;


typedef enum
{
    BL_LILAC_RDD_FORWARD_DISABLE = 0,
    BL_LILAC_RDD_FORWARD_ENABLE  = 1,
}
BL_LILAC_RDD_FORWARD_MATRIX_DTE;


typedef enum
{
    BL_LILAC_RDD_VLAN_SWITCHING_DISABLE = 0,
    BL_LILAC_RDD_VLAN_SWITCHING_ENABLE  = 1,
}
BL_LILAC_RDD_VLAN_SWITCHING_CONFIG_DTE;


typedef enum
{
    BL_LILAC_RDD_VLAN_BINDING_DISABLE = 0,
    BL_LILAC_RDD_VLAN_BINDING_ENABLE  = 1,
}
BL_LILAC_RDD_VLAN_BINDING_CONFIG_DTE;


typedef enum
{
    BL_LILAC_RDD_AGGREGATION_MODE_DISABLED = 0,
    BL_LILAC_RDD_AGGREGATION_MODE_ENABLED  = 1,
}
BL_LILAC_RDD_AGGREGATION_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_BRIDGE_PORT_VECTOR_PCI  = 0x1,
    BL_LILAC_RDD_BRIDGE_PORT_VECTOR_LAN0 = 0x2,
    BL_LILAC_RDD_BRIDGE_PORT_VECTOR_LAN1 = 0x4,
    BL_LILAC_RDD_BRIDGE_PORT_VECTOR_LAN2 = 0x8,
    BL_LILAC_RDD_BRIDGE_PORT_VECTOR_LAN3 = 0x10,
    BL_LILAC_RDD_BRIDGE_PORT_VECTOR_LAN4 = 0x20,
}
BL_LILAC_RDD_BRIDGE_PORT_VECTOR_DTE;


typedef enum
{
    BL_LILAC_RDD_SUBNET_CLASSIFY_ETHERNET_FLOW = 0,
    BL_LILAC_RDD_SUBNET_CLASSIFY_MAC_FILTER    = 1,
}
BL_LILAC_RDD_SUBNET_CLASSIFY_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_SUBNET_FLOW_CACHE  = 0,
    BL_LILAC_RDD_SUBNET_BRIDGE      = 1,
    BL_LILAC_RDD_SUBNET_BRIDGE_IPTV = 2,
    BL_LILAC_RDD_SUBNET_LAN         = 2,
}
BL_LILAC_RDD_SUBNET_ID_DTE;


typedef enum
{
    BL_LILAC_RDD_DS_RATE_CONTROL_DISABLE = 0,
    BL_LILAC_RDD_DS_RATE_CONTROL_ENABLE  = 1,
}
BL_LILAC_RDD_DS_RATE_CONTROL_MODE_DTE;

typedef enum
{
    RDD_RATE_LIMITER_EMAC_0                 = 0,
    RDD_RATE_LIMITER_EMAC_1                 = 1,
    RDD_RATE_LIMITER_EMAC_2                 = 2,
    RDD_RATE_LIMITER_EMAC_3                 = 3,
    RDD_RATE_LIMITER_EMAC_4                 = 4,
    RDD_RATE_LIMITER_EMAC_5                 = 5,
    RDD_RATE_LIMITER_EMAC_LAST              = 5,
    RDD_RATE_LIMITER_SERVICE_QUEUE_0        = 6,
    RDD_RATE_LIMITER_SERVICE_QUEUE_1        = 7,
    RDD_RATE_LIMITER_SERVICE_QUEUE_2        = 8,
    RDD_RATE_LIMITER_SERVICE_QUEUE_3        = 9,
    RDD_RATE_LIMITER_SERVICE_QUEUE_4        = 10,
    RDD_RATE_LIMITER_SERVICE_QUEUE_5        = 11,
    RDD_RATE_LIMITER_SERVICE_QUEUE_6        = 12,
    RDD_RATE_LIMITER_SERVICE_QUEUE_7        = 13,
    RDD_RATE_LIMITER_SERVICE_QUEUE_OVERALL  = 14,
    RDD_RATE_LIMITER_IDLE                   = 15,
}
RDD_RATE_LIMITER_ID_DTE;

typedef enum
{
    BL_LILAC_RDD_POLICER_0        = 0,
    BL_LILAC_RDD_POLICER_1        = 1,
    BL_LILAC_RDD_POLICER_2        = 2,
    BL_LILAC_RDD_POLICER_3        = 3,
    BL_LILAC_RDD_POLICER_4        = 4,
    BL_LILAC_RDD_POLICER_5        = 5,
    BL_LILAC_RDD_POLICER_6        = 6,
    BL_LILAC_RDD_POLICER_7        = 7,
    BL_LILAC_RDD_POLICER_8        = 8,
    BL_LILAC_RDD_POLICER_9        = 9,
    BL_LILAC_RDD_POLICER_10       = 10,
    BL_LILAC_RDD_POLICER_11       = 11,
    BL_LILAC_RDD_POLICER_12       = 12,
    BL_LILAC_RDD_POLICER_13       = 13,
    BL_LILAC_RDD_POLICER_14       = 14,
    BL_LILAC_RDD_POLICER_15       = 15,
    BL_LILAC_RDD_POLICER_DISABLED = 16,
}
BL_LILAC_RDD_POLICER_ID_DTE;


#define BL_LILAC_RDD_IPV4_ADDRESS_BYTE_SIZE     ( 4 )
#define BL_LILAC_RDD_IPV6_ADDRESS_BYTE_SIZE     ( 16 )


typedef enum
{
    BL_LILAC_RDD_FILTER_DISABLE = 0,
    BL_LILAC_RDD_FILTER_ENABLE  = 1,
}
BL_LILAC_RDD_FILTER_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_RATE_LIMITER_DISABLE = 0,
    BL_LILAC_RDD_RATE_LIMITER_ENABLE  = 1,
}
BL_LILAC_RDD_RATE_LIMITER_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_RATE_LIMITER_LOW  = 0,
    BL_LILAC_RDD_RATE_LIMITER_HIGH = 1,
}
BL_LILAC_RDD_RATE_LIMITER_PRIORITY_DTE;


typedef enum
{
    BL_LILAC_RDD_FILTER_ACTION_CPU_TRAP = 1,
    BL_LILAC_RDD_FILTER_ACTION_DROP     = 2,
}
BL_LILAC_RDD_FILTER_ACTION_DTE;


typedef enum
{
    BL_LILAC_RDD_ETHER_TYPE_FILTER_USER_0      = 2,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_USER_1      = 3,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_USER_2      = 4,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_USER_3      = 5,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_PPPOE_D     = 6,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_PPPOE_S     = 7,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_ARP         = 8,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_1588        = 9,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_802_1X      = 10,
    BL_LILAC_RDD_ETHER_TYPE_FILTER_802_1AG_CFM = 11,
}
BL_LILAC_RDD_ETHER_TYPE_FILTER_NUMBER_DTE;


typedef enum
{
    BL_LILAC_RDD_MAC_LOOKUP_DISABLE = 0,
    BL_LILAC_RDD_MAC_LOOKUP_ENABLE  = 1,
}
BL_LILAC_RDD_MAC_LOOKUP_DTE;


typedef enum
{
    BL_LILAC_RDD_FLOW_BASED_FORWARDING_DISABLED = 0,
    BL_LILAC_RDD_FLOW_BASED_FORWARDING_ENABLED  = 1,
}
BL_LILAC_RDD_FLOW_BASED_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_MAC_FWD_ACTION_FORWARD    = 0,
    BL_LILAC_RDD_MAC_FWD_ACTION_DROP       = 1,
    BL_LILAC_RDD_MAC_FWD_ACTION_CPU_TRAP0  = 2,
    BL_LILAC_RDD_MAC_FWD_ACTION_CPU_TRAP1  = 3,
    BL_LILAC_RDD_MAC_FWD_ACTION_CPU_TRAP2  = 4,
    BL_LILAC_RDD_MAC_FWD_ACTION_CPU_TRAP3  = 5,
    BL_LILAC_RDD_MAC_FWD_ACTION_RATE_LIMIT = 6,
}
BL_LILAC_RDD_MAC_FWD_ACTION_DTE;


typedef enum
{
    BL_LILAC_RDD_ACL_LAYER3_FILTER_DISABLE                      = 0,
    BL_LILAC_RDD_ACL_LAYER3_FILTER_SRC_IP_INCLUSIVE             = 2,
    BL_LILAC_RDD_ACL_LAYER3_FILTER_SRC_IP_EXCLUSIVE             = 3,
    BL_LILAC_RDD_ACL_LAYER3_FILTER_SRC_MAC_SRC_IP_INCLUSIVE     = 4,
    BL_LILAC_RDD_ACL_LAYER3_FILTER_SRC_MAC_SRC_IP_EXCLUSIVE     = 5,
    BL_LILAC_RDD_ACL_LAYER3_FILTER_SRC_MAC_VID_SRC_IP_INCLUSIVE = 8,
    BL_LILAC_RDD_ACL_LAYER3_FILTER_SRC_MAC_VID_SRC_IP_EXCLUSIVE = 9,
}
BL_LILAC_RDD_ACL_LAYER3_FILTER_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_CRC_CALC_DISABLE = 0,
    BL_LILAC_RDD_CRC_CALC_ENABLE  = 1,
}
BL_LILAC_RDD_TX_CRC_CALC_DTE;


typedef enum
{
    rdd_vlan_command_transparent                         = 0,
    rdd_vlan_command_add_tag                             = 1,
    rdd_vlan_command_remove_tag                          = 2,
    rdd_vlan_command_replace_tag                         = 3,
    rdd_vlan_command_add_two_tags                        = 4,
    rdd_vlan_command_remove_two_tags                     = 5,
    rdd_vlan_command_add_outer_tag_replace_inner_tag     = 6,
    rdd_vlan_command_remove_outer_tag_replace_inner_tag  = 7,
    rdd_vlan_command_add_tag_always                      = 8,
    rdd_vlan_command_remove_tag_always                   = 9,
    rdd_vlan_command_replace_outer_tag_replace_inner_tag = 10,
    rdd_vlan_command_remove_outer_tag_copy               = 11,
    rdd_vlan_command_add_3rd_tag                         = 12,
    rdd_max_vlan_command                                 = 13,
}
rdd_bridge_vlan_command;


typedef enum
{
    rdd_pbits_command_transparent = 0,
    rdd_pbits_command_copy        = 1,
    rdd_pbits_command_configured  = 2,
    rdd_pbits_command_remap       = 3,
    rdd_max_pbits_command         = 4,
}
rdd_bridge_pbits_command;


typedef enum
{
    rdd_tpid_id_0   = 0,
    rdd_tpid_id_1   = 1,
    rdd_tpid_id_2   = 2,
    rdd_tpid_id_3   = 3,
    rdd_tpid_id_4   = 4,
    rdd_tpid_id_5   = 5,
    rdd_tpid_id_6   = 6,
    rdd_tpid_id_7   = 7,
}
rdd_tpid_id;


typedef enum
{
    BL_LILAC_RDD_UNKNOWN_MAC_CMD_FORWARD  = 1,
    BL_LILAC_RDD_UNKNOWN_MAC_CMD_CPU_TRAP = 2,
    BL_LILAC_RDD_UNKNOWN_MAC_CMD_DROP     = 4,
    BL_LILAC_RDD_UNKNOWN_MAC_CMD_FLOOD    = 8,
}
BL_LILAC_RDD_UNKNOWN_MAC_COMMAND_DTE;


typedef enum
{
    BL_LILAC_RDD_MAC_TABLE_SIZE_32   = 0,
    BL_LILAC_RDD_MAC_TABLE_SIZE_64   = 1,
    BL_LILAC_RDD_MAC_TABLE_SIZE_128  = 2,
    BL_LILAC_RDD_MAC_TABLE_SIZE_256  = 3,
    BL_LILAC_RDD_MAC_TABLE_SIZE_512  = 4,
    BL_LILAC_RDD_MAC_TABLE_SIZE_1024 = 5,
    BL_LILAC_RDD_MAC_TABLE_SIZE_2048 = 6,
    BL_LILAC_RDD_MAC_TABLE_SIZE_4096 = 7,
}
BL_LILAC_RDD_MAC_TABLE_SIZE_DTE;


typedef enum
{
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_1    = 0,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_2    = 1,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_4    = 2,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_8    = 3,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_16   = 4,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_32   = 5,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_64   = 6,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_128  = 7,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_256  = 8,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_512  = 9,
    BL_LILAC_RDD_MAC_TABLE_MAX_HOP_1024 = 10,
}
BL_LILAC_RDD_MAC_TABLE_MAX_HOP_DTE;


typedef enum
{
    BL_LILAC_RDD_IGMP_FILTER_NUMBER        = 0,
    BL_LILAC_RDD_ICMPV6_FILTER_NUMBER      = 1,
    BL_LILAC_RDD_USER_0_FILTER_NUMBER      = 2,
    BL_LILAC_RDD_USER_1_FILTER_NUMBER      = 3,
    BL_LILAC_RDD_USER_2_FILTER_NUMBER      = 4,
    BL_LILAC_RDD_USER_3_FILTER_NUMBER      = 5,
    BL_LILAC_RDD_PPPOE_D_FILTER_NUMBER     = 6,
    BL_LILAC_RDD_PPPOE_S_FILTER_NUMBER     = 7,
    BL_LILAC_RDD_ARP_FILTER_NUMBER         = 8,
    BL_LILAC_RDD_1588_FILTER_NUMBER        = 9,
    BL_LILAC_RDD_802_1X_FILTER_NUMBER      = 10,
    BL_LILAC_RDD_802_1AG_CFM_FILTER_NUMBER = 11,
    BL_LILAC_RDD_BROADCAST_FILTER_NUMBER   = 12,
    BL_LILAC_RDD_MULTICAST_FILTER_NUMBER   = 13,
    BL_LILAC_RDD_STOP_FILTER_NUMBER        = 14,
    BL_LILAC_RDD_INGRESS_FILTERS_NUMBER    = 14,
}
BL_LILAC_RDD_INGRESS_FILTER_DTE;


typedef enum
{
    RDD_LAYER4_FILTER_ERROR             = 0,
    RDD_LAYER4_FILTER_EXCEPTION         = 1,
    RDD_LAYER4_FILTER_IP_FIRST_FRAGMENT = 2,
    RDD_LAYER4_FILTER_IP_FRAGMENT       = 3,
    RDD_LAYER4_FILTER_GRE               = 4,
    RDD_LAYER4_FILTER_LAYER3_IPV4       = 5,
    RDD_LAYER4_FILTER_LAYER3_IPV6       = 6,
    RDD_LAYER4_FILTER_ICMP              = 7,
    RDD_LAYER4_FILTER_ESP               = 8,
    RDD_LAYER4_FILTER_AH                = 9,
    RDD_LAYER4_FILTER_IPV6              = 10,
    RDD_LAYER4_FILTER_USER_DEFINED_0    = 11,
    RDD_LAYER4_FILTER_USER_DEFINED_1    = 12,
    RDD_LAYER4_FILTER_USER_DEFINED_2    = 13,
    RDD_LAYER4_FILTER_USER_DEFINED_3    = 14,
    RDD_LAYER4_FILTER_UNKNOWN           = 15,
}
RDD_LAYER4_FILTER_INDEX;


typedef enum
{
    BL_LILAC_RDD_LAYER4_FILTER_FORWARD  = 0,
    BL_LILAC_RDD_LAYER4_FILTER_CPU_TRAP = 1,
    BL_LILAC_RDD_LAYER4_FILTER_DROP     = 2,
}
BL_LILAC_RDD_LAYER4_FILTER_ACTION_DTE;


typedef enum
{
    BL_LILAC_RDD_FIREWALL_PROTOCOL_TYPE_TCP = 0,
    BL_LILAC_RDD_FIREWALL_PROTOCOL_TYPE_UDP = 1,
}
BL_LILAC_RDD_FIREWALL_PROTOCOL_TYPE_DTE;


typedef enum
{
    BL_LILAC_RDD_FLOW_CACHE_PBIT_ACTION_DSCP_COPY  = 0,
    BL_LILAC_RDD_FLOW_CACHE_PBIT_ACTION_OUTER_COPY = 1,
    BL_LILAC_RDD_FLOW_CACHE_PBIT_ACTION_INNER_COPY = 2,
}
BL_LILAC_RDD_FLOW_CACHE_PBIT_ACTION_DTE;


typedef enum
{
    RDD_FLOW_CACHE_FORWARD_ACTION_CPU  = 0,
    RDD_FLOW_CACHE_FORWARD_ACTION_DROP = 1,
}
RDD_FLOW_CACHE_FORWARD_ACTION;


typedef enum
{
    BL_LILAC_RDD_ACL_LAYER2_ACTION_DENY   = 0,
    BL_LILAC_RDD_ACL_LAYER2_ACTION_ACCEPT = 1,
}
BL_LILAC_RDD_ACL_LAYER2_ACTION_DTE;


typedef enum
{
    BL_LILAC_RDD_1588_MODE_DISABLE = 0,
    BL_LILAC_RDD_1588_MODE_ENABLE  = 1,
}
BL_LILAC_RDD_1588_MODE_DTE;


typedef enum
{
    RDD_1588_TX_THREAD_RETURN_NO_RESULT = 0,
    RDD_1588_TX_THREAD_RETURN_SUCCESS   = 1,
    RDD_1588_TX_THREAD_RETURN_FAIL      = 2,
}
RDD_1588_TX_THREAD_RESULT_DTE;


typedef enum
{
    BL_LILAC_RDD_INTER_LAN_SCHEDULING_MODE_NORMAL          = 0,
    BL_LILAC_RDD_INTER_LAN_SCHEDULING_MODE_STRICT_PRIORITY = 1,
    BL_LILAC_RDD_INTER_LAN_SCHEDULING_MODE_ROUND_ROBIN     = 2,
}
BL_LILAC_RDD_INTER_LAN_SCHEDULING_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_UPSTREAM_PADDING_DISABLE = 0,
    BL_LILAC_RDD_UPSTREAM_PADDING_ENABLE  = 1,
}
BL_LILAC_RDD_UPSTREAM_PADDING_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_NO_WAIT = 0,
    BL_LILAC_RDD_WAIT    = 1,
}
BL_LILAC_RDD_CPU_WAIT_DTE;


typedef enum
{
    RDD_US_PEAK_SCHEDULING_MODE_ROUND_ROBIN     = 0,
    RDD_US_PEAK_SCHEDULING_MODE_STRICT_PRIORITY = 1,
}
RDD_US_PEAK_SCHEDULING_MODE;


typedef enum
{
    rdd_queue_profile_0         = 0,
    rdd_queue_profile_1         = 1,
    rdd_queue_profile_2         = 2,
    rdd_queue_profile_3         = 3,
    rdd_queue_profile_4         = 4,
    rdd_queue_profile_5         = 5,
    rdd_queue_profile_6         = 6,
    rdd_queue_profile_7         = 7,
    rdd_queue_profile_disabled  = 8,
} rdd_queue_profile;


typedef struct
{
    uint16_t  min_threshold;
    uint16_t  max_threshold;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_PRIORITY_CLASS_THRESHOLDS;


typedef struct
{
    RDD_PRIORITY_CLASS_THRESHOLDS  high_priority_class;
    RDD_PRIORITY_CLASS_THRESHOLDS  low_priority_class;
    uint32_t                       max_drop_probability;
    bdmf_boolean                   us_flow_control_mode;                         

}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_QUEUE_PROFILE;


typedef enum
{
    BL_LILAC_RDD_FLOW_PM_COUNTERS_RX   = 1,
    BL_LILAC_RDD_FLOW_PM_COUNTERS_TX   = 2,
    BL_LILAC_RDD_FLOW_PM_COUNTERS_BOTH = 3,
}
BL_LILAC_RDD_FLOW_PM_COUNTERS_TYPE_DTE;


typedef struct
{
    uint32_t  good_rx_packet;
    uint32_t  good_rx_bytes;
    uint32_t  good_tx_packet;
    uint32_t  good_tx_bytes;
    uint16_t  error_rx_packets_discard;
    uint16_t  error_tx_packets_discard;
}
__PACKING_ATTRIBUTE_STRUCT_END__ BL_LILAC_RDD_FLOW_PM_COUNTERS_DTE;


typedef struct
{
    uint32_t  good_tx_packet;
    uint16_t  error_tx_packets_discard;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_SERVICE_QUEUE_PM_COUNTERS_DTE;


typedef struct
{
    uint32_t  rx_valid;
    uint32_t  tx_valid;
    uint16_t  error_rx_bpm_congestion;
    uint16_t  bridge_filtered_packets;
    uint16_t  bridge_tx_packets_discard;
}
__PACKING_ATTRIBUTE_STRUCT_END__ BL_LILAC_RDD_BRIDGE_PORT_PM_COUNTERS_DTE;


typedef struct
{
    uint32_t  good_rx_packet;
    uint32_t  good_tx_packet;
    uint32_t  good_rx_bytes;
    uint32_t  good_tx_bytes;
    uint16_t  rx_dropped_packet;
    uint16_t  tx_dropped_packet;
}
__PACKING_ATTRIBUTE_STRUCT_END__ BL_LILAC_RDD_SUBNET_PM_COUNTERS_DTE;


typedef struct
{
    uint16_t  invalid_layer2_protocol_drop;
    uint16_t  firewall_drop;
    uint16_t  acl_oui_drop;
    uint16_t  acl_l2_drop;
    uint16_t  acl_l3_drop;
    uint16_t  dst_mac_non_router_drop;
    uint16_t  eth_flow_action_drop;
    uint16_t  sa_lookup_failure_drop;
    uint16_t  da_lookup_failure_drop;
    uint16_t  sa_action_drop;
    uint16_t  da_action_drop;
    uint16_t  forwarding_matrix_disabled_drop;
    uint16_t  connection_action_drop;
    uint16_t  iptv_layer3_drop;
    uint16_t  local_switching_congestion;
    uint16_t  vlan_switching_drop;
    uint16_t  downstream_policers_drop;
    uint16_t  layer4_filters_drop[ 16 ];
    uint16_t  ingress_filters_drop[ BL_LILAC_RDD_INGRESS_FILTERS_NUMBER ];
    uint16_t  ip_validation_filter_drop[ 2 ];
    uint16_t  emac_loopback_drop;
    uint16_t  tpid_detect_drop;
    uint16_t  dual_stack_lite_congestion_drop;
    uint16_t  invalid_subnet_ip_drop;
    uint16_t  us_ddr_queue_drop;
    uint16_t  ds_parallel_processing_no_avialable_slave;
    uint16_t  ds_parallel_processing_reorder_slaves;
    uint16_t  absolute_address_list_overflow_drop;
}
__PACKING_ATTRIBUTE_STRUCT_END__ BL_LILAC_RDD_VARIOUS_COUNTERS_DTE;


typedef enum
{
    INVALID_LAYER2_PROTOCOL_DROP_COUNTER_MASK    = 0x1,
    FIREWALL_DROP_COUNTER_MASK                   = 0x2,
    ACL_OUI_DROP_COUNTER_MASK                    = 0x4,
    ACL_L2_DROP_COUNTER_MASK                     = 0x8,
    ACL_L3_DROP_COUNTER_MASK                     = 0x10,
    DST_MAC_NON_ROUTER_DROP_COUNTER_MASK         = 0x20,
    ETHERNET_FLOW_ACTION_DROP_COUNTER_MASK       = 0x40,
    SA_LOOKUP_FAILURE_DROP_COUNTER_MASK          = 0x80,
    DA_LOOKUP_FAILURE_DROP_COUNTER_MASK          = 0x100,
    SA_ACTION_DROP_COUNTER_MASK                  = 0x200,
    DA_ACTION_DROP_COUNTER_MASK                  = 0x400,
    FORWARDING_MATRIX_DISABLED_DROP_COUNTER_MASK = 0x800,
    CONNECTION_ACTION_DROP_COUNTER_MASK          = 0x1000,
    IPTV_LAYER3_DROP_COUNTER_MASK                = 0x2000,
    LOCAL_SWITCHING_CONGESTION_COUNTER_MASK      = 0x4000,
    VLAN_SWITCHING_DROP_COUNTER_MASK             = 0x8000,
    DOWNSTREAM_POLICERS_DROP_COUNTER_MASK        = 0x10000,
    LAYER4_FILTERS_DROP_COUNTER_MASK             = 0x20000,
    INGRESS_FILTERS_DROP_COUNTER_MASK            = 0x40000,
    IP_VALIDATION_FILTER_DROP_COUNTER_MASK       = 0x80000,
    EMAC_LOOPBACK_DROP_COUNTER_MASK              = 0x100000,
    TPID_DETECT_DROP_COUNTER_MASK                = 0x200000,
    DUAL_STACK_LITE_CONGESTION_DROP_COUNTER_MASK = 0x400000,
    INVALID_SUBNET_IP_DROP_COUNTER_MASK          = 0x800000,
    EPON_DDR_QUEUEU_DROP_COUNTER_MASK            = 0x800000,
    ABSOLUTE_ADDRESS_LIST_OVERFLOW_MASK          = 0x1000000,
}
RDD_VARIOUS_COUNTERS_MASK;

typedef enum
{
    RDD_CHIP_REVISION_A0 = 0,
    RDD_CHIP_REVISION_B0 = 1,
}
BL_LILAC_RDD_CHIP_REVISION_DTE;

#if defined(WL4908)
typedef struct
{
    uint8_t                             *ddr_bm_ptr;
    uint32_t                            ddr_bm_phys;
    uint32_t                            ddr1_bm_phys;
    uint8_t                             *ddr_fm_ptr;
    uint32_t                            ddr_fm_phys;
    BL_LILAC_RDD_MAC_TABLE_SIZE_DTE     mac_table_size;
    BL_LILAC_RDD_MAC_TABLE_SIZE_DTE     iptv_table_size;
    BL_LILAC_RDD_WAN_PHYSICAL_PORT_DTE  wan_physical_port;
    uint32_t                            ddr_headroom_size;
    int16_t                             broadcom_switch_mode;
    BL_LILAC_RDD_BRIDGE_PORT_DTE        broadcom_switch_physical_port;
    uint32_t                            bridge_flow_cache_mode;
    BL_LILAC_RDD_CHIP_REVISION_DTE      chip_revision;
    uint16_t                            cpu_tx_abs_packet_limit;
    uint8_t                             *runner_nat_cache_key_ptr; /*Virtual address*/
    uint8_t                             *runner_nat_cache_context_ptr; /*Virtual address*/
    uint8_t                             *runner_context_cont_ptr; /*Virtual address*/
    uint16_t                            token_size;
    uint8_t                             lp_mode;
}
RDD_INIT_PARAMS;
#else
typedef struct
{
    uint8_t                             *ddr_pool_ptr;       /* virtual address */
    uint32_t                            ddr_pool_ptr_phys;   /* physical address */
    uint8_t                             *extra_ddr_pool_ptr; /* virtual address */
    uint32_t                            extra_ddr_pool_ptr_phys; /* physical address */
    uint8_t                             *ddr_runner_tables_ptr;  /* virtual address */
    uint32_t                            ddr_runner_tables_ptr_phys; /* physical address */
    BL_LILAC_RDD_MAC_TABLE_SIZE_DTE     mac_table_size;
    BL_LILAC_RDD_MAC_TABLE_SIZE_DTE     iptv_table_size;
    BL_LILAC_RDD_WAN_PHYSICAL_PORT_DTE  wan_physical_port;
    uint32_t                            ddr_headroom_size;
    int16_t                             broadcom_switch_mode;
    BL_LILAC_RDD_BRIDGE_PORT_DTE        broadcom_switch_physical_port;
    uint32_t                            bridge_flow_cache_mode;
    uint16_t                            epon_post_scheduling_queue_size;
    BL_LILAC_RDD_CHIP_REVISION_DTE      chip_revision;
    uint16_t                            cpu_tx_abs_packet_limit;
    BL_LILAC_RDD_BRIDGE_PORT_DTE        lan_direct_to_cpu_port;
    uint8_t                             lp_mode;
}
RDD_INIT_PARAMS;
#endif


typedef struct
{
    uint32_t  rate;
    uint32_t  limit;
}
RDD_RATE_LIMIT_PARAMS;

typedef struct
{
    uint32_t               sustain_budget;
    RDD_RATE_LIMIT_PARAMS  peak_budget;
    uint32_t               peak_weight;
}
RDD_RATE_CONTROLLER_PARAMS;


typedef struct
{
    BL_LILAC_RDD_SUBNET_ID_DTE               subnet_id;
    BL_LILAC_RDD_FIREWALL_PROTOCOL_TYPE_DTE  protocol;
    uint32_t                                 dst_port;
    uint32_t                                 dst_port_last;
    bdmf_ip_t                                src_ip;
    uint32_t                                 src_ip_mask;
    bdmf_ip_t                                dst_ip;
    uint32_t                                 check_mask_src_ip;
    uint32_t                                 check_src_ip;
    uint32_t                                 check_dst_ip;
    uint32_t                                 next_rule_index;
}
RDD_FIREWALL_RULE_PARAMS;


typedef struct
{
    bdmf_mac_t                         mac_addr;
    uint16_t                           vlan_id;
    BL_LILAC_RDD_BRIDGE_PORT_DTE       bridge_port;
    BL_LILAC_RDD_MAC_ENTRY_TYPE_DTE    entry_type;
    BL_LILAC_RDD_AGGREGATION_MODE_DTE  aggregation_mode;
    uint8_t                            extension_entry;
    BL_LILAC_RDD_MAC_FWD_ACTION_DTE    sa_action;
    BL_LILAC_RDD_MAC_FWD_ACTION_DTE    da_action;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_MAC_PARAMS;


typedef struct
{
    uint16_t                             vid;
    BL_LILAC_RDD_BRIDGE_PORT_VECTOR_DTE  isolation_mode_port_vector;
    BL_LILAC_RDD_BRIDGE_PORT_VECTOR_DTE  aggregation_mode_port_vector;
    uint16_t                             aggregation_vid_index;
}
__PACKING_ATTRIBUTE_STRUCT_END__ RDD_LAN_VID_PARAMS;


typedef struct
{
    uint8_t                       *packet_ptr;
    uint32_t                      packet_size;
    BL_LILAC_RDD_BRIDGE_PORT_DTE  src_bridge_port;
    uint8_t                       wifi_src_ssid_index;
    uint16_t                      wifi_dst_ssid_vector;
    uint16_t                      buffer_number;
}
RDD_PCI_TX_PARAMS;


typedef struct
{
    uint8_t                         *packet_ptr;
    uint32_t                        packet_size;
    BL_LILAC_RDD_BRIDGE_PORT_DTE    src_bridge_port;
    uint32_t                        flow_id;
    rdpa_cpu_reason                 reason;
    uint16_t                        buffer_number;
}
RDD_CPU_RX_PARAMS;


typedef enum
{
    BL_LILAC_RDD_UPSTREAM_FLOW_CLASSIFY_VID                = 0,
    BL_LILAC_RDD_UPSTREAM_FLOW_CLASSIFY_VID_PBITS          = 0,
    BL_LILAC_RDD_UPSTREAM_FLOW_CLASSIFY_VID_SRC_PORT       = 1,
    BL_LILAC_RDD_UPSTREAM_FLOW_CLASSIFY_VID_PBITS_SRC_PORT = 2,
}
BL_LILAC_RDD_UPSTREAM_FLOW_CLASSIFY_MODE_DTE;


typedef enum
{
    BL_LILAC_RDD_DOWNSTREAM_FLOW_CLASSIFY_WAN_FLOW = 0,
    BL_LILAC_RDD_DOWNSTREAM_FLOW_CLASSIFY_PACKET   = 1,
}
BL_LILAC_RDD_DOWNSTREAM_FLOW_CLASSIFY_MODE_DTE;

typedef struct
{
	uint32_t                                vlan_command_id;
    rdd_bridge_vlan_command                 vlan_command;
    rdd_bridge_pbits_command                pbits_command;
    uint16_t                                outer_vid;
    uint16_t                                inner_vid;
    uint8_t                                 outer_pbits;
    uint8_t                                 inner_pbits;
	bdmf_boolean                            outer_tpid_overwrite_enable;
	bdmf_boolean                            inner_tpid_overwrite_enable;
    rdd_tpid_id                             outer_tpid_id; 
    rdd_tpid_id                             inner_tpid_id; 
}
rdd_vlan_command_params;

typedef enum
{
    rdd_dei_command_transparent                         = 0,
    rdd_dei_command_clear                               = 1,
    rdd_dei_command_set                                 = 2,
}
rdd_dei_command;

/** Ingress classification lookup mode */
typedef enum
{
    rdd_ingress_classification_lookup_mode_ih        = 0,
    rdd_ingress_classification_lookup_mode_optimized = 1,
    rdd_ingress_classification_lookup_mode_short     = 2,
    rdd_ingress_classification_lookup_mode_long      = 3,
} rdd_ingress_classification_lookup_mode;

#ifndef RDD_BASIC
typedef struct
{
    rdpa_qos_method               qos_method; /**< QoS classification method flow / pbit */
    uint8_t                       wan_flow;  /**< WAN flow : Gem Flow or LLID */
    rdpa_forward_action           action; /**< forward/drop/cpu */
    bdmf_index                    policer; /**< Policer ID */
    rdpa_forwarding_mode          forw_mode;  /** < flow/pkt based */
    bdmf_boolean                  opbit_remark; /**< enable outer pbit remark */
    rdpa_pbit                     opbit_val;	/**< outer pbit remark value */
    bdmf_boolean                  ipbit_remark; /**< enable inner pbit remark */
    rdpa_pbit                     ipbit_val; /**< inner pbit remark value */
    bdmf_boolean                  dscp_remark; /**< enable dscp remark */
    rdpa_dscp                     dscp_val; /**< dscp remark value */
    uint8_t                       ecn_val;
    BL_LILAC_RDD_BRIDGE_PORT_DTE  egress_port;
    uint8_t                       wifi_ssid;
    BL_LILAC_RDD_SUBNET_ID_DTE    subnet_id;
    bdmf_index                    rate_shaper;
    uint8_t                       rate_controller_id;
    uint8_t                       priority;
    uint8_t                       wan_flow_mapping_table;
    rdpa_qos_method               wan_flow_mapping_mode;
    bdmf_boolean                  service_queue_mode;
    uint8_t                       service_queue;
    bdmf_boolean                  qos_rule_wan_flow_overrun; /**< enable overrun wan flow value by qos rule   */
    rdd_dei_command               dei_command;
    bdmf_boolean                  cpu_mirroring;
    bdmf_boolean                  ic_ip_flow;
    uint8_t                       trap_reason;
    union {
        struct {
            uint8_t  eth0_vlan_command;
            uint8_t  eth1_vlan_command;
            uint8_t  eth2_vlan_command;
            uint8_t  eth3_vlan_command;
            uint8_t  eth4_vlan_command;
            uint8_t  pci_vlan_command;
            uint8_t  multicast_vlan_command;
        } ds_vlan_command;
        uint8_t  us_vlan_command;
    } vlan_command_id;
} rdd_ingress_classification_context_t;
#endif

/** Full flow cache corner case acceleration modes */
typedef enum
{
    rdd_full_fc_acceleration_non_ip       = 0,
    rdd_full_fc_acceleration_multicast_ip = 1,
} rdd_full_fc_acceleration_mode;

typedef enum
{
    rdd_single_priority_mode = 0,
    rdd_double_priority_mode = 1,
} rdd_policer_mode;



/** CPU TX redesign **/
typedef enum
{
    rdd_cpu_tx_queue_table_fast_a = 0,
    rdd_cpu_tx_queue_table_fast_b = 1,
    rdd_cpu_tx_queue_table_pico_a = 2,
    rdd_cpu_tx_queue_table_pico_b = 3,
} rdd_cpu_tx_queue_table;


typedef enum
{
    rdd_cpu_tx_mode_full         = 0,
    rdd_cpu_tx_mode_interworking = 1,
    rdd_cpu_tx_mode_egress_enq   = 2,
} rdd_cpu_tx_mode;


typedef enum
{
    rdd_host_buffer   = 0,
    rdd_runner_buffer = 1,
} rdd_buffer_type;

typedef struct
{
    rdpa_traffic_dir  traffic_dir;
    rdd_cpu_tx_mode   mode;
    rdd_buffer_type   buffer_type;

    uint8_t   wifi_ssid;
    uint16_t  wan_flow;
    rdpa_discard_prty  drop_precedence;

    union 
    {
        struct 
        {
#if defined(LEGACY_RDP)
            BL_LILAC_RDD_EMAC_ID_DTE   emac_id;
#else
            rdd_emac_id_t              emac_id;
#endif
            BL_LILAC_RDD_QUEUE_ID_DTE  queue_id;
            bdmf_boolean               en_1588;
        } ds;

        struct
        {
            uint32_t                      wan_channel;
            uint32_t                      rate_controller;
            uint32_t                      queue;
            BL_LILAC_RDD_BRIDGE_PORT_DTE  src_bridge_port;
        } us;
    } direction;
    int is_spdsvc_setup_packet;
} rdd_cpu_tx_args_t;

static inline uint32_t rdd_rate_to_alloc_unit(uint32_t rate, uint32_t period)
{
    /* original algorithm cannot provide enough token for the rate */
#if 0
    return ((rate + ((1000000 / period) / 2)) / (1000000 / period));
#endif
    return rate;
}

typedef void ( * BL_LILAC_RDD_LOCK_CRITICAL_SECTION_FP_DTE )( bdmf_fastlock * );
typedef void ( * BL_LILAC_RDD_UNLOCK_CRITICAL_SECTION_FP_DTE )( bdmf_fastlock * );
typedef void ( * BL_LILAC_RDD_LOCK_CRITICAL_SECTION_FP_IRQ_DTE )( bdmf_fastlock *, unsigned long * );
typedef void ( * BL_LILAC_RDD_UNLOCK_CRITICAL_SECTION_FP_IRQ_DTE )( bdmf_fastlock *, unsigned long );

#endif
