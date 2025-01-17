/*
   Copyright (c) 2015 Broadcom Corporation
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

#ifndef _RDD_CPU_RX_H_
#define _RDD_CPU_RX_H_

#include "bdmf_errno.h"
#include "rdd.h"
#include "XRDP_AG.h"

#define HOST_BUFFER_SIZE                    2048
#define RING_INTERRUPT_THRESHOLD_MAX   ((1 << 16) - 1)
#define CPU_RING_SIZE_32_RESOLUTION 5
#define CPU_RING_SIZE_64_RESOLUTION 6

typedef enum
{
    DATA_RING_ID_FIRST = 0,
    DATA_RING_ID_LAST = ( RDD_CPU_RING_DESCRIPTORS_TABLE_SIZE - 1 ),
    FEED_RING_ID,
    FEED_RCYCLE_RING_ID,
    TX_RCYCLE_RING_ID,
    TX_HIGH_PRIO_RING_ID,
    TX_LOW_PRIO_RING_ID,
    RING_ID_LAST = TX_LOW_PRIO_RING_ID,
    RING_ID_NUM_OF
} ring_id_t;

static inline CPU_RING_DESCRIPTOR_STRUCT *get_recycle_ring_entry(uint32_t ring_id)
{
    if (ring_id == FEED_RCYCLE_RING_ID)
        return (CPU_RING_DESCRIPTOR_STRUCT *)RDD_CPU_RECYCLE_RING_DESCRIPTOR_TABLE_PTR(get_runner_idx(cpu_rx_runner_image));
    return (CPU_RING_DESCRIPTOR_STRUCT *)RDD_CPU_RECYCLE_RING_DESCRIPTOR_TABLE_PTR(get_runner_idx(cpu_tx_runner_image));
}

static inline int rdd_cpu_get_read_idx(uint32_t ring_id, uint8_t type, uint16_t *read_idx)
{
    int sram_table_idx;
#ifndef RDP_SIM
    CPU_RING_DESCRIPTOR_STRUCT *entry;
#endif

#ifndef RDP_SIM
    if (type == CPU_IF_RDD_DATA)
        entry = ((CPU_RING_DESCRIPTOR_STRUCT *)RDD_CPU_RING_DESCRIPTORS_TABLE_PTR(get_runner_idx(cpu_rx_runner_image))) + ring_id;
    else if (type == CPU_IF_RDD_RECYCLE)
        entry = get_recycle_ring_entry(ring_id);
    else if (type == CPU_IF_RDD_CPU_TX)
    {      
      sram_table_idx = ring_id == TX_HIGH_PRIO_RING_ID ? 0 : 1;
      RDD_CPU_TX_RING_INDICES_READ_IDX_READ_G(*read_idx, RDD_CPU_TX_RING_INDICES_VALUES_TABLE_ADDRESS_ARR, sram_table_idx);
      return BDMF_ERR_OK;
    }
    else
        return BDMF_ERR_NOT_SUPPORTED;    

    RDD_CPU_RING_DESCRIPTOR_READ_IDX_READ(*read_idx, entry);
#else
    /* XXX: Fix simulator to use work with non READ_G/WRITE_G macros */
    if (type == CPU_IF_RDD_DATA)
        RDD_CPU_RING_DESCRIPTOR_READ_IDX_READ_G(*read_idx, RDD_CPU_RING_DESCRIPTORS_TABLE_ADDRESS_ARR, ring_id);
    else if (type == CPU_IF_RDD_RECYCLE)
        RDD_CPU_RING_DESCRIPTOR_READ_IDX_READ_G(*read_idx, RDD_CPU_RECYCLE_RING_DESCRIPTOR_TABLE_ADDRESS_ARR, 0);
    else if (type == CPU_IF_RDD_CPU_TX)
    {
      sram_table_idx = ring_id == TX_HIGH_PRIO_RING_ID ? 0 : 1;
      RDD_CPU_TX_RING_INDICES_READ_IDX_READ_G(*read_idx, RDD_CPU_TX_RING_INDICES_VALUES_TABLE_ADDRESS_ARR, sram_table_idx);
    }
    else
        return BDMF_ERR_NOT_SUPPORTED;
#endif

    return BDMF_ERR_OK;
}

static inline int rdd_cpu_get_write_idx(uint32_t ring_id, uint8_t type, uint16_t *write_idx)
{
    int sram_table_idx;
#ifndef RDP_SIM
    CPU_RING_DESCRIPTOR_STRUCT *entry;
#endif

#ifndef RDP_SIM
    if (type == CPU_IF_RDD_DATA)
        entry = ((CPU_RING_DESCRIPTOR_STRUCT *)RDD_CPU_RING_DESCRIPTORS_TABLE_PTR(get_runner_idx(cpu_rx_runner_image))) + ring_id;
    else if (type == CPU_IF_RDD_FEED)
        entry = (CPU_RING_DESCRIPTOR_STRUCT *)RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_PTR(get_runner_idx(cpu_rx_runner_image));
    else if (type == CPU_IF_RDD_RECYCLE)
        entry = get_recycle_ring_entry(ring_id);
    else if (type == CPU_IF_RDD_CPU_TX)
    {      
      sram_table_idx = ring_id == TX_HIGH_PRIO_RING_ID ? 0 : 1;
      RDD_CPU_TX_RING_INDICES_WRITE_IDX_READ_G(*write_idx, RDD_CPU_TX_RING_INDICES_VALUES_TABLE_ADDRESS_ARR, sram_table_idx);
      return BDMF_ERR_OK;
    }
    else
        return BDMF_ERR_NOT_SUPPORTED;

    RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_READ(*write_idx, entry);
#else
    if (type == CPU_IF_RDD_DATA)
        RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_READ_G(*write_idx, RDD_CPU_RING_DESCRIPTORS_TABLE_ADDRESS_ARR, ring_id);
    else if (type == CPU_IF_RDD_FEED)
        RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_READ_G(*write_idx, RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_ADDRESS_ARR, 0);
    else if (type == CPU_IF_RDD_RECYCLE)
        RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_READ_G(*write_idx, RDD_CPU_RECYCLE_RING_DESCRIPTOR_TABLE_ADDRESS_ARR, 0);
    else if (type == CPU_IF_RDD_CPU_TX)
    {
      sram_table_idx = ring_id == TX_HIGH_PRIO_RING_ID ? 0 : 1;
      RDD_CPU_TX_RING_INDICES_WRITE_IDX_READ_G(*write_idx, RDD_CPU_TX_RING_INDICES_VALUES_TABLE_ADDRESS_ARR, sram_table_idx);
    }
    else
        return BDMF_ERR_NOT_SUPPORTED;
#endif

    return BDMF_ERR_OK;
}

