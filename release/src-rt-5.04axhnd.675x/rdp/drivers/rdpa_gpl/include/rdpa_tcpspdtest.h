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

#ifndef _RDPA_TCPSPDTEST_H_
#define _RDPA_TCPSPDTEST_H_

/** \defgroup Tcp Speed Test
 * This object is used to manage the Tcp Speed Test \n
 * @{
 */

#include "rdd.h"
#include "rdpa_types.h"
#include "rdpa_spdtest_common.h"

/** Minimum transmitted packet size for padding */
#define RDPA_TCPSPDTEST_MIN_TX_PD_LEN  RDPA_SPDTEST_MIN_TX_PD_LEN
#define RDD_SPDTEST_ENGINE_REF_PKT_HDR_HDR_NUMBER 120

#define RDPA_TCPSPDTEST_RTO_RING_TX_SEQ_ELEMENT_SIZE  TCPSPDTEST_RTO_RING_TX_SEQ_ELEMENT_SIZE
#define RDPA_TCPSPDTEST_RTO_RING_TX_SEQ_SIZE  ((uint32_t)(TCPSPDTEST_RTO_RING_TX_SEQ_SIZE + sizeof(uint64_t))) /* Add rd/wr idx space */
#define RDPA_TCPSPDTEST_RTO_RING_TX_SEQ_MASK  TCPSPDTEST_RTO_RING_TX_SEQ_MASK
#define RDPA_TCPSPDTEST_RTO_RING_TX_SEQ_COALESCING_THR  TCPSPDTEST_RTO_RING_TX_SEQ_COALESCING_THR
#define RDPA_TCPSPDTEST_RTO_RING_RETRANS_ELEMENT_SIZE  TCPSPDTEST_RTO_RING_RETRANS_ELEMENT_SIZE
#define RDPA_TCPSPDTEST_RTO_RING_RETRANS_SIZE  ((uint32_t)(TCPSPDTEST_RTO_RING_RETRANS_SIZE + sizeof(uint64_t))) /* Add rd/wr idx space */
#define RDPA_TCPSPDTEST_RTO_RING_RETRANS_MASK  TCPSPDTEST_RTO_RING_RETRANS_MASK

/** Tcp Speed Test Engine Global Information.\n
 * Contains the Global Information for Tcp Speed Test Engine. \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct {
    uint8_t  num_streams;                 /**< Number of tCP streams */
    uint32_t up_bucket_tokens;            /**< Upload tcp tx leaky bucket num of tokens */
    uint32_t up_bucket_full_tokens;       /**< Upload tcp tx leaky bucket full num of tokens */
    uint16_t up_bucket_tokens_fill_rate;  /**< Upload tcp tx leaky bucket tokens per timer tick */
} rdpa_tcpspdtest_engine_global_info_t;

/** Tcp Speed Test Engine Connection Information.\n
 * Contains the Connection Information to Server \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct {
    uint8_t   l2_hdr_len;               /**< L2 header len */
    uint8_t   l3_hdr_len;               /**< L3 header len */
    rdpa_ic_l3_protocol  l3_protocol;   /**< L3 Protocol */
    uint8_t   l4_hdr_len;               /**< L4 header len */
    uint8_t   tx_hdr_len;               /**< Tx packet header len */
    uint32_t  cpu_rx_rdd_queue;         /**< CPU queue num */
    rdpa_if   port;                     /**< Destination port for method=port, source port for method=bridge */
    rdpa_flow wan_flow;                 /**< Destination flow for method=port, Source flow for method=bridge,port=wan */
    uint32_t  egress_queue_id;          /**< Egress queue id. method=port only */
    uint16_t  tx_qm_queue;              /**< Runner first level queue */
    uint16_t  up_tx_mss;                /**< Upload tcp tx mss */
    uint16_t  up_tx_max_pd_len;         /**< Upload tcp max pd len */
    uint16_t  up_pppoe_hdr_ofs;         /**< Upload tcp pppoe header offset */
    uint8_t  up_peer_rx_scale;          /**< Upload tcp peer rx window scale */
    uint8_t   sack_permitted;           /**< is selective ack permitted */
} rdpa_tcpspdtest_engine_conn_info_t;

