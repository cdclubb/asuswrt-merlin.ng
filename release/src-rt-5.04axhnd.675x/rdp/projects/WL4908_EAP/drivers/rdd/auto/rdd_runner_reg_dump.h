/*
   Copyright (c) 2015 Broadcom
   All Rights Reserved

    <:label-BRCM:2015:DUAL/GPL:standard
    
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



/* This is an automated file. Do not edit its contents. */


#ifndef __RDD_RUNNER_REG_DUMP_H__
#define __RDD_RUNNER_REG_DUMP_H__

#include "bdmf_shell.h"

typedef struct
{
#ifndef USE_BDMF_SHELL
	void  (*callback)(unsigned char *xi_value, int rw, int unionreq);
#else
	void  (*callback)(bdmf_session_handle session, unsigned char *value);
#endif
	unsigned int starts;
} ENTRY_STRUCT;

typedef struct
{
	int length; /* length of each entry in bytes */
	ENTRY_STRUCT entries[];
} DUMP_RUNNERREG_STRUCT;

typedef struct
{
	char * table_name;
	int tbldmp; /* boolean */
	int segment;
	DUMP_RUNNERREG_STRUCT * entries;
    int size_rows; /* Number of rows in table */
    int size_rows_d2;/* If table's entries are tables by themselfves, number of rows in each entry table (dimention 2)*/
    int size_rows_d3; /* Like above, dimention 3 */
} TABLE_STRUCT;

#ifndef STT_PRINTF
	#if defined LINUX_KERNEL
		#define STT_PRINTF printk
	#else
		#define STT_PRINTF printf
	#endif
#endif


void dump_RDD_IH_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PACKET_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
#if defined WL4908_EAP
void dump_RDD_BBH_TX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
#endif

