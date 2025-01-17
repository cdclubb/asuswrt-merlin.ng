/*
    <:copyright-BRCM:2015:DUAL/GPL:standard
    
       Copyright (c) 2015 Broadcom 
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
    
* :>
*/

#include "rdd.h"
#include "rdd_defs.h"
#include "rdd_init.h"

#include "XRDP_AG.h"
#include "rdd_map_auto.h"
#include "rdp_common.h"
#include "rdd_runner_proj_defs.h"
#include "xrdp_drv_rnr_regs_ag.h"

extern int reg_id[32];


int rdd_init(void)
{
    return 0;
}

void rdd_exit(void)
{
}

#ifndef RDP_SIM
void rdp_rnr_write_context(void *__to, void *__from, unsigned int __n);
#endif

static void rdd_global_registers_init(uint32_t core_index, uint32_t local_regs[NUM_OF_MAIN_RUNNER_THREADS][NUM_OF_LOCAL_REGS], uint32_t last_thread)
{
     uint32_t i;

    /********** Reserved global registers **********/
    /* R6 - ingress qos don't drop counter in processing cores */

    /********** common to all runners **********/
    /* in this project we don't have really global, so will set all registers that should be global for all threads */
    for (i = 0; i <= last_thread; ++i)
    {
        local_regs[i][1] = 1; /* CONST_1 is 1 */
    }
}

static void image_0_context_set(uint32_t core_index)
{
    static uint32_t local_regs[NUM_OF_MAIN_RUNNER_THREADS][NUM_OF_LOCAL_REGS];
    uint32_t *sram_context;

    rdd_global_registers_init(core_index, local_regs, core_index);
    sram_context = (uint32_t *)RUNNER_CORE_CONTEXT_ADDRESS(core_index);
#ifndef XRDP_EMULATION
    /* read the local registers from the Context memory - maybe it was initialized by the ACE compiler */
    MREAD_BLK_32(local_regs, sram_context, sizeof(local_regs));
#endif

    /* UPDATE_FIFO_READ: thread 1 */
    local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[0]]  = ADDRESS_OF(image_0, direct_processing_wakeup_request);
    local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[9]]  = IMAGE_0_RX_FLOW_TABLE_ADDRESS << 16 | IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER;
    local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[10]] = BB_ID_DISPATCHER_REORDER;
    local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[11]] = 0;
    local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[16]] = IMAGE_0_DIRECT_PROCESSING_PD_TABLE_ADDRESS;
    local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[17]] = IMAGE_0_SRAM_PD_FIFO_ADDRESS;
    local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[18]] = IMAGE_0_SRAM_PD_FIFO_ADDRESS + IMAGE_0_SRAM_PD_FIFO_BYTE_SIZE - sizeof(CPU_RX_DESCRIPTOR_STRUCT);

    /* CPU_TX: thread 1 */
    local_regs[IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER][reg_id[0]] = ADDRESS_OF(image_0, cpu_tx_wakeup_request);
    local_regs[IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER][reg_id[8]] = IMAGE_0_BBH_TX_RING_TABLE_ADDRESS;
    local_regs[IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER][reg_id[9]] = IMAGE_0_BBH_TX_BB_DESTINATION_TABLE_ADDRESS;

#if defined(RDP_SIM) || defined(XRDP_EMULATION)
    /* copy the local registers initial values to the Context memory */
    MWRITE_BLK_32(sram_context, local_regs, sizeof(local_regs));
#else

    MWRITE_32(sram_context, local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[0]]);
    MWRITE_32(sram_context + (9), local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[9]]);
    MWRITE_32(sram_context + (10), local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[10]]);
    MWRITE_32(sram_context + (11), local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[11]]);
    MWRITE_32(sram_context + (16), local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[16]]);
    MWRITE_32(sram_context + (17), local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[17]]);
    MWRITE_32(sram_context + (18), local_regs[IMAGE_0_CFE_CORE_CPU_RX_THREAD_NUMBER][reg_id[18]]);

    MWRITE_32(sram_context + (IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER * 32), local_regs[IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER][reg_id[0]]);
    MWRITE_32(sram_context + ((IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER * 32) + 8), local_regs[IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER][reg_id[8]]);
    MWRITE_32(sram_context + ((IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER * 32) + 9), local_regs[IMAGE_0_CFE_CORE_CPU_TX_THREAD_NUMBER][reg_id[9]]);

#endif
}

static void rdd_local_registers_init(void)
{
    image_0_context_set(0);
}

int rdd_data_structures_init(rdd_init_params_t *init_params)
{
    bdmf_error_t rc = BDMF_ERR_OK;
    CPU_RX_LAST_READ_INDEX_STRUCT *last_read_idx_ptr = RDD_CPU_RX_LAST_READ_INDEX_PTR(0);
    uint32_t flow_map[] = {BB_ID_RX_BBH_0, BB_ID_RX_BBH_1, BB_ID_RX_BBH_2,
                           BB_ID_RX_BBH_3, BB_ID_RX_BBH_4, BB_ID_RX_BBH_5,
                           BB_ID_RX_BBH_6, BB_ID_RX_BBH_7};
    uint32_t num_of_queues = sizeof(flow_map)/sizeof(uint32_t);
    int i;

    /* 4912 has BB_ID_RX_BBH_0 to BB_ID_RX_BBH_8.  This initialization misses
     * BB_ID_RX_BBH_8, but shouldn't break anything. */
    rdd_local_registers_init();
    MWRITE_16(last_read_idx_ptr, (IMAGE_0_SRAM_PD_FIFO_ADDRESS +
                                  IMAGE_0_SRAM_PD_FIFO_BYTE_SIZE -
                                  sizeof(CPU_RX_DESCRIPTOR_STRUCT)));
    for (i = 0; i < num_of_queues; i++)
        rdd_rx_flow_cfg((256 + flow_map[i]), 0, i, 0);

    return rc;
}