/** Tcp Speed Test Engine TCB.\n
 * Contains the Task Control State of the Runner Tcp Speed Test Engine \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct {
    uint32_t rx_pkts;                   /**< Received packets counter */
    uint32_t txed_pkts;                 /**< Num of txed packets */
    uint32_t freed_pkts;                /**< Num of freed packets */
    uint32_t ack_seq;                   /**< Calculated ack seq */
    uint32_t tx_seq;                    /**< Last transmitted seq */
    uint32_t bad_pkts;                  /**< Num of received packets with unexpected seq */
    uint32_t no_credits;                /**< Num of dispatcher no credits */
    uint64_t bad_bytes;                 /**< Num of received bytes with unexpected seq */
    uint64_t rx_bytes;                  /**< Received bytes */
    uint64_t expected_bytes;            /**< Expected bytes */
    uint64_t up_to_send_bytes;          /**< Upload num of remaining transmit bytes */
    uint32_t up_cwnd;                   /**< Upload tcp tx congestion window */
    uint32_t up_cwnd_thr;               /**< Upload tcp tx congestion window threshold */
    uint32_t up_last_ack_seq;           /**< Upload last rx ack sequence */
} rdpa_tcpspdtest_engine_tcb_t;

/** Tcp/Udp Speed Test Engine Reference Packet Header.\n
 * Contains the Acknowledge Refernce Packet for Tcp/Udp Speed Test Engine \n
 * required by the Runner Tcp/Udp Speed Test Engine.\n
 */
typedef struct
{
    uint16_t size;                                           /**< Reference packet header size */
    uint16_t offset;                                         /**< Packet offset for l3 8 bytes align */
    uint8_t  hdr[RDD_SPDTEST_ENGINE_REF_PKT_HDR_HDR_NUMBER]; /**< Reference packet header ptr */
} rdpa_spdtest_engine_ref_pkt_hdr_t;

typedef rdpa_spdtest_engine_ref_pkt_hdr_t rdpa_tcpspdtest_engine_ref_pkt_hdr_t;

/** Tcp Speed Test Engine Reference Packet, includes both packet header and payload.\n
 * required by the Runner Tcp Speed Test Engine for Upload test.\n
 */
typedef rdpa_spdtest_ref_pkt_t rdpa_tcpspdtest_engine_ref_pkt_t;


/** Tcp Speed Test Engine Packet Drop Handling.\n
 * Contains the Packet Drop Handling State for Tcp Speed Test Engine \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct
{
    uint8_t   is_drop;       /**< Is packets drop */
    uint8_t   is_win_full;   /**< Is sequence window full */
    uint16_t  num_errs;      /**< Num of err events. One event for multiple burst lost */
    uint16_t  wr_ofs;        /**< Write offset for good frames window during pkt drops */
    uint16_t  rd_ofs;        /**< Read offset for good frames window during pkt drops */
} rdpa_tcpspdtest_engine_pkt_drop_t;

typedef struct
{
    uint32_t  addr_low;      /**< ring ddr phys addr low */
    uint32_t  addr_high;     /**< ring ddr phys addr high */
    uint32_t  send_cnt;      /**< ring send counter */
    uint32_t  drop_cnt;      /**< ring drop counter */
    uint32_t  receive_cnt;   /**< ring drop counter */
    void      *mem_ptr;      /**< ddr memory addr for runner txed seqs */
} rdpa_tcpspdtest_ring_ddr_t;

/** Tcp Speed Test Engine RTO Handling.\n
 * Contains the RTO Handling State for Tcp Speed Test Engine \n
 * required by the Runner Tcp Speed Test Engine.\n
 */
typedef struct
{
    rdpa_tcpspdtest_ring_ddr_t ring_tx_seq; /**< Ring if runner txed seqs */
    rdpa_tcpspdtest_ring_ddr_t ring_retrans; /**< Ring if runner txed seqs */
} rdpa_tcpspdtest_engine_rto_t;

typedef struct
{
    uint32_t stream_idx;
    uint32_t reserved;
} rdpa_tcpspdtest_tx_info_t;

/** @} end of tcpspdtest Doxygen group. */

#endif /* _RDPA_TCPSPDTEST_H_ */
