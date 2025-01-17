/*
* <:copyright-BRCM:2014:DUAL/GPL:standard
* 
*    Copyright (c) 2014 Broadcom 
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

#ifndef _RDPA_DHD_HELPER_BASIC_H_
#define _RDPA_DHD_HELPER_BASIC_H_

#include "rdpa_types.h"

/** \addtogroup dhd_helper DHD Helper Interface
 *
 * @{
 */

/* RDP Feature capability defines for this release */
#define RDPA_DHD_HELPER_FEATURE_TXCOMPL_SUPPORT
#define RDPA_DHD_HELPER_FEATURE_LLCSNAPHDR_SUPPORT
#define RDPA_DHD_HELPER_FEATURE_LBRAGGR_SUPPORT
#define RDPA_DHD_HELPER_MIXED_CWI64_CWI32_MSGFORMAT_SUPPORT
#define RDPA_DHD_HELPER_FEATURE_MSGFORMAT_SUPPORT
/*#define RDPA_DHD_HELPER_FEATURE_FAST_FLOWRING_DELETE_SUPPORT*/
#define RDPA_DHD_HELPER_FEATURE_BACKUP_QUEUE_SUPPORT
#define RDPA_DHD_TX_POST_PHY_RING_SIZE 512
#define RDPA_DHD_HELPER_FEATURE_HWA_WAKEUP_SUPPORT


#if defined(XRDP)
#define RDPA_DHD_HELPER_FEATURE_HBQD_SUPPORT
#define RDPA_DHD_HELPER_FEATURE_CODEL_SUPPORT
#define DHD_MAX_SSID_NUM 16
typedef uint32_t rdpa_dhd_ssid_tx_dropped_t[DHD_MAX_SSID_NUM];
#else
#define DHD_MAX_SSID_NUM 8
#endif
/* Not supported any more
#define RDPA_DHD_HELPER_FEATURE_NPLUSM
*/

#ifndef BDMF_SYSTEM_SIM
#if defined(BCM_DSL_RDP)
#define RDPA_DHD_DOORBELL_IRQ (INTERRUPT_ID_RUNNER_0 + 2) /* Comply to definition in RDD */
#else
#define RDPA_DHD_DOORBELL_IRQ (INTERRUPT_ID_RDP_RUNNER + 2) /* Comply to definition in RDD */
#endif
#else
#define RDPA_DHD_DOORBELL_IRQ 2 /* Comply to definition in RDD */
#endif

#define RDPA_DHD_HELPER_CPU_QUEUE_SIZE 128

#define RDPA_DHD_HELPER_NUM_OF_FLOW_RINGS (4 * 136)


#if !defined(BCM6846) && !defined(BCM6878)
#define RDPA_MAX_RADIOS 3
#else
#define RDPA_MAX_RADIOS 1
#endif

#define RDPA_MAX_AC 4 /* exclude BC/MC */


#define RDPA_DHD_TX_POST_SKB_BUFFER_VALUE    0 /* 00: possible value in tx complete only */
#define RDPA_DHD_TX_POST_HOST_BUFFER_VALUE   1 /* 01: possible value in tx post and tx complete */
#define RDPA_DHD_TX_POST_BPM_BUFFER_VALUE    2 /* 10: possible value in tx post and tx complete */
#define RDPA_DHD_TX_POST_FKB_BUFFER_VALUE    3 /* 11: possible value in tx complete only */


/** DHD init configuration */
typedef struct
{
    /* FlowRings base addresses */
    void *rx_post_flow_ring_base_addr;
    void *tx_post_flow_ring_base_addr; /**< Fake base, (first 2 indexes are not in use) */
    void *rx_complete_flow_ring_base_addr;
    void *tx_complete_flow_ring_base_addr;

    /* RD/WR indexes arrays base addresses */
    void *r2d_wr_arr_base_addr;
    void *d2r_rd_arr_base_addr;
    void *r2d_rd_arr_base_addr;
    void *d2r_wr_arr_base_addr;


    uint32_t r2d_wr_arr_base_phys_addr;
    uint32_t d2r_rd_arr_base_phys_addr;
    uint32_t r2d_rd_arr_base_phys_addr;
    uint32_t d2r_wr_arr_base_phys_addr;

    void *tx_post_mgmt_arr_base_addr;
    uint32_t tx_post_mgmt_arr_base_phys_addr;
    uint32_t tx_post_mgmt_arr_entry_count;

    int (*doorbell_isr)(int irq, void *priv);
    void *doorbell_ctx;

    uint32_t dongle_wakeup_register;
    uint8_t  add_llcsnap_header;
    uint8_t  flow_ring_format;               /* 0-legacy, 1- CWI32 */
    uint32_t dongle_wakeup_register_2;
    uint8_t  dongle_wakeup_hwa;              /* 0: disabled Use wakeup_register for all rings */
                                             /* 1: enabled  Use wakeup_register for txpost, and
                                                wakeup_register_2 for hwa rxpost, rxcpl, txcpl rings */
    void *dongle_wakeup_register_virt;       /* Virtual address of dongle_wakeup_register for rdd access */
    void *dongle_wakeup_register_2_virt;     /* Virtual address of dongle_wakeup_register_2 for rdd access */

    uint8_t  hbqd_mode;                      /* Host Backup Queue Depth (HBQD) mode
                                                0 - disabled, 32 FRs in idma group. 1 - enabled, 16 FRs in idma group */
    uint32_t reserved[4];                    /* reserved for next features to keep structure backward compatibility */
} rdpa_dhd_init_cfg_t;