static inline void rdd_cpu_inc_feed_ring_write_idx(uint32_t delta)
{
#ifndef RDP_SIM
    CPU_FEED_RING_DESCRIPTOR_TABLE_STRUCT *entry;
#endif
    uint32_t write_idx, size_of_ring;

#ifndef RDP_SIM
    entry = RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_PTR(get_runner_idx(cpu_rx_runner_image));
    RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_READ(write_idx, entry);
    RDD_CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_READ(size_of_ring, entry);
#else
    RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_READ_G(write_idx, RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_ADDRESS_ARR, 0);
    RDD_CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_READ_G(size_of_ring, RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_ADDRESS_ARR, 0);
#endif

    RDD_CPU_RING_DESCRIPTOR_WRITE_IDX_WRITE_G(((write_idx + delta) & ((size_of_ring << CPU_RING_SIZE_64_RESOLUTION) - 1)), RDD_CPU_FEED_RING_DESCRIPTOR_TABLE_ADDRESS_ARR, 0);
}

static inline int rdd_cpu_inc_read_idx(uint32_t ring_id, uint8_t type, uint16_t delta)
{
#ifndef RDP_SIM
    CPU_RING_DESCRIPTOR_STRUCT *entry;
#endif
    uint32_t read_idx, size_of_ring;

    if (type == CPU_IF_RDD_DATA)
    {
#ifndef RDP_SIM
        entry = ((CPU_RING_DESCRIPTOR_STRUCT *)RDD_CPU_RING_DESCRIPTORS_TABLE_PTR(get_runner_idx(cpu_rx_runner_image))) + ring_id;
        RDD_CPU_RING_DESCRIPTOR_READ_IDX_READ(read_idx, entry);
        RDD_CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_READ(size_of_ring, entry);
#else
        RDD_CPU_RING_DESCRIPTOR_READ_IDX_READ_G(read_idx, RDD_CPU_RING_DESCRIPTORS_TABLE_ADDRESS_ARR, ring_id);
        RDD_CPU_RING_DESCRIPTOR_NUMBER_OF_ENTRIES_READ_G(size_of_ring, RDD_CPU_RING_DESCRIPTORS_TABLE_ADDRESS_ARR,
            ring_id);
#endif
        RDD_CPU_RING_DESCRIPTOR_READ_IDX_WRITE_G((read_idx + delta) & ((size_of_ring << CPU_RING_SIZE_32_RESOLUTION) - 1), RDD_CPU_RING_DESCRIPTORS_TABLE_ADDRESS_ARR, ring_id);
    }
    else
    {
        return BDMF_ERR_NOT_SUPPORTED;
    }

    return BDMF_ERR_OK;
}

void rdd_cpu_rx_init(void);
uint16_t total_feed_reservation(uint32_t number_of_entries);
int rdd_ring_init(uint32_t ring_id, uint8_t type, bdmf_phys_addr_t ring_address, uint32_t  number_of_entries,
    uint32_t size_of_entry, uint32_t irq, uint32_t write_idx_init_val, bdmf_phys_addr_t phys_ring_index_addr, uint8_t high_prio_tc_thr);
int rdd_ring_destroy(uint32_t ring_id);
int rdd_cpu_rx_interrupt_coalescing_config(uint32_t ring_id, uint32_t timeout_us, uint32_t max_packet_count);
int rdd_cpu_rx_meter_drop_counter_get(int cpu_meter, rdpa_traffic_dir dir, uint32_t *drop_counter);
int rdd_cpu_rx_meter_config(int cpu_meter, uint32_t average_rate, uint32_t burst_size, rdpa_traffic_dir dir);
int rdd_cpu_rx_queue_discard_get(uint32_t ring_id, uint16_t *num_of_packets);
void rdd_cpu_tc_to_rxq_set(rdpa_cpu_port port, uint8_t tc, uint8_t rxq);
void rdd_cpu_exc_tc_to_rxq_set(rdpa_cpu_port port, uint8_t tc, uint8_t rxq);
void rdd_cpu_vport_cpu_obj_set(rdd_vport_id_t vport, uint8_t cpu_obj_idx);
void rdd_cpu_tc_to_rqx_init(uint8_t def_rxq_idx);
void rdd_cpu_vport_cpu_obj_init(uint8_t def_cpu_obj_idx);
int rdd_cpu_rx_ring_low_prio_set(uint32_t ring_id, uint8_t type, uint16_t threshold);
int rdd_cpu_reason_to_cpu_rx_meter(rdpa_cpu_reason reason, rdd_cpu_rx_meter meter, rdpa_traffic_dir dir,
    rdd_vport_vector_t vports_vector);
void rdd_cpu_rx_meters_init(void);
void rdd_cpu_rx_meter_clean_stat(bdmf_index index);
#endif /* _RDD_CPU_RX_H_ */

