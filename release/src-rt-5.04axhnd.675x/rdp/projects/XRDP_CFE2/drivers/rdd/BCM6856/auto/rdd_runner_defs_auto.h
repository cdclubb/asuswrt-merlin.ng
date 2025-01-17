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


#ifndef _RDD_RUNNER_DEFS_AUTO_H_
#define _RDD_RUNNER_DEFS_AUTO_H_

#ifdef XRDP_CFE
/* DDR */
/* PSRAM */
/* IMAGE_0 */
#define IMAGE_0_CPU_RX_CFE_SRAM_COUNTERS_ADDRESS 0x0000
#define IMAGE_0_CPU_RX_CFE_SRAM_COUNTERS_BYTE_SIZE 0x0050
#define IMAGE_0_CPU_RX_CFE_SRAM_COUNTERS_LOG2_BYTE_SIZE 0x0007
#define RDD_IMAGE_0_CPU_RX_CFE_SRAM_COUNTERS_SIZE     10
#define RDD_IMAGE_0_CPU_RX_CFE_SRAM_COUNTERS_LOG2_SIZE     4
#define IMAGE_0_BBH_TX_RING_TABLE_ADDRESS 0x0050
#define IMAGE_0_BBH_TX_RING_TABLE_BYTE_SIZE 0x0010
#define IMAGE_0_BBH_TX_RING_TABLE_LOG2_BYTE_SIZE 0x0004
#define RDD_IMAGE_0_BBH_TX_RING_TABLE_SIZE     1
#define IMAGE_0_RUNNER_GLOBAL_REGISTERS_INIT_ADDRESS 0x0060
#define IMAGE_0_RUNNER_GLOBAL_REGISTERS_INIT_BYTE_SIZE 0x0020
#define IMAGE_0_RUNNER_GLOBAL_REGISTERS_INIT_LOG2_BYTE_SIZE 0x0005
#define RDD_IMAGE_0_RUNNER_GLOBAL_REGISTERS_INIT_SIZE     8
#define RDD_IMAGE_0_RUNNER_GLOBAL_REGISTERS_INIT_LOG2_SIZE     3
#define IMAGE_0_CPU_TX_CFE_SRAM_COUNTERS_ADDRESS 0x0080
#define IMAGE_0_CPU_TX_CFE_SRAM_COUNTERS_BYTE_SIZE 0x0050
#define IMAGE_0_CPU_TX_CFE_SRAM_COUNTERS_LOG2_BYTE_SIZE 0x0007
#define RDD_IMAGE_0_CPU_TX_CFE_SRAM_COUNTERS_SIZE     10
#define RDD_IMAGE_0_CPU_TX_CFE_SRAM_COUNTERS_LOG2_SIZE     4
#define IMAGE_0_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_ADDRESS 0x00d0
#define IMAGE_0_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_BYTE_SIZE 0x000c
#define IMAGE_0_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_LOG2_BYTE_SIZE 0x0004
#define RDD_IMAGE_0_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_SIZE     3
#define RDD_IMAGE_0_CPU_TX_EGRESS_DISPATCHER_CREDIT_TABLE_LOG2_SIZE     2
#define IMAGE_0_BBH_TX_BB_DESTINATION_TABLE_ADDRESS 0x00dc
#define IMAGE_0_BBH_TX_BB_DESTINATION_TABLE_BYTE_SIZE 0x0004
#define IMAGE_0_BBH_TX_BB_DESTINATION_TABLE_LOG2_BYTE_SIZE 0x0002
#define RDD_IMAGE_0_BBH_TX_BB_DESTINATION_TABLE_SIZE     1
#define IMAGE_0_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_ADDRESS 0x00e0
#define IMAGE_0_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_BYTE_SIZE 0x000c
#define IMAGE_0_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_LOG2_BYTE_SIZE 0x0004
#define RDD_IMAGE_0_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_SIZE     3
#define RDD_IMAGE_0_CPU_TX_INGRESS_DISPATCHER_CREDIT_TABLE_LOG2_SIZE     2
#define IMAGE_0_TASK_IDX_ADDRESS 0x00ec
#define IMAGE_0_TASK_IDX_BYTE_SIZE 0x0004
#define IMAGE_0_TASK_IDX_LOG2_BYTE_SIZE 0x0002
#define RDD_IMAGE_0_TASK_IDX_SIZE     1
#define IMAGE_0_CPU_RX_INTERRUPT_SCRATCH_ADDRESS 0x00f0
#define IMAGE_0_CPU_RX_INTERRUPT_SCRATCH_BYTE_SIZE 0x0008
#define IMAGE_0_CPU_RX_INTERRUPT_SCRATCH_LOG2_BYTE_SIZE 0x0003
#define RDD_IMAGE_0_CPU_RX_INTERRUPT_SCRATCH_SIZE     8
#define RDD_IMAGE_0_CPU_RX_INTERRUPT_SCRATCH_LOG2_SIZE     3
#define IMAGE_0_CPU_RX_INTERRUPT_ID_DDR_ADDR_ADDRESS 0x00f8
#define IMAGE_0_CPU_RX_INTERRUPT_ID_DDR_ADDR_BYTE_SIZE 0x0008
#define IMAGE_0_CPU_RX_INTERRUPT_ID_DDR_ADDR_LOG2_BYTE_SIZE 0x0003
#define RDD_IMAGE_0_CPU_RX_INTERRUPT_ID_DDR_ADDR_SIZE     8
#define RDD_IMAGE_0_CPU_RX_INTERRUPT_ID_DDR_ADDR_LOG2_SIZE     3
#define IMAGE_0_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_ADDRESS 0x0100
#define IMAGE_0_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_BYTE_SIZE 0x0040
#define IMAGE_0_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_LOG2_BYTE_SIZE 0x0006
#define RDD_IMAGE_0_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_SIZE     8
#define RDD_IMAGE_0_US_TM_BBH_TX_EGRESS_COUNTER_TABLE_LOG2_SIZE     3
#define IMAGE_0_DIRECT_PROCESSING_PD_TABLE_ADDRESS 0x0140
#define IMAGE_0_DIRECT_PROCESSING_PD_TABLE_BYTE_SIZE 0x0020
#define IMAGE_0_DIRECT_PROCESSING_PD_TABLE_LOG2_BYTE_SIZE 0x0005
#define RDD_IMAGE_0_DIRECT_PROCESSING_PD_TABLE_SIZE     2
#define RDD_IMAGE_0_DIRECT_PROCESSING_PD_TABLE_LOG2_SIZE     1
#define IMAGE_0_SRAM_DUMMY_STORE_ADDRESS 0x0160
#define IMAGE_0_SRAM_DUMMY_STORE_BYTE_SIZE 0x0001
#define IMAGE_0_SRAM_DUMMY_STORE_LOG2_BYTE_SIZE 0x0001
#define RDD_IMAGE_0_SRAM_DUMMY_STORE_SIZE     1
#define IMAGE_0_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_ADDRESS 0x0180
#define IMAGE_0_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_BYTE_SIZE 0x0040
#define IMAGE_0_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_LOG2_BYTE_SIZE 0x0006
#define RDD_IMAGE_0_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_SIZE     8
#define RDD_IMAGE_0_DS_TM_BBH_TX_EGRESS_COUNTER_TABLE_LOG2_SIZE     3
#define IMAGE_0_REGISTERS_BUFFER_ADDRESS 0x01c0
#define IMAGE_0_REGISTERS_BUFFER_BYTE_SIZE 0x0080
#define IMAGE_0_REGISTERS_BUFFER_LOG2_BYTE_SIZE 0x0007
#define RDD_IMAGE_0_REGISTERS_BUFFER_SIZE     32
#define RDD_IMAGE_0_REGISTERS_BUFFER_LOG2_SIZE     5
#define IMAGE_0_RX_FLOW_TABLE_ADDRESS 0x0400
#define IMAGE_0_RX_FLOW_TABLE_BYTE_SIZE 0x0280
#define IMAGE_0_RX_FLOW_TABLE_LOG2_BYTE_SIZE 0x000a
#define RDD_IMAGE_0_RX_FLOW_TABLE_SIZE     320
#define RDD_IMAGE_0_RX_FLOW_TABLE_LOG2_SIZE     9
#define IMAGE_0_SRAM_PD_FIFO_ADDRESS 0x0800
#define IMAGE_0_SRAM_PD_FIFO_BYTE_SIZE 0x0400
#define IMAGE_0_SRAM_PD_FIFO_LOG2_BYTE_SIZE 0x000a
#define RDD_IMAGE_0_SRAM_PD_FIFO_SIZE     64
#define RDD_IMAGE_0_SRAM_PD_FIFO_LOG2_SIZE     6
#define IMAGE_0_CPU_RING_DESCRIPTORS_TABLE_ADDRESS 0x3000
#define IMAGE_0_CPU_RING_DESCRIPTORS_TABLE_BYTE_SIZE 0x0100
#define IMAGE_0_CPU_RING_DESCRIPTORS_TABLE_LOG2_BYTE_SIZE 0x0008
#define RDD_IMAGE_0_CPU_RING_DESCRIPTORS_TABLE_SIZE     16
#define RDD_IMAGE_0_CPU_RING_DESCRIPTORS_TABLE_LOG2_SIZE     4
#endif
#endif /* _RDD_RUNNER_DEFS_AUTO_H_ */