/** Extra data that can be passed along with the packet to be posted for transmission */
typedef struct
{
    uint32_t radio_idx;
    uint32_t flow_ring_id; /**< Destination Flow-Ring */
    uint32_t ssid_if_idx; /**< SSID index */
    int is_spdsvc_setup_packet; /**<when set, indicates that a Speed Service Setup packet is being transmitted */
    int is_bpm;  /**< 1 for BPM, 0 for host buffer */
    uint32_t spdt_so_mark; /**< in use for Speed Service packet setup */
} rdpa_dhd_tx_post_info_t;

/* no autogenerated rdpa_dhd_data_stat_t to api */

typedef struct
{
    uint32_t dhd_rx_drop; /**< DHD RX drop packets */
    uint32_t dhd_tx_fpm_used; /**< DHD TX FPM used */
    uint32_t dhd_tx_high_prio_fpm_used; /**< DHD TX High priority FPM used */
    uint32_t dhd_tx_total_fpm_used; /**< DHD TX FPM used */
    uint32_t dhd_tx_fpm_drop; /**< DHD TX FPM drop */
    uint32_t dhd_tx_high_prio_fpm_drop; /**< DHD TX high priority and mcast FPM drop */
    uint32_t dhd_mcast_sbpm_drop;  /**< DHD MCAST SBPM drop \RDP limited */
    uint32_t dhd_tx_fr_ac_bk_full; /**< DHD TX feeder ring AC BK is full*/
    uint32_t dhd_tx_fr_ac_be_full; /**< DHD TX feeder ring AC BE is full*/
    uint32_t dhd_tx_fr_ac_vi_full; /**< DHD TX feeder ring AC VI is full */
    uint32_t dhd_tx_fr_ac_vo_full; /**< DHD TX feeder ring AC VO is full */
    uint32_t dhd_tx_fr_ac_bc_mc_full; /**< DHD TX feeder ring AC BC/MC is full  */
    uint32_t dhd_tx_post_packets; /**< DHD TX post packets */
    uint32_t dhd_tx_complete_packets; /**< DHD TX completed packets */
    uint32_t dhd_rx_complete_packets; /**< DHD RX completed packets */
    uint32_t dhd_tx_drop_packets; /**< DHD TX total dropped packets  */
    uint32_t dhd_tx_host_drop_packets; /**< DHD TX host dropped packets */
} rdpa_dhd_data_stat_t;

/** Runner wakeup information returned to DHD by RDD */
typedef struct
{
    uint32_t radio_idx;
    bdmf_phys_addr_t tx_complete_wakeup_register;
    uint32_t tx_complete_wakeup_value;
    bdmf_phys_addr_t rx_complete_wakeup_register;
    uint32_t rx_complete_wakeup_value;
} rdpa_dhd_wakeup_info_t;

/* Description of TxPost ring for caching */
typedef struct rdpa_dhd_flring_cache
{
    uint32_t base_addr_low; /* XXX: Add dedicated struct for addr_64 */
    uint32_t base_addr_high;
    uint16_t items; /* Number of descriptors in flow ring (including backup queue if exist) */
#define FLOW_RING_FLAG_DISABLED   (1 << 1)
#define FLOW_RING_FLAG_SSID_SHIFT (8)
#define FLOW_RING_FLAG_SSID_MASK  (0xF << FLOW_RING_FLAG_SSID_SHIFT)
    uint16_t flags;
#ifdef RDPA_DHD_HELPER_FEATURE_BACKUP_QUEUE_SUPPORT
    uint16_t backup_first_index;
    uint16_t backup_last_index;
    uint16_t backup_num_entries;
    uint16_t phy_ring_size;  /* Number of descriptors in physical flow ring */
#else
    uint32_t reserved;       /* Maintain the structure for platforms without backup queues feature */
#endif
#ifdef RDPA_DHD_HELPER_FEATURE_CODEL_SUPPORT
    uint16_t window_ts;     /* Sliding window endpoint timestamp */
    uint16_t drop_interval; /* Number of consequitive drops */
    uint16_t codel_flags;   /* Codel state flags */
    uint16_t codel_drop_counter;
#endif
} rdpa_dhd_flring_cache_t;


/** Tx Complete descriptor data for host DHD driver */
typedef struct rdpa_dhd_complete_data
{
    uint32_t radio_idx;

    uint32_t request_id;
    uint8_t  buf_type;          /* RDPA_DHD_TX_POST_SKB_BUFFER_VALUE, RDPA_DHD_TX_POST_FKB_BUFFER_VALUE, RDPA_DHD_TX_POST_HOST_BUFFER_VALUE  */
    void     *txp;
    uint16_t status;
    uint16_t flow_ring_id;
} rdpa_dhd_complete_data_t;

/** DHD CPU Data resources for exception traffic */
typedef struct
{
    uint32_t cpu_port;
    uint8_t exception_rxq;
    bdmf_boolean set_exception_tc_to_rxq;
} rdpa_dhd_cpu_data_t;

typedef union
{
    uint32_t u32;
    struct {
        uint32_t flowring_idx   :16;
        uint32_t read_idx       :10;
        uint32_t read_idx_valid :1;
        uint32_t reserved       :5;
    };
} rdpa_dhd_ffd_data_t;

/** @} end of dhd_heler Doxygen group */


#endif /* _RDPA_DHD_HELPER_H_ */