void dump_RDD_SERVICE_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CONNECTION_CONTEXT_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GSO_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GSO_PSEUDO_HEADER_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TWO_BYTES(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BUDGET_ALLOCATOR_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_REASON_TO_METER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_RX_METER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DS_WAN_FLOW_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DS_INGRESS_CLASSIFICATION_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CAPWAPF_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SERVICE_QUEUES_RATE_LIMITER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_EIGHT_BYTES(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_FILTERS_PARAMETER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_POLICER_ENTRY(bdmf_session_handle session, unsigned char *p);
#if defined WL4908_EAP
void dump_RDD_CONTEXT_CONTINUATION_ENTRY(bdmf_session_handle session, unsigned char *p);
#endif

void dump_RDD_ETH_TX_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_L2_UCAST_TUPLE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FORWARDING_MATRIX_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TIMER_SCHEDULER_PRIMITIVE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RATE_LIMITER_REMAINDER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DS_WAN_UDP_FILTER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_MCAST_PORT_HEADER_ENTRY(bdmf_session_handle session, unsigned char *p);
#if defined WL4908_EAP
void dump_RDD_BBH_RX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
#endif

void dump_RDD_CONNECTION_CONTEXT_MULTICAST_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_MCAST_PACKET_SAVE_DATA_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FAST_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SBPM_REPLY_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ETH_TX_QUEUE_POINTERS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PICO_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_FILTERS_LOOKUP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_BBH_DESCRIPTORS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FOUR_BYTES(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RUNNER_FLOW_HEADER_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DESCRIPTOR_CORE(bdmf_session_handle session, unsigned char *p);
#if defined WL4908_EAP
void dump_RDD_CPU_TX_DESCRIPTOR_BPM(bdmf_session_handle session, unsigned char *p);
#endif

void dump_RDD_CPU_TX_DESCRIPTOR_ABS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DESCRIPTOR_DS_FAST(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DESCRIPTOR_US_FAST(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO_WIFI(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_MESSAGE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ONE_BYTE(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_MESSAGE_DATA_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RATE_LIMITER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GRE_RUNNER_FLOW_HEADER_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_CLASSIFICATION_RULE_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PROFILING_BUFFER_PICO_RUNNER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SPDSVC_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_L2_UCAST_CONNECTION_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTES_4(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ETH_TX_LOCAL_REGISTERS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TOTAL_PPS_RATE_LIMITER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_QUEUE_PROFILE(bdmf_session_handle session, unsigned char *p);
void dump_RDD_EMAC_SKB_ENQUEUED_INDEXES_FIFO_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GPE_COMMAND_PRIMITIVE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_FILTERS_CONFIGURATION_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_PARAMETERS_BLOCK_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RUNNER_FLOW_HEADER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GSO_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_MCAST_LKP_WORD3_CRC(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_QUEUE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SYSTEM_CONFIGURATION(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CONNECTION_TABLE_CONFIG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_HASH_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BROADCOM_SWITCH_PORT_MAPPING(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DEBUG_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CONTEXT_TABLE_CONFIG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PARALLEL_PROCESSING_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GSO_DESC_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SIXTEEN_BYTES(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PARALLEL_PROCESSING_TASK_REORDER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TIMER_CONTROL_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ENQUEUE_PCI_PACKET_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ETH_TX_EMACS_STATUS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_IPTV_COUNTERS_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_HASH_BASED_FORWARDING_PORT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FIREWALL_IPV6_R16_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_PICO_INGRESS_QUEUE_PTR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_RX_PICO_INGRESS_QUEUE_PTR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_RX_FAST_INGRESS_QUEUE_PTR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PARALLEL_PROCESSING_IH_BUFFER_PTR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ANY_SRC_PORT_FLOW_COUNTER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WAN_PHYSICAL_PORT(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RUNNER_CONGESTION_STATE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTES_2(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DUMMY_STORE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ETH_TX_INTER_LAN_SCHEDULING_OFFSET_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_GLOBAL_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PARALLEL_PROCESSING_SLAVE_VECTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTE_1(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DHD_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DHD_MESSAGE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_UPDATE_PD_POOL_QUOTA_MESSAGE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RUNNER_FLOW_IH_RESPONSE(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ETH_TX_MAC_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CSO_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CSO_PSEUDO_HEADER_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_QUEUE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WAN_CHANNEL_8_39_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WAN_TX_SERVICE_QUEUE_SCHEDULER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_WAN_FLOW_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_INGRESS_CLASSIFICATION_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WAN_CHANNEL_0_7_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_RATE_LIMITER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GPON_ABSOLUTE_TX_COUNTER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ETH_RX_DESCRIPTORS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CSO_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RATE_CONTROLLER_EXPONENT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WAN_ENQUEUE_INGRESS_QUEUE_PTR_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BBH_TX_WAN_CHANNEL_INDEX(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RUNNER_SCRATCHPAD(bdmf_session_handle session, unsigned char *p);
void dump_RDD_MAC_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DDR_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TRACE_C_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FREE_SKB_INDEXES_FIFO_TAIL(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BPM_REPLY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CAPWAPF_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_REASON_TO_CPU_RX_QUEUE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GPON_SKB_ENQUEUED_INDEXES_FIFO_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CONNECTION_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INTERRUPT_COALESCING_CONFIG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_MAC_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_CLASSIFICATION_LONG_LOOKUP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PM_COUNTERS(bdmf_session_handle session, unsigned char *p);
#if defined WL4908_EAP
void dump_RDD_ETHWAN2_RX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
#endif

void dump_RDD_RING_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_RX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DDR_QUEUE_ADDRESS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_MAC_EXTENSION_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SERVICE_QUEUES_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PM_COUNTERS_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CAPWAPF_STATS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DS_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DS_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_CLASSIFICATION_SHORT_LOOKUP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WAN_TX_SERVICE_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WAN_TX_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DUMMY_WAN_TX_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CAPWAPR_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PACKET_SRAM_TO_DDR_COPY_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DUMMY_RATE_CONTROLLER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_LAN_INGRESS_FIFO_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CAPWAPR_STATS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CAPWAPR_FLUSH_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CAPWAP_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_FLOW_IP_ADDRESSES_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_US_RATE_CONTROLLER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BPM_PACKET_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_UCAST_FLOW_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_L2_UCAST_FLOW_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_MCAST_FLOW_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_MCAST_MASTER_FLOW_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_NAT_CACHE_LKP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_NAT_CACHE_MCAST_LKP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_NAT_CACHE_L2_LKP_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_NATC_L2_UCAST_FLOW_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_NATC_MCAST_FLOW_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);

#endif /* __RDD_RUNNER_REG_DUMP_H__ */
