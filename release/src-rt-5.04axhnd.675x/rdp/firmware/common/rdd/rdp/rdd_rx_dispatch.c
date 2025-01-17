/*
   <:copyright-BRCM:2014-2016:DUAL/GPL:standard
   
      Copyright (c) 2014-2016 Broadcom 
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

#include "rdd.h"

#ifdef DS_DYNAMIC_DISPATCH
void rdd_ds_dynamic_dispatcher_init(uint16_t *processing_tasks_arr, uint32_t num_of_tasks)
{
    uint16_t *rx_dispatch_fifo_read_ptr;
    RDD_DS_RX_DISPATCH_PROCESSING_TASKS_WAKEUP_REQUESTS_TABLE_DTS *processing_tasks_wakeup_requests_table;
    uint32_t i;

    /* processing tasks vector initialize (all 4 tasks are available) */
    MEMSET(RDD_DS_RX_DISPATCH_PROCESSING_TASKS_VECTOR_PTR(), 1, DS_RX_DISPATCH_PROCESSING_TASKS_VECTOR_BYTE_SIZE);

    /* dispatch fifo read\write pointers initialize */
    rx_dispatch_fifo_read_ptr = (uint16_t *)(DEVICE_ADDRESS(RUNNER_PRIVATE_0_OFFSET) +
        DS_RX_DISPATCH_FIFO_READ_PTR_ADDRESS);

    MWRITE_16(rx_dispatch_fifo_read_ptr, DS_RX_DISPATCH_FIFO_ADDRESS);

    /* processing tasks wakeup request table initialize */
    processing_tasks_wakeup_requests_table = RDD_DS_RX_DISPATCH_PROCESSING_TASKS_WAKEUP_REQUESTS_TABLE_PTR();

    for (i = 0; i < num_of_tasks; i++)
        MWRITE_16(&processing_tasks_wakeup_requests_table->entry[i], THREAD_WAKEUP_REQUEST(processing_tasks_arr[i]));
}
#endif

#ifdef US_DYNAMIC_DISPATCH
void rdd_us_dynamic_dispatcher_init(uint16_t *processing_tasks_arr, uint32_t num_of_tasks)
{
    uint16_t *rx_dispatch_fifo_read_ptr;
    RDD_US_RX_DISPATCH_PROCESSING_TASKS_WAKEUP_REQUESTS_TABLE_DTS *processing_tasks_wakeup_requests_table;
    uint32_t i;

    /* processing tasks vector initialize (all 4 tasks are available) */
    MEMSET(RDD_US_RX_DISPATCH_PROCESSING_TASKS_VECTOR_PTR(), 1, US_RX_DISPATCH_PROCESSING_TASKS_VECTOR_BYTE_SIZE);

    /* dispatch fifo read pointer initialize */
    rx_dispatch_fifo_read_ptr = (uint16_t *)(DEVICE_ADDRESS(RUNNER_PRIVATE_1_OFFSET) +
        US_RX_DISPATCH_FIFO_READ_PTR_ADDRESS);

    MWRITE_16(rx_dispatch_fifo_read_ptr, US_RX_DISPATCH_FIFO_ADDRESS);

    /* processing tasks wakeup request table initialize */
    processing_tasks_wakeup_requests_table = RDD_US_RX_DISPATCH_PROCESSING_TASKS_WAKEUP_REQUESTS_TABLE_PTR();

    for (i = 0; i < num_of_tasks; i++)
        MWRITE_16(&processing_tasks_wakeup_requests_table->entry[i], THREAD_WAKEUP_REQUEST(processing_tasks_arr[i]));
}
#endif

void rdd_parallel_processing_init(void)
{
    uint16_t *bbh_descriptors_fifo_read_ptr;
    uint16_t *task_reorder_fifo_ptr;

    /* BBH hardware dispatch */
    /* Ethernet WAN */
    bbh_descriptors_fifo_read_ptr = (uint16_t *)RDD_DS_BBH_DESCRIPTORS_FIFO_READ_PTR_PTR();

    MWRITE_16(bbh_descriptors_fifo_read_ptr, WAN_RX_NORMAL_DESCRIPTORS_ADDRESS);

    /* Task reorder */
    task_reorder_fifo_ptr = (uint16_t *)(DEVICE_ADDRESS(RUNNER_PRIVATE_0_OFFSET) +
        DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO_IN_PTR_ADDRESS);

    MWRITE_16(task_reorder_fifo_ptr, DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO_ADDRESS);

    task_reorder_fifo_ptr = (uint16_t *)(DEVICE_ADDRESS(RUNNER_PRIVATE_0_OFFSET) +
        DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO_OUT_PTR_ADDRESS);

    MWRITE_16(task_reorder_fifo_ptr, DS_PARALLEL_PROCESSING_TASK_REORDER_FIFO_ADDRESS);

    /* Upstream - dynamic dispatch */
    task_reorder_fifo_ptr = (uint16_t *)(DEVICE_ADDRESS(RUNNER_PRIVATE_1_OFFSET) +
        US_PARALLEL_PROCESSING_TASK_REORDER_FIFO_IN_PTR_ADDRESS);

    MWRITE_16(task_reorder_fifo_ptr, US_PARALLEL_PROCESSING_TASK_REORDER_FIFO_ADDRESS);

    task_reorder_fifo_ptr = (uint16_t *)(DEVICE_ADDRESS(RUNNER_PRIVATE_1_OFFSET) +
        US_PARALLEL_PROCESSING_TASK_REORDER_FIFO_OUT_PTR_ADDRESS);

    MWRITE_16(task_reorder_fifo_ptr, US_PARALLEL_PROCESSING_TASK_REORDER_FIFO_ADDRESS);

}
