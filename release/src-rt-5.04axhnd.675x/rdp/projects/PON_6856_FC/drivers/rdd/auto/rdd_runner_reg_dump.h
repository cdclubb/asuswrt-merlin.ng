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

typedef struct
{
    char * table_name;
    int core;
	uint32_t base_address;
    int size;
} TABLE_STACK_STRUCT;

#ifndef STT_PRINTF
	#if defined LINUX_KERNEL
		#define STT_PRINTF printk
	#else
		#define STT_PRINTF printf
	#endif
#endif


void dump_RDD_IPTV_DDR_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WLAN_MCAST_DHD_LIST_ENTRY_ARRAY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_WLAN_MCAST_DHD_LIST_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PROCESSING_TX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SCHEDULING_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BASIC_SCHEDULER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTES_4(bdmf_session_handle session, unsigned char *p);
void dump_RDD_REPORTING_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BBH_TX_WAKE_UP_DATA_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FLUSH_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TM_FLOW_CNTR_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_QM_QUEUE_COUNTER_DATA(bdmf_session_handle session, unsigned char *p);
void dump_RDD_REPORTING_QUEUE_COUNTER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTES_2(bdmf_session_handle session, unsigned char *p);
void dump_RDD_GHOST_REPORTING_GLOBAL_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_QUEUE_DYNAMIC_MNG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BUFFER_CONG_MGT(bdmf_session_handle session, unsigned char *p);
void dump_RDD_COMPLEX_SCHEDULER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TRACE_EVENT(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CODEL_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BUFFER_CONG_Q_OCCUPANCY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTE_1(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTES_8(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CODEL_BIAS_SLOPE(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BASIC_RATE_LIMITER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PACKETS_AND_BYTES(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TX_EXCEPTION_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_MIRRORING_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_UPDATE_FIFO_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BBH_TX_EGRESS_COUNTER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FLUSH_CFG_ENABLE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CODEL_DROP_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_NATC_TBL_CONFIGURATION(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FPM_GLOBAL_CFG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DEBUG_PRINT_INFO(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BBH_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PROCESSING_RX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PAUSE_QUANTA_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_OVERALL_RATE_LIMITER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_MAC_TYPE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RX_FLOW_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_VPORT_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TX_FLOW_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TUNNEL_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TCAM_IC_CMD(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_DBG_CNTRS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FW_POLICER_BUDGET_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CBS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_LAYER2_HEADER_COPY_MAPPING_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PACKET_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_POLICER_PARAMS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TC_TO_QUEUE_8(bdmf_session_handle session, unsigned char *p);
void dump_RDD_FPM_POOL_NUMBER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PBIT_TO_QUEUE_8(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DDR_ADDRESS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_INTERRUPT_COALESCING_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_FILTER_CTRL(bdmf_session_handle session, unsigned char *p);
void dump_RDD_EMAC_FLOW_CTRL_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_VPORT_CFG_EX_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_EMAC_FLOW_CTRL_BUDGET_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SYSTEM_CONFIGURATION_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_ECN_IPV6_REMARK_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SPDTEST_GEN_CFG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_PACKET_BASED_MAPPING_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SPDSVC_ANALYZER_PARAMS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TCAM_IC_CFG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_RING_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DEFAULT_VLAN_VID_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BRIDGE_CFG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_REDIRECT_MODE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_IPTV_CLASSIFICATION_CFG_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RING_CPU_TX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_HW_IPTV_CONFIGURATION(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_SYNC_FIFO_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_RING_INTERRUPT_COUNTER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TUNNEL_HEADER_PSRAM_BUFFER(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_TX_RING_INDICES(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TUNNELS_PARSING_CFG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_IPTV_CFG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_MULTICAST_KEY_MASK_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_IPTV_DDR_CTX_TABLE_ADDRESS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_NAT_CACHE_CFG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_INGRESS_FILTER_CFG(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TCPSPDTEST_STREAM(bdmf_session_handle session, unsigned char *p);
void dump_RDD_UDPSPDT_STREAM_RX_STAT(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PKTGEN_TX_STREAM_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_RX_METER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SPDSVC_GEN_PARAMS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_UDPSPDT_STREAM_TX_STAT(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CSO_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TX_ABS_RECYCLE_COUNTERS_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_TCPSPDTEST_ENGINE_GLOBAL_INFO(bdmf_session_handle session, unsigned char *p);
void dump_RDD_UDPSPDT_TX_PARAMS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SPDSVC_TCPSPDTEST_COMMON_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PKTGEN_SBPM_HDR_BN(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SPDSVC_RX_TS_STAT(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PKTGEN_TX_PARAMS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PKTGEN_FPM_UG_MGMT_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PKTGEN_SBPM_EXT(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PKTGEN_TX_STREAM_SCRATCH_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_COMPLETE_COMMON_RADIO_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_RX_COMPLETE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_TX_COMPLETE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_RX_POST_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_HW_CONFIGURATION(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_RING_SIZE(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_DOORBELL(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SPDSVC_WLAN_GEN_PARAMS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CODEL_SQ_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_AUX_INFO_CACHE_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_TX_POST_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_CODEL_BIAS_SLOPE(bdmf_session_handle session, unsigned char *p);
void dump_RDD_SPDSVC_WLAN_TXPOST_PARAMS(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_POST_COMMON_RADIO_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_BACKUP_IDX_CACHE_TABLE(bdmf_session_handle session, unsigned char *p);
void dump_RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY(bdmf_session_handle session, unsigned char *p);

#endif /* __RDD_RUNNER_REG_DUMP_H__ */
