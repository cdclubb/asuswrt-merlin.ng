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
#ifdef WL4908_EAP
 0x0 + RUNNER_PRIVATE_0_OFFSET, 0x0 + RUNNER_PRIVATE_1_OFFSET, 0x0 + RUNNER_COMMON_0_OFFSET, 0x8000 + RUNNER_COMMON_1_OFFSET, 0x0, 0x0 + PSRAM_BLOCK_OFFSET,
#endif
};
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT INGRESS_HANDLER_BUFFER =
{
	256,
	{
		{ dump_RDD_IH_BUFFER, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FREE_PACKET_DESCRIPTORS_POOL =
{
	8,
	{
		{ dump_RDD_PACKET_DESCRIPTOR, 0x2000 },
#if defined WL4908_EAP
		{ dump_RDD_BBH_TX_DESCRIPTOR, 0x2000 },
#endif
		{ dump_RDD_SERVICE_QUEUE_DESCRIPTOR, 0x2000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_CONTEXT_BUFFER =
{
	128,
	{
		{ dump_RDD_CONNECTION_CONTEXT_BUFFER_ENTRY, 0x6000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_GSO_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_GSO_BUFFER_ENTRY, 0x6400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_GSO_PSEUDO_HEADER_BUFFER =
{
	40,
	{
		{ dump_RDD_GSO_PSEUDO_HEADER_BUFFER_ENTRY, 0x6480 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_TIMER_7_SCHEDULER_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x64a8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RATE_SHAPER_BUDGET_ALLOCATOR_TABLE =
{
	2,
	{
		{ dump_RDD_BUDGET_ALLOCATOR_ENTRY, 0x64b0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_REASON_TO_METER_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_METER_ENTRY, 0x64c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_GSO_CHUNK_BUFFER =
{
	128,
	{
		{ dump_RDD_GSO_BUFFER_ENTRY, 0x6500 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_METER_TABLE =
{
	8,
	{
		{ dump_RDD_CPU_RX_METER_ENTRY, 0x6580 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_WAN_FLOW_TABLE =
{
	2,
	{
		{ dump_RDD_DS_WAN_FLOW_ENTRY, 0x6600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_CONTEXT_TABLE =
{
	8,
	{
		{ dump_RDD_DS_INGRESS_CLASSIFICATION_CONTEXT_ENTRY, 0x6800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPF_CONTEXT_BUFFER =
{
	224,
	{
		{ dump_RDD_CAPWAPF_CONTEXT_ENTRY, 0x7000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_RATE_LIMITER_TABLE =
{
	24,
	{
		{ dump_RDD_SERVICE_QUEUES_RATE_LIMITER_DESCRIPTOR, 0x72a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_MAIN_TIMER_TASK_DESCRIPTOR_TABLE =
{
	8,
	{
		{ dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY, 0x75a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_TIMER_TASK_DESCRIPTOR_TABLE =
{
	8,
	{
		{ dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY, 0x75c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_MAIN_PROFILING_BUFFER_RUNNER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x75e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_FILTERS_PARAMETER_TABLE =
{
	1,
	{
		{ dump_RDD_INGRESS_FILTERS_PARAMETER_ENTRY, 0x76e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_POLICER_TABLE =
{
	16,
	{
		{ dump_RDD_POLICER_ENTRY, 0x7700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_CONTEXT_REMAINING_BUFFER =
{
#if defined WL4908_EAP
	76,
	{
		{ dump_RDD_CONTEXT_CONTINUATION_ENTRY, 0x7800 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH_TX_QUEUES_TABLE =
{
	16,
	{
		{ dump_RDD_ETH_TX_QUEUE_DESCRIPTOR, 0x7a60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FC_L2_UCAST_TUPLE_BUFFER =
{
	32,
	{
		{ dump_RDD_FC_L2_UCAST_TUPLE_ENTRY, 0x7ee0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FORWARDING_MATRIX_TABLE =
{
	1,
	{
		{ dump_RDD_FORWARDING_MATRIX_ENTRY, 0x7f00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_TIMER_SCHEDULER_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TIMER_SCHEDULER_PRIMITIVE_ENTRY, 0x7f90 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE =
{
	8,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_ENTRY, 0x7fa0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RATE_LIMITER_REMAINDER_TABLE =
{
	2,
	{
		{ dump_RDD_RATE_LIMITER_REMAINDER_ENTRY, 0x7fc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_WAN_UDP_FILTER_TABLE =
{
	16,
	{
		{ dump_RDD_DS_WAN_UDP_FILTER_ENTRY, 0x8000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT FC_MCAST_PORT_HEADER_BUFFER =
{
	1,
	{
		{ dump_RDD_FC_MCAST_PORT_HEADER_ENTRY, 0x8200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_LAN_ENQUEUE_SQ_PD =
{
#if defined WL4908_EAP
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0x8400 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_CONTEXT_MULTICAST_BUFFER =
{
	64,
	{
		{ dump_RDD_CONNECTION_CONTEXT_MULTICAST_BUFFER_ENTRY, 0x8600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FC_MCAST_PACKET_SAVE_DATA_TABLE =
{
	88,
	{
		{ dump_RDD_FC_MCAST_PACKET_SAVE_DATA_ENTRY, 0x8800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FAST_RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_FAST_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY, 0x8960 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SBPM_REPLY =
{
	128,
	{
		{ dump_RDD_SBPM_REPLY_ENTRY, 0x8980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH_TX_QUEUES_POINTERS_TABLE =
{
	4,
	{
		{ dump_RDD_ETH_TX_QUEUE_POINTERS_ENTRY, 0x8a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_PICO_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY, 0x8b20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x8b40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_FILTERS_LOOKUP_TABLE =
{
	4,
	{
		{ dump_RDD_INGRESS_FILTERS_LOOKUP_ENTRY, 0x8b80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_RX_SQ_PD_INGRESS_QUEUE =
{
#if defined WL4908_EAP
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0x8c00 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_BBH_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_CPU_TX_BBH_DESCRIPTORS_ENTRY, 0x8e00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT INGRESS_HANDLER_SKB_DATA_POINTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x8f00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RUNNER_FLOW_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_RUNNER_FLOW_HEADER_BUFFER, 0x8f80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GSO_PICO_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0x9000 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0x9000 },
#if defined WL4908_EAP
		{ dump_RDD_CPU_TX_DESCRIPTOR_BPM, 0x9000 },
#endif
		{ dump_RDD_CPU_TX_DESCRIPTOR_ABS, 0x9000 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_FAST, 0x9000 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_US_FAST, 0x9000 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO, 0x9000 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_DS_PICO_WIFI, 0x9000 },
		{ dump_RDD_CPU_TX_MESSAGE_DESCRIPTOR, 0x9000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_LAN_ENQUEUE_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9240 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9280 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_MESSAGE_DATA_BUFFER =
{
	64,
	{
		{ dump_RDD_CPU_TX_MESSAGE_DATA_BUFFER_ENTRY, 0x92c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RATE_LIMITER_TABLE =
{
	8,
	{
		{ dump_RDD_RATE_LIMITER_ENTRY, 0x9300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_GRE_RUNNER_FLOW_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_GRE_RUNNER_FLOW_HEADER_BUFFER, 0x9400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_RULE_CFG_TABLE =
{
	8,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_RULE_CFG_ENTRY, 0x9480 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PROFILING_BUFFER_PICO_RUNNER =
{
	256,
	{
		{ dump_RDD_PROFILING_BUFFER_PICO_RUNNER, 0x9500 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_SPDSVC_CONTEXT_TABLE =
{
	80,
	{
		{ dump_RDD_SPDSVC_CONTEXT_ENTRY, 0x9680 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FC_L2_UCAST_CONNECTION_BUFFER =
{
	16,
	{
		{ dump_RDD_FC_L2_UCAST_CONNECTION_ENTRY, 0x96d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x96e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH_TX_LOCAL_REGISTERS =
{
	8,
	{
		{ dump_RDD_ETH_TX_LOCAL_REGISTERS_ENTRY, 0x9780 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_TOTAL_PPS_RATE_LIMITER =
{
	8,
	{
		{ dump_RDD_TOTAL_PPS_RATE_LIMITER_ENTRY, 0x97c8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINA_PARAM =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x97d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x97e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_RX_PD_INGRESS_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_QUEUE_PROFILE_TABLE =
{
	16,
	{
		{ dump_RDD_QUEUE_PROFILE, 0x9880 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_RX_FAST_PD_INGRESS_QUEUE =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9900 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT EMAC_SKB_ENQUEUED_INDEXES_FIFO =
{
	32,
	{
		{ dump_RDD_EMAC_SKB_ENQUEUED_INDEXES_FIFO_ENTRY, 0x9980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9a20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_GPE_COMMAND_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_GPE_COMMAND_PRIMITIVE_ENTRY, 0x9a40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_SQ_ENQUEUE_QUEUE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9a80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_NULL_BUFFER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9ac0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_FILTERS_CONFIGURATION_TABLE =
{
	4,
	{
		{ dump_RDD_INGRESS_FILTERS_CONFIGURATION_ENTRY, 0x9ad8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_PARAMETERS_BLOCK =
{
	20,
	{
		{ dump_RDD_CPU_PARAMETERS_BLOCK_ENTRY, 0x9ae0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_WAN_UDP_FILTER_CONTROL_TABLE =
{
	4,
	{
		{ dump_RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY, 0x9af4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RUNNER_FLOW_HEADER_DESCRIPTOR =
{
	8,
	{
		{ dump_RDD_RUNNER_FLOW_HEADER_DESCRIPTOR, 0x9af8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_GSO_CONTEXT_TABLE =
{
	132,
	{
		{ dump_RDD_GSO_CONTEXT_ENTRY, 0x9b00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_BPM_EXTRA_DDR_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9b84 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MCAST_LKP_WORD3_CRC_BUFFER =
{
	8,
	{
		{ dump_RDD_MCAST_LKP_WORD3_CRC, 0x9b88 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_PICOA_PARAM =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9b90 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_DATA_POINTER_DUMMY_TARGET =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9ba0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_OPTIMIZED_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9bb4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FAST_MALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9bb8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_WLAN_SCRATCH =
{
	20,
	{
		{ dump_RDD_CPU_PARAMETERS_BLOCK_ENTRY, 0x9bc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9bd4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_MALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9bd8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE =
{
	2,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY, 0x9be0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT EMAC_SKB_ENQUEUED_INDEXES_PUT_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9bf0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_PICO_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_SYSTEM_CONFIGURATION =
{
	36,
	{
		{ dump_RDD_SYSTEM_CONFIGURATION, 0x9c40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9c64 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_1_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9c68 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_CONNECTION_TABLE_CONFIG, 0x9c6c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT EMAC_SKB_ENQUEUED_INDEXES_FREE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9c70 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_ROUTER_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9c80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE =
{
	2,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY, 0x9cc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT HASH_BUFFER =
{
	16,
	{
		{ dump_RDD_HASH_BUFFER, 0x9cd0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9ce0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE =
{
	1,
	{
		{ dump_RDD_BROADCOM_SWITCH_PORT_MAPPING, 0x9cf0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_FAST_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9d00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_DEBUG_BUFFER =
{
	4,
	{
		{ dump_RDD_DEBUG_BUFFER_ENTRY, 0x9d40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FW_MAC_ADDRS =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9dc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT BITS_CALC_MASKS_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0x9e40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH_TX_SCRATCH =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9e50 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_OVERALL_RATE_LIMITER =
{
	24,
	{
		{ dump_RDD_SERVICE_QUEUES_RATE_LIMITER_DESCRIPTOR, 0x9e60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CONTEXT_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_CONTEXT_TABLE_CONFIG, 0x9e78 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_ENTRY, 0x9e7c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_GSO_DESC_TABLE =
{
	128,
	{
		{ dump_RDD_GSO_DESC_ENTRY, 0x9e80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_KEY_BUFFER =
{
	16,
	{
		{ dump_RDD_SIXTEEN_BYTES, 0x9f00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_TASK_REORDER_ENTRY, 0x9f10 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_DEBUG_PERIPHERALS_STATUS_REGISTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f14 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f18 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CONTEXT_CONTINUATION_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_MAIN_TIMER_CONTROL_DESCRIPTOR =
{
	2,
	{
		{ dump_RDD_TIMER_CONTROL_DESCRIPTOR, 0x9f24 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_TIMER_CONTROL_DESCRIPTOR =
{
	2,
	{
		{ dump_RDD_TIMER_CONTROL_DESCRIPTOR, 0x9f26 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GSO_TX_ENQUEUE_PCI_PACKET_CONTEXT =
{
	8,
	{
		{ dump_RDD_ENQUEUE_PCI_PACKET_CONTEXT_ENTRY, 0x9f28 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_TX_ENQUEUE_PCI_PACKET_CONTEXT =
{
	8,
	{
		{ dump_RDD_ENQUEUE_PCI_PACKET_CONTEXT_ENTRY, 0x9f30 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPF_CPU_PROCESSING_TASK_REORDER_FIFO =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f38 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SPDSVC_HOST_BUF_PTR =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f3c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT EMAC_SKB_ENQUEUED_INDEXES_FIFO_COUNTERS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH_TX_EMACS_STATUS =
{
	1,
	{
		{ dump_RDD_ETH_TX_EMACS_STATUS_ENTRY, 0x9f45 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT IPTV_COUNTERS_BUFFER =
{
	2,
	{
		{ dump_RDD_IPTV_COUNTERS_BUFFER, 0x9f46 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT HASH_BASED_FORWARDING_PORT_TABLE =
{
	1,
	{
		{ dump_RDD_HASH_BASED_FORWARDING_PORT_ENTRY, 0x9f48 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_DATA_POINTER_DUMMY_TARGET =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f4c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT FIREWALL_IPV6_R16_BUFFER =
{
	4,
	{
		{ dump_RDD_FIREWALL_IPV6_R16_BUFFER_ENTRY, 0x9f50 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_TX_PICO_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_TX_PICO_INGRESS_QUEUE_PTR, 0x9f54 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD =
{
	2,
	{
		{ dump_RDD_FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD, 0x9f56 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9f58 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_RX_PD_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9f5a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_PICO_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_RX_PICO_INGRESS_QUEUE_PTR, 0x9f5c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_BUFFER_HEADROOM_SIZE =
{
	2,
	{
		{ dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE, 0x9f5e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION =
{
	2,
	{
		{ dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION, 0x9f60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_RX_FAST_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_RX_FAST_INGRESS_QUEUE_PTR, 0x9f62 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR =
{
	2,
	{
		{ dump_RDD_PARALLEL_PROCESSING_IH_BUFFER_PTR, 0x9f64 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_ANY_SRC_PORT_FLOW_COUNTER =
{
	2,
	{
		{ dump_RDD_ANY_SRC_PORT_FLOW_COUNTER, 0x9f66 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GSO_DESC_PTR =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f68 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_TIMER_7_SCHEDULER_NEXT_ENTRY =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9f6c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_MEMLIB_SEMAPHORE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9f6e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_PHYSICAL_PORT =
{
	2,
	{
		{ dump_RDD_WAN_PHYSICAL_PORT, 0x9f70 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9f72 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RUNNER_CONGESTION_STATE =
{
	2,
	{
		{ dump_RDD_RUNNER_CONGESTION_STATE_ENTRY, 0x9f74 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0x9f76 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GSO_PICO_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9f78 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT PRIVATE_A_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_DUMMY_STORE_ENTRY, 0x9f7a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH_TX_INTER_LAN_SCHEDULING_OFFSET =
{
	1,
	{
		{ dump_RDD_ETH_TX_INTER_LAN_SCHEDULING_OFFSET_ENTRY, 0x9f7b },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f7c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f7d },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_TX_DS_PICO_SEMAPHORE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f7e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FC_GLOBAL_CFG =
{
	1,
	{
		{ dump_RDD_FC_GLOBAL_CFG_ENTRY, 0x9f7f },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f81 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PACKET_BUFFER_SIZE_ASR_8 =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f82 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_MAIN_DMA_SYNCRONIZATION_ADDRESS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f83 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_DMA_SYNCRONIZATION_ADDRESS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f84 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RUNNER_FLOW_IH_RESPONSE_MUTEX =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f85 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_SLAVE_VECTOR =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_SLAVE_VECTOR, 0x9f86 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f87 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_IH_CONGESTION_THRESHOLD =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f88 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FAST_MALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x9f89 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_PICO_MALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x9f8a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RX_SBPM_TO_FPM_COPY_SEMAPHORE =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0x9f8b },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_FW_MAC_ADDRS_COUNT =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x9f8c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_TX_FAST_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0xac00 },
#if defined WL4908_EAP
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
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_TX_PICO_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0xad00 },
#if defined WL4908_EAP
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
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT EMAC_ABSOLUTE_TX_BBH_COUNTER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xb2c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR =
{
	10,
	{
		{ dump_RDD_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR_ENTRY, 0xb310 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GPON_RX_DIRECT_DESCRIPTORS =
{
#if defined WL4908_EAP
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0xb400 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FLOW_IH_RESPONSE =
{
	8,
	{
		{ dump_RDD_RUNNER_FLOW_IH_RESPONSE, 0xb6f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH_TX_MAC_TABLE =
{
	32,
	{
		{ dump_RDD_ETH_TX_MAC_DESCRIPTOR, 0xbb00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GPON_RX_NORMAL_DESCRIPTORS =
{
#if defined WL4908_EAP
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0xbe00 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_HANDLER_BUFFER =
{
	256,
	{
		{ dump_RDD_IH_BUFFER, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CSO_CHUNK_BUFFER =
{
	128,
	{
		{ dump_RDD_CSO_BUFFER_ENTRY, 0x2000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CSO_PSEUDO_HEADER_BUFFER =
{
	40,
	{
		{ dump_RDD_CSO_PSEUDO_HEADER_BUFFER_ENTRY, 0x2080 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_TIMER_7_SCHEDULER_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x20a8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RATE_CONTROL_BUDGET_ALLOCATOR_TABLE =
{
	2,
	{
		{ dump_RDD_BUDGET_ALLOCATOR_ENTRY, 0x20b0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_REASON_TO_METER_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_METER_ENTRY, 0x20c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_MAIN_PROFILING_BUFFER_RUNNER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x2100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FREE_PACKET_DESCRIPTORS_POOL =
{
	8,
	{
		{ dump_RDD_PACKET_DESCRIPTOR, 0x2200 },
#if defined WL4908_EAP
		{ dump_RDD_BBH_TX_DESCRIPTOR, 0x2200 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_FILTERS_LOOKUP_TABLE =
{
	4,
	{
		{ dump_RDD_INGRESS_FILTERS_LOOKUP_ENTRY, 0x8200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_TRAFFIC_CLASS_TO_QUEUE_TABLE =
{
	1,
	{
		{ dump_RDD_US_QUEUE_ENTRY, 0x83c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_CHANNELS_8_39_TABLE =
{
	32,
	{
		{ dump_RDD_WAN_CHANNEL_8_39_DESCRIPTOR, 0x8400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RUNNER_FLOW_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_RUNNER_FLOW_HEADER_BUFFER, 0x8800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_SBPM_REPLY =
{
	128,
	{
		{ dump_RDD_SBPM_REPLY_ENTRY, 0x8980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_POLICER_TABLE =
{
	16,
	{
		{ dump_RDD_POLICER_ENTRY, 0x8a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_TX_SERVICE_QUEUE_SCHEDULER_TABLE =
{
	128,
	{
		{ dump_RDD_WAN_TX_SERVICE_QUEUE_SCHEDULER_DESCRIPTOR, 0x8b00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_WAN_FLOW_TABLE =
{
	4,
	{
		{ dump_RDD_US_WAN_FLOW_ENTRY, 0x8c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_TX_BBH_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_CPU_TX_BBH_DESCRIPTORS_ENTRY, 0x9000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FORWARDING_MATRIX_TABLE =
{
	1,
	{
		{ dump_RDD_FORWARDING_MATRIX_ENTRY, 0x9100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_TIMER_SCHEDULER_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TIMER_SCHEDULER_PRIMITIVE_ENTRY, 0x9190 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_MAIN_TIMER_TASK_DESCRIPTOR_TABLE =
{
	8,
	{
		{ dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY, 0x91a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x91c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_RX_PICO_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0x9200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9240 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9280 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_TIMER_TASK_DESCRIPTOR_TABLE =
{
	8,
	{
		{ dump_RDD_TIMER_TASK_DESCRIPTOR_ENTRY, 0x92c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FC_L2_UCAST_TUPLE_BUFFER =
{
	32,
	{
		{ dump_RDD_FC_L2_UCAST_TUPLE_ENTRY, 0x92e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RATE_LIMITER_TABLE =
{
	8,
	{
		{ dump_RDD_RATE_LIMITER_ENTRY, 0x9300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_QUEUE_PROFILE_TABLE =
{
	16,
	{
		{ dump_RDD_QUEUE_PROFILE, 0x9380 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CONNECTION_CONTEXT_BUFFER =
{
	128,
	{
		{ dump_RDD_CONNECTION_CONTEXT_BUFFER_ENTRY, 0x9400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_CONTEXT_TABLE =
{
	8,
	{
		{ dump_RDD_US_INGRESS_CLASSIFICATION_CONTEXT_ENTRY, 0x9800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_CHANNELS_0_7_TABLE =
{
	88,
	{
		{ dump_RDD_WAN_CHANNEL_0_7_DESCRIPTOR, 0xa000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE =
{
	8,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_ENTRY, 0xa2c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FAST_RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_FAST_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY, 0xa2e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_RX_METER_TABLE =
{
	8,
	{
		{ dump_RDD_CPU_RX_METER_ENTRY, 0xa300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_HANDLER_SKB_DATA_POINTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa380 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CONNECTION_CONTEXT_REMAINING_BUFFER =
{
#if defined WL4908_EAP
	76,
	{
		{ dump_RDD_CONTEXT_CONTINUATION_ENTRY, 0xa400 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_RUNNER_GLOBAL_REGISTERS_INIT =
{
	4,
	{
		{ dump_RDD_PICO_RUNNER_GLOBAL_REGISTERS_INIT_ENTRY, 0xa660 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_GRE_RUNNER_FLOW_HEADER_BUFFER =
{
	128,
	{
		{ dump_RDD_GRE_RUNNER_FLOW_HEADER_BUFFER, 0xa680 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PROFILING_BUFFER_PICO_RUNNER =
{
	256,
	{
		{ dump_RDD_PROFILING_BUFFER_PICO_RUNNER, 0xa700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_RULE_CFG_TABLE =
{
	8,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_RULE_CFG_ENTRY, 0xa800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_FILTERS_PARAMETER_TABLE =
{
	1,
	{
		{ dump_RDD_INGRESS_FILTERS_PARAMETER_ENTRY, 0xa880 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FC_L2_UCAST_CONNECTION_BUFFER =
{
	16,
	{
		{ dump_RDD_FC_L2_UCAST_CONNECTION_ENTRY, 0xa8f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_RATE_LIMITER_TABLE =
{
	16,
	{
		{ dump_RDD_INGRESS_RATE_LIMITER_ENTRY, 0xa900 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINB_PARAM =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xa950 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DHD_RX_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xa960 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETHWAN_ABSOLUTE_TX_BBH_COUNTER =
{
	1,
	{
		{ dump_RDD_GPON_ABSOLUTE_TX_COUNTER, 0xa980 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT PRIVATE_B_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_DUMMY_STORE_ENTRY, 0xa981 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_MAIN_TIMER_CONTROL_DESCRIPTOR =
{
	2,
	{
		{ dump_RDD_TIMER_CONTROL_DESCRIPTOR, 0xa982 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_ETH0_EEE_MODE_CONFIG_MESSAGE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa984 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETHWAN_ABSOLUTE_TX_FIRMWARE_COUNTER =
{
	1,
	{
		{ dump_RDD_GPON_ABSOLUTE_TX_COUNTER, 0xa988 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xa989 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_TIMER_CONTROL_DESCRIPTOR =
{
	2,
	{
		{ dump_RDD_TIMER_CONTROL_DESCRIPTOR, 0xa98a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_BPM_EXTRA_DDR_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xa98c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GPON_ABSOLUTE_TX_BBH_COUNTER =
{
	1,
	{
		{ dump_RDD_GPON_ABSOLUTE_TX_COUNTER, 0xa990 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_TOTAL_PPS_RATE_LIMITER =
{
	8,
	{
		{ dump_RDD_TOTAL_PPS_RATE_LIMITER_ENTRY, 0xa9b8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_TX_MESSAGE_DATA_BUFFER =
{
	64,
	{
		{ dump_RDD_CPU_TX_MESSAGE_DATA_BUFFER_ENTRY, 0xa9c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_SPDSVC_CONTEXT_TABLE =
{
	80,
	{
		{ dump_RDD_SPDSVC_CONTEXT_ENTRY, 0xaa00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_PICOB_PARAM =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xaa50 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_0_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xaa60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_ROUTER_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0xaa80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPR0_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xaac0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_0_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xaae0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_RX_FAST_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0xab00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_DEBUG_BUFFER =
{
	4,
	{
		{ dump_RDD_DEBUG_BUFFER_ENTRY, 0xab40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPR1_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xabc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_1_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xabe0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_TX_FAST_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0xac00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0xac00 },
#if defined WL4908_EAP
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
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FW_MAC_ADDRS =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xac80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_TX_PICO_QUEUE =
{
	8,
	{
		{ dump_RDD_CPU_TX_DESCRIPTOR, 0xad00 },
		{ dump_RDD_CPU_TX_DESCRIPTOR_CORE, 0xad00 },
#if defined WL4908_EAP
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
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_TABLE =
{
	2,
	{
		{ dump_RDD_US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_ENTRY, 0xad80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_1_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xade0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CSO_CONTEXT_TABLE =
{
	84,
	{
		{ dump_RDD_CSO_CONTEXT_ENTRY, 0xae00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_OPTIMIZED_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xae54 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_ONE_BUFFER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xae58 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_2_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xae60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPR2_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xae80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_2_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xaea0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_TX_FPM_ALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xaec0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_GPE_COMMAND_PRIMITIVE_TABLE =
{
	2,
	{
		{ dump_RDD_GPE_COMMAND_PRIMITIVE_ENTRY, 0xaee0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_FILTERS_CONFIGURATION_TABLE =
{
	4,
	{
		{ dump_RDD_INGRESS_FILTERS_CONFIGURATION_ENTRY, 0xaf20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xaf3c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RUNNER_FLOW_HEADER_DESCRIPTOR =
{
	8,
	{
		{ dump_RDD_RUNNER_FLOW_HEADER_DESCRIPTOR, 0xaf40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_NULL_BUFFER =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0xaf58 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_PARAMETERS_BLOCK =
{
	20,
	{
		{ dump_RDD_CPU_PARAMETERS_BLOCK_ENTRY, 0xaf60 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xaf74 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GPON_ABSOLUTE_TX_FIRMWARE_COUNTER =
{
	1,
	{
		{ dump_RDD_GPON_ABSOLUTE_TX_COUNTER, 0xaf78 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE =
{
	2,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY, 0xafa0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xafb0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_SYSTEM_CONFIGURATION =
{
	36,
	{
		{ dump_RDD_SYSTEM_CONFIGURATION, 0xafc0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_1_BUFFERS_BASE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xafe4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FAST_MALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xafe8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE =
{
	1,
	{
		{ dump_RDD_BROADCOM_SWITCH_PORT_MAPPING, 0xaff0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE =
{
	2,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_ENTRY, 0xb000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_TABLE =
{
	1,
	{
		{ dump_RDD_US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_ENTRY, 0xb010 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_TX_SCRATCH =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb030 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_REASON_AND_SRC_BRIDGE_PORT_TO_METER_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_METER_ENTRY, 0xb048 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_RX_PICO_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_RX_PICO_INGRESS_QUEUE_PTR, 0xb05a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CONNECTION_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_CONNECTION_TABLE_CONFIG, 0xb05c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT BROADCOM_SWITCH_PORT_TO_BRIDGE_PORT_MAPPING_TABLE =
{
	1,
	{
		{ dump_RDD_BROADCOM_SWITCH_PORT_MAPPING, 0xb060 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb069 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_BUFFER_HEADROOM_SIZE =
{
	2,
	{
		{ dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE, 0xb06a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CONTEXT_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_CONTEXT_TABLE_CONFIG, 0xb06c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_KEY_BUFFER =
{
	16,
	{
		{ dump_RDD_SIXTEEN_BYTES, 0xb070 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_MALLOC_RESULT_TABLE =
{
	4,
	{
		{ dump_RDD_BYTES_4, 0xb080 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR =
{
	6,
	{
		{ dump_RDD_US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR_ENTRY, 0xb088 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION =
{
	2,
	{
		{ dump_RDD_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION, 0xb08e },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DATA_POINTER_DUMMY_TARGET =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb090 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_ENTRY, 0xb098 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_DEBUG_PERIPHERALS_STATUS_REGISTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb09c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_TASK_REORDER_FIFO =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_TASK_REORDER_ENTRY, 0xb0a0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT IH_BUFFER_BBH_POINTER =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb0a4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0a8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CONTEXT_CONTINUATION_TABLE_CONFIG =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb0b0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_TX_DATA_POINTER_DUMMY_TARGET =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xb0b4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RATE_CONTROLLER_EXPONENT_TABLE =
{
	1,
	{
		{ dump_RDD_RATE_CONTROLLER_EXPONENT_ENTRY, 0xb0b8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_RX_FAST_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_CPU_RX_FAST_INGRESS_QUEUE_PTR, 0xb0bc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 0xb0be },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 0xb0c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR =
{
	2,
	{
		{ dump_RDD_PARALLEL_PROCESSING_IH_BUFFER_PTR, 0xb0c2 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_ANY_SRC_PORT_FLOW_COUNTER =
{
	2,
	{
		{ dump_RDD_ANY_SRC_PORT_FLOW_COUNTER, 0xb0c4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_TIMER_7_SCHEDULER_NEXT_ENTRY =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb0c6 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_MEMLIB_SEMAPHORE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb0c8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETHWAN2_RX_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xb0ca },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RUNNER_CONGESTION_STATE =
{
	2,
	{
		{ dump_RDD_RUNNER_CONGESTION_STATE_ENTRY, 0xb0cc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_ENQUEUE_INGRESS_QUEUE_PTR =
{
	2,
	{
		{ dump_RDD_WAN_ENQUEUE_INGRESS_QUEUE_PTR_ENTRY, 0xb0ce },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0xb0d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FC_GLOBAL_CFG =
{
	1,
	{
		{ dump_RDD_FC_GLOBAL_CFG_ENTRY, 0xb0d2 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETHWAN2_SWITCH_PORT =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0d3 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0d4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0d5 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PACKET_BUFFER_SIZE_ASR_8 =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0d6 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_MAIN_DMA_SYNCRONIZATION_ADDRESS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0d7 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_DMA_SYNCRONIZATION_ADDRESS =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0d8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RUNNER_FLOW_IH_RESPONSE_MUTEX =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0d9 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DSL_BUFFER_ALIGNMENT =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0da },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_SLAVE_VECTOR =
{
	1,
	{
		{ dump_RDD_PARALLEL_PROCESSING_SLAVE_VECTOR, 0xb0db },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0dc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_IH_CONGESTION_THRESHOLD =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0dd },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FAST_MALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb0de },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_PICO_MALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb0df },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DHD_RX_FPM_ALLOC_RESULT_MUTEX =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb0e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RX_SBPM_TO_FPM_COPY_SEMAPHORE =
{
	1,
	{
		{ dump_RDD_BYTE_1, 0xb0e1 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_FW_MAC_ADDRS_COUNT =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xb0e2 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RUNNER_FLOW_IH_RESPONSE =
{
	8,
	{
		{ dump_RDD_RUNNER_FLOW_IH_RESPONSE, 0xb6f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH2_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xba00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH1_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xbc00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETH0_RX_DESCRIPTORS =
{
	8,
	{
		{ dump_RDD_ETH_RX_DESCRIPTORS, 0xbe00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT BBH_TX_WAN_CHANNEL_INDEX =
{
	4,
	{
		{ dump_RDD_BBH_TX_WAN_CHANNEL_INDEX, 0xbfe8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT FC_MCAST_RUNNER_A_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_DDR_CACHE_FIFO =
{
	16,
	{
		{ dump_RDD_SIXTEEN_BYTES, 0x2000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_RX_RUNNER_A_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x3000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MAC_TABLE =
{
	8,
	{
		{ dump_RDD_MAC_ENTRY, 0x3800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_COUNTERS_TABLE =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0x3a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_DESCRIPTOR_TABLE =
{
	16,
	{
		{ dump_RDD_DDR_QUEUE_DESCRIPTOR, 0x3c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MAC_TABLE_CAM =
{
	8,
	{
		{ dump_RDD_MAC_ENTRY, 0x3e00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT TRACE_C_TABLE =
{
	8,
	{
		{ dump_RDD_TRACE_C_ENTRY, 0x3f00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINA_CURR_OFFSET =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x3f20 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x3f30 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE_LAST_ENTRY =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x3f34 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT FREE_SKB_INDEXES_DDR_FIFO_TAIL =
{
	4,
	{
		{ dump_RDD_FREE_SKB_INDEXES_FIFO_TAIL, 0x3f38 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT BPM_REPLY_RUNNER_A =
{
	48,
	{
		{ dump_RDD_BPM_REPLY, 0x3f40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DDR_ADDRESS_FOR_SKB_DATA_POINTERS_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x3f70 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINA_BASE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x3f74 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_PICOA_BASE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x3f76 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RATE_CONTROLLER_EXPONENT_TABLE =
{
	1,
	{
		{ dump_RDD_RATE_CONTROLLER_EXPONENT_ENTRY, 0x3f78 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPF_CFG =
{
	4,
	{
		{ dump_RDD_CAPWAPF_CFG_ENTRY, 0x3f7c },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_REASON_TO_CPU_RX_QUEUE_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_CPU_RX_QUEUE_ENTRY, 0x3f80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GPON_SKB_ENQUEUED_INDEXES_FIFO =
{
	48,
	{
		{ dump_RDD_GPON_SKB_ENQUEUED_INDEXES_FIFO_ENTRY, 0x4000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CONNECTION_BUFFER_TABLE =
{
	16,
	{
		{ dump_RDD_CONNECTION_ENTRY, 0x4600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT INTERRUPT_COALESCING_CONFIG_TABLE =
{
	4,
	{
		{ dump_RDD_INTERRUPT_COALESCING_CONFIG, 0x4740 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MAC_CONTEXT_TABLE =
{
	2,
	{
		{ dump_RDD_MAC_CONTEXT_ENTRY, 0x4780 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x4800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE =
{
	16,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_LONG_LOOKUP_ENTRY, 0x5000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT PM_COUNTERS =
{
	6144,
	{
		{ dump_RDD_PM_COUNTERS, 0x5800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT ETHWAN2_RX_INGRESS_QUEUE =
{
#if defined WL4908_EAP
	8,
	{
		{ dump_RDD_ETHWAN2_RX_DESCRIPTOR, 0x7000 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_CPU_TX_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x7100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPF0_CPU_TX_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x7200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPF1_CPU_TX_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x7300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPF2_CPU_TX_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x7400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RING_DESCRIPTORS_TABLE =
{
	16,
	{
		{ dump_RDD_RING_DESCRIPTOR, 0x7500 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DS_RING_PACKET_DESCRIPTORS_CACHE =
{
	16,
	{
		{ dump_RDD_CPU_RX_DESCRIPTOR, 0x7600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_DDR_QUEUE_ADDRESS_TABLE =
{
	8,
	{
		{ dump_RDD_DDR_QUEUE_ADDRESS_ENTRY, 0x7700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RATE_SHAPERS_STATUS_DESCRIPTOR =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x7800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MAC_CONTEXT_TABLE_CAM =
{
	2,
	{
		{ dump_RDD_MAC_CONTEXT_ENTRY, 0x7880 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MAC_EXTENSION_TABLE =
{
	1,
	{
		{ dump_RDD_MAC_EXTENSION_ENTRY, 0x78c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT SERVICE_QUEUES_CFG =
{
	20,
	{
		{ dump_RDD_SERVICE_QUEUES_CFG_ENTRY, 0x7900 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT TIMER_7_TIMER_PERIOD =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7914 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT INTERRUPT_COALESCING_TIMER_PERIOD =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7916 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MAC_EXTENSION_TABLE_CAM =
{
	1,
	{
		{ dump_RDD_MAC_EXTENSION_ENTRY, 0x7918 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT INTERRUPT_COALESCING_TIMER_ARMED =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x7938 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT COMMON_A_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_DUMMY_STORE_ENTRY, 0x793a },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT FC_SERVICE_QUEUE_MODE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x793b },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT PM_COUNTERS_BUFFER =
{
	32,
	{
		{ dump_RDD_PM_COUNTERS_BUFFER, 0x7940 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPF_STATS =
{
	32,
	{
		{ dump_RDD_CAPWAPF_STATS_ENTRY, 0x7960 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MAIN_A_DEBUG_TRACE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x7a00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT PICO_A_DEBUG_TRACE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0x7c00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE =
{
	16,
	{
		{ dump_RDD_INGRESS_CLASSIFICATION_LONG_LOOKUP_ENTRY, 0x8000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_RX_RUNNER_B_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x8800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_INGRESS_CLASSIFICATION_COUNTERS_TABLE =
{
	2,
	{
		{ dump_RDD_BYTES_2, 0x9000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE =
{
#if defined WL4908_EAP
	8,
	{
		{ dump_RDD_BBH_RX_DESCRIPTOR, 0x9200 },
#endif
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
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
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_TX_SERVICE_QUEUES_TABLE =
{
	32,
	{
		{ dump_RDD_WAN_TX_SERVICE_QUEUE_DESCRIPTOR, 0x9400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
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
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_TX_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0x9d00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CONNECTION_BUFFER_TABLE =
{
	16,
	{
		{ dump_RDD_CONNECTION_ENTRY, 0x9e00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT IPV6_HOST_ADDRESS_CRC_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9f40 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GPON_SKB_ENQUEUED_INDEXES_FREE_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0x9f80 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINB_CURR_OFFSET =
{
	8,
	{
		{ dump_RDD_EIGHT_BYTES, 0x9fd0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT IPV4_HOST_ADDRESS_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0x9fe0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
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
#if defined WL4908_EAP
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
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_TX_QUEUES_TABLE =
{
	16,
	{
		{ dump_RDD_WAN_TX_QUEUE_DESCRIPTOR, 0xb000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_TX_RUNNER_B_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0xc000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RING_PACKET_DESCRIPTORS_CACHE =
{
	16,
	{
		{ dump_RDD_CPU_RX_DESCRIPTOR, 0xc100 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT GPON_SKB_ENQUEUED_INDEXES_PUT_PTR =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xc200 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_CPU_REASON_TO_CPU_RX_QUEUE_TABLE =
{
	1,
	{
		{ dump_RDD_CPU_REASON_TO_CPU_RX_QUEUE_ENTRY, 0xc250 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DUMMY_WAN_TX_QUEUE_DESCRIPTOR =
{
	16,
	{
		{ dump_RDD_DUMMY_WAN_TX_QUEUE_DESCRIPTOR, 0xc2d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPR_CONTEXT_CAM_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xc2e0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CPU_TX_DESCRIPTOR_QUEUE_TAIL_TABLE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xc2f0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_MAINB_BASE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xc2f4 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT RUNNER_FWTRACE_PICOB_BASE =
{
	2,
	{
		{ dump_RDD_TWO_BYTES, 0xc2f6 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPR_CFG =
{
	4,
	{
		{ dump_RDD_CAPWAPR_CFG_ENTRY, 0xc2f8 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT COMMON_B_DUMMY_STORE =
{
	1,
	{
		{ dump_RDD_DUMMY_STORE_ENTRY, 0xc2fc },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT PACKET_SRAM_TO_DDR_COPY_BUFFER_1 =
{
	128,
	{
		{ dump_RDD_PACKET_SRAM_TO_DDR_COPY_BUFFER, 0xc300 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT PACKET_SRAM_TO_DDR_COPY_BUFFER_2 =
{
	128,
	{
		{ dump_RDD_PACKET_SRAM_TO_DDR_COPY_BUFFER, 0xc380 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT DUMMY_RATE_CONTROLLER_DESCRIPTOR =
{
	64,
	{
		{ dump_RDD_DUMMY_RATE_CONTROLLER_DESCRIPTOR, 0xc400 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LAN5_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc440 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LAN0_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc480 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LAN6_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc4c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LAN1_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc500 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LAN7_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc540 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LAN2_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc580 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPR_STATS =
{
	48,
	{
		{ dump_RDD_CAPWAPR_STATS_ENTRY, 0xc5c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LAN3_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc600 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPR_CONTEXT_RING_TABLE =
{
	4,
	{
		{ dump_RDD_FOUR_BYTES, 0xc640 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAPR_FLUSH_TABLE =
{
	1,
	{
		{ dump_RDD_CAPWAPR_FLUSH_ENTRY, 0xc650 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT LAN4_INGRESS_FIFO =
{
	64,
	{
		{ dump_RDD_LAN_INGRESS_FIFO_ENTRY, 0xc680 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CAPWAP_CFG =
{
	18,
	{
		{ dump_RDD_CAPWAP_CFG_ENTRY, 0xc6c0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT FC_FLOW_IP_ADDRESSES_TABLE =
{
	48,
	{
		{ dump_RDD_FC_FLOW_IP_ADDRESSES_ENTRY, 0xc700 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT BPM_REPLY_RUNNER_B =
{
	48,
	{
		{ dump_RDD_BPM_REPLY, 0xc7d0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RATE_CONTROLLERS_TABLE =
{
	48,
	{
		{ dump_RDD_US_RATE_CONTROLLER_DESCRIPTOR, 0xc800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD =
{
	256,
	{
		{ dump_RDD_RUNNER_SCRATCHPAD, 0xe000 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT WAN_ENQUEUE_INGRESS_QUEUE =
{
	1,
	{
		{ dump_RDD_INGRESS_QUEUE_ENTRY, 0xe800 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT MAIN_B_DEBUG_TRACE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xea00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT PICO_B_DEBUG_TRACE =
{
	1,
	{
		{ dump_RDD_ONE_BYTE, 0xec00 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT BPM_PACKET_BUFFERS =
{
	2048,
	{
		{ dump_RDD_BPM_PACKET_BUFFER, 0x0 },
		{ 0, 0 },
	}
};
#endif
#if defined WL4908_EAP
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
#if defined WL4908_EAP
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
#if defined WL4908_EAP
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
#if defined WL4908_EAP
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
#if defined WL4908_EAP
static DUMP_RUNNERREG_STRUCT CONTEXT_CONTINUATION_TABLE =
{
#if defined WL4908_EAP
	76,
	{
		{ dump_RDD_CONTEXT_CONTINUATION_ENTRY, 0x0 },
#endif
		{ 0, 0 },
	}
};
#endif

TABLE_STRUCT RUNNER_TABLES[NUMBER_OF_TABLES] =
{
#if defined WL4908_EAP
	{ "INGRESS_HANDLER_BUFFER", 1, PRIVATE_A_INDEX, &INGRESS_HANDLER_BUFFER, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FREE_PACKET_DESCRIPTORS_POOL", 1, PRIVATE_A_INDEX, &DS_FREE_PACKET_DESCRIPTORS_POOL, 2048, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CONNECTION_CONTEXT_BUFFER", 1, PRIVATE_A_INDEX, &DS_CONNECTION_CONTEXT_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_GSO_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &DS_GSO_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_GSO_PSEUDO_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &DS_GSO_PSEUDO_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_TIMER_7_SCHEDULER_PRIMITIVE_TABLE", 1, PRIVATE_A_INDEX, &DS_TIMER_7_SCHEDULER_PRIMITIVE_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RATE_SHAPER_BUDGET_ALLOCATOR_TABLE", 1, PRIVATE_A_INDEX, &DS_RATE_SHAPER_BUDGET_ALLOCATOR_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_REASON_TO_METER_TABLE", 1, PRIVATE_A_INDEX, &DS_CPU_REASON_TO_METER_TABLE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_GSO_CHUNK_BUFFER", 1, PRIVATE_A_INDEX, &DS_GSO_CHUNK_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_RX_METER_TABLE", 1, PRIVATE_A_INDEX, &DS_CPU_RX_METER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_WAN_FLOW_TABLE", 1, PRIVATE_A_INDEX, &DS_WAN_FLOW_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_CONTEXT_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_CONTEXT_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPF_CONTEXT_BUFFER", 1, PRIVATE_A_INDEX, &CAPWAPF_CONTEXT_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SERVICE_QUEUES_RATE_LIMITER_TABLE", 1, PRIVATE_A_INDEX, &SERVICE_QUEUES_RATE_LIMITER_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_MAIN_TIMER_TASK_DESCRIPTOR_TABLE", 1, PRIVATE_A_INDEX, &DS_MAIN_TIMER_TASK_DESCRIPTOR_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_TIMER_TASK_DESCRIPTOR_TABLE", 1, PRIVATE_A_INDEX, &DS_PICO_TIMER_TASK_DESCRIPTOR_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_MAIN_PROFILING_BUFFER_RUNNER", 1, PRIVATE_A_INDEX, &DS_MAIN_PROFILING_BUFFER_RUNNER, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_FILTERS_PARAMETER_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_FILTERS_PARAMETER_TABLE, 2, 16, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_POLICER_TABLE", 1, PRIVATE_A_INDEX, &DS_POLICER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CONNECTION_CONTEXT_REMAINING_BUFFER", 1, PRIVATE_A_INDEX, &DS_CONNECTION_CONTEXT_REMAINING_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH_TX_QUEUES_TABLE", 1, PRIVATE_A_INDEX, &ETH_TX_QUEUES_TABLE, 72, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FC_L2_UCAST_TUPLE_BUFFER", 1, PRIVATE_A_INDEX, &DS_FC_L2_UCAST_TUPLE_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FORWARDING_MATRIX_TABLE", 1, PRIVATE_A_INDEX, &DS_FORWARDING_MATRIX_TABLE, 9, 16, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_TIMER_SCHEDULER_PRIMITIVE_TABLE", 1, PRIVATE_A_INDEX, &DS_TIMER_SCHEDULER_PRIMITIVE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RATE_LIMITER_REMAINDER_TABLE", 1, PRIVATE_A_INDEX, &RATE_LIMITER_REMAINDER_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_WAN_UDP_FILTER_TABLE", 1, PRIVATE_A_INDEX, &DS_WAN_UDP_FILTER_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "FC_MCAST_PORT_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &FC_MCAST_PORT_HEADER_BUFFER, 8, 64, 1 },
#endif
#if defined WL4908_EAP
	{ "DOWNSTREAM_LAN_ENQUEUE_SQ_PD", 1, PRIVATE_A_INDEX, &DOWNSTREAM_LAN_ENQUEUE_SQ_PD, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CONNECTION_CONTEXT_MULTICAST_BUFFER", 1, PRIVATE_A_INDEX, &DS_CONNECTION_CONTEXT_MULTICAST_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FC_MCAST_PACKET_SAVE_DATA_TABLE", 1, PRIVATE_A_INDEX, &DS_FC_MCAST_PACKET_SAVE_DATA_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FAST_RUNNER_GLOBAL_REGISTERS_INIT", 1, PRIVATE_A_INDEX, &DS_FAST_RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SBPM_REPLY", 1, PRIVATE_A_INDEX, &SBPM_REPLY, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH_TX_QUEUES_POINTERS_TABLE", 1, PRIVATE_A_INDEX, &ETH_TX_QUEUES_POINTERS_TABLE, 72, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_RUNNER_GLOBAL_REGISTERS_INIT", 1, PRIVATE_A_INDEX, &DS_PICO_RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_FILTERS_LOOKUP_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_FILTERS_LOOKUP_TABLE, 2, 16, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_RX_SQ_PD_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &CPU_RX_SQ_PD_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_TX_BBH_DESCRIPTORS", 1, PRIVATE_A_INDEX, &DS_CPU_TX_BBH_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "INGRESS_HANDLER_SKB_DATA_POINTER", 1, PRIVATE_A_INDEX, &INGRESS_HANDLER_SKB_DATA_POINTER, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RUNNER_FLOW_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &DS_RUNNER_FLOW_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GSO_PICO_QUEUE", 1, PRIVATE_A_INDEX, &GSO_PICO_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DOWNSTREAM_LAN_ENQUEUE_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DOWNSTREAM_LAN_ENQUEUE_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE", 1, PRIVATE_A_INDEX, &DS_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE", 1, PRIVATE_A_INDEX, &DS_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_TX_MESSAGE_DATA_BUFFER", 1, PRIVATE_A_INDEX, &DS_CPU_TX_MESSAGE_DATA_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RATE_LIMITER_TABLE", 1, PRIVATE_A_INDEX, &DS_RATE_LIMITER_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_GRE_RUNNER_FLOW_HEADER_BUFFER", 1, PRIVATE_A_INDEX, &DS_GRE_RUNNER_FLOW_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_RULE_CFG_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_RULE_CFG_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PROFILING_BUFFER_PICO_RUNNER", 1, PRIVATE_A_INDEX, &DS_PROFILING_BUFFER_PICO_RUNNER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_SPDSVC_CONTEXT_TABLE", 1, PRIVATE_A_INDEX, &DS_SPDSVC_CONTEXT_TABLE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FC_L2_UCAST_CONNECTION_BUFFER", 1, PRIVATE_A_INDEX, &DS_FC_L2_UCAST_CONNECTION_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE", 1, PRIVATE_A_INDEX, &DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH_TX_LOCAL_REGISTERS", 1, PRIVATE_A_INDEX, &ETH_TX_LOCAL_REGISTERS, 9, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_TOTAL_PPS_RATE_LIMITER", 1, PRIVATE_A_INDEX, &DS_TOTAL_PPS_RATE_LIMITER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_MAINA_PARAM", 1, PRIVATE_A_INDEX, &RUNNER_FWTRACE_MAINA_PARAM, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_RX_PD_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &CPU_RX_PD_INGRESS_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_QUEUE_PROFILE_TABLE", 1, PRIVATE_A_INDEX, &DS_QUEUE_PROFILE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_RX_FAST_PD_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &CPU_RX_FAST_PD_INGRESS_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "EMAC_SKB_ENQUEUED_INDEXES_FIFO", 1, PRIVATE_A_INDEX, &EMAC_SKB_ENQUEUED_INDEXES_FIFO, 5, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_TX_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_CPU_TX_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_GPE_COMMAND_PRIMITIVE_TABLE", 1, PRIVATE_A_INDEX, &DS_GPE_COMMAND_PRIMITIVE_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_SQ_ENQUEUE_QUEUE", 1, PRIVATE_A_INDEX, &DS_SQ_ENQUEUE_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_NULL_BUFFER", 1, PRIVATE_A_INDEX, &DS_NULL_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_FILTERS_CONFIGURATION_TABLE", 1, PRIVATE_A_INDEX, &DS_INGRESS_FILTERS_CONFIGURATION_TABLE, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_PARAMETERS_BLOCK", 1, PRIVATE_A_INDEX, &DS_CPU_PARAMETERS_BLOCK, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_WAN_UDP_FILTER_CONTROL_TABLE", 1, PRIVATE_A_INDEX, &DS_WAN_UDP_FILTER_CONTROL_TABLE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RUNNER_FLOW_HEADER_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_RUNNER_FLOW_HEADER_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_GSO_CONTEXT_TABLE", 1, PRIVATE_A_INDEX, &DS_GSO_CONTEXT_TABLE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_BPM_EXTRA_DDR_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_EXTRA_DDR_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MCAST_LKP_WORD3_CRC_BUFFER", 1, PRIVATE_A_INDEX, &MCAST_LKP_WORD3_CRC_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_PICOA_PARAM", 1, PRIVATE_A_INDEX, &RUNNER_FWTRACE_PICOA_PARAM, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_DATA_POINTER_DUMMY_TARGET", 1, PRIVATE_A_INDEX, &DS_DATA_POINTER_DUMMY_TARGET, 5, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_BPM_DDR_OPTIMIZED_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_OPTIMIZED_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FAST_MALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_FAST_MALLOC_RESULT_TABLE, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SERVICE_QUEUES_WLAN_SCRATCH", 1, PRIVATE_A_INDEX, &SERVICE_QUEUES_WLAN_SCRATCH, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_MALLOC_RESULT_TABLE", 1, PRIVATE_A_INDEX, &DS_PICO_MALLOC_RESULT_TABLE, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE", 1, PRIVATE_A_INDEX, &DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "EMAC_SKB_ENQUEUED_INDEXES_PUT_PTR", 1, PRIVATE_A_INDEX, &EMAC_SKB_ENQUEUED_INDEXES_PUT_PTR, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_RX_PICO_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DS_CPU_RX_PICO_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_SYSTEM_CONFIGURATION", 1, PRIVATE_A_INDEX, &DS_SYSTEM_CONFIGURATION, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_BPM_DDR_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_BPM_DDR_1_BUFFERS_BASE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_1_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CONNECTION_TABLE_CONFIG", 1, PRIVATE_A_INDEX, &DS_CONNECTION_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "EMAC_SKB_ENQUEUED_INDEXES_FREE_PTR", 1, PRIVATE_A_INDEX, &EMAC_SKB_ENQUEUED_INDEXES_FREE_PTR, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_ROUTER_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DS_ROUTER_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE", 1, PRIVATE_A_INDEX, &DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "HASH_BUFFER", 1, PRIVATE_A_INDEX, &HASH_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE", 1, PRIVATE_A_INDEX, &DS_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_RX_FAST_INGRESS_QUEUE", 1, PRIVATE_A_INDEX, &DS_CPU_RX_FAST_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_DEBUG_BUFFER", 1, PRIVATE_A_INDEX, &DS_DEBUG_BUFFER, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FW_MAC_ADDRS", 1, PRIVATE_A_INDEX, &DS_FW_MAC_ADDRS, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "BITS_CALC_MASKS_TABLE", 1, PRIVATE_A_INDEX, &BITS_CALC_MASKS_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH_TX_SCRATCH", 1, PRIVATE_A_INDEX, &ETH_TX_SCRATCH, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SERVICE_QUEUES_OVERALL_RATE_LIMITER", 1, PRIVATE_A_INDEX, &SERVICE_QUEUES_OVERALL_RATE_LIMITER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CONTEXT_TABLE_CONFIG", 1, PRIVATE_A_INDEX, &DS_CONTEXT_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_GSO_DESC_TABLE", 1, PRIVATE_A_INDEX, &DS_GSO_DESC_TABLE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_KEY_BUFFER", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_KEY_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_DEBUG_PERIPHERALS_STATUS_REGISTER", 1, PRIVATE_A_INDEX, &DS_DEBUG_PERIPHERALS_STATUS_REGISTER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CONTEXT_CONTINUATION_TABLE_CONFIG", 1, PRIVATE_A_INDEX, &DS_CONTEXT_CONTINUATION_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_MAIN_TIMER_CONTROL_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_MAIN_TIMER_CONTROL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_TIMER_CONTROL_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_PICO_TIMER_CONTROL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GSO_TX_ENQUEUE_PCI_PACKET_CONTEXT", 1, PRIVATE_A_INDEX, &GSO_TX_ENQUEUE_PCI_PACKET_CONTEXT, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_TX_ENQUEUE_PCI_PACKET_CONTEXT", 1, PRIVATE_A_INDEX, &CPU_TX_ENQUEUE_PCI_PACKET_CONTEXT, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPF_CPU_PROCESSING_TASK_REORDER_FIFO", 1, PRIVATE_A_INDEX, &CAPWAPF_CPU_PROCESSING_TASK_REORDER_FIFO, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SPDSVC_HOST_BUF_PTR", 1, PRIVATE_A_INDEX, &SPDSVC_HOST_BUF_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "EMAC_SKB_ENQUEUED_INDEXES_FIFO_COUNTERS", 1, PRIVATE_A_INDEX, &EMAC_SKB_ENQUEUED_INDEXES_FIFO_COUNTERS, 5, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH_TX_EMACS_STATUS", 1, PRIVATE_A_INDEX, &ETH_TX_EMACS_STATUS, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "IPTV_COUNTERS_BUFFER", 1, PRIVATE_A_INDEX, &IPTV_COUNTERS_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "HASH_BASED_FORWARDING_PORT_TABLE", 1, PRIVATE_A_INDEX, &HASH_BASED_FORWARDING_PORT_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_TX_DATA_POINTER_DUMMY_TARGET", 1, PRIVATE_A_INDEX, &DS_CPU_TX_DATA_POINTER_DUMMY_TARGET, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "FIREWALL_IPV6_R16_BUFFER", 1, PRIVATE_A_INDEX, &FIREWALL_IPV6_R16_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_TX_PICO_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &CPU_TX_PICO_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD", 1, PRIVATE_A_INDEX, &FREE_PACKET_DESCRIPTORS_POOL_THRESHOLD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &DOWNSTREAM_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_RX_PD_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &CPU_RX_PD_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_RX_PICO_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &DS_CPU_RX_PICO_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_BPM_DDR_BUFFER_HEADROOM_SIZE", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_BUFFER_HEADROOM_SIZE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION", 1, PRIVATE_A_INDEX, &DS_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_RX_FAST_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &DS_CPU_RX_FAST_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_ANY_SRC_PORT_FLOW_COUNTER", 1, PRIVATE_A_INDEX, &DS_ANY_SRC_PORT_FLOW_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GSO_DESC_PTR", 1, PRIVATE_A_INDEX, &GSO_DESC_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_TIMER_7_SCHEDULER_NEXT_ENTRY", 1, PRIVATE_A_INDEX, &DS_TIMER_7_SCHEDULER_NEXT_ENTRY, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_MEMLIB_SEMAPHORE", 1, PRIVATE_A_INDEX, &DS_MEMLIB_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_PHYSICAL_PORT", 1, PRIVATE_A_INDEX, &WAN_PHYSICAL_PORT, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_A_INDEX, &DOWNSTREAM_MULTICAST_LAN_ENQUEUE_SERVICE_QUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RUNNER_CONGESTION_STATE", 1, PRIVATE_A_INDEX, &DS_RUNNER_CONGESTION_STATE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR", 1, PRIVATE_A_INDEX, &DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GSO_PICO_QUEUE_PTR", 1, PRIVATE_A_INDEX, &GSO_PICO_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "PRIVATE_A_DUMMY_STORE", 1, PRIVATE_A_INDEX, &PRIVATE_A_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH_TX_INTER_LAN_SCHEDULING_OFFSET", 1, PRIVATE_A_INDEX, &ETH_TX_INTER_LAN_SCHEDULING_OFFSET, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR", 1, PRIVATE_A_INDEX, &DS_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR", 1, PRIVATE_A_INDEX, &DS_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_TX_DS_PICO_SEMAPHORE", 1, PRIVATE_A_INDEX, &CPU_TX_DS_PICO_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FC_GLOBAL_CFG", 1, PRIVATE_A_INDEX, &DS_FC_GLOBAL_CFG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR", 1, PRIVATE_A_INDEX, &DS_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PACKET_BUFFER_SIZE_ASR_8", 1, PRIVATE_A_INDEX, &DS_PACKET_BUFFER_SIZE_ASR_8, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_MAIN_DMA_SYNCRONIZATION_ADDRESS", 1, PRIVATE_A_INDEX, &DS_MAIN_DMA_SYNCRONIZATION_ADDRESS, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_DMA_SYNCRONIZATION_ADDRESS", 1, PRIVATE_A_INDEX, &DS_PICO_DMA_SYNCRONIZATION_ADDRESS, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RUNNER_FLOW_IH_RESPONSE_MUTEX", 1, PRIVATE_A_INDEX, &DS_RUNNER_FLOW_IH_RESPONSE_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PARALLEL_PROCESSING_SLAVE_VECTOR", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_SLAVE_VECTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE", 1, PRIVATE_A_INDEX, &DS_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_IH_CONGESTION_THRESHOLD", 1, PRIVATE_A_INDEX, &DS_IH_CONGESTION_THRESHOLD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FAST_MALLOC_RESULT_MUTEX", 1, PRIVATE_A_INDEX, &DS_FAST_MALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_PICO_MALLOC_RESULT_MUTEX", 1, PRIVATE_A_INDEX, &DS_PICO_MALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RX_SBPM_TO_FPM_COPY_SEMAPHORE", 1, PRIVATE_A_INDEX, &DS_RX_SBPM_TO_FPM_COPY_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_FW_MAC_ADDRS_COUNT", 1, PRIVATE_A_INDEX, &DS_FW_MAC_ADDRS_COUNT, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_TX_FAST_QUEUE", 1, PRIVATE_A_INDEX, &CPU_TX_FAST_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_TX_PICO_QUEUE", 1, PRIVATE_A_INDEX, &CPU_TX_PICO_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "EMAC_ABSOLUTE_TX_BBH_COUNTER", 1, PRIVATE_A_INDEX, &EMAC_ABSOLUTE_TX_BBH_COUNTER, 10, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR", 1, PRIVATE_A_INDEX, &FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GPON_RX_DIRECT_DESCRIPTORS", 1, PRIVATE_A_INDEX, &GPON_RX_DIRECT_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FLOW_IH_RESPONSE", 1, PRIVATE_A_INDEX, &RUNNER_FLOW_IH_RESPONSE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH_TX_MAC_TABLE", 1, PRIVATE_A_INDEX, &ETH_TX_MAC_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GPON_RX_NORMAL_DESCRIPTORS", 1, PRIVATE_A_INDEX, &GPON_RX_NORMAL_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_HANDLER_BUFFER", 1, PRIVATE_B_INDEX, &US_INGRESS_HANDLER_BUFFER, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CSO_CHUNK_BUFFER", 1, PRIVATE_B_INDEX, &US_CSO_CHUNK_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CSO_PSEUDO_HEADER_BUFFER", 1, PRIVATE_B_INDEX, &US_CSO_PSEUDO_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_TIMER_7_SCHEDULER_PRIMITIVE_TABLE", 1, PRIVATE_B_INDEX, &US_TIMER_7_SCHEDULER_PRIMITIVE_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RATE_CONTROL_BUDGET_ALLOCATOR_TABLE", 1, PRIVATE_B_INDEX, &US_RATE_CONTROL_BUDGET_ALLOCATOR_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_REASON_TO_METER_TABLE", 1, PRIVATE_B_INDEX, &US_CPU_REASON_TO_METER_TABLE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_MAIN_PROFILING_BUFFER_RUNNER", 1, PRIVATE_B_INDEX, &US_MAIN_PROFILING_BUFFER_RUNNER, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FREE_PACKET_DESCRIPTORS_POOL", 1, PRIVATE_B_INDEX, &US_FREE_PACKET_DESCRIPTORS_POOL, 3072, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_FILTERS_LOOKUP_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_FILTERS_LOOKUP_TABLE, 7, 16, 1 },
#endif
#if defined WL4908_EAP
	{ "US_TRAFFIC_CLASS_TO_QUEUE_TABLE", 1, PRIVATE_B_INDEX, &US_TRAFFIC_CLASS_TO_QUEUE_TABLE, 8, 8, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_CHANNELS_8_39_TABLE", 1, PRIVATE_B_INDEX, &WAN_CHANNELS_8_39_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RUNNER_FLOW_HEADER_BUFFER", 1, PRIVATE_B_INDEX, &US_RUNNER_FLOW_HEADER_BUFFER, 3, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_SBPM_REPLY", 1, PRIVATE_B_INDEX, &US_SBPM_REPLY, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_POLICER_TABLE", 1, PRIVATE_B_INDEX, &US_POLICER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_TX_SERVICE_QUEUE_SCHEDULER_TABLE", 1, PRIVATE_B_INDEX, &WAN_TX_SERVICE_QUEUE_SCHEDULER_TABLE, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_WAN_FLOW_TABLE", 1, PRIVATE_B_INDEX, &US_WAN_FLOW_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_TX_BBH_DESCRIPTORS", 1, PRIVATE_B_INDEX, &US_CPU_TX_BBH_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FORWARDING_MATRIX_TABLE", 1, PRIVATE_B_INDEX, &US_FORWARDING_MATRIX_TABLE, 9, 16, 1 },
#endif
#if defined WL4908_EAP
	{ "US_TIMER_SCHEDULER_PRIMITIVE_TABLE", 1, PRIVATE_B_INDEX, &US_TIMER_SCHEDULER_PRIMITIVE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_MAIN_TIMER_TASK_DESCRIPTOR_TABLE", 1, PRIVATE_B_INDEX, &US_MAIN_TIMER_TASK_DESCRIPTOR_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_KEY_PRIMITIVE_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_RX_PICO_INGRESS_QUEUE", 1, PRIVATE_B_INDEX, &US_CPU_RX_PICO_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE", 1, PRIVATE_B_INDEX, &US_FAST_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE", 1, PRIVATE_B_INDEX, &US_PICO_CPU_TX_DESCRIPTOR_ABS_DATA_PTR_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_TIMER_TASK_DESCRIPTOR_TABLE", 1, PRIVATE_B_INDEX, &US_PICO_TIMER_TASK_DESCRIPTOR_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FC_L2_UCAST_TUPLE_BUFFER", 1, PRIVATE_B_INDEX, &US_FC_L2_UCAST_TUPLE_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RATE_LIMITER_TABLE", 1, PRIVATE_B_INDEX, &US_RATE_LIMITER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_QUEUE_PROFILE_TABLE", 1, PRIVATE_B_INDEX, &US_QUEUE_PROFILE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CONNECTION_CONTEXT_BUFFER", 1, PRIVATE_B_INDEX, &US_CONNECTION_CONTEXT_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_CONTEXT_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_CONTEXT_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_CHANNELS_0_7_TABLE", 1, PRIVATE_B_INDEX, &WAN_CHANNELS_0_7_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_GENERIC_RULE_CFG_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FAST_RUNNER_GLOBAL_REGISTERS_INIT", 1, PRIVATE_B_INDEX, &US_FAST_RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_RX_METER_TABLE", 1, PRIVATE_B_INDEX, &US_CPU_RX_METER_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_HANDLER_SKB_DATA_POINTER", 1, PRIVATE_B_INDEX, &US_INGRESS_HANDLER_SKB_DATA_POINTER, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CONNECTION_CONTEXT_REMAINING_BUFFER", 1, PRIVATE_B_INDEX, &US_CONNECTION_CONTEXT_REMAINING_BUFFER, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_RUNNER_GLOBAL_REGISTERS_INIT", 1, PRIVATE_B_INDEX, &US_PICO_RUNNER_GLOBAL_REGISTERS_INIT, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_GRE_RUNNER_FLOW_HEADER_BUFFER", 1, PRIVATE_B_INDEX, &US_GRE_RUNNER_FLOW_HEADER_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PROFILING_BUFFER_PICO_RUNNER", 1, PRIVATE_B_INDEX, &US_PROFILING_BUFFER_PICO_RUNNER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_RULE_CFG_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_RULE_CFG_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_FILTERS_PARAMETER_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_FILTERS_PARAMETER_TABLE, 7, 16, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FC_L2_UCAST_CONNECTION_BUFFER", 1, PRIVATE_B_INDEX, &US_FC_L2_UCAST_CONNECTION_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_RATE_LIMITER_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_RATE_LIMITER_TABLE, 5, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_MAINB_PARAM", 1, PRIVATE_B_INDEX, &RUNNER_FWTRACE_MAINB_PARAM, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DHD_RX_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &DHD_RX_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETHWAN_ABSOLUTE_TX_BBH_COUNTER", 1, PRIVATE_B_INDEX, &ETHWAN_ABSOLUTE_TX_BBH_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "PRIVATE_B_DUMMY_STORE", 1, PRIVATE_B_INDEX, &PRIVATE_B_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_MAIN_TIMER_CONTROL_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_MAIN_TIMER_CONTROL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_ETH0_EEE_MODE_CONFIG_MESSAGE", 1, PRIVATE_B_INDEX, &US_ETH0_EEE_MODE_CONFIG_MESSAGE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETHWAN_ABSOLUTE_TX_FIRMWARE_COUNTER", 1, PRIVATE_B_INDEX, &ETHWAN_ABSOLUTE_TX_FIRMWARE_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR", 1, PRIVATE_B_INDEX, &US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_TIMER_CONTROL_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_PICO_TIMER_CONTROL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_BPM_EXTRA_DDR_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_EXTRA_DDR_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GPON_ABSOLUTE_TX_BBH_COUNTER", 1, PRIVATE_B_INDEX, &GPON_ABSOLUTE_TX_BBH_COUNTER, 40, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_TOTAL_PPS_RATE_LIMITER", 1, PRIVATE_B_INDEX, &US_TOTAL_PPS_RATE_LIMITER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_TX_MESSAGE_DATA_BUFFER", 1, PRIVATE_B_INDEX, &US_CPU_TX_MESSAGE_DATA_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_SPDSVC_CONTEXT_TABLE", 1, PRIVATE_B_INDEX, &US_SPDSVC_CONTEXT_TABLE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_PICOB_PARAM", 1, PRIVATE_B_INDEX, &RUNNER_FWTRACE_PICOB_PARAM, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_0_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_0_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_ROUTER_INGRESS_QUEUE", 1, PRIVATE_B_INDEX, &US_ROUTER_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPR0_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &CAPWAPR0_RX_DESCRIPTORS, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_0_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_0_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_RX_FAST_INGRESS_QUEUE", 1, PRIVATE_B_INDEX, &US_CPU_RX_FAST_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_DEBUG_BUFFER", 1, PRIVATE_B_INDEX, &US_DEBUG_BUFFER, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPR1_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &CAPWAPR1_RX_DESCRIPTORS, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_1_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_1_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_TX_FAST_QUEUE", 1, PRIVATE_B_INDEX, &US_CPU_TX_FAST_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FW_MAC_ADDRS", 1, PRIVATE_B_INDEX, &US_FW_MAC_ADDRS, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_TX_PICO_QUEUE", 1, PRIVATE_B_INDEX, &US_CPU_TX_PICO_QUEUE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_TABLE", 1, PRIVATE_B_INDEX, &US_OVERALL_RATE_LIMITER_WAN_CHANNEL_PTR_TABLE, 48, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_1_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_1_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CSO_CONTEXT_TABLE", 1, PRIVATE_B_INDEX, &US_CSO_CONTEXT_TABLE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_BPM_DDR_OPTIMIZED_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_OPTIMIZED_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_ONE_BUFFER", 1, PRIVATE_B_INDEX, &US_ONE_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_2_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_2_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPR2_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &CAPWAPR2_RX_DESCRIPTORS, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_2_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_2_MCAST_RX_SBPM_TO_FPM_COPY_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_TX_FPM_ALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_CPU_TX_FPM_ALLOC_RESULT_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_GPE_COMMAND_PRIMITIVE_TABLE", 1, PRIVATE_B_INDEX, &US_GPE_COMMAND_PRIMITIVE_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_FILTERS_CONFIGURATION_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_FILTERS_CONFIGURATION_TABLE, 7, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_1_OPTIMIZED_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RUNNER_FLOW_HEADER_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_RUNNER_FLOW_HEADER_DESCRIPTOR, 3, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_NULL_BUFFER", 1, PRIVATE_B_INDEX, &US_NULL_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_PARAMETERS_BLOCK", 1, PRIVATE_B_INDEX, &US_CPU_PARAMETERS_BLOCK, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_BPM_DDR_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GPON_ABSOLUTE_TX_FIRMWARE_COUNTER", 1, PRIVATE_B_INDEX, &GPON_ABSOLUTE_TX_FIRMWARE_COUNTER, 40, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE", 1, PRIVATE_B_INDEX, &US_FAST_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_CAM, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_SYSTEM_CONFIGURATION", 1, PRIVATE_B_INDEX, &US_SYSTEM_CONFIGURATION, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_BPM_DDR_1_BUFFERS_BASE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_1_BUFFERS_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FAST_MALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_FAST_MALLOC_RESULT_TABLE, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE", 1, PRIVATE_B_INDEX, &US_BRIDGE_PORT_TO_LOOKUP_PORT_MAPPING_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE", 1, PRIVATE_B_INDEX, &US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_TABLE", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_DEFAULT_FLOWS_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_TX_SCRATCH", 1, PRIVATE_B_INDEX, &WAN_TX_SCRATCH, 24, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_REASON_AND_SRC_BRIDGE_PORT_TO_METER_TABLE", 1, PRIVATE_B_INDEX, &CPU_REASON_AND_SRC_BRIDGE_PORT_TO_METER_TABLE, 3, 6, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_RX_PICO_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &US_CPU_RX_PICO_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CONNECTION_TABLE_CONFIG", 1, PRIVATE_B_INDEX, &US_CONNECTION_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "BROADCOM_SWITCH_PORT_TO_BRIDGE_PORT_MAPPING_TABLE", 1, PRIVATE_B_INDEX, &BROADCOM_SWITCH_PORT_TO_BRIDGE_PORT_MAPPING_TABLE, 9, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR", 1, PRIVATE_B_INDEX, &US_PICO_FREE_SKB_INDEXES_FIFO_LOCAL_TABLE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_BPM_DDR_BUFFER_HEADROOM_SIZE", 1, PRIVATE_B_INDEX, &US_BPM_DDR_BUFFER_HEADROOM_SIZE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CONTEXT_TABLE_CONFIG", 1, PRIVATE_B_INDEX, &US_CONTEXT_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_KEY_BUFFER", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_KEY_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_MALLOC_RESULT_TABLE", 1, PRIVATE_B_INDEX, &US_PICO_MALLOC_RESULT_TABLE, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_FREE_PACKET_DESCRIPTORS_POOL_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION", 1, PRIVATE_B_INDEX, &US_BPM_DDR_BUFFER_HEADROOM_SIZE_2_BYTE_RESOLUTION, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DATA_POINTER_DUMMY_TARGET", 1, PRIVATE_B_INDEX, &DATA_POINTER_DUMMY_TARGET, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_DEBUG_PERIPHERALS_STATUS_REGISTER", 1, PRIVATE_B_INDEX, &US_DEBUG_PERIPHERALS_STATUS_REGISTER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PARALLEL_PROCESSING_TASK_REORDER_FIFO", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_TASK_REORDER_FIFO, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "IH_BUFFER_BBH_POINTER", 1, PRIVATE_B_INDEX, &IH_BUFFER_BBH_POINTER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_CONTEXT_INDEX_CACHE_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CONTEXT_CONTINUATION_TABLE_CONFIG", 1, PRIVATE_B_INDEX, &US_CONTEXT_CONTINUATION_TABLE_CONFIG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_TX_DATA_POINTER_DUMMY_TARGET", 1, PRIVATE_B_INDEX, &US_CPU_TX_DATA_POINTER_DUMMY_TARGET, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RATE_CONTROLLER_EXPONENT_TABLE", 1, PRIVATE_B_INDEX, &US_RATE_CONTROLLER_EXPONENT_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_RX_FAST_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &US_CPU_RX_FAST_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &LOCAL_SWITCHING_MULTICAST_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_IH_BUFFER_VECTOR_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_ANY_SRC_PORT_FLOW_COUNTER", 1, PRIVATE_B_INDEX, &US_ANY_SRC_PORT_FLOW_COUNTER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_TIMER_7_SCHEDULER_NEXT_ENTRY", 1, PRIVATE_B_INDEX, &US_TIMER_7_SCHEDULER_NEXT_ENTRY, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_MEMLIB_SEMAPHORE", 1, PRIVATE_B_INDEX, &US_MEMLIB_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETHWAN2_RX_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &ETHWAN2_RX_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RUNNER_CONGESTION_STATE", 1, PRIVATE_B_INDEX, &US_RUNNER_CONGESTION_STATE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_ENQUEUE_INGRESS_QUEUE_PTR", 1, PRIVATE_B_INDEX, &WAN_ENQUEUE_INGRESS_QUEUE_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR", 1, PRIVATE_B_INDEX, &US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD_PTR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FC_GLOBAL_CFG", 1, PRIVATE_B_INDEX, &US_FC_GLOBAL_CFG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETHWAN2_SWITCH_PORT", 1, PRIVATE_B_INDEX, &ETHWAN2_SWITCH_PORT, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_RULE_CFG_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR", 1, PRIVATE_B_INDEX, &US_INGRESS_CLASSIFICATION_IP_FLOW_RULE_CFG_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PACKET_BUFFER_SIZE_ASR_8", 1, PRIVATE_B_INDEX, &US_PACKET_BUFFER_SIZE_ASR_8, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_MAIN_DMA_SYNCRONIZATION_ADDRESS", 1, PRIVATE_B_INDEX, &US_MAIN_DMA_SYNCRONIZATION_ADDRESS, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_DMA_SYNCRONIZATION_ADDRESS", 1, PRIVATE_B_INDEX, &US_PICO_DMA_SYNCRONIZATION_ADDRESS, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RUNNER_FLOW_IH_RESPONSE_MUTEX", 1, PRIVATE_B_INDEX, &US_RUNNER_FLOW_IH_RESPONSE_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DSL_BUFFER_ALIGNMENT", 1, PRIVATE_B_INDEX, &DSL_BUFFER_ALIGNMENT, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PARALLEL_PROCESSING_SLAVE_VECTOR", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_SLAVE_VECTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE", 1, PRIVATE_B_INDEX, &US_PARALLEL_PROCESSING_CONTEXT_CACHE_MODE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_IH_CONGESTION_THRESHOLD", 1, PRIVATE_B_INDEX, &US_IH_CONGESTION_THRESHOLD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FAST_MALLOC_RESULT_MUTEX", 1, PRIVATE_B_INDEX, &US_FAST_MALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_PICO_MALLOC_RESULT_MUTEX", 1, PRIVATE_B_INDEX, &US_PICO_MALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DHD_RX_FPM_ALLOC_RESULT_MUTEX", 1, PRIVATE_B_INDEX, &DHD_RX_FPM_ALLOC_RESULT_MUTEX, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RX_SBPM_TO_FPM_COPY_SEMAPHORE", 1, PRIVATE_B_INDEX, &US_RX_SBPM_TO_FPM_COPY_SEMAPHORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_FW_MAC_ADDRS_COUNT", 1, PRIVATE_B_INDEX, &US_FW_MAC_ADDRS_COUNT, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RUNNER_FLOW_IH_RESPONSE", 1, PRIVATE_B_INDEX, &US_RUNNER_FLOW_IH_RESPONSE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH2_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &ETH2_RX_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH1_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &ETH1_RX_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETH0_RX_DESCRIPTORS", 1, PRIVATE_B_INDEX, &ETH0_RX_DESCRIPTORS, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "BBH_TX_WAN_CHANNEL_INDEX", 1, PRIVATE_B_INDEX, &BBH_TX_WAN_CHANNEL_INDEX, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "FC_MCAST_RUNNER_A_SCRATCHPAD", 1, COMMON_A_INDEX, &FC_MCAST_RUNNER_A_SCRATCHPAD, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SERVICE_QUEUES_DDR_CACHE_FIFO", 1, COMMON_A_INDEX, &SERVICE_QUEUES_DDR_CACHE_FIFO, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_RX_RUNNER_A_SCRATCHPAD", 1, COMMON_A_INDEX, &CPU_RX_RUNNER_A_SCRATCHPAD, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MAC_TABLE", 1, COMMON_A_INDEX, &MAC_TABLE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_COUNTERS_TABLE", 1, COMMON_A_INDEX, &DS_INGRESS_CLASSIFICATION_COUNTERS_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SERVICE_QUEUES_DESCRIPTOR_TABLE", 1, COMMON_A_INDEX, &SERVICE_QUEUES_DESCRIPTOR_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MAC_TABLE_CAM", 1, COMMON_A_INDEX, &MAC_TABLE_CAM, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "TRACE_C_TABLE", 1, COMMON_A_INDEX, &TRACE_C_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_MAINA_CURR_OFFSET", 1, COMMON_A_INDEX, &RUNNER_FWTRACE_MAINA_CURR_OFFSET, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE", 1, COMMON_A_INDEX, &DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE_LAST_ENTRY", 1, COMMON_A_INDEX, &DDR_ADDRESS_FOR_FREE_SKB_INDEXES_FIFO_TABLE_LAST_ENTRY, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "FREE_SKB_INDEXES_DDR_FIFO_TAIL", 1, COMMON_A_INDEX, &FREE_SKB_INDEXES_DDR_FIFO_TAIL, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "BPM_REPLY_RUNNER_A", 1, COMMON_A_INDEX, &BPM_REPLY_RUNNER_A, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DDR_ADDRESS_FOR_SKB_DATA_POINTERS_TABLE", 1, COMMON_A_INDEX, &DDR_ADDRESS_FOR_SKB_DATA_POINTERS_TABLE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_MAINA_BASE", 1, COMMON_A_INDEX, &RUNNER_FWTRACE_MAINA_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_PICOA_BASE", 1, COMMON_A_INDEX, &RUNNER_FWTRACE_PICOA_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RATE_CONTROLLER_EXPONENT_TABLE", 1, COMMON_A_INDEX, &DS_RATE_CONTROLLER_EXPONENT_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPF_CFG", 1, COMMON_A_INDEX, &CAPWAPF_CFG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_REASON_TO_CPU_RX_QUEUE_TABLE", 1, COMMON_A_INDEX, &DS_CPU_REASON_TO_CPU_RX_QUEUE_TABLE, 2, 64, 1 },
#endif
#if defined WL4908_EAP
	{ "GPON_SKB_ENQUEUED_INDEXES_FIFO", 1, COMMON_A_INDEX, &GPON_SKB_ENQUEUED_INDEXES_FIFO, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CONNECTION_BUFFER_TABLE", 1, COMMON_A_INDEX, &DS_CONNECTION_BUFFER_TABLE, 5, 4, 1 },
#endif
#if defined WL4908_EAP
	{ "INTERRUPT_COALESCING_CONFIG_TABLE", 1, COMMON_A_INDEX, &INTERRUPT_COALESCING_CONFIG_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MAC_CONTEXT_TABLE", 1, COMMON_A_INDEX, &MAC_CONTEXT_TABLE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD", 1, COMMON_A_INDEX, &DS_RX_SBPM_TO_FPM_COPY_SCRATCHPAD, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE", 1, COMMON_A_INDEX, &DS_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE, 128, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "PM_COUNTERS", 1, COMMON_A_INDEX, &PM_COUNTERS, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "ETHWAN2_RX_INGRESS_QUEUE", 1, COMMON_A_INDEX, &ETHWAN2_RX_INGRESS_QUEUE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_CPU_TX_SCRATCHPAD", 1, COMMON_A_INDEX, &DS_CPU_TX_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPF0_CPU_TX_SCRATCHPAD", 1, COMMON_A_INDEX, &CAPWAPF0_CPU_TX_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPF1_CPU_TX_SCRATCHPAD", 1, COMMON_A_INDEX, &CAPWAPF1_CPU_TX_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPF2_CPU_TX_SCRATCHPAD", 1, COMMON_A_INDEX, &CAPWAPF2_CPU_TX_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RING_DESCRIPTORS_TABLE", 1, COMMON_A_INDEX, &RING_DESCRIPTORS_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_RING_PACKET_DESCRIPTORS_CACHE", 1, COMMON_A_INDEX, &DS_RING_PACKET_DESCRIPTORS_CACHE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SERVICE_QUEUES_DDR_QUEUE_ADDRESS_TABLE", 1, COMMON_A_INDEX, &SERVICE_QUEUES_DDR_QUEUE_ADDRESS_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RATE_SHAPERS_STATUS_DESCRIPTOR", 1, COMMON_A_INDEX, &RATE_SHAPERS_STATUS_DESCRIPTOR, 128, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MAC_CONTEXT_TABLE_CAM", 1, COMMON_A_INDEX, &MAC_CONTEXT_TABLE_CAM, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MAC_EXTENSION_TABLE", 1, COMMON_A_INDEX, &MAC_EXTENSION_TABLE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "SERVICE_QUEUES_CFG", 1, COMMON_A_INDEX, &SERVICE_QUEUES_CFG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "TIMER_7_TIMER_PERIOD", 1, COMMON_A_INDEX, &TIMER_7_TIMER_PERIOD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "INTERRUPT_COALESCING_TIMER_PERIOD", 1, COMMON_A_INDEX, &INTERRUPT_COALESCING_TIMER_PERIOD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MAC_EXTENSION_TABLE_CAM", 1, COMMON_A_INDEX, &MAC_EXTENSION_TABLE_CAM, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "INTERRUPT_COALESCING_TIMER_ARMED", 1, COMMON_A_INDEX, &INTERRUPT_COALESCING_TIMER_ARMED, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "COMMON_A_DUMMY_STORE", 1, COMMON_A_INDEX, &COMMON_A_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "FC_SERVICE_QUEUE_MODE", 1, COMMON_A_INDEX, &FC_SERVICE_QUEUE_MODE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "PM_COUNTERS_BUFFER", 1, COMMON_A_INDEX, &PM_COUNTERS_BUFFER, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPF_STATS", 1, COMMON_A_INDEX, &CAPWAPF_STATS, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MAIN_A_DEBUG_TRACE", 1, COMMON_A_INDEX, &MAIN_A_DEBUG_TRACE, 512, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "PICO_A_DEBUG_TRACE", 1, COMMON_A_INDEX, &PICO_A_DEBUG_TRACE, 512, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE", 1, COMMON_B_INDEX, &US_INGRESS_CLASSIFICATION_LOOKUP_LONG_TABLE, 128, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_RX_RUNNER_B_SCRATCHPAD", 1, COMMON_B_INDEX, &CPU_RX_RUNNER_B_SCRATCHPAD, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_COUNTERS_TABLE", 1, COMMON_B_INDEX, &US_INGRESS_CLASSIFICATION_COUNTERS_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE", 1, COMMON_B_INDEX, &LOCAL_SWITCHING_LAN_ENQUEUE_INGRESS_QUEUE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE", 1, COMMON_B_INDEX, &DS_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_TX_SERVICE_QUEUES_TABLE", 1, COMMON_B_INDEX, &WAN_TX_SERVICE_QUEUES_TABLE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE", 1, COMMON_B_INDEX, &US_INGRESS_CLASSIFICATION_LOOKUP_CAM_TABLE, 32, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_TX_SCRATCHPAD", 1, COMMON_B_INDEX, &US_CPU_TX_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CONNECTION_BUFFER_TABLE", 1, COMMON_B_INDEX, &US_CONNECTION_BUFFER_TABLE, 5, 4, 1 },
#endif
#if defined WL4908_EAP
	{ "IPV6_HOST_ADDRESS_CRC_TABLE", 1, COMMON_B_INDEX, &IPV6_HOST_ADDRESS_CRC_TABLE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GPON_SKB_ENQUEUED_INDEXES_FREE_PTR", 1, COMMON_B_INDEX, &GPON_SKB_ENQUEUED_INDEXES_FREE_PTR, 40, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_MAINB_CURR_OFFSET", 1, COMMON_B_INDEX, &RUNNER_FWTRACE_MAINB_CURR_OFFSET, 2, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "IPV4_HOST_ADDRESS_TABLE", 1, COMMON_B_INDEX, &IPV4_HOST_ADDRESS_TABLE, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DS_INGRESS_CLASSIFICATION_LOOKUP_TABLE", 1, COMMON_B_INDEX, &DS_INGRESS_CLASSIFICATION_LOOKUP_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_INGRESS_CLASSIFICATION_LOOKUP_TABLE", 1, COMMON_B_INDEX, &US_INGRESS_CLASSIFICATION_LOOKUP_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_TX_QUEUES_TABLE", 1, COMMON_B_INDEX, &WAN_TX_QUEUES_TABLE, 256, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_TX_RUNNER_B_SCRATCHPAD", 1, COMMON_B_INDEX, &WAN_TX_RUNNER_B_SCRATCHPAD, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RING_PACKET_DESCRIPTORS_CACHE", 1, COMMON_B_INDEX, &US_RING_PACKET_DESCRIPTORS_CACHE, 16, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "GPON_SKB_ENQUEUED_INDEXES_PUT_PTR", 1, COMMON_B_INDEX, &GPON_SKB_ENQUEUED_INDEXES_PUT_PTR, 40, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_CPU_REASON_TO_CPU_RX_QUEUE_TABLE", 1, COMMON_B_INDEX, &US_CPU_REASON_TO_CPU_RX_QUEUE_TABLE, 2, 64, 1 },
#endif
#if defined WL4908_EAP
	{ "DUMMY_WAN_TX_QUEUE_DESCRIPTOR", 1, COMMON_B_INDEX, &DUMMY_WAN_TX_QUEUE_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPR_CONTEXT_CAM_TABLE", 1, COMMON_B_INDEX, &CAPWAPR_CONTEXT_CAM_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CPU_TX_DESCRIPTOR_QUEUE_TAIL_TABLE", 1, COMMON_B_INDEX, &CPU_TX_DESCRIPTOR_QUEUE_TAIL_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_MAINB_BASE", 1, COMMON_B_INDEX, &RUNNER_FWTRACE_MAINB_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "RUNNER_FWTRACE_PICOB_BASE", 1, COMMON_B_INDEX, &RUNNER_FWTRACE_PICOB_BASE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPR_CFG", 1, COMMON_B_INDEX, &CAPWAPR_CFG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "COMMON_B_DUMMY_STORE", 1, COMMON_B_INDEX, &COMMON_B_DUMMY_STORE, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "PACKET_SRAM_TO_DDR_COPY_BUFFER_1", 1, COMMON_B_INDEX, &PACKET_SRAM_TO_DDR_COPY_BUFFER_1, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "PACKET_SRAM_TO_DDR_COPY_BUFFER_2", 1, COMMON_B_INDEX, &PACKET_SRAM_TO_DDR_COPY_BUFFER_2, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "DUMMY_RATE_CONTROLLER_DESCRIPTOR", 1, COMMON_B_INDEX, &DUMMY_RATE_CONTROLLER_DESCRIPTOR, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LAN5_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN5_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LAN0_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN0_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LAN6_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN6_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LAN1_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN1_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LAN7_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN7_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LAN2_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN2_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPR_STATS", 1, COMMON_B_INDEX, &CAPWAPR_STATS, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "LAN3_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN3_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPR_CONTEXT_RING_TABLE", 1, COMMON_B_INDEX, &CAPWAPR_CONTEXT_RING_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAPR_FLUSH_TABLE", 1, COMMON_B_INDEX, &CAPWAPR_FLUSH_TABLE, 3, 8, 1 },
#endif
#if defined WL4908_EAP
	{ "LAN4_INGRESS_FIFO", 1, COMMON_B_INDEX, &LAN4_INGRESS_FIFO, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CAPWAP_CFG", 1, COMMON_B_INDEX, &CAPWAP_CFG, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "FC_FLOW_IP_ADDRESSES_TABLE", 1, COMMON_B_INDEX, &FC_FLOW_IP_ADDRESSES_TABLE, 4, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "BPM_REPLY_RUNNER_B", 1, COMMON_B_INDEX, &BPM_REPLY_RUNNER_B, 1, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RATE_CONTROLLERS_TABLE", 1, COMMON_B_INDEX, &US_RATE_CONTROLLERS_TABLE, 128, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD", 1, COMMON_B_INDEX, &US_RX_SBPM_TO_FPM_COPY_SCRATCHPAD, 8, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "WAN_ENQUEUE_INGRESS_QUEUE", 1, COMMON_B_INDEX, &WAN_ENQUEUE_INGRESS_QUEUE, 64, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "MAIN_B_DEBUG_TRACE", 1, COMMON_B_INDEX, &MAIN_B_DEBUG_TRACE, 512, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "PICO_B_DEBUG_TRACE", 1, COMMON_B_INDEX, &PICO_B_DEBUG_TRACE, 512, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "BPM_PACKET_BUFFERS", 1, DDR_INDEX, &BPM_PACKET_BUFFERS, 7680, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CONTEXT_TABLE", 1, DDR_INDEX, &CONTEXT_TABLE, 0, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "NAT_CACHE_TABLE", 1, DDR_INDEX, &NAT_CACHE_TABLE, 65536, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "NAT_CACHE_EXTENSION_TABLE", 1, DDR_INDEX, &NAT_CACHE_EXTENSION_TABLE, 7, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "NATC_CONTEXT_TABLE", 1, DDR_INDEX, &NATC_CONTEXT_TABLE, 65536, 1, 1 },
#endif
#if defined WL4908_EAP
	{ "CONTEXT_CONTINUATION_TABLE", 1, DDR_INDEX, &CONTEXT_CONTINUATION_TABLE, 65536, 1, 1 },
#endif
};
