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


#include "bdmf_shell.h"
#include "rdp_map.h"
#include "rdd_runner_reg_dump.h"
#include "rdd_runner_reg_dump_addrs.h"
unsigned int SEGMENTS_ADDRESSES[NUMBER_OF_SEGMENTS] =
{
#ifdef WL4908
 0x0 + RUNNER_PRIVATE_0_OFFSET, 0x0 + RUNNER_PRIVATE_1_OFFSET, 0x0 + RUNNER_COMMON_0_OFFSET, 0x8000 + RUNNER_COMMON_1_OFFSET, 0x0, 0x0 + PSRAM_BLOCK_OFFSET,
#endif
};
#if defined WL4908
static DUMP_RUNNERREG_STRUCT INGRESS_HANDLER_BUFFER =
{
	256,
	{
		{ dump_RDD_IH_BUFFER, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FREE_PACKET_DESCRIPTORS_POOL =
{
	8,
	{
		{ dump_RDD_PACKET_DESCRIPTOR, 0x2000 },
#if defined WL4908
		{ dump_RDD_BBH_TX_DESCRIPTOR, 0x2000 },
#endif
		{ dump_RDD_SERVICE_QUEUE_DESCRIPTOR, 0x2000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_CONTEXT_BUFFER =
{
	128,
	{
		{ dump_RDD_CONNECTION_CONTEXT_BUFFER_ENTRY, 0x6000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_GSO_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_GSO_BUFFER_ENTRY, 0x6400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_GSO_PSEUDO_HEADER_BUFFER =
{
	40,
	{
		{ dump_RDD_GSO_PSEUDO_HEADER_BUFFER_ENTRY, 0x6480 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_TIMER_7_SCHEDULER_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x64a8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RATE_SHAPER_BUDGET_ALLOCATOR_TABLE =
{
	2,
	{
		{ dump_RDD_BUDGET_ALLOCATOR_ENTRY, 0x64b0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_REASON_TO_METER_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_METER_ENTRY, 0x64c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_GSO_CHUNK_BUFFER =
{
	128,
	{
		{ dump_RDD_GSO_BUFFER_ENTRY, 0x6500 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_METER_TABLE =
{
	8,
	{
		{ dump_RDD_CPU_RX_METER_ENTRY, 0x6580 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_WAN_FLOW_TABLE =
{
	2,
	{
		{ dump_RDD_DS_WAN_FLOW_ENTRY, 0x6600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_CONTEXT_TABLE =
{
	8,
	{
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_CONTEXT_ENTRY, 0x6800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_CONTEXT_REMAINING_BUFFER =
{
#if defined WL4908
	76,
	{
		{ dump_RDD_CONTEXT_CONTINUATION_ENTRY, 0x7000 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_RATE_LIMITER_TABLE =
{
	24,
	{
		{ dump_RDD_SERVICE_QUEUES_RATE_LIMITER_DESCRIPTOR, 0x7260 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_MAIN_TIMER_TASK_DESCRIPTOR_TABLE =
{
	8,
	{
		{ dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY, 0x7560 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_SPDSVC_CONTEXT_TABLE =
{
	80,
	{
		{ dump_RDD_SPDSVC_CONTEXT_ENTRY, 0x7580 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_TIMER_SCHEDULER_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TIMER_SCHEDULER_PRIMITIVE_ENTRY, 0x75d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_MAIN_PROFILING_BUFFER_RUNNER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x75e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH_TX_QUEUES_TABLE =
{
	16,
	{
		{ dump_RDD_ETH_TX_QUEUE_DESCRIPTOR, 0x76e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_TIMER_TASK_DESCRIPTOR_TABLE =
{
	8,
	{
		{ dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY, 0x7b60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_FILTERS_LOOKUP_TABLE =
{
	4,
	{
		{ dump_RDD_INGRESS_FILTERS_LOOKUP_ENTRY, 0x7b80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_WAN_UDP_FILTER_TABLE =
{
	16,
	{
		{ dump_RDD_DS_WAN_UDP_FILTER_ENTRY, 0x7c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT FC_MCAST_PORT_HEADER_BUFFER =
{
	1,
	{
		{ dump_RDD_FC_MCAST_PORT_HEADER_ENTRY, 0x7e00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_LAN_ENQUEUE_SQ_PD =
{
#if defined WL4908
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0x8000 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_CONTEXT_MULTICAST_BUFFER =
{
	64,
	{
		{ dump_RDD_CONNECTION_CONTEXT_MULTICAST_BUFFER_ENTRY, 0x8200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_RX_SQ_PD_INGRESS_QUEUE =
{
#if defined WL4908
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0x8400 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FC_MCAST_PACKET_SAVE_DATA_TABLE =
{
	88,
	{
		{ dump_RDD_FC_MCAST_PACKET_SAVE_DATA_ENTRY, 0x8600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_FILTERS_PARAMETER_TABLE =
{
	1,
	{
		{ dump_RDD_INGRESS_FILTERS_PARAMETER_ENTRY, 0x8760 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT INGRESS_HANDLER_SKB_DATA_POINTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x8780 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH_TX_QUEUES_POINTERS_TABLE =
{
	4,
	{
		{ dump_RDD_ETH_TX_QUEUE_POINTERS_ENTRY, 0x8800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FC_L2_UCAST_TUPLE_BUFFER =
{
	32,
	{
		{ dump_RDD_FC_L2_UCAST_TUPLE_ENTRY, 0x8920 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RATE_LIMITER_REMAINDER_TABLE =
{
	2,
	{
		{ dump_RDD_RATE_LIMITER_REMAINDER_ENTRY, 0x8940 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SBPM_REPLY =
{
	128,
	{
		{ dump_RDD_SBPM_REPLY_ENTRY, 0x8980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_POLICER_TABLE =
{
	16,
	{
		{ dump_RDD_POLICER_ENTRY, 0x8a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FORWARDING_MATRIX_TABLE =
{
	1,
	{
		{ dump_RDD_FORWARDING_MATRIX_ENTRY, 0x8b00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FC_L2_UCAST_CONNECTION_BUFFER =
{
	16,
	{
		{ dump_RDD_FC_L2_UCAST_CONNECTION_ENTRY, 0x8b90 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE =
{
	8,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_ENTRY, 0x8ba0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x8bc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GSO_PICO_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0x8c00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0x8c00 },
#if defined WL4908
		{ dump_RDD_CPU_TX_DESCRIPTOR_BPM, 0x8c00 },
#endif
		{ dump_RDD_CPU_TX_DESCRIPTOR_ABS, 0x8c00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_FAST, 0x8c00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_US_FAST, 0x8c00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO, 0x8c00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO_WIFI, 0x8c00 },
		{ dump_RDD_CPU_TX_MESSAGE_DESCRIPTOR, 0x8c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_BBH_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_CPU_TX_BBH_DESCRIPTORS_ENTRY, 0x8e00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RUNNER_FLOW_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_RUNNER_FLOW_HEADER_BUFFER, 0x8f00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_GRE_RUNNER_FLOW_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_GRE_RUNNER_FLOW_HEADER_BUFFER, 0x8f80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_POST_PD_INGRESS_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PROFILING_BUFFER_PICO_RUNNER =
{
	256,
	{
		{ dump_RDD_PROFILING_BUFFER_PICO_RUNNER, 0x9100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_LAN_ENQUEUE_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9240 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9280 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN_TX_ACB_COUNTER_TABLE =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x92c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RATE_LIMITER_TABLE =
{
	8,
	{
		{ dump_RDD_RATE_LIMITER_ENTRY, 0x9300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_TX_POST_FLOW_RING_BUFFER =
{
	48,
	{
		{ dump_RDD_DHD_TX_POST_DESCRIPTOR, 0x9400 },
		{ dump_RDD_DHD_TX_POST_DESCRIPTOR_CWI32, 0x9400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_COMPLETE_FLOW_RING_BUFFER =
{
	16,
	{
		{ dump_RDD_DHD_TX_COMPLETE_DESCRIPTOR, 0x94c0 },
		{ dump_RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32, 0x94c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINA_PARAM =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x94f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_RULE_CFG_TABLE =
{
	8,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_RULE_CFG_ENTRY, 0x9500 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH_TX_LOCAL_REGISTERS =
{
	8,
	{
		{ dump_RDD_ETH_TX_LOCAL_REGISTERS_ENTRY, 0x9580 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_TOTAL_PPS_RATE_LIMITER =
{
	8,
	{
		{ dump_RDD_TOTAL_PPS_RATE_LIMITER_ENTRY, 0x95c8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_PICOA_PARAM =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x95d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FAST_RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_FAST_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY, 0x95e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_QUEUE_PROFILE_TABLE =
{
	16,
	{
		{ dump_RDD_QUEUE_PROFILE, 0x9680 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_SQ_ENQUEUE_QUEUE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9780 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_COMPLETE_RING_DESCRIPTOR_BUFFER =
{
	16,
	{
		{ dump_RDD_DHD_COMPLETE_RING_DESCRIPTOR, 0x97c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT EMAC_SKB_ENQUEUED_INDEXES_PUT_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x97f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_RX_PD_INGRESS_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_PICO_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9880 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_MESSAGE_DATA_BUFFER =
{
	64,
	{
		{ dump_RDD_CPU_TX_MESSAGE_DATA_BUFFER_ENTRY, 0x98c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_RX_FAST_PD_INGRESS_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9900 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_ROUTER_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_PICO_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY, 0x99c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x99e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_TX_POST_HEADER_SCRATCH =
{
	32,
	{
		{ dump_RDD_DHD_L2_HEADER_BUFFER_ENTRY, 0x9a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT EMAC_SKB_ENQUEUED_INDEXES_FIFO =
{
	32,
	{
		{ dump_RDD_EMAC_SKB_ENQUEUED_INDEXES_FIFO_ENTRY, 0x9a80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9b20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9b40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_NULL_BUFFER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9b60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_FILTERS_CONFIGURATION_TABLE =
{
	4,
	{
		{ dump_RDD_INGRESS_FILTERS_CONFIGURATION_ENTRY, 0x9b78 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_FAST_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9b80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_GPE_COMMAND_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_GPE_COMMAND_PRIMITIVE_ENTRY, 0x9bc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_GSO_CONTEXT_TABLE =
{
	132,
	{
		{ dump_RDD_GSO_CONTEXT_ENTRY, 0x9c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_WAN_UDP_FILTER_CONTROL_TABLE =
{
	4,
	{
		{ dump_RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY, 0x9c84 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DEBUG_BUFFER =
{
	4,
	{
		{ dump_RDD_DEBUG_BUFFER_ENTRY, 0x9c88 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FW_MAC_ADDRS =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9d08 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RUNNER_FLOW_HEADER_DESCRIPTOR =
{
	8,
	{
		{ dump_RDD_RUNNER_FLOW_HEADER_DESCRIPTOR, 0x9d88 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT EMAC_SKB_ENQUEUED_INDEXES_FREE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9d90 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_COMPLETE_RING_BUFFER =
{
	8,
	{
		{ dump_RDD_DHD_COMPLETE_RING_ENTRY, 0x9da0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MCAST_LKP_WORD3_CRC_BUFFER =
{
	8,
	{
		{ dump_RDD_MCAST_LKP_WORD3_CRC, 0x9db8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_PARAMETERS_BLOCK =
{
	20,
	{
		{ dump_RDD_CPU_PARAMETERS_BLOCK_ENTRY, 0x9dc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BPM_EXTRA_DDR_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9dd4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FAST_MALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9dd8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DATA_POINTER_DUMMY_TARGET =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9de0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_OPTIMIZED_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9df4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_MALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9df8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_GSO_DESC_TABLE =
{
	128,
	{
		{ dump_RDD_GSO_DESC_ENTRY, 0x9e00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_TX_POST_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9e80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_WLAN_SCRATCH =
{
	20,
	{
		{ dump_RDD_CPU_PARAMETERS_BLOCK_ENTRY, 0x9ec0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9ed4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BUF_SIZE_TO_TOKEN_COUNT_LOG2_TABLE =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x9ed8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE =
{
	2,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY, 0x9ee0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT HASH_BUFFER =
{
	16,
	{
		{ dump_RDD_HASH_BUFFER, 0x9ef0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_FLOW_RING_DROP_COUNTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f14 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_1_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f18 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_CONNECTION_TABLE_CONFIG, 0x9f1c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE =
{
	2,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY, 0x9f20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9f30 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_SYSTEM_CONFIGURATION =
{
	36,
	{
		{ dump_RDD_SYSTEM_CONFIGURATION, 0x9f40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CONTEXT_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_CONTEXT_TABLE_CONFIG, 0x9f64 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_ENTRY, 0x9f68 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DEBUG_PERIPHERALS_STATUS_REGISTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f6c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE =
{
	1,
	{
		{ dump_RDD_BROADCOM_SWITCH_PORT_MAPPING, 0x9f70 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT BITS_CALC_MASKS_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9f80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH_TX_SCRATCH =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f90 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_TX_POST_DOORBELL_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9fa0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_KEY_BUFFER =
{
	16,
	{
		{ dump_RDD_SIXTEEN_BYTES, 0x9fb0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_OVERALL_RATE_LIMITER =
{
	24,
	{
		{ dump_RDD_SERVICE_QUEUES_RATE_LIMITER_DESCRIPTOR, 0x9fc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GSO_TX_DHD_L2_BUFFER =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9fd8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_MAIN_TIMER_CONTROL_DESCRIPTOR =
{
	2,
	{
		{ dump_RDD_TIMER_CONTROL_DESCRIPTOR, 0x9fee },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_DHD_L2_BUFFER =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9ff0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_TIMER_CONTROL_DESCRIPTOR =
{
	2,
	{
		{ dump_RDD_TIMER_CONTROL_DESCRIPTOR, 0xa006 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_TASK_REORDER_ENTRY, 0xa008 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CONTEXT_CONTINUATION_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa00c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_DS_PICO_DHD_TX_POST_CONTEXT =
{
	16,
	{
		{ dump_RDD_DHD_TX_POST_CONTEXT_ENTRY, 0xa010 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WLAN_MCAST_DHD_TX_POST_CONTEXT =
{
	16,
	{
		{ dump_RDD_DHD_TX_POST_CONTEXT_ENTRY, 0xa020 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GSO_TX_DS_PICO_DHD_TX_POST_CONTEXT =
{
	16,
	{
		{ dump_RDD_DHD_TX_POST_CONTEXT_ENTRY, 0xa030 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa040 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GSO_TX_ENQUEUE_PCI_PACKET_CONTEXT =
{
	8,
	{
		{ dump_RDD_ENQUEUE_PCI_PACKET_CONTEXT_ENTRY, 0xa048 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_ENQUEUE_PCI_PACKET_CONTEXT =
{
	8,
	{
		{ dump_RDD_ENQUEUE_PCI_PACKET_CONTEXT_ENTRY, 0xa050 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT TIMER_DHD_TX_POST_DOORBELL_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa058 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SPDSVC_HOST_BUF_PTR =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa05c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT EMAC_SKB_ENQUEUED_INDEXES_FIFO_COUNTERS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa060 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH_TX_EMACS_STATUS =
{
	1,
	{
		{ dump_RDD_ETH_TX_EMACS_STATUS_ENTRY, 0xa065 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT IPTV_COUNTERS_BUFFER =
{
	2,
	{
		{ dump_RDD_IPTV_COUNTERS_BUFFER, 0xa066 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT HASH_BASED_FORWARDING_PORT_TABLE =
{
	1,
	{
		{ dump_RDD_HASH_BASED_FORWARDING_PORT_ENTRY, 0xa068 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_DATA_POINTER_DUMMY_TARGET =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa06c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT FIREWALL_IPV6_R16_BUFFER =
{
	4,
	{
		{ dump_RDD_FIREWALL_IPV6_R16_BUFFER_ENTRY, 0xa070 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_PICO_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_TX_PICO_INGRESS_QUEUE_PTR, 0xa074 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD =
{
	2,
	{
		{ dump_RDD_FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD, 0xa076 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa078 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_RX_PD_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa07a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_PICO_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_RX_PICO_INGRESS_QUEUE_PTR, 0xa07c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_BUFFER_HEADROOM_SIZE =
{
	2,
	{
		{ dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE, 0xa07e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION =
{
	2,
	{
		{ dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION, 0xa080 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_FAST_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_RX_FAST_INGRESS_QUEUE_PTR, 0xa082 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR =
{
	2,
	{
		{ dump_RDD_PARALLEL_PROCESSING_IH_BUFFER_PTR, 0xa084 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_ANY_SRC_PORT_FLOW_COUNTER =
{
	2,
	{
		{ dump_RDD_ANY_SRC_PORT_FLOW_COUNTER, 0xa086 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GSO_DESC_PTR =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa088 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_TX_POST_HOST_DATA_PTR_BUFFER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa08c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GSO_TX_DHD_HOST_BUF_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa090 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_TIMER_7_SCHEDULER_NEXT_ENTRY =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa094 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_MEMLIB_SEMAPHORE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa096 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_DHD_HOST_BUF_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa098 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_PHYSICAL_PORT =
{
	2,
	{
		{ dump_RDD_WAN_PHYSICAL_PORT, 0xa09c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa09e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RUNNER_CONGESTION_STATE =
{
	2,
	{
		{ dump_RDD_RUNNER_CONGESTION_STATE_ENTRY, 0xa0a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xa0a2 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GSO_PICO_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa0a4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_COMPLETE_BPM_REF_COUNTER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa0a6 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_POST_CPU_BPM_REF_COUNTER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa0a8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_BPM_CONGESTION_UG3_DROP_COUNTER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa0aa },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_BPM_CONGESTION_ALLOC_FAIL_DROP_COUNTER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xa0ac },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT PRIVATE_A_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_DUMMY_STORE_ENTRY, 0xa0ae },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH_TX_INTER_LAN_SCHEDULING_OFFSET =
{
	1,
	{
		{ dump_RDD_ETH_TX_INTER_LAN_SCHEDULING_OFFSET_ENTRY, 0xa0af },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b1 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_DS_PICO_SEMAPHORE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b2 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FC_GLOBAL_CFG =
{
	1,
	{
		{ dump_RDD_FC_GLOBAL_CFG_ENTRY, 0xa0b3 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b5 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PACKET_BUFFER_SIZE_ASR_8 =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b6 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_MAIN_DMA_SYNCRONIZATION_ADDRESS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b7 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_DMA_SYNCRONIZATION_ADDRESS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RUNNER_FLOW_IH_RESPONSE_MUTEX =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0b9 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_SLAVE_VECTOR =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_SLAVE_VECTOR, 0xa0ba },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0bb },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_IH_CONGESTION_THRESHOLD =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0bc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FAST_MALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xa0bd },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_PICO_MALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xa0be },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RX_SBPM_TO_FPM_COPY_SEMAPHORE =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xa0bf },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_FW_MAC_ADDRS_COUNT =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_DMA_SYNCHRONIZATION =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0c1 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_POST_CPU_SEMAPHORE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0c2 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RING_CACHE_DHD_TXPOST_MUTEX =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0c3 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT COMMON_DHD_TXPOST_MUTEX =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0c4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT TXCPL_INT_DHD_TXPOST_MUTEX =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa0c5 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_FAST_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0xac00 },
#if defined WL4908
		{ dump_RDD_CPU_TX_DESCRIPTOR_BPM, 0xac00 },
#endif
		{ dump_RDD_CPU_TX_DESCRIPTOR_ABS, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_FAST, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_US_FAST, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO_WIFI, 0xac00 },
		{ dump_RDD_CPU_TX_MESSAGE_DESCRIPTOR, 0xac00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_PICO_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0xad00 },
#if defined WL4908
		{ dump_RDD_CPU_TX_DESCRIPTOR_BPM, 0xad00 },
#endif
		{ dump_RDD_CPU_TX_DESCRIPTOR_ABS, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_FAST, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_US_FAST, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO_WIFI, 0xad00 },
		{ dump_RDD_CPU_TX_MESSAGE_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_DHD_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_DHD_MESSAGE_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_UPDATE_PD_POOL_QUOTA_MESSAGE_DESCRIPTOR, 0xad00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT EMAC_ABSOLUTE_TX_BBH_COUNTER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xb2c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR =
{
	10,
	{
		{ dump_RDD_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR_ENTRY, 0xb310 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GPON_RX_DIRECT_DESCRIPTORS =
{
#if defined WL4908
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0xb400 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FLOW_IH_RESPONSE =
{
	8,
	{
		{ dump_RDD_RUNNER_FLOW_IH_RESPONSE, 0xb6f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH_TX_MAC_TABLE =
{
	32,
	{
		{ dump_RDD_ETH_TX_MAC_DESCRIPTOR, 0xbb00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GPON_RX_NORMAL_DESCRIPTORS =
{
#if defined WL4908
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0xbe00 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_HANDLER_BUFFER =
{
	256,
	{
		{ dump_RDD_IH_BUFFER, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CSO_CHUNK_BUFFER =
{
	128,
	{
		{ dump_RDD_CSO_BUFFER_ENTRY, 0x2000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CSO_PSEUDO_HEADER_BUFFER =
{
	40,
	{
		{ dump_RDD_CSO_PSEUDO_HEADER_BUFFER_ENTRY, 0x2080 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_TIMER_7_SCHEDULER_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x20a8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RATE_CONTROL_BUDGET_ALLOCATOR_TABLE =
{
	2,
	{
		{ dump_RDD_BUDGET_ALLOCATOR_ENTRY, 0x20b0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_REASON_TO_METER_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_METER_ENTRY, 0x20c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_MAIN_PROFILING_BUFFER_RUNNER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x2100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FREE_PACKET_DESCRIPTORS_POOL =
{
	8,
	{
		{ dump_RDD_PACKET_DESCRIPTOR, 0x2200 },
#if defined WL4908
		{ dump_RDD_BBH_TX_DESCRIPTOR, 0x2200 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_FILTERS_LOOKUP_TABLE =
{
	4,
	{
		{ dump_RDD_INGRESS_FILTERS_LOOKUP_ENTRY, 0x8200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_TRAFFIC_CLASS_TO_QUEUE_TABLE =
{
	1,
	{
		{ dump_RDD_US_QUEUE_ENTRY, 0x83c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_CHANNELS_8_39_TABLE =
{
	32,
	{
		{ dump_RDD_WAN_CHANNEL_8_39_DESCRIPTOR, 0x8400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RUNNER_FLOW_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_RUNNER_FLOW_HEADER_BUFFER, 0x8800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_SBPM_REPLY =
{
	128,
	{
		{ dump_RDD_SBPM_REPLY_ENTRY, 0x8980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_POLICER_TABLE =
{
	16,
	{
		{ dump_RDD_POLICER_ENTRY, 0x8a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_TX_SERVICE_QUEUE_SCHEDULER_TABLE =
{
	128,
	{
		{ dump_RDD_WAN_TX_SERVICE_QUEUE_SCHEDULER_DESCRIPTOR, 0x8b00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_WAN_FLOW_TABLE =
{
	4,
	{
		{ dump_RDD_US_WAN_FLOW_ENTRY, 0x8c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_TX_BBH_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_CPU_TX_BBH_DESCRIPTORS_ENTRY, 0x9000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FORWARDING_MATRIX_TABLE =
{
	1,
	{
		{ dump_RDD_FORWARDING_MATRIX_ENTRY, 0x9100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_TIMER_SCHEDULER_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TIMER_SCHEDULER_PRIMITIVE_ENTRY, 0x9190 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_MAIN_TIMER_TASK_DESCRIPTOR_TABLE =
{
	8,
	{
		{ dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY, 0x91a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x91c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_RX_PICO_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9240 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9280 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_TIMER_TASK_DESCRIPTOR_TABLE =
{
	8,
	{
		{ dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY, 0x92c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FC_L2_UCAST_TUPLE_BUFFER =
{
	32,
	{
		{ dump_RDD_FC_L2_UCAST_TUPLE_ENTRY, 0x92e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RATE_LIMITER_TABLE =
{
	8,
	{
		{ dump_RDD_RATE_LIMITER_ENTRY, 0x9300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_QUEUE_PROFILE_TABLE =
{
	16,
	{
		{ dump_RDD_QUEUE_PROFILE, 0x9380 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CONNECTION_CONTEXT_BUFFER =
{
	128,
	{
		{ dump_RDD_CONNECTION_CONTEXT_BUFFER_ENTRY, 0x9400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_CONTEXT_TABLE =
{
	8,
	{
		{ dump_RDD_US_INGRESS_CLASSIFICATION_CONTEXT_ENTRY, 0x9800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_CHANNELS_0_7_TABLE =
{
	88,
	{
		{ dump_RDD_WAN_CHANNEL_0_7_DESCRIPTOR, 0xa000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE =
{
	8,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_ENTRY, 0xa2c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FAST_RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_FAST_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY, 0xa2e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_RX_METER_TABLE =
{
	8,
	{
		{ dump_RDD_CPU_RX_METER_ENTRY, 0xa300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_HANDLER_SKB_DATA_POINTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa380 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CONNECTION_CONTEXT_REMAINING_BUFFER =
{
#if defined WL4908
	76,
	{
		{ dump_RDD_CONTEXT_CONTINUATION_ENTRY, 0xa400 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_PICO_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY, 0xa660 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_GRE_RUNNER_FLOW_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_GRE_RUNNER_FLOW_HEADER_BUFFER, 0xa680 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PROFILING_BUFFER_PICO_RUNNER =
{
	256,
	{
		{ dump_RDD_PROFILING_BUFFER_PICO_RUNNER, 0xa700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_RULE_CFG_TABLE =
{
	8,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_RULE_CFG_ENTRY, 0xa800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_FILTERS_PARAMETER_TABLE =
{
	1,
	{
		{ dump_RDD_INGRESS_FILTERS_PARAMETER_ENTRY, 0xa880 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FC_L2_UCAST_CONNECTION_BUFFER =
{
	16,
	{
		{ dump_RDD_FC_L2_UCAST_CONNECTION_ENTRY, 0xa8f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_RX_COMPLETE_FLOW_RING_BUFFER =
{
	32,
	{
		{ dump_RDD_DHD_RX_POST_DESCRIPTOR, 0xa900 },
		{ dump_RDD_DHD_RX_COMPLETE_DESCRIPTOR, 0xa900 },
		{ dump_RDD_DHD_RX_POST_DESCRIPTOR_CWI32, 0xa900 },
		{ dump_RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32, 0xa900 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_RX_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xa960 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETHWAN_ABSOLUTE_TX_BBH_COUNTER =
{
	1,
	{
		{ dump_RDD_GPON_ABSOLUTE_TX_COUNTER, 0xa980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT PRIVATE_B_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_DUMMY_STORE_ENTRY, 0xa981 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_MAIN_TIMER_CONTROL_DESCRIPTOR =
{
	2,
	{
		{ dump_RDD_TIMER_CONTROL_DESCRIPTOR, 0xa982 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_ETH0_EEE_MODE_CONFIG_MESSAGE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa984 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETHWAN_ABSOLUTE_TX_FIRMWARE_COUNTER =
{
	1,
	{
		{ dump_RDD_GPON_ABSOLUTE_TX_COUNTER, 0xa988 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa989 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_TIMER_CONTROL_DESCRIPTOR =
{
	2,
	{
		{ dump_RDD_TIMER_CONTROL_DESCRIPTOR, 0xa98a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BPM_EXTRA_DDR_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa98c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GPON_ABSOLUTE_TX_BBH_COUNTER =
{
	1,
	{
		{ dump_RDD_GPON_ABSOLUTE_TX_COUNTER, 0xa990 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_TOTAL_PPS_RATE_LIMITER =
{
	8,
	{
		{ dump_RDD_TOTAL_PPS_RATE_LIMITER_ENTRY, 0xa9b8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_TX_MESSAGE_DATA_BUFFER =
{
	64,
	{
		{ dump_RDD_CPU_TX_MESSAGE_DATA_BUFFER_ENTRY, 0xa9c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_RX_POST_FLOW_RING_BUFFER =
{
	32,
	{
		{ dump_RDD_DHD_RX_POST_DESCRIPTOR, 0xaa00 },
		{ dump_RDD_DHD_RX_COMPLETE_DESCRIPTOR, 0xaa00 },
		{ dump_RDD_DHD_RX_POST_DESCRIPTOR_CWI32, 0xaa00 },
		{ dump_RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32, 0xaa00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_0_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xaa60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_RATE_LIMITER_TABLE =
{
	16,
	{
		{ dump_RDD_INGRESS_RATE_LIMITER_ENTRY, 0xaa80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINB_PARAM =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xaad0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_0_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xaae0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_SPDSVC_CONTEXT_TABLE =
{
	80,
	{
		{ dump_RDD_SPDSVC_CONTEXT_ENTRY, 0xab00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_PICOB_PARAM =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xab50 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_1_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xab60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_ROUTER_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0xab80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_1_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xabc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_2_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xabe0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_TX_FAST_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0xac00 },
#if defined WL4908
		{ dump_RDD_CPU_TX_DESCRIPTOR_BPM, 0xac00 },
#endif
		{ dump_RDD_CPU_TX_DESCRIPTOR_ABS, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_FAST, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_US_FAST, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO_WIFI, 0xac00 },
		{ dump_RDD_CPU_TX_MESSAGE_DESCRIPTOR, 0xac00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_RX_FAST_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0xac80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_2_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xacc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_TX_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xace0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_TX_PICO_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0xad00 },
#if defined WL4908
		{ dump_RDD_CPU_TX_DESCRIPTOR_BPM, 0xad00 },
#endif
		{ dump_RDD_CPU_TX_DESCRIPTOR_ABS, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_FAST, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_US_FAST, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO_WIFI, 0xad00 },
		{ dump_RDD_CPU_TX_MESSAGE_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_DHD_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_DHD_MESSAGE_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_UPDATE_PD_POOL_QUOTA_MESSAGE_DESCRIPTOR, 0xad00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DEBUG_BUFFER =
{
	4,
	{
		{ dump_RDD_DEBUG_BUFFER_ENTRY, 0xad80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FW_MAC_ADDRS =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xae00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_TX_POST_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0xae80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_TABLE =
{
	2,
	{
		{ dump_RDD_US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_ENTRY, 0xaec0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_FILTERS_CONFIGURATION_TABLE =
{
	4,
	{
		{ dump_RDD_INGRESS_FILTERS_CONFIGURATION_ENTRY, 0xaf20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_OPTIMIZED_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xaf3c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_TX_POST_HEADER_SCRATCH =
{
	32,
	{
		{ dump_RDD_DHD_L2_HEADER_BUFFER_ENTRY, 0xaf40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RUNNER_FLOW_HEADER_DESCRIPTOR =
{
	8,
	{
		{ dump_RDD_RUNNER_FLOW_HEADER_DESCRIPTOR, 0xaf60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_ONE_BUFFER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xaf78 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CSO_CONTEXT_TABLE =
{
	84,
	{
		{ dump_RDD_CSO_CONTEXT_ENTRY, 0xaf80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xafd4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_GPE_COMMAND_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_GPE_COMMAND_PRIMITIVE_ENTRY, 0xafd8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_NULL_BUFFER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xb018 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_PARAMETERS_BLOCK =
{
	20,
	{
		{ dump_RDD_CPU_PARAMETERS_BLOCK_ENTRY, 0xb020 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb034 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FAST_MALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xb038 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_TX_POST_FLOW_RING_BUFFER =
{
	48,
	{
		{ dump_RDD_DHD_TX_POST_DESCRIPTOR, 0xb040 },
		{ dump_RDD_DHD_TX_POST_DESCRIPTOR_CWI32, 0xb040 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GPON_ABSOLUTE_TX_FIRMWARE_COUNTER =
{
	1,
	{
		{ dump_RDD_GPON_ABSOLUTE_TX_COUNTER, 0xb070 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_MALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xb098 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE =
{
	2,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY, 0xb0a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb0b0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_FLOW_RING_DROP_COUNTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb0c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_1_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb0d4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BUF_SIZE_TO_TOKEN_COUNT_LOG2_TABLE =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb0d8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE =
{
	2,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY, 0xb0e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE =
{
	1,
	{
		{ dump_RDD_BROADCOM_SWITCH_PORT_MAPPING, 0xb0f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_SYSTEM_CONFIGURATION =
{
	36,
	{
		{ dump_RDD_SYSTEM_CONFIGURATION, 0xb100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CONNECTION_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_CONNECTION_TABLE_CONFIG, 0xb124 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_TABLE =
{
	1,
	{
		{ dump_RDD_US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_ENTRY, 0xb128 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_TX_SCRATCH =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb148 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_REASON_AND_SRC_BRIDGE_PORT_TO_METER_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_METER_ENTRY, 0xb160 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_RX_PICO_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_RX_PICO_INGRESS_QUEUE_PTR, 0xb172 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CONTEXT_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_CONTEXT_TABLE_CONFIG, 0xb174 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR =
{
	6,
	{
		{ dump_RDD_US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR_ENTRY, 0xb178 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_BUFFER_HEADROOM_SIZE =
{
	2,
	{
		{ dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE, 0xb17e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT BROADCOM_SWITCH_PORT_TO_BRIDGE_PORT_MAPPING_TABLE =
{
	1,
	{
		{ dump_RDD_BROADCOM_SWITCH_PORT_MAPPING, 0xb180 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb189 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION =
{
	2,
	{
		{ dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION, 0xb18a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_ENTRY, 0xb18c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_KEY_BUFFER =
{
	16,
	{
		{ dump_RDD_SIXTEEN_BYTES, 0xb190 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_DS_EGRESS_DHD_TX_POST_CONTEXT =
{
	16,
	{
		{ dump_RDD_DHD_TX_POST_CONTEXT_ENTRY, 0xb1a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_DHD_LAYER2_HEADER_BUFFER =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb1b0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_RX_FAST_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_RX_FAST_INGRESS_QUEUE_PTR, 0xb1be },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DATA_POINTER_DUMMY_TARGET =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb1c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_TASK_REORDER_FIFO =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_TASK_REORDER_ENTRY, 0xb1c8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DEBUG_PERIPHERALS_STATUS_REGISTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb1cc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb1d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT IH_BUFFER_BBH_POINTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb1d8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CONTEXT_CONTINUATION_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb1dc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_TX_POST_DOORBELL_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb1e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_TX_DATA_POINTER_DUMMY_TARGET =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb1e4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RATE_CONTROLLER_EXPONENT_TABLE =
{
	1,
	{
		{ dump_RDD_RATE_CONTROLLER_EXPONENT_ENTRY, 0xb1e8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 0xb1ec },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 0xb1ee },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR =
{
	2,
	{
		{ dump_RDD_PARALLEL_PROCESSING_IH_BUFFER_PTR, 0xb1f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_ANY_SRC_PORT_FLOW_COUNTER =
{
	2,
	{
		{ dump_RDD_ANY_SRC_PORT_FLOW_COUNTER, 0xb1f2 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_TX_POST_HOST_DATA_PTR_BUFFER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb1f4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_TIMER_7_SCHEDULER_NEXT_ENTRY =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb1f8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_MEMLIB_SEMAPHORE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb1fa },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETHWAN2_RX_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb1fc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RUNNER_CONGESTION_STATE =
{
	2,
	{
		{ dump_RDD_RUNNER_CONGESTION_STATE_ENTRY, 0xb1fe },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_ENQUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_WAN_ENQUEUE_INGRESS_QUEUE_PTR_ENTRY, 0xb200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xb202 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_BPM_CONGESTION_UG3_DROP_COUNTER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb204 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_BPM_CONGESTION_ALLOC_FAIL_DROP_COUNTER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb206 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FC_GLOBAL_CFG =
{
	1,
	{
		{ dump_RDD_FC_GLOBAL_CFG_ENTRY, 0xb208 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETHWAN2_SWITCH_PORT =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb209 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb20a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb20b },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PACKET_BUFFER_SIZE_ASR_8 =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb20c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_MAIN_DMA_SYNCRONIZATION_ADDRESS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb20d },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_DMA_SYNCRONIZATION_ADDRESS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb20e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RUNNER_FLOW_IH_RESPONSE_MUTEX =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb20f },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DSL_BUFFER_ALIGNMENT =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb210 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_SLAVE_VECTOR =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_SLAVE_VECTOR, 0xb211 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb212 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_IH_CONGESTION_THRESHOLD =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb213 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FAST_MALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb214 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_PICO_MALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb215 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_RX_FPM_ALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb216 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RX_SBPM_TO_FPM_COPY_SEMAPHORE =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb217 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_FW_MAC_ADDRS_COUNT =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb218 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_DMA_SYNCHRONIZATION =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb219 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RUNNER_FLOW_IH_RESPONSE =
{
	8,
	{
		{ dump_RDD_RUNNER_FLOW_IH_RESPONSE, 0xb6f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH2_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xba00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH1_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xbc00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETH0_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xbe00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT BBH_TX_WAN_CHANNEL_INDEX =
{
	4,
	{
		{ dump_RDD_BBH_TX_WAN_CHANNEL_INDEX, 0xbfe8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT FC_MCAST_RUNNER_A_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_DDR_CACHE_FIFO =
{
	16,
	{
		{ dump_RDD_SIXTEEN_BYTES, 0x2000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_RX_RUNNER_A_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x3000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MAC_TABLE =
{
	8,
	{
		{ dump_RDD_MAC_ENTRY, 0x3800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_COUNTERS_TABLE =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0x3a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_DESCRIPTOR_TABLE =
{
	16,
	{
		{ dump_RDD_DDR_QUEUE_DESCRIPTOR, 0x3c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MAC_TABLE_CAM =
{
	8,
	{
		{ dump_RDD_MAC_ENTRY, 0x3e00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT TRACE_C_TABLE =
{
	8,
	{
		{ dump_RDD_TRACE_C_ENTRY, 0x3f00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINA_CURR_OFFSET =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x3f20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x3f30 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE_LAST_ENTRY =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x3f34 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT FREE_SKB_INDEXES_DDR_FIFO_TAIL =
{
	4,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_TAIL, 0x3f38 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT BPM_REPLY_RUNNER_A =
{
	48,
	{
		{ dump_RDD_BPM_REPLY, 0x3f40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_BACKUP_ENTRY_SCRATCH =
{
	16,
	{
		{ dump_RDD_DHD_BACKUP_ENTRY, 0x3f70 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_REASON_TO_CPU_RX_QUEUE_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_CPU_RX_QUEUE_ENTRY, 0x3f80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GPON_SKB_ENQUEUED_INDEXES_FIFO =
{
	48,
	{
		{ dump_RDD_GPON_SKB_ENQUEUED_INDEXES_FIFO_ENTRY, 0x4000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_BUFFER_TABLE =
{
	16,
	{
		{ dump_RDD_CONNECTION_ENTRY, 0x4600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT INTERRUPT_COALESCING_CONFIG_TABLE =
{
	4,
	{
		{ dump_RDD_INTERRUPT_COALESCING_CONFIG, 0x4740 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MAC_CONTEXT_TABLE =
{
	2,
	{
		{ dump_RDD_MAC_CONTEXT_ENTRY, 0x4780 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x4800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE =
{
	16,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_LONG_LOOKUP_ENTRY, 0x5000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT PM_COUNTERS =
{
	6144,
	{
		{ dump_RDD_PM_COUNTERS, 0x5800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT ETHWAN2_RX_INGRESS_QUEUE =
{
#if defined WL4908
	8,
	{
		{ dump_RDD_ETHWAN2_RX_DESCRIPTOR, 0x7000 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x7100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RING_PACKET_DESCRIPTORS_CACHE =
{
	16,
	{
		{ dump_RDD_CPU_RX_DESCRIPTOR, 0x7200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_DDR_QUEUE_ADDRESS_TABLE =
{
	8,
	{
		{ dump_RDD_DDR_QUEUE_ADDRESS_ENTRY, 0x7300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_POST_REQUEST_QUEUE =
{
	16,
	{
		{ dump_RDD_DHD_BACKUP_ENTRY, 0x7400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_RADIO_INSTANCE_COMMON_A_DATA =
{
	32,
	{
		{ dump_RDD_DHD_RADIO_INSTANCE_COMMON_A_ENTRY, 0x7480 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_FLOW_RING_CACHE_LKP_TABLE =
{
	2,
	{
		{ dump_RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY, 0x74e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RING_DESCRIPTORS_TABLE =
{
	16,
	{
		{ dump_RDD_RING_DESCRIPTOR, 0x7500 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RATE_SHAPERS_STATUS_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x7600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MAC_CONTEXT_TABLE_CAM =
{
	2,
	{
		{ dump_RDD_MAC_CONTEXT_ENTRY, 0x7680 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_DOORBELL_WRITE_VALUES =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x76c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_BACKUP_INDEX_CACHE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MAC_EXTENSION_TABLE =
{
	1,
	{
		{ dump_RDD_MAC_EXTENSION_ENTRY, 0x7740 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_FLOW_RING_SHADOW_WR_PTR_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7780 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_BUFFER =
{
	20,
	{
		{ dump_RDD_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR, 0x77a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DDR_ADDRESS_FOR_SKB_DATA_POINTERS_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x77b4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_DHD_BACKUP_FLUSH_SCRATCH =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x77b8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_CFG =
{
	20,
	{
		{ dump_RDD_SERVICE_QUEUES_CFG_ENTRY, 0x77c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_POST_REQUEST_QUEUE_IDX =
{
	4,
	{
		{ dump_RDD_CPU_TX_POST_REQUEST_QUEUE_IDX_ENTRY, 0x77d4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MAC_EXTENSION_TABLE_CAM =
{
	1,
	{
		{ dump_RDD_MAC_EXTENSION_ENTRY, 0x77d8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CAM_DHD_DMA_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x77f8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_ENQ_DHD_DMA_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x77fc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT PM_COUNTERS_BUFFER =
{
	32,
	{
		{ dump_RDD_PM_COUNTERS_BUFFER, 0x7800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_R2D_DHD_DMA_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x7820 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_POST_BUFFERS_THRESHOLD =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7830 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_CPU_DHD_DMA_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x783c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT TX_CPL_DHD_DMA_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x7840 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINA_BASE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x784c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_PICOA_BASE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x784e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_RATE_CONTROLLER_EXPONENT_TABLE =
{
	1,
	{
		{ dump_RDD_RATE_CONTROLLER_EXPONENT_ENTRY, 0x7850 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT TIMER_7_TIMER_PERIOD =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7854 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT INTERRUPT_COALESCING_TIMER_PERIOD =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7856 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_POST_BUFFERS_IN_USE_COUNTER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7858 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT INTERRUPT_COALESCING_TIMER_ARMED =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x785c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT COMMON_A_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_DUMMY_STORE_ENTRY, 0x785e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT FC_SERVICE_QUEUE_MODE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x785f },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MAIN_A_DEBUG_TRACE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x7a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT PICO_A_DEBUG_TRACE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x7c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE =
{
	16,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_LONG_LOOKUP_ENTRY, 0x8000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_RX_RUNNER_B_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x8800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_COUNTERS_TABLE =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0x9000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE =
{
#if defined WL4908
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0x9200 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE =
{
	8,
	{
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY, 0x9300 },
		{ dump_RDD_US_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY, 0x9300 },
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY, 0x9300 },
		{ dump_RDD_US_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY, 0x9300 },
		{ dump_RDD_INGRESS_CLASSIFICATION_SHORT_LOOKUP_ENTRY, 0x9300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_TX_SERVICE_QUEUES_TABLE =
{
	32,
	{
		{ dump_RDD_WAN_TX_SERVICE_QUEUE_DESCRIPTOR, 0x9400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE =
{
	8,
	{
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY, 0x9c00 },
		{ dump_RDD_US_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY, 0x9c00 },
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY, 0x9c00 },
		{ dump_RDD_US_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY, 0x9c00 },
		{ dump_RDD_INGRESS_CLASSIFICATION_SHORT_LOOKUP_ENTRY, 0x9c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_TX_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x9d00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CONNECTION_BUFFER_TABLE =
{
	16,
	{
		{ dump_RDD_CONNECTION_ENTRY, 0x9e00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT IPV6_HOST_ADDRESS_CRC_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_BACKUP_INFO_CACHE_TABLE =
{
	8,
	{
		{ dump_RDD_DHD_BACKUP_INFO_CACHE_ENTRY, 0x9f80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_LOOKUP_TABLE =
{
	8,
	{
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY, 0xa000 },
		{ dump_RDD_US_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY, 0xa000 },
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY, 0xa000 },
		{ dump_RDD_US_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY, 0xa000 },
		{ dump_RDD_INGRESS_CLASSIFICATION_SHORT_LOOKUP_ENTRY, 0xa000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_LOOKUP_TABLE =
{
	8,
	{
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY, 0xa800 },
		{ dump_RDD_US_INGRESS_CLASSIFICATION_IH_LOOKUP_ENTRY, 0xa800 },
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY, 0xa800 },
		{ dump_RDD_US_INGRESS_CLASSIFICATION_OPTIMIZED_LOOKUP_ENTRY, 0xa800 },
		{ dump_RDD_INGRESS_CLASSIFICATION_SHORT_LOOKUP_ENTRY, 0xa800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_TX_QUEUES_TABLE =
{
	16,
	{
		{ dump_RDD_WAN_TX_QUEUE_DESCRIPTOR, 0xb000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_TX_RUNNER_B_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0xc000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RING_PACKET_DESCRIPTORS_CACHE =
{
	16,
	{
		{ dump_RDD_CPU_RX_DESCRIPTOR, 0xc100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_FLOW_RING_CACHE_CTX_TABLE =
{
	16,
	{
		{ dump_RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY, 0xc200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_RADIO_INSTANCE_COMMON_B_DATA =
{
	64,
	{
		{ dump_RDD_DHD_RADIO_INSTANCE_COMMON_B_ENTRY, 0xc300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DUMMY_RATE_CONTROLLER_DESCRIPTOR =
{
	64,
	{
		{ dump_RDD_DUMMY_RATE_CONTROLLER_DESCRIPTOR, 0xc3c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GPON_SKB_ENQUEUED_INDEXES_FREE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xc400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINB_CURR_OFFSET =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xc450 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT IPV4_HOST_ADDRESS_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xc460 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT GPON_SKB_ENQUEUED_INDEXES_PUT_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xc480 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CPU_REASON_TO_CPU_RX_QUEUE_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_CPU_RX_QUEUE_ENTRY, 0xc4d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DUMMY_WAN_TX_QUEUE_DESCRIPTOR =
{
	16,
	{
		{ dump_RDD_DUMMY_WAN_TX_QUEUE_DESCRIPTOR, 0xc550 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_FLOW_RING_CACHE_LKP_TABLE =
{
	2,
	{
		{ dump_RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY, 0xc560 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT PACKET_SRAM_TO_DDR_COPY_BUFFER_1 =
{
	128,
	{
		{ dump_RDD_PACKET_SRAM_TO_DDR_COPY_BUFFER, 0xc580 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT PACKET_SRAM_TO_DDR_COPY_BUFFER_2 =
{
	128,
	{
		{ dump_RDD_PACKET_SRAM_TO_DDR_COPY_BUFFER, 0xc600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN0_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc680 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN5_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc6c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT FC_FLOW_IP_ADDRESSES_TABLE =
{
	48,
	{
		{ dump_RDD_FC_FLOW_IP_ADDRESSES_ENTRY, 0xc700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_BACKUP_ENTRY_SCRATCH =
{
	16,
	{
		{ dump_RDD_DHD_BACKUP_ENTRY, 0xc7c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT BPM_REPLY_RUNNER_B =
{
	48,
	{
		{ dump_RDD_BPM_REPLY, 0xc7d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RATE_CONTROLLERS_TABLE =
{
	48,
	{
		{ dump_RDD_US_RATE_CONTROLLER_DESCRIPTOR, 0xc800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0xe000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN1_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xe800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN6_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xe840 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN2_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xe880 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN7_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xe8c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN3_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xe900 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_BACKUP_INDEX_CACHE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xe940 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT LAN4_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xe980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_DOORBELL_COUNTERS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xe9c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_BACKUP_QUEUE_MANAGEMENT_INFO =
{
	16,
	{
		{ dump_RDD_DHD_BACKUP_QUEUE_MANAGEMENT_INFO_ENTRY, 0xe9f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT MAIN_B_DEBUG_TRACE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xea00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT PICO_B_DEBUG_TRACE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xec00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT WAN_ENQUEUE_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0xee00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_BUFFER =
{
	20,
	{
		{ dump_RDD_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR, 0xee40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_CAM_DHD_DMA_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xee54 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_DHD_BACKUP_FLUSH_SCRATCH =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xee58 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_ENQ_DHD_DMA_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xee60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT US_R2D_DHD_DMA_SCRATCH =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xee64 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CPU_TX_DESCRIPTOR_QUEUE_TAIL_TABLE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xee68 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINB_BASE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xee6c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_PICOB_BASE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xee6e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT COMMON_B_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_DUMMY_STORE_ENTRY, 0xee70 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_FLOW_RING_CACHE_CTX_NEXT_INDEX =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xee71 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT BPM_PACKET_BUFFERS =
{
	2048,
	{
		{ dump_RDD_BPM_PACKET_BUFFER, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CONTEXT_TABLE =
{
	132,
	{
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_ENTRY, 0x0 },
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY, 0x0 },
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY, 0x0 },
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY, 0x0 },
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY, 0x0 },
		{ dump_RDD_FC_L2_UCAST_FLOW_CONTEXT_ENTRY, 0x0 },
		{ dump_RDD_FC_MCAST_FLOW_CONTEXT_ENTRY, 0x0 },
		{ dump_RDD_FC_MCAST_MASTER_FLOW_CONTEXT_ENTRY, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT NAT_CACHE_TABLE =
{
	16,
	{
		{ dump_RDD_NAT_CACHE_LKP_ENTRY, 0x0 },
		{ dump_RDD_NAT_CACHE_MCAST_LKP_ENTRY, 0x0 },
		{ dump_RDD_NAT_CACHE_L2_LKP_ENTRY, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT NAT_CACHE_EXTENSION_TABLE =
{
	16,
	{
		{ dump_RDD_NAT_CACHE_LKP_ENTRY, 0x0 },
		{ dump_RDD_NAT_CACHE_MCAST_LKP_ENTRY, 0x0 },
		{ dump_RDD_NAT_CACHE_L2_LKP_ENTRY, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT NATC_CONTEXT_TABLE =
{
	64,
	{
		{ dump_RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY, 0x0 },
		{ dump_RDD_FC_NATC_L2_UCAST_FLOW_CONTEXT_ENTRY, 0x0 },
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY, 0x0 },
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY, 0x0 },
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY, 0x0 },
		{ dump_RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY, 0x0 },
		{ dump_RDD_FC_NATC_MCAST_FLOW_CONTEXT_ENTRY, 0x0 },
		{ dump_RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT CONTEXT_CONTINUATION_TABLE =
{
#if defined WL4908
	76,
	{
		{ dump_RDD_CONTEXT_CONTINUATION_ENTRY, 0x0 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_TABLE =
{
	20,
	{
		{ dump_RDD_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR, 0x5d1500 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_RX_POST_DDR_BUFFER =
{
	32,
	{
		{ dump_RDD_DHD_RX_POST_DESCRIPTOR, 0x5c1100 },
		{ dump_RDD_DHD_RX_POST_DESCRIPTOR_CWI32, 0x5c1100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_RX_COMPLETE_DDR_BUFFER =
{
	32,
	{
		{ dump_RDD_DHD_RX_COMPLETE_DESCRIPTOR, 0x5c9100 },
		{ dump_RDD_DHD_RX_COMPLETE_DESCRIPTOR_CWI32, 0x5c9100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_POST_DDR_BUFFER =
{
	48,
	{
		{ dump_RDD_DHD_TX_POST_DESCRIPTOR, 0x5d15a0 },
		{ dump_RDD_DHD_TX_POST_DESCRIPTOR_CWI32, 0x5d15a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_TX_COMPLETE_DDR_BUFFER =
{
	16,
	{
		{ dump_RDD_DHD_TX_COMPLETE_DESCRIPTOR, 0x5d2da0 },
		{ dump_RDD_DHD_TX_COMPLETE_DESCRIPTOR_CWI32, 0x5d2da0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT R2D_WR_ARR_DDR_BUFFER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x5d1100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT D2R_RD_ARR_DDR_BUFFER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x5d1200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT R2D_RD_ARR_DDR_BUFFER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x5d1300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT D2R_WR_ARR_DDR_BUFFER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x5d1400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908
static DUMP_RUNNERREG_STRUCT DHD_BACKUP_QUEUES_BUFFER =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x600000 },
		{ 0, 0 },
	}
};
#endif

TABLE_STRUCT RUNNER_TABLES[NUMBER_OF_TABLES] =
{
#if defined WL4908
	{ "INGRESS_HANDLER_BUFFER", 1, PRIVATE_A_INDEX, &INGRESS_HANDLER_BUFFER, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FREE_PACKET_DESCRIPTORS_POOL", 1, PRIVATE_A_INDEX, &DS_FREE_PACKET_DESCRIPTORS_POOL, 2048, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CONNECTION_CONTEXT_BUFFER", 1, PRIVATE_A_INDEX, &DS_CONNECTION_CONTEXT_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_GSO_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &DS_GSO_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_GSO_PSEUDO_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &DS_GSO_PSEUDO_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_TIMER_7_SCHEDULER_PRIMITIVE_TABLE", 1, PRIVATE_A_INDEX, &DS_TIMER_7_SCHEDULER_PRIMITIVE_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RATE_SHAPER_BUDGET_ALLOCATOR_TABLE", 1, PRIVATE_A_INDEX, &DS_RATE_SHAPER_BUDGET_ALLOCATOR_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_REASON_TO_METER_TABLE", 1, PRIVATE_A_INDEX, &DS_CPU_REASON_TO_METER_TABLE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_GSO_CHUNK_BUFFER", 1, PRIVATE_A_INDEX, &DS_GSO_CHUNK_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_RX_METER_TABLE", 1, PRIVATE_A_INDEX, &DS_CPU_RX_METER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_WAN_FLOW_TABLE", 1, PRIVATE_A_INDEX, &DS_WAN_FLOW_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_CONTEXT_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_CONTEXT_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CONNECTION_CONTEXT_REMAINING_BUFFER", 1, PRIVATE_A_INDEX, &DS_CONNECTION_CONTEXT_REMAINING_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908
	{ "SERVICE_QUEUES_RATE_LIMITER_TABLE", 1, PRIVATE_A_INDEX, &SERVICE_QUEUES_RATE_LIMITER_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_MAIN_TIMER_TASK_DESCRIPTOR_TABLE", 1, PRIVATE_A_INDEX, &DS_MAIN_TIMER_TASK_DESCRIPTOR_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_SPDSVC_CONTEXT_TABLE", 1, PRIVATE_A_INDEX, &DS_SPDSVC_CONTEXT_TABLE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_TIMER_SCHEDULER_PRIMITIVE_TABLE", 1, PRIVATE_A_INDEX, &DS_TIMER_SCHEDULER_PRIMITIVE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_MAIN_PROFILING_BUFFER_RUNNER", 1, PRIVATE_A_INDEX, &DS_MAIN_PROFILING_BUFFER_RUNNER, 32, 1, 1 },
#endif
#if defined WL4908
	{ "ETH_TX_QUEUES_TABLE", 1, PRIVATE_A_INDEX, &ETH_TX_QUEUES_TABLE, 72, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_TIMER_TASK_DESCRIPTOR_TABLE", 1, PRIVATE_A_INDEX, &DS_PICO_TIMER_TASK_DESCRIPTOR_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_FILTERS_LOOKUP_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_FILTERS_LOOKUP_TABLE, 2, 16, 1 },
#endif
#if defined WL4908
	{ "DS_WAN_UDP_FILTER_TABLE", 1, PRIVATE_A_INDEX, &DS_WAN_UDP_FILTER_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "FC_MCAST_PORT_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &FC_MCAST_PORT_HEADER_BUFFER, 8, 64, 1 },
#endif
#if defined WL4908
	{ "DOWNSTREAM_LAN_ENQUEUE_SQ_PD", 1, PRIVATE_A_INDEX, &DOWNSTREAM_LAN_ENQUEUE_SQ_PD, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CONNECTION_CONTEXT_MULTICAST_BUFFER", 1, PRIVATE_A_INDEX, &DS_CONNECTION_CONTEXT_MULTICAST_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_RX_SQ_PD_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &CPU_RX_SQ_PD_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FC_MCAST_PACKET_SAVE_DATA_TABLE", 1, PRIVATE_A_INDEX, &DS_FC_MCAST_PACKET_SAVE_DATA_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_FILTERS_PARAMETER_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_FILTERS_PARAMETER_TABLE, 2, 16, 1 },
#endif
#if defined WL4908
	{ "INGRESS_HANDLER_SKB_DATA_POINTER", 1, PRIVATE_A_INDEX, &INGRESS_HANDLER_SKB_DATA_POINTER, 32, 1, 1 },
#endif
#if defined WL4908
	{ "ETH_TX_QUEUES_POINTERS_TABLE", 1, PRIVATE_A_INDEX, &ETH_TX_QUEUES_POINTERS_TABLE, 72, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FC_L2_UCAST_TUPLE_BUFFER", 1, PRIVATE_A_INDEX, &DS_FC_L2_UCAST_TUPLE_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "RATE_LIMITER_REMAINDER_TABLE", 1, PRIVATE_A_INDEX, &RATE_LIMITER_REMAINDER_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "SBPM_REPLY", 1, PRIVATE_A_INDEX, &SBPM_REPLY, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_POLICER_TABLE", 1, PRIVATE_A_INDEX, &DS_POLICER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FORWARDING_MATRIX_TABLE", 1, PRIVATE_A_INDEX, &DS_FORWARDING_MATRIX_TABLE, 9, 16, 1 },
#endif
#if defined WL4908
	{ "DS_FC_L2_UCAST_CONNECTION_BUFFER", 1, PRIVATE_A_INDEX, &DS_FC_L2_UCAST_CONNECTION_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "GSO_PICO_QUEUE", 1, PRIVATE_A_INDEX, &GSO_PICO_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_TX_BBH_DESCRIPTORS", 1, PRIVATE_A_INDEX, &DS_CPU_TX_BBH_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RUNNER_FLOW_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &DS_RUNNER_FLOW_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_GRE_RUNNER_FLOW_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &DS_GRE_RUNNER_FLOW_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_POST_PD_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DHD_TX_POST_PD_INGRESS_QUEUE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PROFILING_BUFFER_PICO_RUNNER", 1, PRIVATE_A_INDEX, &DS_PROFILING_BUFFER_PICO_RUNNER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DOWNSTREAM_LAN_ENQUEUE_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DOWNSTREAM_LAN_ENQUEUE_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE", 1, PRIVATE_A_INDEX, &DS_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE", 1, PRIVATE_A_INDEX, &DS_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "LAN_TX_ACB_COUNTER_TABLE", 1, PRIVATE_A_INDEX, &LAN_TX_ACB_COUNTER_TABLE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RATE_LIMITER_TABLE", 1, PRIVATE_A_INDEX, &DS_RATE_LIMITER_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_TX_POST_FLOW_RING_BUFFER", 1, PRIVATE_A_INDEX, &DS_DHD_TX_POST_FLOW_RING_BUFFER, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_COMPLETE_FLOW_RING_BUFFER", 1, PRIVATE_A_INDEX, &DHD_TX_COMPLETE_FLOW_RING_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_MAINA_PARAM", 1, PRIVATE_A_INDEX, &RUNNER_FWTRACE_MAINA_PARAM, 2, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_RULE_CFG_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_RULE_CFG_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "ETH_TX_LOCAL_REGISTERS", 1, PRIVATE_A_INDEX, &ETH_TX_LOCAL_REGISTERS, 9, 1, 1 },
#endif
#if defined WL4908
	{ "DS_TOTAL_PPS_RATE_LIMITER", 1, PRIVATE_A_INDEX, &DS_TOTAL_PPS_RATE_LIMITER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_PICOA_PARAM", 1, PRIVATE_A_INDEX, &RUNNER_FWTRACE_PICOA_PARAM, 2, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FAST_RUNNER_GLOBAL_REGISTERS_INIT", 1, PRIVATE_A_INDEX, &DS_FAST_RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_QUEUE_PROFILE_TABLE", 1, PRIVATE_A_INDEX, &DS_QUEUE_PROFILE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE", 1, PRIVATE_A_INDEX, &DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_SQ_ENQUEUE_QUEUE", 1, PRIVATE_A_INDEX, &DS_SQ_ENQUEUE_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_COMPLETE_RING_DESCRIPTOR_BUFFER", 1, PRIVATE_A_INDEX, &DHD_COMPLETE_RING_DESCRIPTOR_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908
	{ "EMAC_SKB_ENQUEUED_INDEXES_PUT_PTR", 1, PRIVATE_A_INDEX, &EMAC_SKB_ENQUEUED_INDEXES_PUT_PTR, 8, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_RX_PD_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &CPU_RX_PD_INGRESS_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_RX_PICO_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DS_CPU_RX_PICO_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_TX_MESSAGE_DATA_BUFFER", 1, PRIVATE_A_INDEX, &DS_CPU_TX_MESSAGE_DATA_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_RX_FAST_PD_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &CPU_RX_FAST_PD_INGRESS_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_ROUTER_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DS_ROUTER_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_RUNNER_GLOBAL_REGISTERS_INIT", 1, PRIVATE_A_INDEX, &DS_PICO_RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_TX_POST_HEADER_SCRATCH", 1, PRIVATE_A_INDEX, &DS_DHD_TX_POST_HEADER_SCRATCH, 4, 1, 1 },
#endif
#if defined WL4908
	{ "EMAC_SKB_ENQUEUED_INDEXES_FIFO", 1, PRIVATE_A_INDEX, &EMAC_SKB_ENQUEUED_INDEXES_FIFO, 5, 1, 1 },
#endif
#if defined WL4908
	{ "DS_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_TX_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_CPU_TX_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_NULL_BUFFER", 1, PRIVATE_A_INDEX, &DS_NULL_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_FILTERS_CONFIGURATION_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_FILTERS_CONFIGURATION_TABLE, 2, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_RX_FAST_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DS_CPU_RX_FAST_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_GPE_COMMAND_PRIMITIVE_TABLE", 1, PRIVATE_A_INDEX, &DS_GPE_COMMAND_PRIMITIVE_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_GSO_CONTEXT_TABLE", 1, PRIVATE_A_INDEX, &DS_GSO_CONTEXT_TABLE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_WAN_UDP_FILTER_CONTROL_TABLE", 1, PRIVATE_A_INDEX, &DS_WAN_UDP_FILTER_CONTROL_TABLE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DEBUG_BUFFER", 1, PRIVATE_A_INDEX, &DS_DEBUG_BUFFER, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FW_MAC_ADDRS", 1, PRIVATE_A_INDEX, &DS_FW_MAC_ADDRS, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RUNNER_FLOW_HEADER_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_RUNNER_FLOW_HEADER_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "EMAC_SKB_ENQUEUED_INDEXES_FREE_PTR", 1, PRIVATE_A_INDEX, &EMAC_SKB_ENQUEUED_INDEXES_FREE_PTR, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_COMPLETE_RING_BUFFER", 1, PRIVATE_A_INDEX, &DHD_COMPLETE_RING_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908
	{ "MCAST_LKP_WORD3_CRC_BUFFER", 1, PRIVATE_A_INDEX, &MCAST_LKP_WORD3_CRC_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_PARAMETERS_BLOCK", 1, PRIVATE_A_INDEX, &DS_CPU_PARAMETERS_BLOCK, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BPM_EXTRA_DDR_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_EXTRA_DDR_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FAST_MALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_FAST_MALLOC_RESULT_TABLE, 2, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DATA_POINTER_DUMMY_TARGET", 1, PRIVATE_A_INDEX, &DS_DATA_POINTER_DUMMY_TARGET, 5, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BPM_DDR_OPTIMIZED_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_OPTIMIZED_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_MALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_PICO_MALLOC_RESULT_TABLE, 2, 1, 1 },
#endif
#if defined WL4908
	{ "DS_GSO_DESC_TABLE", 1, PRIVATE_A_INDEX, &DS_GSO_DESC_TABLE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_TX_POST_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DS_DHD_TX_POST_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "SERVICE_QUEUES_WLAN_SCRATCH", 1, PRIVATE_A_INDEX, &SERVICE_QUEUES_WLAN_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BUF_SIZE_TO_TOKEN_COUNT_LOG2_TABLE", 1, PRIVATE_A_INDEX, &DS_BUF_SIZE_TO_TOKEN_COUNT_LOG2_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE", 1, PRIVATE_A_INDEX, &DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "HASH_BUFFER", 1, PRIVATE_A_INDEX, &HASH_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_FLOW_RING_DROP_COUNTER", 1, PRIVATE_A_INDEX, &DS_DHD_FLOW_RING_DROP_COUNTER, 5, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BPM_DDR_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BPM_DDR_1_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_1_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CONNECTION_TABLE_CONFIG", 1, PRIVATE_A_INDEX, &DS_CONNECTION_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE", 1, PRIVATE_A_INDEX, &DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_SYSTEM_CONFIGURATION", 1, PRIVATE_A_INDEX, &DS_SYSTEM_CONFIGURATION, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CONTEXT_TABLE_CONFIG", 1, PRIVATE_A_INDEX, &DS_CONTEXT_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DEBUG_PERIPHERALS_STATUS_REGISTER", 1, PRIVATE_A_INDEX, &DS_DEBUG_PERIPHERALS_STATUS_REGISTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE", 1, PRIVATE_A_INDEX, &DS_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "BITS_CALC_MASKS_TABLE", 1, PRIVATE_A_INDEX, &BITS_CALC_MASKS_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "ETH_TX_SCRATCH", 1, PRIVATE_A_INDEX, &ETH_TX_SCRATCH, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_TX_POST_DOORBELL_SCRATCH", 1, PRIVATE_A_INDEX, &DS_DHD_TX_POST_DOORBELL_SCRATCH, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_KEY_BUFFER", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_KEY_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "SERVICE_QUEUES_OVERALL_RATE_LIMITER", 1, PRIVATE_A_INDEX, &SERVICE_QUEUES_OVERALL_RATE_LIMITER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GSO_TX_DHD_L2_BUFFER", 1, PRIVATE_A_INDEX, &GSO_TX_DHD_L2_BUFFER, 22, 1, 1 },
#endif
#if defined WL4908
	{ "DS_MAIN_TIMER_CONTROL_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_MAIN_TIMER_CONTROL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_DHD_L2_BUFFER", 1, PRIVATE_A_INDEX, &CPU_TX_DHD_L2_BUFFER, 22, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_TIMER_CONTROL_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_PICO_TIMER_CONTROL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CONTEXT_CONTINUATION_TABLE_CONFIG", 1, PRIVATE_A_INDEX, &DS_CONTEXT_CONTINUATION_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_DS_PICO_DHD_TX_POST_CONTEXT", 1, PRIVATE_A_INDEX, &CPU_TX_DS_PICO_DHD_TX_POST_CONTEXT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "WLAN_MCAST_DHD_TX_POST_CONTEXT", 1, PRIVATE_A_INDEX, &WLAN_MCAST_DHD_TX_POST_CONTEXT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GSO_TX_DS_PICO_DHD_TX_POST_CONTEXT", 1, PRIVATE_A_INDEX, &GSO_TX_DS_PICO_DHD_TX_POST_CONTEXT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "GSO_TX_ENQUEUE_PCI_PACKET_CONTEXT", 1, PRIVATE_A_INDEX, &GSO_TX_ENQUEUE_PCI_PACKET_CONTEXT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_ENQUEUE_PCI_PACKET_CONTEXT", 1, PRIVATE_A_INDEX, &CPU_TX_ENQUEUE_PCI_PACKET_CONTEXT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "TIMER_DHD_TX_POST_DOORBELL_SCRATCH", 1, PRIVATE_A_INDEX, &TIMER_DHD_TX_POST_DOORBELL_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "SPDSVC_HOST_BUF_PTR", 1, PRIVATE_A_INDEX, &SPDSVC_HOST_BUF_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "EMAC_SKB_ENQUEUED_INDEXES_FIFO_COUNTERS", 1, PRIVATE_A_INDEX, &EMAC_SKB_ENQUEUED_INDEXES_FIFO_COUNTERS, 5, 1, 1 },
#endif
#if defined WL4908
	{ "ETH_TX_EMACS_STATUS", 1, PRIVATE_A_INDEX, &ETH_TX_EMACS_STATUS, 1, 1, 1 },
#endif
#if defined WL4908
	{ "IPTV_COUNTERS_BUFFER", 1, PRIVATE_A_INDEX, &IPTV_COUNTERS_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "HASH_BASED_FORWARDING_PORT_TABLE", 1, PRIVATE_A_INDEX, &HASH_BASED_FORWARDING_PORT_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_TX_DATA_POINTER_DUMMY_TARGET", 1, PRIVATE_A_INDEX, &DS_CPU_TX_DATA_POINTER_DUMMY_TARGET, 1, 1, 1 },
#endif
#if defined WL4908
	{ "FIREWALL_IPV6_R16_BUFFER", 1, PRIVATE_A_INDEX, &FIREWALL_IPV6_R16_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_PICO_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &CPU_TX_PICO_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD", 1, PRIVATE_A_INDEX, &FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_RX_PD_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &CPU_RX_PD_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_RX_PICO_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &DS_CPU_RX_PICO_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BPM_DDR_BUFFER_HEADROOM_SIZE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_BUFFER_HEADROOM_SIZE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_RX_FAST_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &DS_CPU_RX_FAST_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_ANY_SRC_PORT_FLOW_COUNTER", 1, PRIVATE_A_INDEX, &DS_ANY_SRC_PORT_FLOW_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GSO_DESC_PTR", 1, PRIVATE_A_INDEX, &GSO_DESC_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_TX_POST_HOST_DATA_PTR_BUFFER", 1, PRIVATE_A_INDEX, &DS_DHD_TX_POST_HOST_DATA_PTR_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GSO_TX_DHD_HOST_BUF_PTR", 1, PRIVATE_A_INDEX, &GSO_TX_DHD_HOST_BUF_PTR, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DS_TIMER_7_SCHEDULER_NEXT_ENTRY", 1, PRIVATE_A_INDEX, &DS_TIMER_7_SCHEDULER_NEXT_ENTRY, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_MEMLIB_SEMAPHORE", 1, PRIVATE_A_INDEX, &DS_MEMLIB_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_DHD_HOST_BUF_PTR", 1, PRIVATE_A_INDEX, &CPU_TX_DHD_HOST_BUF_PTR, 4, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_PHYSICAL_PORT", 1, PRIVATE_A_INDEX, &WAN_PHYSICAL_PORT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RUNNER_CONGESTION_STATE", 1, PRIVATE_A_INDEX, &DS_RUNNER_CONGESTION_STATE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR", 1, PRIVATE_A_INDEX, &DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GSO_PICO_QUEUE_PTR", 1, PRIVATE_A_INDEX, &GSO_PICO_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_COMPLETE_BPM_REF_COUNTER", 1, PRIVATE_A_INDEX, &DHD_TX_COMPLETE_BPM_REF_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_POST_CPU_BPM_REF_COUNTER", 1, PRIVATE_A_INDEX, &DHD_TX_POST_CPU_BPM_REF_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_BPM_CONGESTION_UG3_DROP_COUNTER", 1, PRIVATE_A_INDEX, &DS_DHD_BPM_CONGESTION_UG3_DROP_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_BPM_CONGESTION_ALLOC_FAIL_DROP_COUNTER", 1, PRIVATE_A_INDEX, &DS_DHD_BPM_CONGESTION_ALLOC_FAIL_DROP_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "PRIVATE_A_DUMMY_STORE", 1, PRIVATE_A_INDEX, &PRIVATE_A_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "ETH_TX_INTER_LAN_SCHEDULING_OFFSET", 1, PRIVATE_A_INDEX, &ETH_TX_INTER_LAN_SCHEDULING_OFFSET, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR", 1, PRIVATE_A_INDEX, &DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR", 1, PRIVATE_A_INDEX, &DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_DS_PICO_SEMAPHORE", 1, PRIVATE_A_INDEX, &CPU_TX_DS_PICO_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FC_GLOBAL_CFG", 1, PRIVATE_A_INDEX, &DS_FC_GLOBAL_CFG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PACKET_BUFFER_SIZE_ASR_8", 1, PRIVATE_A_INDEX, &DS_PACKET_BUFFER_SIZE_ASR_8, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_MAIN_DMA_SYNCRONIZATION_ADDRESS", 1, PRIVATE_A_INDEX, &DS_MAIN_DMA_SYNCRONIZATION_ADDRESS, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_DMA_SYNCRONIZATION_ADDRESS", 1, PRIVATE_A_INDEX, &DS_PICO_DMA_SYNCRONIZATION_ADDRESS, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RUNNER_FLOW_IH_RESPONSE_MUTEX", 1, PRIVATE_A_INDEX, &DS_RUNNER_FLOW_IH_RESPONSE_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PARALLEL_PROCESSING_SLAVE_VECTOR", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_SLAVE_VECTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_IH_CONGESTION_THRESHOLD", 1, PRIVATE_A_INDEX, &DS_IH_CONGESTION_THRESHOLD, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FAST_MALLOC_RESULT_MUTEX", 1, PRIVATE_A_INDEX, &DS_FAST_MALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_PICO_MALLOC_RESULT_MUTEX", 1, PRIVATE_A_INDEX, &DS_PICO_MALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RX_SBPM_TO_FPM_COPY_SEMAPHORE", 1, PRIVATE_A_INDEX, &DS_RX_SBPM_TO_FPM_COPY_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_FW_MAC_ADDRS_COUNT", 1, PRIVATE_A_INDEX, &DS_FW_MAC_ADDRS_COUNT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_DMA_SYNCHRONIZATION", 1, PRIVATE_A_INDEX, &DS_DHD_DMA_SYNCHRONIZATION, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_POST_CPU_SEMAPHORE", 1, PRIVATE_A_INDEX, &DHD_TX_POST_CPU_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "RING_CACHE_DHD_TXPOST_MUTEX", 1, PRIVATE_A_INDEX, &RING_CACHE_DHD_TXPOST_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "COMMON_DHD_TXPOST_MUTEX", 1, PRIVATE_A_INDEX, &COMMON_DHD_TXPOST_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "TXCPL_INT_DHD_TXPOST_MUTEX", 1, PRIVATE_A_INDEX, &TXCPL_INT_DHD_TXPOST_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_FAST_QUEUE", 1, PRIVATE_A_INDEX, &CPU_TX_FAST_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_PICO_QUEUE", 1, PRIVATE_A_INDEX, &CPU_TX_PICO_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "EMAC_ABSOLUTE_TX_BBH_COUNTER", 1, PRIVATE_A_INDEX, &EMAC_ABSOLUTE_TX_BBH_COUNTER, 10, 1, 1 },
#endif
#if defined WL4908
	{ "FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR", 1, PRIVATE_A_INDEX, &FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GPON_RX_DIRECT_DESCRIPTORS", 1, PRIVATE_A_INDEX, &GPON_RX_DIRECT_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FLOW_IH_RESPONSE", 1, PRIVATE_A_INDEX, &RUNNER_FLOW_IH_RESPONSE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "ETH_TX_MAC_TABLE", 1, PRIVATE_A_INDEX, &ETH_TX_MAC_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "GPON_RX_NORMAL_DESCRIPTORS", 1, PRIVATE_A_INDEX, &GPON_RX_NORMAL_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_HANDLER_BUFFER", 1, PRIVATE_B_INDEX, &US_INGRESS_HANDLER_BUFFER, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_CSO_CHUNK_BUFFER", 1, PRIVATE_B_INDEX, &US_CSO_CHUNK_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CSO_PSEUDO_HEADER_BUFFER", 1, PRIVATE_B_INDEX, &US_CSO_PSEUDO_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_TIMER_7_SCHEDULER_PRIMITIVE_TABLE", 1, PRIVATE_B_INDEX, &US_TIMER_7_SCHEDULER_PRIMITIVE_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "US_RATE_CONTROL_BUDGET_ALLOCATOR_TABLE", 1, PRIVATE_B_INDEX, &US_RATE_CONTROL_BUDGET_ALLOCATOR_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_REASON_TO_METER_TABLE", 1, PRIVATE_B_INDEX, &US_CPU_REASON_TO_METER_TABLE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "US_MAIN_PROFILING_BUFFER_RUNNER", 1, PRIVATE_B_INDEX, &US_MAIN_PROFILING_BUFFER_RUNNER, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_FREE_PACKET_DESCRIPTORS_POOL", 1, PRIVATE_B_INDEX, &US_FREE_PACKET_DESCRIPTORS_POOL, 3072, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_FILTERS_LOOKUP_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_FILTERS_LOOKUP_TABLE, 7, 16, 1 },
#endif
#if defined WL4908
	{ "US_TRAFFIC_CLASS_TO_QUEUE_TABLE", 1, PRIVATE_B_INDEX, &US_TRAFFIC_CLASS_TO_QUEUE_TABLE, 8, 8, 1 },
#endif
#if defined WL4908
	{ "WAN_CHANNELS_8_39_TABLE", 1, PRIVATE_B_INDEX, &WAN_CHANNELS_8_39_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_RUNNER_FLOW_HEADER_BUFFER", 1, PRIVATE_B_INDEX, &US_RUNNER_FLOW_HEADER_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908
	{ "US_SBPM_REPLY", 1, PRIVATE_B_INDEX, &US_SBPM_REPLY, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_POLICER_TABLE", 1, PRIVATE_B_INDEX, &US_POLICER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_TX_SERVICE_QUEUE_SCHEDULER_TABLE", 1, PRIVATE_B_INDEX, &WAN_TX_SERVICE_QUEUE_SCHEDULER_TABLE, 2, 1, 1 },
#endif
#if defined WL4908
	{ "US_WAN_FLOW_TABLE", 1, PRIVATE_B_INDEX, &US_WAN_FLOW_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_TX_BBH_DESCRIPTORS", 1, PRIVATE_B_INDEX, &US_CPU_TX_BBH_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_FORWARDING_MATRIX_TABLE", 1, PRIVATE_B_INDEX, &US_FORWARDING_MATRIX_TABLE, 9, 16, 1 },
#endif
#if defined WL4908
	{ "US_TIMER_SCHEDULER_PRIMITIVE_TABLE", 1, PRIVATE_B_INDEX, &US_TIMER_SCHEDULER_PRIMITIVE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_MAIN_TIMER_TASK_DESCRIPTOR_TABLE", 1, PRIVATE_B_INDEX, &US_MAIN_TIMER_TASK_DESCRIPTOR_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_RX_PICO_INGRESS_QUEUE", 1, PRIVATE_B_INDEX, &US_CPU_RX_PICO_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "US_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE", 1, PRIVATE_B_INDEX, &US_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE", 1, PRIVATE_B_INDEX, &US_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_TIMER_TASK_DESCRIPTOR_TABLE", 1, PRIVATE_B_INDEX, &US_PICO_TIMER_TASK_DESCRIPTOR_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "US_FC_L2_UCAST_TUPLE_BUFFER", 1, PRIVATE_B_INDEX, &US_FC_L2_UCAST_TUPLE_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RATE_LIMITER_TABLE", 1, PRIVATE_B_INDEX, &US_RATE_LIMITER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_QUEUE_PROFILE_TABLE", 1, PRIVATE_B_INDEX, &US_QUEUE_PROFILE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_CONNECTION_CONTEXT_BUFFER", 1, PRIVATE_B_INDEX, &US_CONNECTION_CONTEXT_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_CONTEXT_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_CONTEXT_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_CHANNELS_0_7_TABLE", 1, PRIVATE_B_INDEX, &WAN_CHANNELS_0_7_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "US_FAST_RUNNER_GLOBAL_REGISTERS_INIT", 1, PRIVATE_B_INDEX, &US_FAST_RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_RX_METER_TABLE", 1, PRIVATE_B_INDEX, &US_CPU_RX_METER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_HANDLER_SKB_DATA_POINTER", 1, PRIVATE_B_INDEX, &US_INGRESS_HANDLER_SKB_DATA_POINTER, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_CONNECTION_CONTEXT_REMAINING_BUFFER", 1, PRIVATE_B_INDEX, &US_CONNECTION_CONTEXT_REMAINING_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_RUNNER_GLOBAL_REGISTERS_INIT", 1, PRIVATE_B_INDEX, &US_PICO_RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_GRE_RUNNER_FLOW_HEADER_BUFFER", 1, PRIVATE_B_INDEX, &US_GRE_RUNNER_FLOW_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PROFILING_BUFFER_PICO_RUNNER", 1, PRIVATE_B_INDEX, &US_PROFILING_BUFFER_PICO_RUNNER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_RULE_CFG_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_RULE_CFG_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_FILTERS_PARAMETER_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_FILTERS_PARAMETER_TABLE, 7, 16, 1 },
#endif
#if defined WL4908
	{ "US_FC_L2_UCAST_CONNECTION_BUFFER", 1, PRIVATE_B_INDEX, &US_FC_L2_UCAST_CONNECTION_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_RX_COMPLETE_FLOW_RING_BUFFER", 1, PRIVATE_B_INDEX, &DHD_RX_COMPLETE_FLOW_RING_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_RX_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &DHD_RX_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "ETHWAN_ABSOLUTE_TX_BBH_COUNTER", 1, PRIVATE_B_INDEX, &ETHWAN_ABSOLUTE_TX_BBH_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "PRIVATE_B_DUMMY_STORE", 1, PRIVATE_B_INDEX, &PRIVATE_B_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_MAIN_TIMER_CONTROL_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_MAIN_TIMER_CONTROL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_ETH0_EEE_MODE_CONFIG_MESSAGE", 1, PRIVATE_B_INDEX, &US_ETH0_EEE_MODE_CONFIG_MESSAGE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "ETHWAN_ABSOLUTE_TX_FIRMWARE_COUNTER", 1, PRIVATE_B_INDEX, &ETHWAN_ABSOLUTE_TX_FIRMWARE_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR", 1, PRIVATE_B_INDEX, &US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_TIMER_CONTROL_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_PICO_TIMER_CONTROL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_BPM_EXTRA_DDR_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_EXTRA_DDR_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GPON_ABSOLUTE_TX_BBH_COUNTER", 1, PRIVATE_B_INDEX, &GPON_ABSOLUTE_TX_BBH_COUNTER, 40, 1, 1 },
#endif
#if defined WL4908
	{ "US_TOTAL_PPS_RATE_LIMITER", 1, PRIVATE_B_INDEX, &US_TOTAL_PPS_RATE_LIMITER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_TX_MESSAGE_DATA_BUFFER", 1, PRIVATE_B_INDEX, &US_CPU_TX_MESSAGE_DATA_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_RX_POST_FLOW_RING_BUFFER", 1, PRIVATE_B_INDEX, &DHD_RX_POST_FLOW_RING_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908
	{ "US_0_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_0_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_RATE_LIMITER_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_RATE_LIMITER_TABLE, 5, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_MAINB_PARAM", 1, PRIVATE_B_INDEX, &RUNNER_FWTRACE_MAINB_PARAM, 2, 1, 1 },
#endif
#if defined WL4908
	{ "US_0_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_0_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_SPDSVC_CONTEXT_TABLE", 1, PRIVATE_B_INDEX, &US_SPDSVC_CONTEXT_TABLE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_PICOB_PARAM", 1, PRIVATE_B_INDEX, &RUNNER_FWTRACE_PICOB_PARAM, 2, 1, 1 },
#endif
#if defined WL4908
	{ "US_1_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_1_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_ROUTER_INGRESS_QUEUE", 1, PRIVATE_B_INDEX, &US_ROUTER_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "US_1_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_1_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_2_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_2_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_TX_FAST_QUEUE", 1, PRIVATE_B_INDEX, &US_CPU_TX_FAST_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_RX_FAST_INGRESS_QUEUE", 1, PRIVATE_B_INDEX, &US_CPU_RX_FAST_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "US_2_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_2_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_TX_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_CPU_TX_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_TX_PICO_QUEUE", 1, PRIVATE_B_INDEX, &US_CPU_TX_PICO_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_DEBUG_BUFFER", 1, PRIVATE_B_INDEX, &US_DEBUG_BUFFER, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_FW_MAC_ADDRS", 1, PRIVATE_B_INDEX, &US_FW_MAC_ADDRS, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_TX_POST_INGRESS_QUEUE", 1, PRIVATE_B_INDEX, &US_DHD_TX_POST_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_TABLE", 1, PRIVATE_B_INDEX, &US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_TABLE, 48, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_FILTERS_CONFIGURATION_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_FILTERS_CONFIGURATION_TABLE, 7, 1, 1 },
#endif
#if defined WL4908
	{ "US_BPM_DDR_OPTIMIZED_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_OPTIMIZED_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_TX_POST_HEADER_SCRATCH", 1, PRIVATE_B_INDEX, &US_DHD_TX_POST_HEADER_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RUNNER_FLOW_HEADER_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_RUNNER_FLOW_HEADER_DESCRIPTOR, 3, 1, 1 },
#endif
#if defined WL4908
	{ "US_ONE_BUFFER", 1, PRIVATE_B_INDEX, &US_ONE_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CSO_CONTEXT_TABLE", 1, PRIVATE_B_INDEX, &US_CSO_CONTEXT_TABLE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_GPE_COMMAND_PRIMITIVE_TABLE", 1, PRIVATE_B_INDEX, &US_GPE_COMMAND_PRIMITIVE_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_NULL_BUFFER", 1, PRIVATE_B_INDEX, &US_NULL_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_PARAMETERS_BLOCK", 1, PRIVATE_B_INDEX, &US_CPU_PARAMETERS_BLOCK, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_BPM_DDR_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_FAST_MALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_FAST_MALLOC_RESULT_TABLE, 2, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_TX_POST_FLOW_RING_BUFFER", 1, PRIVATE_B_INDEX, &US_DHD_TX_POST_FLOW_RING_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GPON_ABSOLUTE_TX_FIRMWARE_COUNTER", 1, PRIVATE_B_INDEX, &GPON_ABSOLUTE_TX_FIRMWARE_COUNTER, 40, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_MALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_PICO_MALLOC_RESULT_TABLE, 2, 1, 1 },
#endif
#if defined WL4908
	{ "US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE", 1, PRIVATE_B_INDEX, &US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_FLOW_RING_DROP_COUNTER", 1, PRIVATE_B_INDEX, &US_DHD_FLOW_RING_DROP_COUNTER, 5, 1, 1 },
#endif
#if defined WL4908
	{ "US_BPM_DDR_1_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_1_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_BUF_SIZE_TO_TOKEN_COUNT_LOG2_TABLE", 1, PRIVATE_B_INDEX, &US_BUF_SIZE_TO_TOKEN_COUNT_LOG2_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE", 1, PRIVATE_B_INDEX, &US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE", 1, PRIVATE_B_INDEX, &US_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "US_SYSTEM_CONFIGURATION", 1, PRIVATE_B_INDEX, &US_SYSTEM_CONFIGURATION, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CONNECTION_TABLE_CONFIG", 1, PRIVATE_B_INDEX, &US_CONNECTION_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_TX_SCRATCH", 1, PRIVATE_B_INDEX, &WAN_TX_SCRATCH, 24, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_REASON_AND_SRC_BRIDGE_PORT_TO_METER_TABLE", 1, PRIVATE_B_INDEX, &CPU_REASON_AND_SRC_BRIDGE_PORT_TO_METER_TABLE, 3, 6, 1 },
#endif
#if defined WL4908
	{ "US_CPU_RX_PICO_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &US_CPU_RX_PICO_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CONTEXT_TABLE_CONFIG", 1, PRIVATE_B_INDEX, &US_CONTEXT_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_BPM_DDR_BUFFER_HEADROOM_SIZE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_BUFFER_HEADROOM_SIZE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "BROADCOM_SWITCH_PORT_TO_BRIDGE_PORT_MAPPING_TABLE", 1, PRIVATE_B_INDEX, &BROADCOM_SWITCH_PORT_TO_BRIDGE_PORT_MAPPING_TABLE, 9, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR", 1, PRIVATE_B_INDEX, &US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION", 1, PRIVATE_B_INDEX, &US_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR, 4, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_KEY_BUFFER", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_KEY_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_DS_EGRESS_DHD_TX_POST_CONTEXT", 1, PRIVATE_B_INDEX, &CPU_TX_DS_EGRESS_DHD_TX_POST_CONTEXT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_DHD_LAYER2_HEADER_BUFFER", 1, PRIVATE_B_INDEX, &CPU_TX_DHD_LAYER2_HEADER_BUFFER, 14, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_RX_FAST_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &US_CPU_RX_FAST_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DATA_POINTER_DUMMY_TARGET", 1, PRIVATE_B_INDEX, &DATA_POINTER_DUMMY_TARGET, 2, 1, 1 },
#endif
#if defined WL4908
	{ "US_PARALLEL_PROCESSING_TASK_REORDER_FIFO", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_TASK_REORDER_FIFO, 4, 1, 1 },
#endif
#if defined WL4908
	{ "US_DEBUG_PERIPHERALS_STATUS_REGISTER", 1, PRIVATE_B_INDEX, &US_DEBUG_PERIPHERALS_STATUS_REGISTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "IH_BUFFER_BBH_POINTER", 1, PRIVATE_B_INDEX, &IH_BUFFER_BBH_POINTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CONTEXT_CONTINUATION_TABLE_CONFIG", 1, PRIVATE_B_INDEX, &US_CONTEXT_CONTINUATION_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_TX_POST_DOORBELL_SCRATCH", 1, PRIVATE_B_INDEX, &US_DHD_TX_POST_DOORBELL_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_TX_DATA_POINTER_DUMMY_TARGET", 1, PRIVATE_B_INDEX, &US_CPU_TX_DATA_POINTER_DUMMY_TARGET, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RATE_CONTROLLER_EXPONENT_TABLE", 1, PRIVATE_B_INDEX, &US_RATE_CONTROLLER_EXPONENT_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_ANY_SRC_PORT_FLOW_COUNTER", 1, PRIVATE_B_INDEX, &US_ANY_SRC_PORT_FLOW_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_TX_POST_HOST_DATA_PTR_BUFFER", 1, PRIVATE_B_INDEX, &US_DHD_TX_POST_HOST_DATA_PTR_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_TIMER_7_SCHEDULER_NEXT_ENTRY", 1, PRIVATE_B_INDEX, &US_TIMER_7_SCHEDULER_NEXT_ENTRY, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_MEMLIB_SEMAPHORE", 1, PRIVATE_B_INDEX, &US_MEMLIB_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "ETHWAN2_RX_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &ETHWAN2_RX_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RUNNER_CONGESTION_STATE", 1, PRIVATE_B_INDEX, &US_RUNNER_CONGESTION_STATE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_ENQUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &WAN_ENQUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR", 1, PRIVATE_B_INDEX, &US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_BPM_CONGESTION_UG3_DROP_COUNTER", 1, PRIVATE_B_INDEX, &US_DHD_BPM_CONGESTION_UG3_DROP_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_BPM_CONGESTION_ALLOC_FAIL_DROP_COUNTER", 1, PRIVATE_B_INDEX, &US_DHD_BPM_CONGESTION_ALLOC_FAIL_DROP_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_FC_GLOBAL_CFG", 1, PRIVATE_B_INDEX, &US_FC_GLOBAL_CFG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "ETHWAN2_SWITCH_PORT", 1, PRIVATE_B_INDEX, &ETHWAN2_SWITCH_PORT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PACKET_BUFFER_SIZE_ASR_8", 1, PRIVATE_B_INDEX, &US_PACKET_BUFFER_SIZE_ASR_8, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_MAIN_DMA_SYNCRONIZATION_ADDRESS", 1, PRIVATE_B_INDEX, &US_MAIN_DMA_SYNCRONIZATION_ADDRESS, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_DMA_SYNCRONIZATION_ADDRESS", 1, PRIVATE_B_INDEX, &US_PICO_DMA_SYNCRONIZATION_ADDRESS, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RUNNER_FLOW_IH_RESPONSE_MUTEX", 1, PRIVATE_B_INDEX, &US_RUNNER_FLOW_IH_RESPONSE_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DSL_BUFFER_ALIGNMENT", 1, PRIVATE_B_INDEX, &DSL_BUFFER_ALIGNMENT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PARALLEL_PROCESSING_SLAVE_VECTOR", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_SLAVE_VECTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_IH_CONGESTION_THRESHOLD", 1, PRIVATE_B_INDEX, &US_IH_CONGESTION_THRESHOLD, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_FAST_MALLOC_RESULT_MUTEX", 1, PRIVATE_B_INDEX, &US_FAST_MALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_PICO_MALLOC_RESULT_MUTEX", 1, PRIVATE_B_INDEX, &US_PICO_MALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_RX_FPM_ALLOC_RESULT_MUTEX", 1, PRIVATE_B_INDEX, &DHD_RX_FPM_ALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RX_SBPM_TO_FPM_COPY_SEMAPHORE", 1, PRIVATE_B_INDEX, &US_RX_SBPM_TO_FPM_COPY_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_FW_MAC_ADDRS_COUNT", 1, PRIVATE_B_INDEX, &US_FW_MAC_ADDRS_COUNT, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_DMA_SYNCHRONIZATION", 1, PRIVATE_B_INDEX, &US_DHD_DMA_SYNCHRONIZATION, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RUNNER_FLOW_IH_RESPONSE", 1, PRIVATE_B_INDEX, &US_RUNNER_FLOW_IH_RESPONSE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "ETH2_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &ETH2_RX_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908
	{ "ETH1_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &ETH1_RX_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908
	{ "ETH0_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &ETH0_RX_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908
	{ "BBH_TX_WAN_CHANNEL_INDEX", 1, PRIVATE_B_INDEX, &BBH_TX_WAN_CHANNEL_INDEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "FC_MCAST_RUNNER_A_SCRATCHPAD", 1, COMMON_A_INDEX, &FC_MCAST_RUNNER_A_SCRATCHPAD, 32, 1, 1 },
#endif
#if defined WL4908
	{ "SERVICE_QUEUES_DDR_CACHE_FIFO", 1, COMMON_A_INDEX, &SERVICE_QUEUES_DDR_CACHE_FIFO, 256, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_RX_RUNNER_A_SCRATCHPAD", 1, COMMON_A_INDEX, &CPU_RX_RUNNER_A_SCRATCHPAD, 8, 1, 1 },
#endif
#if defined WL4908
	{ "MAC_TABLE", 1, COMMON_A_INDEX, &MAC_TABLE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_COUNTERS_TABLE", 1, COMMON_A_INDEX, &DS_INGRESS_CLASSIFICATION_COUNTERS_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "SERVICE_QUEUES_DESCRIPTOR_TABLE", 1, COMMON_A_INDEX, &SERVICE_QUEUES_DESCRIPTOR_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "MAC_TABLE_CAM", 1, COMMON_A_INDEX, &MAC_TABLE_CAM, 32, 1, 1 },
#endif
#if defined WL4908
	{ "TRACE_C_TABLE", 1, COMMON_A_INDEX, &TRACE_C_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_MAINA_CURR_OFFSET", 1, COMMON_A_INDEX, &RUNNER_FWTRACE_MAINA_CURR_OFFSET, 2, 1, 1 },
#endif
#if defined WL4908
	{ "DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE", 1, COMMON_A_INDEX, &DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE_LAST_ENTRY", 1, COMMON_A_INDEX, &DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE_LAST_ENTRY, 1, 1, 1 },
#endif
#if defined WL4908
	{ "FREE_SKB_INDEXES_DDR_FIFO_TAIL", 1, COMMON_A_INDEX, &FREE_SKB_INDEXES_DDR_FIFO_TAIL, 2, 1, 1 },
#endif
#if defined WL4908
	{ "BPM_REPLY_RUNNER_A", 1, COMMON_A_INDEX, &BPM_REPLY_RUNNER_A, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_BACKUP_ENTRY_SCRATCH", 1, COMMON_A_INDEX, &DS_DHD_BACKUP_ENTRY_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_REASON_TO_CPU_RX_QUEUE_TABLE", 1, COMMON_A_INDEX, &DS_CPU_REASON_TO_CPU_RX_QUEUE_TABLE, 2, 64, 1 },
#endif
#if defined WL4908
	{ "GPON_SKB_ENQUEUED_INDEXES_FIFO", 1, COMMON_A_INDEX, &GPON_SKB_ENQUEUED_INDEXES_FIFO, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CONNECTION_BUFFER_TABLE", 1, COMMON_A_INDEX, &DS_CONNECTION_BUFFER_TABLE, 5, 4, 1 },
#endif
#if defined WL4908
	{ "INTERRUPT_COALESCING_CONFIG_TABLE", 1, COMMON_A_INDEX, &INTERRUPT_COALESCING_CONFIG_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "MAC_CONTEXT_TABLE", 1, COMMON_A_INDEX, &MAC_CONTEXT_TABLE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD", 1, COMMON_A_INDEX, &DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE", 1, COMMON_A_INDEX, &DS_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE, 128, 1, 1 },
#endif
#if defined WL4908
	{ "PM_COUNTERS", 1, COMMON_A_INDEX, &PM_COUNTERS, 1, 1, 1 },
#endif
#if defined WL4908
	{ "ETHWAN2_RX_INGRESS_QUEUE", 1, COMMON_A_INDEX, &ETHWAN2_RX_INGRESS_QUEUE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_TX_SCRATCHPAD", 1, COMMON_A_INDEX, &DS_CPU_TX_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RING_PACKET_DESCRIPTORS_CACHE", 1, COMMON_A_INDEX, &DS_RING_PACKET_DESCRIPTORS_CACHE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "SERVICE_QUEUES_DDR_QUEUE_ADDRESS_TABLE", 1, COMMON_A_INDEX, &SERVICE_QUEUES_DDR_QUEUE_ADDRESS_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_POST_REQUEST_QUEUE", 1, COMMON_A_INDEX, &CPU_TX_POST_REQUEST_QUEUE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_RADIO_INSTANCE_COMMON_A_DATA", 1, COMMON_A_INDEX, &DHD_RADIO_INSTANCE_COMMON_A_DATA, 3, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_FLOW_RING_CACHE_LKP_TABLE", 1, COMMON_A_INDEX, &DS_DHD_FLOW_RING_CACHE_LKP_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "RING_DESCRIPTORS_TABLE", 1, COMMON_A_INDEX, &RING_DESCRIPTORS_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "RATE_SHAPERS_STATUS_DESCRIPTOR", 1, COMMON_A_INDEX, &RATE_SHAPERS_STATUS_DESCRIPTOR, 128, 1, 1 },
#endif
#if defined WL4908
	{ "MAC_CONTEXT_TABLE_CAM", 1, COMMON_A_INDEX, &MAC_CONTEXT_TABLE_CAM, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_DOORBELL_WRITE_VALUES", 1, COMMON_A_INDEX, &DHD_DOORBELL_WRITE_VALUES, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_BACKUP_INDEX_CACHE", 1, COMMON_A_INDEX, &DS_DHD_BACKUP_INDEX_CACHE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "MAC_EXTENSION_TABLE", 1, COMMON_A_INDEX, &MAC_EXTENSION_TABLE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_FLOW_RING_SHADOW_WR_PTR_TABLE", 1, COMMON_A_INDEX, &DHD_FLOW_RING_SHADOW_WR_PTR_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_BUFFER", 1, COMMON_A_INDEX, &DS_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DDR_ADDRESS_FOR_SKB_DATA_POINTERS_TABLE", 1, COMMON_A_INDEX, &DDR_ADDRESS_FOR_SKB_DATA_POINTERS_TABLE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_DHD_BACKUP_FLUSH_SCRATCH", 1, COMMON_A_INDEX, &DS_DHD_BACKUP_FLUSH_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "SERVICE_QUEUES_CFG", 1, COMMON_A_INDEX, &SERVICE_QUEUES_CFG, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_POST_REQUEST_QUEUE_IDX", 1, COMMON_A_INDEX, &CPU_TX_POST_REQUEST_QUEUE_IDX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "MAC_EXTENSION_TABLE_CAM", 1, COMMON_A_INDEX, &MAC_EXTENSION_TABLE_CAM, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CAM_DHD_DMA_SCRATCH", 1, COMMON_A_INDEX, &DS_CAM_DHD_DMA_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_ENQ_DHD_DMA_SCRATCH", 1, COMMON_A_INDEX, &DS_ENQ_DHD_DMA_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "PM_COUNTERS_BUFFER", 1, COMMON_A_INDEX, &PM_COUNTERS_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_R2D_DHD_DMA_SCRATCH", 1, COMMON_A_INDEX, &DS_R2D_DHD_DMA_SCRATCH, 4, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_POST_BUFFERS_THRESHOLD", 1, COMMON_A_INDEX, &DHD_TX_POST_BUFFERS_THRESHOLD, 6, 1, 1 },
#endif
#if defined WL4908
	{ "DS_CPU_DHD_DMA_SCRATCH", 1, COMMON_A_INDEX, &DS_CPU_DHD_DMA_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "TX_CPL_DHD_DMA_SCRATCH", 1, COMMON_A_INDEX, &TX_CPL_DHD_DMA_SCRATCH, 3, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_MAINA_BASE", 1, COMMON_A_INDEX, &RUNNER_FWTRACE_MAINA_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_PICOA_BASE", 1, COMMON_A_INDEX, &RUNNER_FWTRACE_PICOA_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DS_RATE_CONTROLLER_EXPONENT_TABLE", 1, COMMON_A_INDEX, &DS_RATE_CONTROLLER_EXPONENT_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "TIMER_7_TIMER_PERIOD", 1, COMMON_A_INDEX, &TIMER_7_TIMER_PERIOD, 1, 1, 1 },
#endif
#if defined WL4908
	{ "INTERRUPT_COALESCING_TIMER_PERIOD", 1, COMMON_A_INDEX, &INTERRUPT_COALESCING_TIMER_PERIOD, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_POST_BUFFERS_IN_USE_COUNTER", 1, COMMON_A_INDEX, &DHD_TX_POST_BUFFERS_IN_USE_COUNTER, 2, 1, 1 },
#endif
#if defined WL4908
	{ "INTERRUPT_COALESCING_TIMER_ARMED", 1, COMMON_A_INDEX, &INTERRUPT_COALESCING_TIMER_ARMED, 1, 1, 1 },
#endif
#if defined WL4908
	{ "COMMON_A_DUMMY_STORE", 1, COMMON_A_INDEX, &COMMON_A_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "FC_SERVICE_QUEUE_MODE", 1, COMMON_A_INDEX, &FC_SERVICE_QUEUE_MODE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "MAIN_A_DEBUG_TRACE", 1, COMMON_A_INDEX, &MAIN_A_DEBUG_TRACE, 512, 1, 1 },
#endif
#if defined WL4908
	{ "PICO_A_DEBUG_TRACE", 1, COMMON_A_INDEX, &PICO_A_DEBUG_TRACE, 512, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE", 1, COMMON_B_INDEX, &US_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE, 128, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_RX_RUNNER_B_SCRATCHPAD", 1, COMMON_B_INDEX, &CPU_RX_RUNNER_B_SCRATCHPAD, 8, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_COUNTERS_TABLE", 1, COMMON_B_INDEX, &US_INGRESS_CLASSIFICATION_COUNTERS_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE", 1, COMMON_B_INDEX, &LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE", 1, COMMON_B_INDEX, &DS_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_TX_SERVICE_QUEUES_TABLE", 1, COMMON_B_INDEX, &WAN_TX_SERVICE_QUEUES_TABLE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE", 1, COMMON_B_INDEX, &US_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_TX_SCRATCHPAD", 1, COMMON_B_INDEX, &US_CPU_TX_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CONNECTION_BUFFER_TABLE", 1, COMMON_B_INDEX, &US_CONNECTION_BUFFER_TABLE, 5, 4, 1 },
#endif
#if defined WL4908
	{ "IPV6_HOST_ADDRESS_CRC_TABLE", 1, COMMON_B_INDEX, &IPV6_HOST_ADDRESS_CRC_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_BACKUP_INFO_CACHE_TABLE", 1, COMMON_B_INDEX, &DHD_BACKUP_INFO_CACHE_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DS_INGRESS_CLASSIFICATION_LOOKUP_TABLE", 1, COMMON_B_INDEX, &DS_INGRESS_CLASSIFICATION_LOOKUP_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "US_INGRESS_CLASSIFICATION_LOOKUP_TABLE", 1, COMMON_B_INDEX, &US_INGRESS_CLASSIFICATION_LOOKUP_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_TX_QUEUES_TABLE", 1, COMMON_B_INDEX, &WAN_TX_QUEUES_TABLE, 256, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_TX_RUNNER_B_SCRATCHPAD", 1, COMMON_B_INDEX, &WAN_TX_RUNNER_B_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RING_PACKET_DESCRIPTORS_CACHE", 1, COMMON_B_INDEX, &US_RING_PACKET_DESCRIPTORS_CACHE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_FLOW_RING_CACHE_CTX_TABLE", 1, COMMON_B_INDEX, &DHD_FLOW_RING_CACHE_CTX_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_RADIO_INSTANCE_COMMON_B_DATA", 1, COMMON_B_INDEX, &DHD_RADIO_INSTANCE_COMMON_B_DATA, 3, 1, 1 },
#endif
#if defined WL4908
	{ "DUMMY_RATE_CONTROLLER_DESCRIPTOR", 1, COMMON_B_INDEX, &DUMMY_RATE_CONTROLLER_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "GPON_SKB_ENQUEUED_INDEXES_FREE_PTR", 1, COMMON_B_INDEX, &GPON_SKB_ENQUEUED_INDEXES_FREE_PTR, 40, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_MAINB_CURR_OFFSET", 1, COMMON_B_INDEX, &RUNNER_FWTRACE_MAINB_CURR_OFFSET, 2, 1, 1 },
#endif
#if defined WL4908
	{ "IPV4_HOST_ADDRESS_TABLE", 1, COMMON_B_INDEX, &IPV4_HOST_ADDRESS_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "GPON_SKB_ENQUEUED_INDEXES_PUT_PTR", 1, COMMON_B_INDEX, &GPON_SKB_ENQUEUED_INDEXES_PUT_PTR, 40, 1, 1 },
#endif
#if defined WL4908
	{ "US_CPU_REASON_TO_CPU_RX_QUEUE_TABLE", 1, COMMON_B_INDEX, &US_CPU_REASON_TO_CPU_RX_QUEUE_TABLE, 2, 64, 1 },
#endif
#if defined WL4908
	{ "DUMMY_WAN_TX_QUEUE_DESCRIPTOR", 1, COMMON_B_INDEX, &DUMMY_WAN_TX_QUEUE_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_FLOW_RING_CACHE_LKP_TABLE", 1, COMMON_B_INDEX, &US_DHD_FLOW_RING_CACHE_LKP_TABLE, 16, 1, 1 },
#endif
#if defined WL4908
	{ "PACKET_SRAM_TO_DDR_COPY_BUFFER_1", 1, COMMON_B_INDEX, &PACKET_SRAM_TO_DDR_COPY_BUFFER_1, 1, 1, 1 },
#endif
#if defined WL4908
	{ "PACKET_SRAM_TO_DDR_COPY_BUFFER_2", 1, COMMON_B_INDEX, &PACKET_SRAM_TO_DDR_COPY_BUFFER_2, 1, 1, 1 },
#endif
#if defined WL4908
	{ "LAN0_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN0_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "LAN5_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN5_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "FC_FLOW_IP_ADDRESSES_TABLE", 1, COMMON_B_INDEX, &FC_FLOW_IP_ADDRESSES_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_BACKUP_ENTRY_SCRATCH", 1, COMMON_B_INDEX, &US_DHD_BACKUP_ENTRY_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "BPM_REPLY_RUNNER_B", 1, COMMON_B_INDEX, &BPM_REPLY_RUNNER_B, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_RATE_CONTROLLERS_TABLE", 1, COMMON_B_INDEX, &US_RATE_CONTROLLERS_TABLE, 128, 1, 1 },
#endif
#if defined WL4908
	{ "US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD", 1, COMMON_B_INDEX, &US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD, 8, 1, 1 },
#endif
#if defined WL4908
	{ "LAN1_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN1_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "LAN6_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN6_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "LAN2_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN2_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "LAN7_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN7_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "LAN3_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN3_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_BACKUP_INDEX_CACHE", 1, COMMON_B_INDEX, &US_DHD_BACKUP_INDEX_CACHE, 32, 1, 1 },
#endif
#if defined WL4908
	{ "LAN4_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN4_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_DOORBELL_COUNTERS", 1, COMMON_B_INDEX, &DHD_DOORBELL_COUNTERS, 48, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_BACKUP_QUEUE_MANAGEMENT_INFO", 1, COMMON_B_INDEX, &US_DHD_BACKUP_QUEUE_MANAGEMENT_INFO, 1, 1, 1 },
#endif
#if defined WL4908
	{ "MAIN_B_DEBUG_TRACE", 1, COMMON_B_INDEX, &MAIN_B_DEBUG_TRACE, 512, 1, 1 },
#endif
#if defined WL4908
	{ "PICO_B_DEBUG_TRACE", 1, COMMON_B_INDEX, &PICO_B_DEBUG_TRACE, 512, 1, 1 },
#endif
#if defined WL4908
	{ "WAN_ENQUEUE_INGRESS_QUEUE", 1, COMMON_B_INDEX, &WAN_ENQUEUE_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_BUFFER", 1, COMMON_B_INDEX, &US_DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_CAM_DHD_DMA_SCRATCH", 1, COMMON_B_INDEX, &US_CAM_DHD_DMA_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_DHD_BACKUP_FLUSH_SCRATCH", 1, COMMON_B_INDEX, &US_DHD_BACKUP_FLUSH_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_ENQ_DHD_DMA_SCRATCH", 1, COMMON_B_INDEX, &US_ENQ_DHD_DMA_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "US_R2D_DHD_DMA_SCRATCH", 1, COMMON_B_INDEX, &US_R2D_DHD_DMA_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908
	{ "CPU_TX_DESCRIPTOR_QUEUE_TAIL_TABLE", 1, COMMON_B_INDEX, &CPU_TX_DESCRIPTOR_QUEUE_TAIL_TABLE, 4, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_MAINB_BASE", 1, COMMON_B_INDEX, &RUNNER_FWTRACE_MAINB_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "RUNNER_FWTRACE_PICOB_BASE", 1, COMMON_B_INDEX, &RUNNER_FWTRACE_PICOB_BASE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "COMMON_B_DUMMY_STORE", 1, COMMON_B_INDEX, &COMMON_B_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_FLOW_RING_CACHE_CTX_NEXT_INDEX", 1, COMMON_B_INDEX, &DHD_FLOW_RING_CACHE_CTX_NEXT_INDEX, 1, 1, 1 },
#endif
#if defined WL4908
	{ "BPM_PACKET_BUFFERS", 1, DDR_INDEX, &BPM_PACKET_BUFFERS, 7680, 1, 1 },
#endif
#if defined WL4908
	{ "CONTEXT_TABLE", 1, DDR_INDEX, &CONTEXT_TABLE, 0, 1, 1 },
#endif
#if defined WL4908
	{ "NAT_CACHE_TABLE", 1, DDR_INDEX, &NAT_CACHE_TABLE, 65536, 1, 1 },
#endif
#if defined WL4908
	{ "NAT_CACHE_EXTENSION_TABLE", 1, DDR_INDEX, &NAT_CACHE_EXTENSION_TABLE, 7, 1, 1 },
#endif
#if defined WL4908
	{ "NATC_CONTEXT_TABLE", 1, DDR_INDEX, &NATC_CONTEXT_TABLE, 65536, 1, 1 },
#endif
#if defined WL4908
	{ "CONTEXT_CONTINUATION_TABLE", 1, DDR_INDEX, &CONTEXT_CONTINUATION_TABLE, 65536, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_TABLE", 1, DDR_INDEX, &DHD_TX_POST_FLOW_RING_MGMT_DESCRIPTOR_TABLE, 8, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_RX_POST_DDR_BUFFER", 1, DDR_INDEX, &DHD_RX_POST_DDR_BUFFER, 1024, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_RX_COMPLETE_DDR_BUFFER", 1, DDR_INDEX, &DHD_RX_COMPLETE_DDR_BUFFER, 1024, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_POST_DDR_BUFFER", 1, DDR_INDEX, &DHD_TX_POST_DDR_BUFFER, 8, 16, 1 },
#endif
#if defined WL4908
	{ "DHD_TX_COMPLETE_DDR_BUFFER", 1, DDR_INDEX, &DHD_TX_COMPLETE_DDR_BUFFER, 16, 1, 1 },
#endif
#if defined WL4908
	{ "R2D_WR_ARR_DDR_BUFFER", 1, DDR_INDEX, &R2D_WR_ARR_DDR_BUFFER, 128, 1, 1 },
#endif
#if defined WL4908
	{ "D2R_RD_ARR_DDR_BUFFER", 1, DDR_INDEX, &D2R_RD_ARR_DDR_BUFFER, 128, 1, 1 },
#endif
#if defined WL4908
	{ "R2D_RD_ARR_DDR_BUFFER", 1, DDR_INDEX, &R2D_RD_ARR_DDR_BUFFER, 128, 1, 1 },
#endif
#if defined WL4908
	{ "D2R_WR_ARR_DDR_BUFFER", 1, DDR_INDEX, &D2R_WR_ARR_DDR_BUFFER, 128, 1, 1 },
#endif
#if defined WL4908
	{ "DHD_BACKUP_QUEUES_BUFFER", 1, DDR_INDEX, &DHD_BACKUP_QUEUES_BUFFER, 524288, 1, 1 },
#endif
};
