/*
    <:copyright-BRCM:2013:DUAL/GPL:standard
    
       Copyright (c) 2013 Broadcom 
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
#if defined(FIRMWARE_INIT)
#include <strings.h>
#endif

#include "rdp_natcache.h"
//#include "bdmf_system_common.h"

#define RDD_NAT_CACHE_LKP_ENTRY_SIZE sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS)

/* Address tables for indexed DPE blocks */
enum {
    natc_nop = 0,
    natc_lookup,
    natc_add,
    natc_del,
};

#define NATC_STATUS_BUSY_BIT  (1 << 4)
#define NATC_STATUS_ERROR_BIT (1 << 5)
#define NATC_STATUS_MISS_BIT  (1 << 6)
#define TIME_OUT_MS                  20
#define KEY_LEN_SHIFT                8
#define NAT_CACHE_SEARCH_ENGINES_NUM 4

/* Offsets must correspond to current rdd_data_structures_auto.h number_of_ports and port_mask offsets. */
#define RDD_FC_NATC_MCAST_FLOW_CONTEXT_ENTRY_NUM_PORTS_PORT_MASK_WRITE( v, p ) FIELD_MWRITE_16((uint8_t *)p + 8, 0, 12, v )

#define RDD_FC_MCAST_CONNECTION2_NEXT_INVALID   (RDD_FC_MCAST_CONNECTION2_TABLE_SIZE-1)

/******************************************************************************/
/*                                                                            */
/*                            Global Variables                                */
/*                                                                            */
/******************************************************************************/

extern uint8_t  *ContextTableBase;
extern uint8_t  *ContextContTableBase;
extern uint8_t  *NatCacheTableBase;
extern uint8_t  *g_runner_extra_ddr_base_addr;
extern uint32_t  g_runner_extra_ddr_base_addr_phys;

extern uint32_t  g_free_context_entries_number;
uint32_t  g_free_flow_entries_number;
uint32_t  g_free_flow_entries_head;
uint32_t  *g_free_flow_entries;

extern bdmf_fastlock int_lock_irq;

volatile uint32_t result_regs_addr[NAT_CACHE_SEARCH_ENGINES_NUM];
volatile uint32_t status_regs_addr[NAT_CACHE_SEARCH_ENGINES_NUM];
volatile uint32_t hit_count_reg_addr[NAT_CACHE_SEARCH_ENGINES_NUM];
volatile uint32_t byte_count_reg_addr[NAT_CACHE_SEARCH_ENGINES_NUM];

int f_rdd_free_context_entry ( uint32_t  context_entry_index );

int rdd_fc_global_cfg_get(RDD_FC_GLOBAL_CFG_ENTRY_DTS *xo_global_cfg)
{
    uint8_t *global_cfg_config_ptr;

    global_cfg_config_ptr = (uint8_t *)(DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_FC_GLOBAL_CFG_ADDRESS);
    RDD_FC_GLOBAL_CFG_ENTRY_FC_ACCEL_MODE_READ(xo_global_cfg->fc_accel_mode, global_cfg_config_ptr);
    RDD_FC_GLOBAL_CFG_ENTRY_FC_TCP_ACK_MFLOWS_READ(xo_global_cfg->fc_tcp_ack_mflows, global_cfg_config_ptr);

    return BDMF_ERR_OK;
}

int rdd_fc_global_cfg_set(RDD_FC_GLOBAL_CFG_ENTRY_DTS *xi_global_cfg)
{
    uint8_t *global_cfg_config_ptr;

    global_cfg_config_ptr = (uint8_t *)(DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_FC_GLOBAL_CFG_ADDRESS);
    RDD_FC_GLOBAL_CFG_ENTRY_FC_ACCEL_MODE_WRITE(xi_global_cfg->fc_accel_mode, global_cfg_config_ptr);
    RDD_FC_GLOBAL_CFG_ENTRY_FC_TCP_ACK_MFLOWS_WRITE(xi_global_cfg->fc_tcp_ack_mflows, global_cfg_config_ptr);

    global_cfg_config_ptr = (uint8_t *)(DEVICE_ADDRESS( RUNNER_PRIVATE_1_OFFSET ) + US_FC_GLOBAL_CFG_ADDRESS);
    RDD_FC_GLOBAL_CFG_ENTRY_FC_ACCEL_MODE_WRITE(xi_global_cfg->fc_accel_mode, global_cfg_config_ptr);
    RDD_FC_GLOBAL_CFG_ENTRY_FC_TCP_ACK_MFLOWS_WRITE(xi_global_cfg->fc_tcp_ack_mflows, global_cfg_config_ptr);

    return BDMF_ERR_OK;
}

int rdd_free_context_entry(uint32_t  context_entry_index)
{
    return f_rdd_free_context_entry(context_entry_index);
}

BL_LILAC_RDD_ERROR_DTE f_rdd_connection_table_initialize ( void )
{
    uint32_t indirect_addr_regs_addr;
    uint32_t indirect_data_regs_addr;
    uint32_t nat_cache_entry_idx;
    uint32_t nat_cache_data_word_idx;
    uint32_t register_value;
    uint32_t *connection_table_config_ptr;
    uint32_t nat_cache_table_address;
    uint32_t *context_table_config_ptr;
    uint32_t context_table_address;
    uint32_t *context_cont_table_config_ptr;
    uint32_t context_cont_table_address;
    uint32_t i;
    RUNNER_REGS_CFG_CAM_CFG runner_cam_configuration_register;

    runner_cam_configuration_register.stop_value = 0xFFFF;
    RUNNER_REGS_0_CFG_CAM_CFG_WRITE(runner_cam_configuration_register);
    RUNNER_REGS_1_CFG_CAM_CFG_WRITE(runner_cam_configuration_register);

    result_regs_addr[0] = NATCACHE_RDP_NAT0_KEY_RESULT_0_17;
    result_regs_addr[1] = NATCACHE_RDP_NAT1_KEY_RESULT_0_17;
    result_regs_addr[2] = NATCACHE_RDP_NAT2_KEY_RESULT_0_17;
    result_regs_addr[3] = NATCACHE_RDP_NAT3_KEY_RESULT_0_17;

    status_regs_addr[0] = NATCACHE_RDP_NAT0_COMMAND_STATUS;
    status_regs_addr[1] = NATCACHE_RDP_NAT1_COMMAND_STATUS;
    status_regs_addr[2] = NATCACHE_RDP_NAT2_COMMAND_STATUS;
    status_regs_addr[3] = NATCACHE_RDP_NAT3_COMMAND_STATUS;

    hit_count_reg_addr[0] = NATCACHE_RDP_NAT0_HIT_COUNT;
    hit_count_reg_addr[1] = NATCACHE_RDP_NAT1_HIT_COUNT;
    hit_count_reg_addr[2] = NATCACHE_RDP_NAT2_HIT_COUNT;
    hit_count_reg_addr[3] = NATCACHE_RDP_NAT3_HIT_COUNT;

    byte_count_reg_addr[0] = NATCACHE_RDP_NAT0_BYTE_COUNT;
    byte_count_reg_addr[1] = NATCACHE_RDP_NAT1_BYTE_COUNT;
    byte_count_reg_addr[2] = NATCACHE_RDP_NAT2_BYTE_COUNT;
    byte_count_reg_addr[3] = NATCACHE_RDP_NAT3_BYTE_COUNT;

    indirect_addr_regs_addr = NATCACHE_RDP_INDIRECT_ADDRESS;
    indirect_data_regs_addr = NATCACHE_RDP_INDIRECT_DATA;

    for (nat_cache_entry_idx = 0; nat_cache_entry_idx < 1024; nat_cache_entry_idx++)
    {
       for (nat_cache_data_word_idx = 0; nat_cache_data_word_idx < 20; nat_cache_data_word_idx++)
       {
           register_value = 0;
           WRITE_32(indirect_data_regs_addr + nat_cache_data_word_idx*4, register_value);
       }

       register_value = (1 << 10) | nat_cache_entry_idx;
       WRITE_32(indirect_addr_regs_addr, register_value);
    }

#if !defined(BDMF_SYSTEM_SIM)
    nat_cache_table_address = RDD_RSV_VIRT_TO_PHYS( g_runner_extra_ddr_base_addr, g_runner_extra_ddr_base_addr_phys,
        NatCacheTableBase );
#else
    nat_cache_table_address = RDP_NATC_KEY_TABLE_ADDR; /* NAT_CACHE_TABLE_ADDRESS; */
#endif
    connection_table_config_ptr = ( uint32_t * )(DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_CONNECTION_TABLE_CONFIG_ADDRESS );
    MWRITE_32( connection_table_config_ptr, nat_cache_table_address );
    connection_table_config_ptr = ( uint32_t * )(DEVICE_ADDRESS( RUNNER_PRIVATE_1_OFFSET ) + US_CONNECTION_TABLE_CONFIG_ADDRESS );
    MWRITE_32( connection_table_config_ptr, nat_cache_table_address );

#if !defined(BDMF_SYSTEM_SIM)
    context_table_address = RDD_RSV_VIRT_TO_PHYS( g_runner_extra_ddr_base_addr, g_runner_extra_ddr_base_addr_phys,
        ContextTableBase );
#else
    context_table_address = RDP_NATC_CONTEXT_TABLE_ADDR; /* NATC_CONTEXT_TABLE_ADDRESS; */
#endif
    context_table_config_ptr = ( uint32_t * )(DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_CONTEXT_TABLE_CONFIG_ADDRESS );
    MWRITE_32( context_table_config_ptr, context_table_address );

#if !defined(BDMF_SYSTEM_SIM)
    context_cont_table_address = RDD_RSV_VIRT_TO_PHYS( g_runner_extra_ddr_base_addr, g_runner_extra_ddr_base_addr_phys,
        ContextContTableBase );
#else
    context_cont_table_address = RDP_CONTEXT_CONTINUATION_TABLE_ADDR; /* CONTEXT_CONTINUATION_TABLE_ADDRESS; */
#endif
    context_cont_table_config_ptr = ( uint32_t * )(DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_CONTEXT_CONTINUATION_TABLE_CONFIG_ADDRESS );
    MWRITE_32( context_cont_table_config_ptr, context_cont_table_address );

    context_cont_table_config_ptr = ( uint32_t * )(DEVICE_ADDRESS( RUNNER_PRIVATE_1_OFFSET ) + US_CONTEXT_CONTINUATION_TABLE_CONFIG_ADDRESS );
    MWRITE_32( context_cont_table_config_ptr, context_cont_table_address );

    g_free_context_entries_number = 0;

    for ( i = 0; i < RDD_NATC_CONTEXT_TABLE_SIZE; i++ )
    {
        f_rdd_free_context_entry ( i );
    }

    memset(ContextContTableBase, 0x00, CONTEXT_CONTINUATION_TABLE_BYTE_SIZE);

    g_free_flow_entries = (uint32_t *) bdmf_alloc(RDD_FLOW_ENTRIES_SIZE * sizeof(uint32_t));
    g_free_flow_entries_number = RDD_FLOW_ENTRIES_SIZE;
    g_free_flow_entries_head = 0;
    memset(g_free_flow_entries, 0, RDD_FLOW_ENTRIES_SIZE * sizeof(uint32_t));

    return BDMF_ERR_OK;
}

#if !defined(FIRMWARE_INIT)
static int rdd_nat_cache_write_command(uint32_t natc_engine_idx, uint32_t command)
{
    uint32_t status_reg;
    uint32_t status_mask;
    uint8_t break_out_counter = 200;

    if (command == natc_lookup)
        status_mask = (NATC_STATUS_BUSY_BIT | NATC_STATUS_MISS_BIT);
    else
        status_mask = (NATC_STATUS_BUSY_BIT | NATC_STATUS_ERROR_BIT);

    /* write command and wait for not busy */
    command |= NATC_STATUS_BUSY_BIT;

    WRITE_32(status_regs_addr[natc_engine_idx], command);

    while (--break_out_counter)
    {
        READ_32(status_regs_addr[natc_engine_idx], status_reg);

        if ((status_reg & status_mask) == 0)
            return BDMF_ERR_OK;
    }

    BDMF_TRACE_INFO("rdd_nat_cache_write_command(): status register = 0x%0x\n", status_reg);
    return BDMF_ERR_INTERNAL;
}

static void rdd_nat_cache_write_key_result_regs(uint32_t natc_engine_idx, uint32_t *keyword)
{
    uint32_t key_value;

    key_value = swap4bytes(*(uint32_t *)(keyword + 3));
    WRITE_32(result_regs_addr[natc_engine_idx] + 0, key_value);

    key_value = swap4bytes(*(uint32_t *)(keyword + 2));
    WRITE_32(result_regs_addr[natc_engine_idx] + 4, key_value);

    key_value = swap4bytes(*(uint32_t *)(keyword + 1));
    WRITE_32(result_regs_addr[natc_engine_idx] + 8, key_value);

    key_value = swap4bytes(*(uint32_t *)(keyword + 0));
    WRITE_32(result_regs_addr[natc_engine_idx] + 12, key_value);
}

int rdd_nat_cache_submit_command(uint32_t command, uint32_t *keyword, uint32_t *hit_count, uint32_t *byte_count)
{
    uint32_t natc_engine_idx = command;
    int rc;

    rdd_nat_cache_write_key_result_regs(natc_engine_idx, keyword);

    if (command == natc_add)
    {
        uint32_t key_value;
        int i, j;

        /* Write the context in keyword[4] through keyword[17] to the that
         * NAT Cache result registers 4 through 17 (bytes 16 through 72)
         * starting from the last word to the first word.
         */
        for (i = 17, j = 16; i > 3; i--, j += 4)
        {
            key_value = swap4bytes(*(uint32_t *)(keyword + i));
            WRITE_32(result_regs_addr[natc_engine_idx] + j, key_value);
        }
    }

    rc = rdd_nat_cache_write_command(natc_engine_idx, command);

    if ((rc == BDMF_ERR_OK) && (command == natc_lookup))
    {
       if (hit_count)
           READ_32(hit_count_reg_addr[natc_engine_idx], *hit_count);

       if (byte_count)
           READ_32(byte_count_reg_addr[natc_engine_idx], *byte_count);
    }

    return rc;
}

static int f_rdd_nat_cache_entry_flush ( rdd_fc_context_t *context_entry,
                                         bdmf_index flow_entry_index )
{
    RDD_NAT_CACHE_TABLE_DTS *nat_cache_table_ptr =
        (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr =
        (RDD_CONTEXT_CONTINUATION_TABLE_DTS *)ContextContTableBase;
    RDD_NAT_CACHE_LKP_ENTRY_DTS *nat_cache_lkp_entry_ptr, nat_cache_lookup_entry;
    uint32_t entry_index = RDD_NATC_CONTEXT_TABLE_SIZE;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint32_t connection_table_index;
    unsigned long flags;
    uint32_t valid;
    int rc;
    uint32_t hit_count, byte_count;
    RDD_NATC_CONTEXT_TABLE_DTS   *natc_context_table_ptr;
    RDD_NATC_CONTEXT_ENTRY_UNION_DTS *natc_context_entry_ptr;

    if ((g_free_flow_entries[flow_entry_index] & RDD_FLOW_ENTRY_VALID) == RDD_FLOW_ENTRY_VALID)
    {
        entry_index = g_free_flow_entries[flow_entry_index] & ~RDD_FLOW_ENTRY_VALID;
    }
    else
    {
        return BDMF_ERR_PARM;
    }

    if (entry_index >= RDD_NATC_CONTEXT_TABLE_SIZE)
    {
        return BDMF_ERR_PARM;
    }

    context_cont_entry_ptr = &context_cont_table_ptr->entry[entry_index];

    RDD_CONTEXT_CONTINUATION_ENTRY_VALID_READ (valid, context_cont_entry_ptr);

    if(!valid)
    {
        return BDMF_ERR_NOENT;
    }

    natc_context_table_ptr = ( RDD_NATC_CONTEXT_TABLE_DTS * )ContextTableBase;
    natc_context_entry_ptr = &( natc_context_table_ptr->entry[ entry_index ] );

    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_READ (connection_table_index, context_cont_entry_ptr);

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *)&nat_cache_table_ptr->entry[connection_table_index];

    memcpy(&nat_cache_lookup_entry, nat_cache_lkp_entry_ptr, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));

    bdmf_fastlock_lock_irq (&int_lock_irq, flags);

    rc = rdd_nat_cache_submit_command(natc_lookup, (uint32_t *)&nat_cache_lookup_entry, &hit_count, &byte_count);

    if (rc == BDMF_ERR_OK)
    {
        /* 4908 NATC does not push the stats back to DDR when flow is deleted from NATC internal cache.
         * During context/flow modification, when the flow is required to be flushed from NATC internal cache using natc_del command,
         * it causes the flow-hits to get lost.
         * This issue became more visible with multi-flow multicast because master flow gets modified too often */
        RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_FLOW_HITS_WRITE( hit_count, natc_context_entry_ptr );
        RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_FLOW_BYTES_WRITE( byte_count, natc_context_entry_ptr );
        rc = rdd_nat_cache_submit_command(natc_del, (uint32_t *)&nat_cache_lookup_entry, NULL, NULL);
    }

    bdmf_fastlock_unlock_irq (&int_lock_irq, flags);

    return rc;
}
#endif /*!FIRMWARE_INIT*/

int f_rdd_free_context_entry ( uint32_t  context_entry_index )
{
    RDD_NATC_CONTEXT_TABLE_DTS   *natc_context_table_ptr = ( RDD_NATC_CONTEXT_TABLE_DTS * )ContextTableBase;
    RDD_NATC_CONTEXT_ENTRY_UNION_DTS *natc_context_entry_ptr;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;

    natc_context_entry_ptr = &( natc_context_table_ptr->entry[ context_entry_index ] );
    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ context_entry_index ] );

    memset(natc_context_entry_ptr, 0x00, sizeof(RDD_NATC_CONTEXT_ENTRY_UNION_DTS));
    RDD_CONTEXT_CONTINUATION_ENTRY_VALID_WRITE ( 0, context_cont_entry_ptr );
    g_free_context_entries_number++;

    return BDMF_ERR_OK;
}

static int f_rdd_mcast_master_context_entry_write ( RDD_CONTEXT_ENTRY_UNION_DTS  *context_entry,
                                                    RDD_NATC_CONTEXT_ENTRY_UNION_DTS  *natc_context_entry_ptr,
                                                    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr,
                                                    uint32_t is_new_entry )
{
    int i;
    RDD_FC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_DTS  *master_context_entry_p = &context_entry->fc_mcast_master_flow_context_entry;
    if(is_new_entry)
    {
        RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_FLOW_HITS_WRITE( 0, natc_context_entry_ptr );
        RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_FLOW_BYTES_WRITE( 0, natc_context_entry_ptr );
        RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_MULTICAST_FLAG_WRITE( master_context_entry_p->multicast_flag, natc_context_entry_ptr );
        RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_CONTEXT_CONTINUATION_FLAG_WRITE( 0, natc_context_entry_ptr );

        RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_DIRECTION_WRITE ( context_entry->fc_ucast_flow_context_entry.connection_direction, context_cont_entry_ptr );
        RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_WRITE ( context_entry->fc_ucast_flow_context_entry.connection_table_index, context_cont_entry_ptr );
        RDD_CONTEXT_CONTINUATION_ENTRY_VALID_WRITE ( context_entry->fc_ucast_flow_context_entry.valid, context_cont_entry_ptr );
    }
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_SERVICE_QUEUE_ID_WRITE ( master_context_entry_p->service_queue_id, natc_context_entry_ptr );
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_FWD_AND_TRAP_WRITE( master_context_entry_p->fwd_and_trap, natc_context_entry_ptr );
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_PATHSTAT_IDX_WRITE( master_context_entry_p->pathstat_idx, natc_context_entry_ptr );
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_MTU_WRITE(master_context_entry_p->mtu, natc_context_entry_ptr);
    for (i=0; i < RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_CLIENT_IDX_VECTOR_NUMBER; i++)
    {
        RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_CLIENT_IDX_VECTOR_WRITE(master_context_entry_p->client_idx_vector[i], natc_context_entry_ptr, i);
    }

    return ( BL_LILAC_RDD_OK );
}
static int f_rdd_mcast_master_context_entry_read ( RDD_NATC_CONTEXT_ENTRY_UNION_DTS  *natc_context_entry_ptr,
                                                   RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr,
                                                   RDD_CONTEXT_ENTRY_UNION_DTS  *context_entry )
{
    int i;
    RDD_FC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_DTS  *master_context_entry_p = &context_entry->fc_mcast_master_flow_context_entry;
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_MULTICAST_FLAG_READ( master_context_entry_p->multicast_flag, natc_context_entry_ptr );
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_SERVICE_QUEUE_ID_READ ( master_context_entry_p->service_queue_id, natc_context_entry_ptr );
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_FWD_AND_TRAP_READ( master_context_entry_p->fwd_and_trap, natc_context_entry_ptr );
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_PATHSTAT_IDX_READ( master_context_entry_p->pathstat_idx, natc_context_entry_ptr );
    RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_MTU_READ(master_context_entry_p->mtu, natc_context_entry_ptr);
    for (i=0; i < RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_CLIENT_IDX_VECTOR_NUMBER; i++)
    {
        RDD_FC_NATC_MCAST_MASTER_FLOW_CONTEXT_ENTRY_CLIENT_IDX_VECTOR_READ(master_context_entry_p->client_idx_vector[i], natc_context_entry_ptr, i);
    }

    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_DIRECTION_READ ( context_entry->fc_ucast_flow_context_entry.connection_direction, context_cont_entry_ptr );
    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_READ ( context_entry->fc_ucast_flow_context_entry.connection_table_index, context_cont_entry_ptr );
    RDD_CONTEXT_CONTINUATION_ENTRY_VALID_READ ( context_entry->fc_ucast_flow_context_entry.valid, context_cont_entry_ptr );

    return ( BL_LILAC_RDD_OK );
}
/* Function: rdd_fc_mcast_compose_lkup_key()
 * Description: Prepare rdd mcast lookup key (13 Bytes) and does not set the VALID bit */ 
static int rdd_fc_mcast_compose_lkup_key(rdpa_mcast_flow_key_t  *mcast_lookup_entry,
                                              uint8_t *key_bytes)
{
    /* Note: this function does not set the valid bit */

    RDD_MCAST_LKP_WORD3_CRC_DTS lkp_word3;
    uint32_t crc;
    uint16_t vid;

    memset(key_bytes, 0, sizeof(RDD_NAT_CACHE_MCAST_LKP_ENTRY_DTS));

    RDD_NAT_CACHE_MCAST_LKP_ENTRY_KEY_EXTEND_WRITE(mcast_lookup_entry->key.mcast_group.l3.gr_ip.family, key_bytes);
    if (mcast_lookup_entry->key.mcast_group.l3.gr_ip.family == bdmf_ip_family_ipv4 )
    {
        RDD_NAT_CACHE_MCAST_LKP_ENTRY_DST_IP_WRITE(mcast_lookup_entry->key.mcast_group.l3.gr_ip.addr.ipv4, key_bytes);
    }
    else
    {
        crc = crcbitbybit((uint8_t *)&mcast_lookup_entry->key.mcast_group.l3.gr_ip.addr.ipv6.data,
                                             16, 0, 0xffffffff, RDD_CRC_TYPE_32);
        RDD_NAT_CACHE_MCAST_LKP_ENTRY_DST_IP_WRITE(crc, key_bytes);
    }
    if (mcast_lookup_entry->key.mcast_group.l3.src_ip.family == bdmf_ip_family_ipv4 )
    {
        RDD_NAT_CACHE_MCAST_LKP_ENTRY_SRC_IP_WRITE(mcast_lookup_entry->key.mcast_group.l3.src_ip.addr.ipv4, key_bytes);
    }
    else
    {
        crc = crcbitbybit((uint8_t *)&mcast_lookup_entry->key.mcast_group.l3.src_ip.addr.ipv6.data,
                                             16, 0, 0xffffffff, RDD_CRC_TYPE_32);
        RDD_NAT_CACHE_MCAST_LKP_ENTRY_SRC_IP_WRITE(crc, key_bytes);
    }

    RDD_NAT_CACHE_MCAST_LKP_ENTRY_IS_MULTICAST_WRITE(1, key_bytes);
    RDD_NAT_CACHE_MCAST_LKP_ENTRY_CLIENT_INDEX_WRITE(mcast_lookup_entry->entry_idx, key_bytes);

    memset((uint8_t *)&lkp_word3, 0, sizeof(RDD_MCAST_LKP_WORD3_CRC_DTS));
    vid = (mcast_lookup_entry->outer_vlan == RDPA_VID_MASK) ? 0 : mcast_lookup_entry->outer_vlan;
    RDD_MCAST_LKP_WORD3_CRC_VID0_WRITE(vid, &lkp_word3);
    vid = (mcast_lookup_entry->inner_vlan == RDPA_VID_MASK) ? 0 : mcast_lookup_entry->inner_vlan;
    RDD_MCAST_LKP_WORD3_CRC_VID1_WRITE(vid, &lkp_word3);
    RDD_MCAST_LKP_WORD3_CRC_TOS_WRITE(mcast_lookup_entry->tos, &lkp_word3);
    RDD_MCAST_LKP_WORD3_CRC_LKUP_PORT_WRITE(mcast_lookup_entry->rx_if, &lkp_word3);
    RDD_MCAST_LKP_WORD3_CRC_NUM_OF_VLANS_WRITE(mcast_lookup_entry->num_vlan_tags, &lkp_word3);
    crc = crcbitbybit((uint8_t *)&lkp_word3, sizeof(lkp_word3), 0, 0xffffffff, RDD_CRC_TYPE_32);

    RDD_NAT_CACHE_MCAST_LKP_ENTRY_VID1_VID0_TOS_PORT_NUMVLANS_CRC_WRITE(crc, key_bytes);

    return ( BL_LILAC_RDD_OK );
}

/* Function: rdd_fc_mcast_decompose_lkup_key()
 * Description: Prepare rdpa mcast lookup key from rdd key */ 
static int rdd_fc_mcast_decompose_lkup_key(uint8_t *key_bytes,
                                           rdpa_mcast_flow_key_t  *mcast_lookup_entry)
{
    uint32_t connection_entry_valid;
    uint32_t connection_entry_is_multicast;

    RDD_NAT_CACHE_MCAST_LKP_ENTRY_VALID_READ ( connection_entry_valid, key_bytes );
    RDD_NAT_CACHE_MCAST_LKP_ENTRY_IS_MULTICAST_READ ( connection_entry_is_multicast, key_bytes );

    if ( ( !connection_entry_valid ) || ( !connection_entry_is_multicast ) )
    {
        return ( BL_LILAC_RDD_ERROR_GET_LOOKUP_ENTRY );
    }

    RDD_NAT_CACHE_MCAST_LKP_ENTRY_KEY_EXTEND_READ(mcast_lookup_entry->key.mcast_group.l3.gr_ip.family, key_bytes);
    RDD_NAT_CACHE_MCAST_LKP_ENTRY_DST_IP_READ(mcast_lookup_entry->key.mcast_group.l3.gr_ip.addr.ipv4, key_bytes);
    RDD_NAT_CACHE_MCAST_LKP_ENTRY_SRC_IP_READ(mcast_lookup_entry->key.mcast_group.l3.src_ip.addr.ipv4, key_bytes);
    RDD_NAT_CACHE_MCAST_LKP_ENTRY_CLIENT_INDEX_READ(mcast_lookup_entry->entry_idx, key_bytes);
    return ( BL_LILAC_RDD_OK );
}

int rdd_mcast_connection_entry_get ( rdpa_traffic_dir    direction,
                                     uint32_t            entry_index,
                                     rdpa_mcast_flow_key_t  *connection_entry )
{
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;


    if ( entry_index >= RDD_NATC_CONTEXT_TABLE_SIZE )
    {
        return ( BL_LILAC_RDD_ERROR_GET_LOOKUP_ENTRY );
    }

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ entry_index ] );

    return rdd_fc_mcast_decompose_lkup_key((uint8_t *)nat_cache_lkp_entry_ptr, connection_entry);
}

static int _rdd_is_mcast_master_entry ( bdmf_index flow_entry_index )
{
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    uint32_t                     valid;
    uint32_t                     multicast_flag;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;
    uint32_t                     entry_index = RDD_NATC_CONTEXT_TABLE_SIZE;

    if ((g_free_flow_entries[flow_entry_index] & RDD_FLOW_ENTRY_VALID) == RDD_FLOW_ENTRY_VALID)
    {
        entry_index = g_free_flow_entries[flow_entry_index] & ~RDD_FLOW_ENTRY_VALID;
    }
    else
    {
        return 0;
    }

    if ( entry_index >= RDD_NATC_CONTEXT_TABLE_SIZE )
    {
        return ( 0 );
    }

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ entry_index ] );

    RDD_NAT_CACHE_MCAST_LKP_ENTRY_VALID_READ (valid, nat_cache_lkp_entry_ptr );

    if(!valid)
    {
        return 0;
    }

    RDD_NAT_CACHE_MCAST_LKP_ENTRY_IS_MULTICAST_READ( multicast_flag, nat_cache_lkp_entry_ptr );

    if( multicast_flag )
    {
        uint32_t client_index;
        RDD_NAT_CACHE_MCAST_LKP_ENTRY_CLIENT_INDEX_READ( client_index, nat_cache_lkp_entry_ptr);
        /* Client flow shares the same ucast flow context but Master flow context is different */
        if ( client_index == 0 )
        {
            return ( 1 );
        }
    }
    return 0;
}


static int f_rdd_context_entry_write ( rdd_fc_context_t            *context_entry,
                                       uint32_t                     nat_cache_entry_index,
                                       uint32_t                     is_mcast_mstr,
                                       uint32_t                     is_new_entry )
{
    uint32_t i;
    RDD_NATC_CONTEXT_TABLE_DTS   *natc_context_table_ptr;
    RDD_NATC_CONTEXT_ENTRY_UNION_DTS *natc_context_entry_ptr;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    int continuation_flag;

    natc_context_table_ptr = ( RDD_NATC_CONTEXT_TABLE_DTS * )ContextTableBase;
    natc_context_entry_ptr = &( natc_context_table_ptr->entry[ nat_cache_entry_index ] );
    context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ nat_cache_entry_index ] );

    {
        /* Master flow context is different from unicast/client context */
        if(is_mcast_mstr)
        {
            return f_rdd_mcast_master_context_entry_write(context_entry, natc_context_entry_ptr, context_cont_entry_ptr, is_new_entry);
        }
        if(is_new_entry)
        {
            /* + 4 because remaining fields of context can be used for command list if continuation not required */
            continuation_flag = ( (context_entry->fc_ucast_flow_context_entry.command_list_length_32 * 4 > RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER + 4) || context_entry->fc_ucast_flow_context_entry.drop ) ? 1 : 0;

            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_FLOW_HITS_WRITE( 0, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_FLOW_BYTES_WRITE( 0, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_MULTICAST_FLAG_WRITE( context_entry->fc_ucast_flow_context_entry.multicast_flag, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_CONTEXT_CONTINUATION_FLAG_WRITE ( continuation_flag, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_ROUTED_WRITE( context_entry->fc_ucast_flow_context_entry.is_routed, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_L2_ACCEL_WRITE( context_entry->fc_ucast_flow_context_entry.is_l2_accel, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_MAPT_US_WRITE( context_entry->fc_ucast_flow_context_entry.is_mapt_us, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_DF_WRITE( context_entry->fc_ucast_flow_context_entry.is_df, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_EGRESS_PHY_WRITE( context_entry->fc_ucast_flow_context_entry.egress_phy, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_UNICAST_WFD_ANY_WRITE(context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_any, natc_context_entry_ptr);
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_DROP_WRITE(context_entry->fc_ucast_flow_context_entry.drop, natc_context_entry_ptr);
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_WFD_IDX_WRITE(context_entry->fc_ucast_flow_context_entry.wfd_idx, natc_context_entry_ptr);
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_HIT_TRAP_WRITE(context_entry->fc_ucast_flow_context_entry.is_hit_trap, natc_context_entry_ptr);
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_CPU_REASON_WRITE(context_entry->fc_ucast_flow_context_entry.cpu_reason, natc_context_entry_ptr);
            RDD_CONTEXT_CONTINUATION_ENTRY_IS_UNICAST_WFD_NIC_WRITE(context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_nic, context_cont_entry_ptr);
            RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_DIRECTION_WRITE ( context_entry->fc_ucast_flow_context_entry.connection_direction, context_cont_entry_ptr );
            RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_WRITE ( context_entry->fc_ucast_flow_context_entry.connection_table_index, context_cont_entry_ptr );

            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IP_ADDRESSES_TABLE_INDEX_WRITE( context_entry->fc_ucast_flow_context_entry.ip_addresses_table_index, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_PATHSTAT_IDX_WRITE( context_entry->fc_ucast_flow_context_entry.pathstat_idx, natc_context_entry_ptr );

            if (continuation_flag)
            {
                int remaining_length;

                if (!context_entry->fc_ucast_flow_context_entry.drop)
                {
                    remaining_length = context_entry->fc_ucast_flow_context_entry.command_list_length_32 * 4 - RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER;
                }
                else
                {
                    remaining_length = RDD_CONTEXT_CONTINUATION_ENTRY_COMMAND_LIST_NUMBER;
                }

                for ( i = 0; i < RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER; i++ )
                {
                    RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_WRITE ( context_entry->fc_ucast_flow_context_entry.command_list[ i ], 
                                                                              natc_context_entry_ptr, i );
                }

                for ( i = 0; i < remaining_length; i++ )
                {
                    RDD_CONTEXT_CONTINUATION_ENTRY_COMMAND_LIST_WRITE( context_entry->fc_ucast_flow_context_entry.command_list[ i + RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER ], 
                                                                       context_cont_entry_ptr, i );
                }

                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_REMAINING_LENGTH_WRITE ( remaining_length, natc_context_entry_ptr ); 
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_CONTEXT_CONTINUATION_TABLE_INDEX_WRITE ( nat_cache_entry_index, natc_context_entry_ptr );    
            }
            else
            {
                /* + 4 because remaining fields of context can be used for command list if continuation not required */
                for ( i = 0; i < RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER + 4; i++ )
                {
                    RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_WRITE ( context_entry->fc_ucast_flow_context_entry.command_list[ i ], 
                                                                              natc_context_entry_ptr, i );
                }
            }

            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_WRED_HIGH_PRIO_WRITE( context_entry->fc_ucast_flow_context_entry.is_wred_high_prio, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_INGQOS_HIGH_PRIO_WRITE( context_entry->fc_ucast_flow_context_entry.is_ingqos_high_prio, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_MTU_WRITE( context_entry->fc_ucast_flow_context_entry.mtu, natc_context_entry_ptr );
            RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_TOS_WRITE( context_entry->fc_ucast_flow_context_entry.tos, natc_context_entry_ptr );
            if (context_entry->fc_ucast_flow_context_entry.egress_phy != rdd_egress_phy_wlan)
            {
                RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_TRAFFIC_CLASS_WRITE(context_entry->fc_ucast_flow_context_eth_xtm_entry.traffic_class, natc_context_entry_ptr);
                RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_RATE_CONTROLLER_WRITE(context_entry->fc_ucast_flow_context_eth_xtm_entry.rate_controller, natc_context_entry_ptr);
            }

            RDD_CONTEXT_CONTINUATION_ENTRY_VALID_WRITE ( context_entry->fc_ucast_flow_context_entry.valid, context_cont_entry_ptr );
        }
#if defined(CONFIG_BCM_DPI_WLAN_QOS)
	else {
            if (context_entry->fc_ucast_flow_context_entry.egress_phy == rdd_egress_phy_wlan)
            {
                if (context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_any)
                {
                    if (context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_nic)
                    {
		        RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_PRIORITY_WRITE(context_entry->fc_ucast_flow_context_entry.priority, natc_context_entry_ptr);
                    }
                    else
                    {
                        RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY_FLOW_RING_ID_WRITE(context_entry->fc_ucast_flow_context_wfd_dhd_entry.flow_ring_id, natc_context_entry_ptr);
			RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_PRIORITY_WRITE(context_entry->fc_ucast_flow_context_entry.priority, natc_context_entry_ptr);
                    }
                }
#if defined(CONFIG_DHD_RUNNER)
                else
                {
                    RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_FLOW_RING_ID_WRITE(context_entry->fc_ucast_flow_context_rnr_dhd_entry.flow_ring_id, natc_context_entry_ptr);
		    RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_PRIORITY_WRITE(context_entry->fc_ucast_flow_context_entry.priority, natc_context_entry_ptr);
                }
#endif
            }
	}
#endif /* CONFIG_BCM_DPI_WLAN_QOS */

        RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_PRIORITY_WRITE(context_entry->fc_ucast_flow_context_entry.priority, natc_context_entry_ptr);
        RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_WFD_PRIO_WRITE(context_entry->fc_ucast_flow_context_entry.wfd_prio, natc_context_entry_ptr);

        if (context_entry->fc_ucast_flow_context_entry.egress_phy == rdd_egress_phy_wlan)
        {
            if (context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_any)
            {
                RDD_FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY_IS_MCAST_WRITE(context_entry->fc_ucast_flow_context_wfd_nic_entry.is_mcast, natc_context_entry_ptr);
                if (context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_nic)
                {
                    RDD_FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY_CHAIN_IDX_WRITE(context_entry->fc_ucast_flow_context_wfd_nic_entry.chain_idx, natc_context_entry_ptr);
                }
                else
                {
                    RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY_WIFI_SSID_WRITE(context_entry->fc_ucast_flow_context_wfd_dhd_entry.wifi_ssid, natc_context_entry_ptr);
                    RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY_FLOW_RING_ID_WRITE(context_entry->fc_ucast_flow_context_wfd_dhd_entry.flow_ring_id, natc_context_entry_ptr);
                }
            }
#if defined(CONFIG_DHD_RUNNER)
            else
            {
                RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_RADIO_IDX_WRITE(context_entry->fc_ucast_flow_context_rnr_dhd_entry.radio_idx, natc_context_entry_ptr);
                RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_WIFI_SSID_WRITE(context_entry->fc_ucast_flow_context_rnr_dhd_entry.wifi_ssid, natc_context_entry_ptr);
                RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_FLOW_RING_ID_WRITE(context_entry->fc_ucast_flow_context_rnr_dhd_entry.flow_ring_id, natc_context_entry_ptr);
                RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_DHD_FLOW_PRIORITY_WRITE(context_entry->fc_ucast_flow_context_rnr_dhd_entry.dhd_flow_priority, natc_context_entry_ptr);
            }
#endif
        }
        else
        {
            RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_EGRESS_PORT_WRITE(context_entry->fc_ucast_flow_context_eth_xtm_entry.egress_port, natc_context_entry_ptr);
            RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_TRAFFIC_CLASS_WRITE(context_entry->fc_ucast_flow_context_eth_xtm_entry.traffic_class, natc_context_entry_ptr);
            RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_RATE_CONTROLLER_WRITE(context_entry->fc_ucast_flow_context_eth_xtm_entry.rate_controller, natc_context_entry_ptr);
            RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_LAG_PORT_WRITE(context_entry->fc_ucast_flow_context_eth_xtm_entry.egress_info , natc_context_entry_ptr);
        }
        RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_SERVICE_QUEUE_ID_WRITE( context_entry->fc_ucast_flow_context_entry.service_queue_id, natc_context_entry_ptr );
    }

    return BDMF_ERR_OK;
}

static int f_rdd_context_entry_add ( rdd_fc_context_t            *context_entry,
                                     uint32_t                    nat_cache_entry_index,
                                     uint32_t                    is_mcast_mstr,
                                     uint32_t                    *flow_entry_index )
{
    assert(g_free_context_entries_number > 0);

    if (g_free_context_entries_number > RDD_RESERVED_CONTEXT_ENTRIES)
    {
        int i;

        for (i = 0; i < RDD_FLOW_ENTRIES_SIZE; i++)
        {
            if (!(g_free_flow_entries[g_free_flow_entries_head] & RDD_FLOW_ENTRY_VALID))
            {
                *flow_entry_index = g_free_flow_entries_head;
                g_free_flow_entries[g_free_flow_entries_head] = RDD_FLOW_ENTRY_VALID | nat_cache_entry_index;
                g_free_flow_entries_head = (g_free_flow_entries_head + 1) % RDD_FLOW_ENTRIES_SIZE;
                g_free_flow_entries_number--;
                g_free_context_entries_number--;
                break;
            }
            g_free_flow_entries_head = (g_free_flow_entries_head + 1) % RDD_FLOW_ENTRIES_SIZE;
        }

        if (i == RDD_FLOW_ENTRIES_SIZE)
        {
            return BDMF_ERR_NORES;
        }
    }
    else
    {
        return BDMF_ERR_NORES;
    }

    context_entry->fc_mcast_flow_context_entry.valid = 1;

    f_rdd_context_entry_write ( context_entry, nat_cache_entry_index, is_mcast_mstr, 1 /*is_new_entry*/ );

#if defined(CC_RDD_ROUTER_DEBUG)
    {
        uint32_t context_entry_connection_table_index;

        if (context_entry_ptr->fc_ucast_flow_context_entry.multicast_flag == 0)
        {
            __debug("%s, %u: connection_table_index %u, context_entry_ptr %px\n", __FUNCTION__, __LINE__, 
                nat_cache_entry_index, context_entry_ptr);
        }
        else
        {
            RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
            RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;

            context_cont_entry_ptr = &( context_cont_table_ptr->entry[ nat_cache_entry_index ] );

            RDD_FC_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_READ ( context_entry_connection_table_index, context_cont_entry_ptr );

            __debug("%s, %u: connection_table_index %u, context_entry_index %u, context_entry_ptr %px\n", __FUNCTION__, __LINE__, 
                context_entry_connection_table_index, nat_cache_entry_index, context_entry_ptr);
        }
    }
#endif

    return BDMF_ERR_OK;
}

/* f_rdd_ipproto_lookup_port_get() gets IP Proto (TCP, UDP, etc.) and source bridge port from the protocol fields */
static inline BL_LILAC_RDD_ERROR_DTE f_rdd_ipproto_lookup_port_get ( uint8_t    *xi_prot_ptr,
                                                                     uint8_t    *xo_lookup_port_ptr,
                                                                     uint8_t    *xo_lookup_tcp_pure_ack )
{
    uint8_t ipproto_idx;
    uint8_t ipproto;

    *xo_lookup_tcp_pure_ack = 0;
    *xo_lookup_port_ptr = (*xi_prot_ptr >> TUPLE_PROTO_LOOKUP_PORT_F_OFFSET) & TUPLE_PROTO_LOOKUP_PORT_F_MASK;
    ipproto_idx = (*xi_prot_ptr >> TUPLE_PROTO_PROTOCOL_F_OFFSET) & TUPLE_PROTO_PROTOCOL_F_MASK;

    switch (ipproto_idx)
    {
        case IPPROTO_IDX_TCP_ACK:
            *xo_lookup_tcp_pure_ack = 1;
            /* fall through */

        case IPPROTO_IDX_TCP:
            ipproto = IPPROTO_TCP;
            break;

        case IPPROTO_IDX_UDP:
            ipproto = IPPROTO_UDP;
            break;

        case IPPROTO_IDX_IPIP:
            ipproto = IPPROTO_IPIP;
            break;

        case IPPROTO_IDX_IPV6:
            ipproto = IPPROTO_IPV6;
            break;

        case IPPROTO_IDX_GRE:
            ipproto = IPPROTO_GRE;
            break;            
            
        default:
            ipproto = IPPROTO_UDP;
    }

    *xi_prot_ptr = ipproto;

    return ( BL_LILAC_RDD_OK );
}


/* f_rdd_prot_set() sets protocol field using IP Proto (TCP, UDP, etc.) and connection port */
static inline BL_LILAC_RDD_ERROR_DTE f_rdd_prot_set ( uint8_t    *xi_prot_ptr,
                                                      uint8_t    xi_lookup_port,
                                                      uint8_t    xi_tcp_pure_ack )
{
    uint8_t ipproto_idx;

    switch (*xi_prot_ptr)
    {
        case IPPROTO_TCP:
            ipproto_idx = (xi_tcp_pure_ack) ? IPPROTO_IDX_TCP_ACK : IPPROTO_IDX_TCP;
            break;

        case IPPROTO_UDP:
            ipproto_idx = IPPROTO_IDX_UDP;
            break;

        case IPPROTO_IPIP:
            ipproto_idx = IPPROTO_IDX_IPIP;
            break;

        case IPPROTO_IPV6:
            ipproto_idx = IPPROTO_IDX_IPV6;
            break;

        case IPPROTO_GRE:
            ipproto_idx = IPPROTO_IDX_GRE;
            break;            
            
        default:
            ipproto_idx = IPPROTO_IDX_UNDEF;
    }

    *xi_prot_ptr = (ipproto_idx << TUPLE_PROTO_PROTOCOL_F_OFFSET) | (xi_lookup_port & TUPLE_PROTO_LOOKUP_PORT_F_MASK);

    return ( BL_LILAC_RDD_OK );
}

static inline int f_rdd_nat_cache_lkp_entry_alloc ( uint32_t                  hash_index,
                                                    rdpa_ip_flow_key_t        *lookup_entry,
                                                    uint32_t                  ipv6_src_ip_crc,
                                                    uint32_t                  ipv6_dst_ip_crc,
                                                    uint32_t                  *tries_res )
{
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;
    uint32_t                  tries;
    uint32_t                  nat_cache_entry_index;
    uint32_t                  nat_cache_lkp_entry_valid;
    uint8_t                   nat_cache_lkp_entry_protocol;
    uint8_t                   nat_cache_lkp_entry_lookup_port;
    uint8_t                   nat_cache_lkp_entry_tcp_pure_ack;
    uint16_t                  nat_cache_lkp_entry_src_port;
    uint16_t                  nat_cache_lkp_entry_dst_port;
    bdmf_ip_t                 nat_cache_lkp_entry_src_ip;
    bdmf_ip_t                 nat_cache_lkp_entry_dst_ip;
    RDD_NAT_CACHE_TABLE_DTS   *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;

    for ( tries = 0; tries < RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE; tries++ )
    {
        nat_cache_entry_index = hash_index + tries;

        nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ nat_cache_entry_index ] );

        RDD_NAT_CACHE_LKP_ENTRY_VALID_READ ( nat_cache_lkp_entry_valid, nat_cache_lkp_entry_ptr );

        if ( !( nat_cache_lkp_entry_valid ) )
        {
            break;
        }
        /* XXX: Below comparision does not make sense if we are breaking above */
        /* if entry is valid, check if it matches entry being added */
        RDD_NAT_CACHE_LKP_ENTRY_PROTOCOL_READ ( nat_cache_lkp_entry_protocol, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_SRC_PORT_READ ( nat_cache_lkp_entry_src_port, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_DST_PORT_READ ( nat_cache_lkp_entry_dst_port, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_SRC_IP_READ ( nat_cache_lkp_entry_src_ip.addr.ipv4, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_DST_IP_READ ( nat_cache_lkp_entry_dst_ip.addr.ipv4, nat_cache_lkp_entry_ptr );

        f_rdd_ipproto_lookup_port_get ( &nat_cache_lkp_entry_protocol, &nat_cache_lkp_entry_lookup_port,
            &nat_cache_lkp_entry_tcp_pure_ack );

        if ( ( nat_cache_lkp_entry_protocol == lookup_entry->prot ) &&
             ( nat_cache_lkp_entry_lookup_port == lookup_entry->lookup_port ) &&
             ( nat_cache_lkp_entry_tcp_pure_ack == lookup_entry->tcp_pure_ack ) &&
             ( nat_cache_lkp_entry_src_port == lookup_entry->src_port ) &&
             ( nat_cache_lkp_entry_dst_port == lookup_entry->dst_port ) &&
             ( ( ( lookup_entry->dst_ip.family == bdmf_ip_family_ipv4 ) &&
                 ( nat_cache_lkp_entry_src_ip.addr.ipv4 == lookup_entry->src_ip.addr.ipv4 ) &&
                 ( nat_cache_lkp_entry_dst_ip.addr.ipv4 == lookup_entry->dst_ip.addr.ipv4 ) ) ||
               ( ( ( lookup_entry->dst_ip.family == bdmf_ip_family_ipv6 ) &&
                   ( nat_cache_lkp_entry_src_ip.addr.ipv4 == ipv6_src_ip_crc ) &&
                   ( nat_cache_lkp_entry_dst_ip.addr.ipv4 == ipv6_dst_ip_crc ) ) ) ) )
        {
            return BDMF_ERR_ALREADY;
        }
    }

    *tries_res = tries;
    return BDMF_ERR_OK;
}

static void rdd_connection_hash_function(uint32_t *hash_idx, uint8_t *connection_entry)
{
    *hash_idx = crcbitbybit(connection_entry, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS), 0, 0, RDD_CRC_TYPE_32);
    *hash_idx = (*hash_idx >> 16) ^ (*hash_idx & 0xffff);
}

int rdd_connection_entry_add ( rdd_ip_flow_t  *add_connection,
                               rdpa_traffic_dir                 direction )
{
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint8_t                      entry_bytes[ RDD_NAT_CACHE_LKP_ENTRY_SIZE ];
    uint32_t                     hash_index, tries = 0;
    uint32_t                     nat_cache_entry_index;
    uint32_t                     flow_entry_index;
    uint32_t                     ipv6_src_ip_crc;
    uint32_t                     ipv6_dst_ip_crc;
    int       bdmf_error;
    unsigned long                flags;
    int                          create_dup_key=0; /*NAT Cache errata workaround*/
    uint8_t                      nat_cache_lkp_entry_protocol;
    uint16_t                     any_src_port_flow_counter;
    RDD_ANY_SRC_PORT_FLOW_COUNTER_DTS *any_src_port_flow_counter_ptr;

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );

    nat_cache_lkp_entry_protocol = add_connection->lookup_entry->prot;
    f_rdd_prot_set ( &nat_cache_lkp_entry_protocol, add_connection->lookup_entry->lookup_port,
        add_connection->lookup_entry->tcp_pure_ack );

    ipv6_src_ip_crc = 0;
    ipv6_dst_ip_crc = 0;

    entry_bytes[ 0 ] = (1 << 7); /* valid bit */
    entry_bytes[ 1 ] = 0;
    entry_bytes[ 2 ] = 0;
    entry_bytes[ 3 ] = nat_cache_lkp_entry_protocol;
    entry_bytes[ 4 ] = ( add_connection->lookup_entry->src_port >> 8 ) & 0xFF;
    entry_bytes[ 5 ] = add_connection->lookup_entry->src_port & 0xFF;
    entry_bytes[ 6 ] = ( add_connection->lookup_entry->dst_port >> 8 ) & 0xFF;
    entry_bytes[ 7 ] = add_connection->lookup_entry->dst_port & 0xFF;

    if ( add_connection->lookup_entry->dst_ip.family == bdmf_ip_family_ipv4 )
    {
        entry_bytes[ 8 ] = ( add_connection->lookup_entry->src_ip.addr.ipv4 >> 24 ) & 0xFF;
        entry_bytes[ 9 ] = ( add_connection->lookup_entry->src_ip.addr.ipv4 >> 16 ) & 0xFF;
        entry_bytes[ 10 ] = ( add_connection->lookup_entry->src_ip.addr.ipv4 >> 8 ) & 0xFF;
        entry_bytes[ 11 ] = add_connection->lookup_entry->src_ip.addr.ipv4 & 0xFF;
        entry_bytes[ 12 ] = ( add_connection->lookup_entry->dst_ip.addr.ipv4 >> 24 ) & 0xFF;
        entry_bytes[ 13 ] = ( add_connection->lookup_entry->dst_ip.addr.ipv4 >> 16 ) & 0xFF;
        entry_bytes[ 14 ] = ( add_connection->lookup_entry->dst_ip.addr.ipv4 >> 8 ) & 0xFF;
        entry_bytes[ 15 ] = add_connection->lookup_entry->dst_ip.addr.ipv4 & 0xFF;
    }
    else
    {
        ipv6_src_ip_crc = crcbitbybit((uint8_t *)&add_connection->lookup_entry->src_ip.addr.ipv6.data,
                                             16, 0, 0xffffffff, RDD_CRC_TYPE_32);
        entry_bytes[ 8 ] = ( ipv6_src_ip_crc >> 24 ) & 0xFF;
        entry_bytes[ 9 ] = ( ipv6_src_ip_crc >> 16 ) & 0xFF;
        entry_bytes[ 10 ] = ( ipv6_src_ip_crc >> 8 ) & 0xFF;
        entry_bytes[ 11 ] = ( ipv6_src_ip_crc >> 0 ) & 0xFF;

        ipv6_dst_ip_crc = crcbitbybit((uint8_t *)&add_connection->lookup_entry->dst_ip.addr.ipv6.data,
                                             16, 0, 0xffffffff, RDD_CRC_TYPE_32);
        entry_bytes[ 12 ] = ( ipv6_dst_ip_crc >> 24 ) & 0xFF;
        entry_bytes[ 13 ] = ( ipv6_dst_ip_crc >> 16 ) & 0xFF;
        entry_bytes[ 14 ] = ( ipv6_dst_ip_crc >> 8 ) & 0xFF;
        entry_bytes[ 15 ] = ( ipv6_dst_ip_crc >> 0 ) & 0xFF;

        entry_bytes[ 2 ] = 1; /* key extend */
    }

    rdd_connection_hash_function(&hash_index, entry_bytes);

    bdmf_error = f_rdd_nat_cache_lkp_entry_alloc ( hash_index, add_connection->lookup_entry, ipv6_src_ip_crc, ipv6_dst_ip_crc, &tries );

    if ( bdmf_error != BDMF_ERR_OK )
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return ( bdmf_error );
    }

    if ( tries == RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE )
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return BDMF_ERR_IGNORE;
    }

    /*Wrap index at 64K - Part of NAT Cache workaround below*/
    nat_cache_entry_index = (hash_index + tries) & (RDD_NAT_CACHE_TABLE_SIZE - 1);

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ nat_cache_entry_index ] );

    if( add_connection->context_entry.fc_ucast_flow_context_entry.multicast_flag == 0 )
    {
        add_connection->context_entry.fc_ucast_flow_context_entry.connection_table_index = nat_cache_entry_index;
        add_connection->context_entry.fc_ucast_flow_context_entry.connection_direction = direction;
    }

#if defined(CC_RDD_ROUTER_DEBUG)
    rdd_flow_dump(&add_connection->context_entry, direction);
#endif

    bdmf_error = f_rdd_context_entry_add ( &add_connection->context_entry, nat_cache_entry_index, 0 /* is_mcast_mstr */, &flow_entry_index );
    if (bdmf_error != BDMF_ERR_OK)
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return BDMF_ERR_NORES;
    }

    if (add_connection->lookup_entry->lookup_port == BL_LILAC_RDD_ANY_BRIDGE_PORT)
    {
        any_src_port_flow_counter_ptr = ( RDD_ANY_SRC_PORT_FLOW_COUNTER_DTS * )( DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_ANY_SRC_PORT_FLOW_COUNTER_ADDRESS ); 

        MREAD_16 ( any_src_port_flow_counter_ptr, any_src_port_flow_counter );
        any_src_port_flow_counter++;
        MWRITE_16 ( any_src_port_flow_counter_ptr, any_src_port_flow_counter );

        any_src_port_flow_counter_ptr = ( RDD_ANY_SRC_PORT_FLOW_COUNTER_DTS * )( DEVICE_ADDRESS( RUNNER_PRIVATE_1_OFFSET ) + US_ANY_SRC_PORT_FLOW_COUNTER_ADDRESS ); 
   
        MREAD_16 ( any_src_port_flow_counter_ptr, any_src_port_flow_counter );
        any_src_port_flow_counter++;
        MWRITE_16 ( any_src_port_flow_counter_ptr, any_src_port_flow_counter );
    }

    do
    {
        if ( add_connection->lookup_entry->dst_ip.family == bdmf_ip_family_ipv4 )
        {
            RDD_NAT_CACHE_LKP_ENTRY_DST_IP_WRITE ( add_connection->lookup_entry->dst_ip.addr.ipv4, nat_cache_lkp_entry_ptr );
            RDD_NAT_CACHE_LKP_ENTRY_SRC_IP_WRITE ( add_connection->lookup_entry->src_ip.addr.ipv4, nat_cache_lkp_entry_ptr );
        }
        else
        {
            RDD_NAT_CACHE_LKP_ENTRY_DST_IP_WRITE ( ipv6_dst_ip_crc ,nat_cache_lkp_entry_ptr );
            RDD_NAT_CACHE_LKP_ENTRY_SRC_IP_WRITE ( ipv6_src_ip_crc ,nat_cache_lkp_entry_ptr );
        }
        RDD_NAT_CACHE_LKP_ENTRY_DST_PORT_WRITE ( add_connection->lookup_entry->dst_port, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_SRC_PORT_WRITE ( add_connection->lookup_entry->src_port, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_PROTOCOL_WRITE ( nat_cache_lkp_entry_protocol, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_KEY_EXTEND_WRITE ( add_connection->lookup_entry->dst_ip.family, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_VALID_WRITE ( 1/*On*/, nat_cache_lkp_entry_ptr );
     
        /* NAT cache workaround: the context table is wrap around at 64K while the key table is continuous */
        if (nat_cache_entry_index < RDD_NAT_CACHE_EXTENSION_TABLE_SIZE)
        {
            nat_cache_entry_index = RDD_NAT_CACHE_TABLE_SIZE + nat_cache_entry_index;
            nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &(nat_cache_table_ptr->entry[nat_cache_entry_index]);
            create_dup_key = 1;
        }
        else
        {
            nat_cache_entry_index = nat_cache_entry_index & (RDD_NAT_CACHE_TABLE_SIZE - 1);
            nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &(nat_cache_table_ptr->entry[nat_cache_entry_index]);
            create_dup_key = 0;
        }
    } while (create_dup_key);

    /* return the index of the entry in the table */
    add_connection->xo_entry_index = flow_entry_index;

    context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    context_cont_entry_ptr = &(context_cont_table_ptr->entry[ nat_cache_entry_index ] );
    RDD_CONTEXT_CONTINUATION_ENTRY_FLOW_INDEX_WRITE ( flow_entry_index, context_cont_entry_ptr );

#if defined(CC_RDD_ROUTER_DEBUG)
    {
        __debug("%s, %u: connection_table_index %u\n", __FUNCTION__, __LINE__, context_cont_entry_ptr->connection_table_index);
    }
#endif

    bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
    return BDMF_ERR_OK;
}


static int f_rdd_nat_cache_lkp_entry_lookup ( uint32_t                  hash_index,
                                              rdpa_ip_flow_key_t        *lookup_entry,
                                              uint32_t                  ipv6_src_ip_crc,
                                              uint32_t                  ipv6_dst_ip_crc,
                                              uint32_t                  *tries_res )
{
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;
    uint32_t                  tries;
    uint32_t                  nat_cache_entry_index;
    uint32_t                  nat_cache_lkp_entry_valid;
    uint8_t                   nat_cache_lkp_entry_protocol;
    uint8_t                   nat_cache_lkp_entry_lookup_port;
    uint8_t                   nat_cache_lkp_entry_tcp_pure_ack;
    uint16_t                  nat_cache_lkp_entry_src_port;
    uint16_t                  nat_cache_lkp_entry_dst_port;
    bdmf_ip_t                 nat_cache_lkp_entry_src_ip;
    bdmf_ip_t                 nat_cache_lkp_entry_dst_ip;
    RDD_NAT_CACHE_TABLE_DTS   *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;

    for ( tries = 0; tries < RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE; tries++ )
    {
        nat_cache_entry_index = hash_index + tries;

        nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ nat_cache_entry_index ] );

        RDD_NAT_CACHE_LKP_ENTRY_VALID_READ ( nat_cache_lkp_entry_valid, nat_cache_lkp_entry_ptr );

        if ( nat_cache_lkp_entry_valid )
        {
            RDD_NAT_CACHE_LKP_ENTRY_PROTOCOL_READ ( nat_cache_lkp_entry_protocol, nat_cache_lkp_entry_ptr );
            RDD_NAT_CACHE_LKP_ENTRY_SRC_PORT_READ ( nat_cache_lkp_entry_src_port, nat_cache_lkp_entry_ptr );
            RDD_NAT_CACHE_LKP_ENTRY_DST_PORT_READ ( nat_cache_lkp_entry_dst_port, nat_cache_lkp_entry_ptr );
            RDD_NAT_CACHE_LKP_ENTRY_SRC_IP_READ ( nat_cache_lkp_entry_src_ip.addr.ipv4, nat_cache_lkp_entry_ptr );
            RDD_NAT_CACHE_LKP_ENTRY_DST_IP_READ ( nat_cache_lkp_entry_dst_ip.addr.ipv4, nat_cache_lkp_entry_ptr );

            f_rdd_ipproto_lookup_port_get ( &nat_cache_lkp_entry_protocol, &nat_cache_lkp_entry_lookup_port,
                &nat_cache_lkp_entry_tcp_pure_ack );

            if ( ( nat_cache_lkp_entry_protocol == lookup_entry->prot ) &&
                 ( nat_cache_lkp_entry_tcp_pure_ack == lookup_entry->tcp_pure_ack ) &&
                 ( nat_cache_lkp_entry_lookup_port == lookup_entry->lookup_port ) &&
                 ( nat_cache_lkp_entry_src_port == lookup_entry->src_port ) &&
                 ( nat_cache_lkp_entry_dst_port == lookup_entry->dst_port ) &&
                 ( ( ( lookup_entry->dst_ip.family == bdmf_ip_family_ipv4 ) &&
                     ( nat_cache_lkp_entry_src_ip.addr.ipv4 == lookup_entry->src_ip.addr.ipv4 ) &&
                     ( nat_cache_lkp_entry_dst_ip.addr.ipv4 == lookup_entry->dst_ip.addr.ipv4 ) ) ||
                   ( ( ( lookup_entry->dst_ip.family == bdmf_ip_family_ipv6 ) &&
                       ( nat_cache_lkp_entry_src_ip.addr.ipv4 == ipv6_src_ip_crc ) &&
                       ( nat_cache_lkp_entry_dst_ip.addr.ipv4 == ipv6_dst_ip_crc ) ) ) ) )
            {
                break;
            }
        }
    }

    *tries_res = tries;

    return BDMF_ERR_OK;
}


int rdd_connection_entry_delete ( bdmf_index  flow_entry_index )
{
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr, nat_cache_lookup_entry;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint32_t                     nat_cache_lkp_entry_valid;
    uint32_t                     nat_cache_lkp_entry_is_multicast;
    uint32_t                     context_cont_flow_index;
    uint32_t                     entry_index = RDD_NATC_CONTEXT_TABLE_SIZE;
    uint32_t                     context_entry_connection_table_index;
    unsigned long                flags;
    bdmf_error_t rc = BDMF_ERR_OK;
    uint8_t                      connection_entry_protocol;
    uint8_t                      connection_entry_tcp_pure_ack;
    uint8_t                      connection_entry_lookup_port;
    uint16_t                     any_src_port_flow_counter;
    uint32_t                     connection_direction;
    RDD_ANY_SRC_PORT_FLOW_COUNTER_DTS *any_src_port_flow_counter_ptr;

    if ((g_free_flow_entries[flow_entry_index] & RDD_FLOW_ENTRY_VALID) == RDD_FLOW_ENTRY_VALID)
    {
        entry_index = g_free_flow_entries[flow_entry_index] & ~RDD_FLOW_ENTRY_VALID;
    }
    else
    {
        return BDMF_ERR_PARM;
    }

    if ( entry_index >= RDD_NATC_CONTEXT_TABLE_SIZE )
    {
        return BDMF_ERR_PARM;
    }

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );

    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ entry_index ] );

    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_READ ( context_entry_connection_table_index, context_cont_entry_ptr );
    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_DIRECTION_READ ( connection_direction, context_cont_entry_ptr );

    /* NAT cache workaround: the context table is wrap around at 64K while the key table is continuous */
    if (entry_index < RDD_NAT_CACHE_EXTENSION_TABLE_SIZE) {
        nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &(nat_cache_table_ptr->entry[RDD_NAT_CACHE_TABLE_SIZE + entry_index]);
        memset(nat_cache_lkp_entry_ptr, 0, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));
    }

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ context_entry_connection_table_index ] );

    RDD_NAT_CACHE_LKP_ENTRY_VALID_READ ( nat_cache_lkp_entry_valid, nat_cache_lkp_entry_ptr );
    RDD_CONTEXT_CONTINUATION_ENTRY_FLOW_INDEX_READ ( context_cont_flow_index, context_cont_entry_ptr );

    if ( nat_cache_lkp_entry_valid && ( flow_entry_index == context_cont_flow_index ) )
    {
        RDD_NAT_CACHE_MCAST_LKP_ENTRY_IS_MULTICAST_READ ( nat_cache_lkp_entry_is_multicast, nat_cache_lkp_entry_ptr );
        RDD_NAT_CACHE_LKP_ENTRY_PROTOCOL_READ ( connection_entry_protocol, nat_cache_lkp_entry_ptr );

        f_rdd_ipproto_lookup_port_get ( &connection_entry_protocol, &connection_entry_lookup_port,
            &connection_entry_tcp_pure_ack );

        if (connection_entry_lookup_port == BL_LILAC_RDD_ANY_BRIDGE_PORT && !nat_cache_lkp_entry_is_multicast)
        {
            any_src_port_flow_counter_ptr = ( RDD_ANY_SRC_PORT_FLOW_COUNTER_DTS * )( DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_ANY_SRC_PORT_FLOW_COUNTER_ADDRESS ); 

            MREAD_16 ( any_src_port_flow_counter_ptr, any_src_port_flow_counter );
            any_src_port_flow_counter--;
            MWRITE_16 ( any_src_port_flow_counter_ptr, any_src_port_flow_counter );

            any_src_port_flow_counter_ptr = ( RDD_ANY_SRC_PORT_FLOW_COUNTER_DTS * )( DEVICE_ADDRESS( RUNNER_PRIVATE_1_OFFSET ) + US_ANY_SRC_PORT_FLOW_COUNTER_ADDRESS ); 

            MREAD_16 ( any_src_port_flow_counter_ptr, any_src_port_flow_counter );
            any_src_port_flow_counter--;
            MWRITE_16 ( any_src_port_flow_counter_ptr, any_src_port_flow_counter );
        }

        /* Remove flow context from DDR */
        memcpy(&nat_cache_lookup_entry, nat_cache_lkp_entry_ptr, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));

        memset(nat_cache_lkp_entry_ptr, 0, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));

#if !defined(FIRMWARE_INIT)
        wmb();

        /* Delete the entry in the NAT cache internal memory */
        rdd_nat_cache_submit_command(natc_del, (uint32_t *)&nat_cache_lookup_entry, NULL, NULL);
#endif

        /* Delete continuation flow cache index from cam_lkp tbl */
        f_rdd_cpu_tx_send_message( LILAC_RDD_CPU_TX_MESSAGE_INVALIDATE_CONTEXT_INDEX_CACHE_ENTRY,
                           (connection_direction == rdpa_dir_ds) ?
                           PICO_RUNNER_A : FAST_RUNNER_B,
                           (connection_direction == rdpa_dir_ds) ?
                           RUNNER_PRIVATE_0_OFFSET : RUNNER_PRIVATE_1_OFFSET,
                           context_entry_connection_table_index, 0, 0, BL_LILAC_RDD_WAIT );

        f_rdd_free_context_entry ( entry_index );

        if (rc == BDMF_ERR_OK)
        {
            g_free_flow_entries[flow_entry_index] = 0;
            g_free_flow_entries_number++;
        }
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );

        return rc;
    }
    else
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return BDMF_ERR_INTERNAL;
    }
}


int rdd_connection_entry_search ( rdd_ip_flow_t  *get_connection,
                                  rdpa_traffic_dir       direction,
                                  bdmf_index             *entry_index )
{
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint8_t                   entry_bytes[ RDD_NAT_CACHE_LKP_ENTRY_SIZE ];
    uint32_t                  hash_index, tries = 0;
    uint32_t                  nat_cache_entry_index;
    uint16_t                  flow_entry_index;
    uint32_t                  ipv6_src_ip_crc;
    uint32_t                  ipv6_dst_ip_crc;
    unsigned long             flags;
    uint8_t                   nat_cache_lkp_entry_protocol;

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );

    nat_cache_lkp_entry_protocol = get_connection->lookup_entry->prot;
    f_rdd_prot_set ( &nat_cache_lkp_entry_protocol, get_connection->lookup_entry->lookup_port,
        get_connection->lookup_entry->tcp_pure_ack );

    ipv6_src_ip_crc = 0;
    ipv6_dst_ip_crc = 0;

    entry_bytes[ 0 ] = (1 << 7); /* valid bit */
    entry_bytes[ 1 ] = 0;
    entry_bytes[ 2 ] = 0;
    entry_bytes[ 3 ] = nat_cache_lkp_entry_protocol;
    entry_bytes[ 4 ] = ( get_connection->lookup_entry->src_port >> 8 ) & 0xFF;
    entry_bytes[ 5 ] = get_connection->lookup_entry->src_port & 0xFF;
    entry_bytes[ 6 ] = ( get_connection->lookup_entry->dst_port >> 8 ) & 0xFF;
    entry_bytes[ 7 ] = get_connection->lookup_entry->dst_port & 0xFF;

    if ( get_connection->lookup_entry->dst_ip.family == bdmf_ip_family_ipv4 )
    {
        entry_bytes[ 8 ] = ( get_connection->lookup_entry->src_ip.addr.ipv4 >> 24 ) & 0xFF;
        entry_bytes[ 9 ] = ( get_connection->lookup_entry->src_ip.addr.ipv4 >> 16 ) & 0xFF;
        entry_bytes[ 10 ] = ( get_connection->lookup_entry->src_ip.addr.ipv4 >> 8 ) & 0xFF;
        entry_bytes[ 11 ] = get_connection->lookup_entry->src_ip.addr.ipv4 & 0xFF;
        entry_bytes[ 12 ] = ( get_connection->lookup_entry->dst_ip.addr.ipv4 >> 24 ) & 0xFF;
        entry_bytes[ 13 ] = ( get_connection->lookup_entry->dst_ip.addr.ipv4 >> 16 ) & 0xFF;
        entry_bytes[ 14 ] = ( get_connection->lookup_entry->dst_ip.addr.ipv4 >> 8 ) & 0xFF;
        entry_bytes[ 15 ] = get_connection->lookup_entry->dst_ip.addr.ipv4 & 0xFF;
    }
    else
    {
        ipv6_src_ip_crc = crcbitbybit((uint8_t *)&get_connection->lookup_entry->src_ip.addr.ipv6.data,
                                             16, 0, 0xffffffff, RDD_CRC_TYPE_32);
        entry_bytes[ 8 ] = ( ipv6_src_ip_crc >> 24 ) & 0xFF;
        entry_bytes[ 9 ] = ( ipv6_src_ip_crc >> 16 ) & 0xFF;
        entry_bytes[ 10 ] = ( ipv6_src_ip_crc >> 8 ) & 0xFF;
        entry_bytes[ 11 ] = ( ipv6_src_ip_crc >> 0 ) & 0xFF;

        ipv6_dst_ip_crc = crcbitbybit((uint8_t *)&get_connection->lookup_entry->dst_ip.addr.ipv6.data,
                                             16, 0, 0xffffffff, RDD_CRC_TYPE_32);
        entry_bytes[ 12 ] = ( ipv6_dst_ip_crc >> 24 ) & 0xFF;
        entry_bytes[ 13 ] = ( ipv6_dst_ip_crc >> 16 ) & 0xFF;
        entry_bytes[ 14 ] = ( ipv6_dst_ip_crc >> 8 ) & 0xFF;
        entry_bytes[ 15 ] = ( ipv6_dst_ip_crc >> 0 ) & 0xFF;
    }

    rdd_connection_hash_function(&hash_index, entry_bytes);

    f_rdd_nat_cache_lkp_entry_lookup ( hash_index, get_connection->lookup_entry, ipv6_src_ip_crc, ipv6_dst_ip_crc, &tries );

    if ( tries == RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE )
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return BDMF_ERR_NOENT;
    }

    nat_cache_entry_index = hash_index + tries;

    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ nat_cache_entry_index ] );
    RDD_CONTEXT_CONTINUATION_ENTRY_FLOW_INDEX_READ ( flow_entry_index, context_cont_entry_ptr );

    *entry_index = flow_entry_index;

    bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
    return BDMF_ERR_OK;
}

int rdd_connection_entry_get ( rdpa_traffic_dir    direction,
                               uint32_t            entry_index,
                               rdpa_ip_flow_key_t  *nat_cache_lkp_entry,
                               bdmf_index          *flow_entry_index )
{
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;
    uint32_t                     nat_cache_lkp_entry_valid;
    uint32_t flow_index;

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ entry_index ] );

    RDD_NAT_CACHE_LKP_ENTRY_VALID_READ ( nat_cache_lkp_entry_valid, nat_cache_lkp_entry_ptr );

    if ( !nat_cache_lkp_entry_valid )
    {
        return BDMF_ERR_NOENT;
    }

    {
        uint32_t nat_cache_lkp_entry_is_multicast;

        RDD_NAT_CACHE_MCAST_LKP_ENTRY_IS_MULTICAST_READ ( nat_cache_lkp_entry_is_multicast, nat_cache_lkp_entry_ptr );

        if ( nat_cache_lkp_entry_is_multicast )
        {
            return BDMF_ERR_NOENT;
        }
    }

    RDD_NAT_CACHE_LKP_ENTRY_PROTOCOL_READ ( nat_cache_lkp_entry->prot, nat_cache_lkp_entry_ptr );
    RDD_NAT_CACHE_LKP_ENTRY_SRC_PORT_READ ( nat_cache_lkp_entry->src_port, nat_cache_lkp_entry_ptr );
    RDD_NAT_CACHE_LKP_ENTRY_DST_PORT_READ ( nat_cache_lkp_entry->dst_port, nat_cache_lkp_entry_ptr );
    RDD_NAT_CACHE_LKP_ENTRY_SRC_IP_READ ( nat_cache_lkp_entry->src_ip.addr.ipv4, nat_cache_lkp_entry_ptr );
    RDD_NAT_CACHE_LKP_ENTRY_DST_IP_READ ( nat_cache_lkp_entry->dst_ip.addr.ipv4, nat_cache_lkp_entry_ptr );
    RDD_NAT_CACHE_LKP_ENTRY_KEY_EXTEND_READ ( nat_cache_lkp_entry->dst_ip.family ,nat_cache_lkp_entry_ptr );
    nat_cache_lkp_entry->src_ip.family = nat_cache_lkp_entry->dst_ip.family;

    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ entry_index ] );
    RDD_CONTEXT_CONTINUATION_ENTRY_FLOW_INDEX_READ ( flow_index, context_cont_entry_ptr );
    *flow_entry_index = flow_index;

    f_rdd_ipproto_lookup_port_get ( &nat_cache_lkp_entry->prot, &nat_cache_lkp_entry->lookup_port,
        &nat_cache_lkp_entry->tcp_pure_ack );

    return BDMF_ERR_OK;
}

int rdd_context_entry_get ( bdmf_index                  flow_entry_index,
                            rdd_fc_context_t            *context_entry )
{
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NATC_CONTEXT_TABLE_DTS   *context_table_ptr = ( RDD_NATC_CONTEXT_TABLE_DTS * )ContextTableBase;
    RDD_NATC_CONTEXT_ENTRY_UNION_DTS  *context_entry_ptr;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint32_t                     valid;
    uint32_t                     multicast_flag;
    uint32_t                     connection_direction;
    int                          continuation_flag;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr, nat_cache_lookup_entry;
    uint32_t                     connection_table_index;
    uint32_t                     entry_index = RDD_NATC_CONTEXT_TABLE_SIZE;

    if ((g_free_flow_entries[flow_entry_index] & RDD_FLOW_ENTRY_VALID) == RDD_FLOW_ENTRY_VALID)
    {
        entry_index = g_free_flow_entries[flow_entry_index] & ~RDD_FLOW_ENTRY_VALID;
    }
    else
    {
        return BDMF_ERR_PARM;
    }

    if ( entry_index >= RDD_NATC_CONTEXT_TABLE_SIZE )
    {
        return ( BDMF_ERR_PARM );
    }

    context_entry_ptr = &(context_table_ptr->entry[ entry_index ] );
    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ entry_index ] );

    RDD_CONTEXT_CONTINUATION_ENTRY_VALID_READ (valid, context_cont_entry_ptr );

    if(!valid)
    {
        return BDMF_ERR_NOENT;
    }

    RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_MULTICAST_FLAG_READ( multicast_flag, context_entry_ptr );
    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_DIRECTION_READ ( connection_direction, context_cont_entry_ptr );
    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_READ ( connection_table_index, context_cont_entry_ptr );

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ connection_table_index ] );
    RDD_NAT_CACHE_LKP_ENTRY_VALID_READ ( valid, nat_cache_lkp_entry_ptr );

    {
        uint32_t context_index;
        uint32_t i;


        if ( valid )
        {
            RDD_CONTEXT_CONTINUATION_ENTRY_FLOW_INDEX_READ ( context_index, context_cont_entry_ptr );
            if ( flow_entry_index == context_index )
            {
                /* look for the entry in the NAT cache internal memory, if found then statistics is also there */
                int rc = BDMF_ERR_OK;
                uint32_t hit_count, byte_count;
#if !defined(FIRMWARE_INIT)
                unsigned long flags;
#endif

                memcpy(&nat_cache_lookup_entry, nat_cache_lkp_entry_ptr, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));
#if !defined(FIRMWARE_INIT)
                bdmf_fastlock_lock_irq ( &int_lock_irq, flags );
                rc = rdd_nat_cache_submit_command(natc_lookup, (uint32_t *)&nat_cache_lookup_entry, &hit_count, &byte_count);
                bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
#else
                hit_count = 0;
                byte_count = 0;
#endif
                if (rc == BDMF_ERR_OK)
                {
                    context_entry->fc_ucast_flow_context_entry.flow_hits = hit_count;
                    context_entry->fc_ucast_flow_context_entry.flow_bytes = byte_count;
                }
                else
                {
                    RDD_FC_UCAST_FLOW_CONTEXT_ENTRY_FLOW_HITS_READ( context_entry->fc_ucast_flow_context_entry.flow_hits, context_entry_ptr );
                    RDD_FC_UCAST_FLOW_CONTEXT_ENTRY_FLOW_BYTES_READ( context_entry->fc_ucast_flow_context_entry.flow_bytes, context_entry_ptr );
                }

                if ( multicast_flag )
                {
                    uint32_t client_index;
                    RDD_NAT_CACHE_MCAST_LKP_ENTRY_CLIENT_INDEX_READ( client_index, nat_cache_lkp_entry_ptr);
                    /* Client flow shares the same ucast flow context but Master flow context is different */
                    if ( client_index == 0 )
                    {
                        f_rdd_mcast_master_context_entry_read(context_entry_ptr, context_cont_entry_ptr, context_entry);
                        return ( BL_LILAC_RDD_OK );
                    }
                }

                context_entry->fc_ucast_flow_context_entry.multicast_flag = multicast_flag;
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_ROUTED_READ( context_entry->fc_ucast_flow_context_entry.is_routed, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_L2_ACCEL_READ( context_entry->fc_ucast_flow_context_entry.is_l2_accel, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_WRED_HIGH_PRIO_READ( context_entry->fc_ucast_flow_context_entry.is_wred_high_prio, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_INGQOS_HIGH_PRIO_READ( context_entry->fc_ucast_flow_context_entry.is_ingqos_high_prio, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_MAPT_US_READ( context_entry->fc_ucast_flow_context_entry.is_mapt_us, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_DF_READ( context_entry->fc_ucast_flow_context_entry.is_df, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_EGRESS_PHY_READ( context_entry->fc_ucast_flow_context_entry.egress_phy, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_MTU_READ( context_entry->fc_ucast_flow_context_entry.mtu, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_TOS_READ( context_entry->fc_ucast_flow_context_entry.tos, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_SERVICE_QUEUE_ID_READ( context_entry->fc_ucast_flow_context_entry.service_queue_id, context_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_UNICAST_WFD_ANY_READ(context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_any, context_entry_ptr);
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_DROP_READ(context_entry->fc_ucast_flow_context_entry.drop, context_entry_ptr);
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_PRIORITY_READ(context_entry->fc_ucast_flow_context_entry.priority, context_entry_ptr);
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_WFD_PRIO_READ(context_entry->fc_ucast_flow_context_entry.wfd_prio, context_entry_ptr);
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_WFD_IDX_READ(context_entry->fc_ucast_flow_context_entry.wfd_idx, context_entry_ptr);
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_PATHSTAT_IDX_READ(context_entry->fc_ucast_flow_context_entry.pathstat_idx, context_entry_ptr);
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_HIT_TRAP_READ(context_entry->fc_ucast_flow_context_entry.is_hit_trap, context_entry_ptr);
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_CPU_REASON_READ(context_entry->fc_ucast_flow_context_entry.cpu_reason, context_entry_ptr);
                RDD_CONTEXT_CONTINUATION_ENTRY_IS_UNICAST_WFD_NIC_READ(context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_nic, context_cont_entry_ptr);

                if (context_entry->fc_ucast_flow_context_entry.egress_phy == rdd_egress_phy_wlan)
                {
                    if (context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_any)
                    {
                        RDD_FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY_IS_MCAST_READ(context_entry->fc_ucast_flow_context_wfd_nic_entry.is_mcast, context_entry_ptr);
                        if (context_entry->fc_ucast_flow_context_entry.is_unicast_wfd_nic)
                        {
                            RDD_FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY_CHAIN_IDX_READ(context_entry->fc_ucast_flow_context_wfd_nic_entry.chain_idx, context_entry_ptr);
                        }
                        else
                        {
                            RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY_WIFI_SSID_READ(context_entry->fc_ucast_flow_context_wfd_dhd_entry.wifi_ssid, context_entry_ptr);
                            RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY_FLOW_RING_ID_READ(context_entry->fc_ucast_flow_context_wfd_dhd_entry.flow_ring_id, context_entry_ptr);
                        }
                    }
#if defined(CONFIG_DHD_RUNNER)
                    else
                    {
                        RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_RADIO_IDX_READ(context_entry->fc_ucast_flow_context_rnr_dhd_entry.radio_idx, context_entry_ptr);
                        RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_WIFI_SSID_READ(context_entry->fc_ucast_flow_context_rnr_dhd_entry.wifi_ssid, context_entry_ptr);
                        RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_FLOW_RING_ID_READ(context_entry->fc_ucast_flow_context_rnr_dhd_entry.flow_ring_id, context_entry_ptr);
                    }
#endif
                }
                else
                {
                    RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_EGRESS_PORT_READ(context_entry->fc_ucast_flow_context_eth_xtm_entry.egress_port, context_entry_ptr);
                    RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_TRAFFIC_CLASS_READ(context_entry->fc_ucast_flow_context_eth_xtm_entry.traffic_class, context_entry_ptr);
                    RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_RATE_CONTROLLER_READ(context_entry->fc_ucast_flow_context_eth_xtm_entry.rate_controller, context_entry_ptr);
                }

                context_entry->fc_ucast_flow_context_entry.connection_direction = connection_direction;
                context_entry->fc_ucast_flow_context_entry.connection_table_index = connection_table_index;

                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_CONTEXT_CONTINUATION_FLAG_READ ( continuation_flag, context_entry_ptr );
                if (continuation_flag)
                {
                    context_entry->fc_ucast_flow_context_entry.command_list_length_32 = RDD_FC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER / 4;

                    for ( i = 0; i < RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER; i++ )
                    {
                        RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_READ ( context_entry->fc_ucast_flow_context_entry.command_list[ i ], context_entry_ptr, i );
                    }

                    for ( i = 0; i < RDD_CONTEXT_CONTINUATION_ENTRY_COMMAND_LIST_NUMBER; i++ )
                    {
                        uint32_t cmd_list_idx = i + RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER; 
                        RDD_CONTEXT_CONTINUATION_ENTRY_COMMAND_LIST_READ ( context_entry->fc_ucast_flow_context_entry.command_list[cmd_list_idx], context_cont_entry_ptr, i );
                    }
                }
                else
                {
                    context_entry->fc_ucast_flow_context_entry.command_list_length_32 = (RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER + 3) / 4;
                    for ( i = 0; i < RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_NUMBER+4; i++ )
                    {
                        RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_COMMAND_LIST_READ ( context_entry->fc_ucast_flow_context_entry.command_list[ i ], context_entry_ptr, i );
                    }
                }

                RDD_CONTEXT_CONTINUATION_ENTRY_VALID_READ (context_entry->fc_ucast_flow_context_entry.valid, context_cont_entry_ptr );
                RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IP_ADDRESSES_TABLE_INDEX_READ( context_entry->fc_ucast_flow_context_entry.ip_addresses_table_index, context_entry_ptr );
            }
            else
            {
                return BDMF_ERR_NOENT;
            }
        }
        else
        {
            return BDMF_ERR_NOENT;
        }
    }
    return BDMF_ERR_OK;
}

int rdd_context_entry_flwstat_get ( bdmf_index                  flow_entry_index,
                                    rdd_fc_context_t            *context_entry )
{
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NATC_CONTEXT_TABLE_DTS   *context_table_ptr = ( RDD_NATC_CONTEXT_TABLE_DTS * )ContextTableBase;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    RDD_NATC_CONTEXT_ENTRY_UNION_DTS  *context_entry_ptr;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr, nat_cache_lookup_entry;
    uint32_t                     entry_index = RDD_NATC_CONTEXT_TABLE_SIZE;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint32_t                     connection_table_index;
    /* look for the entry in the NAT cache internal memory, if found then statistics is also there */
    int rc = BDMF_ERR_OK;
    uint32_t hit_count, byte_count;
    uint32_t valid;
    uint32_t multicast_flag;
#if !defined(FIRMWARE_INIT)
    unsigned long flags;
#endif

    if ((g_free_flow_entries[flow_entry_index] & RDD_FLOW_ENTRY_VALID) == RDD_FLOW_ENTRY_VALID)
    {
        entry_index = g_free_flow_entries[flow_entry_index] & ~RDD_FLOW_ENTRY_VALID;
    }
    else
    {
        return BDMF_ERR_PARM;
    }

    if ( entry_index >= RDD_NATC_CONTEXT_TABLE_SIZE )
    {
        return ( BDMF_ERR_PARM );
    }

    context_entry_ptr = &(context_table_ptr->entry[ entry_index ] );
    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ entry_index ] );

    RDD_CONTEXT_CONTINUATION_ENTRY_VALID_READ (valid, context_cont_entry_ptr );

    if(!valid)
    {
        return BDMF_ERR_NOENT;
    }
    RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_MULTICAST_FLAG_READ(multicast_flag, context_entry_ptr );
    RDD_FC_NATC_UCAST_FLOW_CONTEXT_ENTRY_IS_L2_ACCEL_READ( context_entry->fc_ucast_flow_context_entry.is_l2_accel, context_entry_ptr );

    context_entry->fc_ucast_flow_context_entry.multicast_flag = multicast_flag;
    context_entry->fc_mcast_flow_context_entry.multicast_flag = multicast_flag;
    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_READ ( connection_table_index, context_cont_entry_ptr );

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ connection_table_index ] );

    memcpy(&nat_cache_lookup_entry, nat_cache_lkp_entry_ptr, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));
#if !defined(FIRMWARE_INIT)
    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );
    rc = rdd_nat_cache_submit_command(natc_lookup, (uint32_t *)&nat_cache_lookup_entry, &hit_count, &byte_count);
    bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
#else
    hit_count = 0;
    byte_count = 0;
#endif
    if (rc == BDMF_ERR_OK)
    {
        context_entry->fc_ucast_flow_context_entry.flow_hits = hit_count;
        context_entry->fc_ucast_flow_context_entry.flow_bytes = byte_count;
    }
    else
    {
        RDD_FC_UCAST_FLOW_CONTEXT_ENTRY_FLOW_HITS_READ( context_entry->fc_ucast_flow_context_entry.flow_hits, context_entry_ptr );
        RDD_FC_UCAST_FLOW_CONTEXT_ENTRY_FLOW_BYTES_READ( context_entry->fc_ucast_flow_context_entry.flow_bytes, context_entry_ptr );
    }
    return BDMF_ERR_OK;
}

int rdd_context_entry_modify ( rdd_fc_context_t *context_entry,
                               bdmf_index       flow_entry_index )
{
    uint32_t entry_index;
    uint32_t is_mcast_mstr = 0;
    unsigned long                flags;

    if ((g_free_flow_entries[flow_entry_index] & RDD_FLOW_ENTRY_VALID) == RDD_FLOW_ENTRY_VALID)
    {
        entry_index = g_free_flow_entries[flow_entry_index] & ~RDD_FLOW_ENTRY_VALID;
    }
    else
    {
        return BDMF_ERR_PARM;
    }

    if ( entry_index >= RDD_NATC_CONTEXT_TABLE_SIZE )
    {
        return BDMF_ERR_PARM;
    }

    if ( _rdd_is_mcast_master_entry(flow_entry_index) )
    {
        is_mcast_mstr = 1;
    }

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );
    context_entry->fc_mcast_flow_context_entry.valid = 1;
    f_rdd_context_entry_write ( context_entry, entry_index, is_mcast_mstr, 0 );
    bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );

#if !defined(FIRMWARE_INIT)
    f_rdd_nat_cache_entry_flush (context_entry, flow_entry_index);

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );
    f_rdd_cpu_tx_send_message( LILAC_RDD_CPU_TX_MESSAGE_INVALIDATE_CONTEXT_INDEX_CACHE_ENTRY,
                               (context_entry->fc_ucast_flow_context_entry.connection_direction == rdpa_dir_ds) ?
                               PICO_RUNNER_A : FAST_RUNNER_B,
                               (context_entry->fc_ucast_flow_context_entry.connection_direction == rdpa_dir_ds) ?
                               RUNNER_PRIVATE_0_OFFSET : RUNNER_PRIVATE_1_OFFSET,
                               flow_entry_index, 0, 0, BL_LILAC_RDD_WAIT );
    bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
#endif
    return BDMF_ERR_OK;
}

int rdd_connections_number_get ( uint32_t  *connections_number )
{
    *connections_number = RDD_FLOW_ENTRIES_SIZE - g_free_flow_entries_number;

    return BDMF_ERR_OK;
}


int rdd_clear_connection_table ( void )
{
    RDD_NAT_CACHE_TABLE_DTS   *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr, nat_cache_lookup_entry;
    uint16_t                  entry_index;
    unsigned long             flags;
    bdmf_error_t rc = BDMF_ERR_OK;

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );

    for ( entry_index = 0; entry_index < RDD_NAT_CACHE_TABLE_SIZE; entry_index++ )
    {
        nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ entry_index ] );

        if ( nat_cache_lkp_entry_ptr->valid )
        {
            f_rdd_free_context_entry ( entry_index );
        }

        memcpy(&nat_cache_lookup_entry, nat_cache_lkp_entry_ptr, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));

        memset(nat_cache_lkp_entry_ptr, 0, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));

#if !defined(FIRMWARE_INIT)
        /* look for the entry in the NAT cache internal memory if its there delete it */
        rc = rdd_nat_cache_submit_command(natc_lookup, (uint32_t *)&nat_cache_lookup_entry, NULL, NULL);

        if (rc == BDMF_ERR_OK)
            rc = rdd_nat_cache_submit_command(natc_del, (uint32_t *)&nat_cache_lookup_entry, NULL, NULL);

        if (rc != BDMF_ERR_OK)
        break;
#endif
    }

    bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
    return rc;
}

int rdd_3_tupples_connection_mode_config ( bdmf_boolean  tri_tuple_mode )
{
    return BDMF_ERR_OK;
}

void rdd_full_flow_cache_acceleration_config ( rdd_full_fc_acceleration_mode  mode,
                                               rdpa_traffic_dir               direction,
                                               bdmf_boolean                   enable )
{
}

void f_rdd_full_flow_cache_config ( bdmf_boolean  control )
{
}

int rdd_ipv6_ecn_remark ( uint32_t  control )
{
    return BDMF_ERR_OK;
}

int rdd_fc_flow_ip_addresses_add ( RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS  *ip_addresses_entry,
                                   bdmf_index                          *entry_index,
                                   uint16_t                            *entry_sram_address )
{
    RDD_FC_FLOW_IP_ADDRESSES_TABLE_DTS *fc_flow_ip_addresses_table_ptr;
    RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS *entry, curr, available;
    uint8_t                          *addr;
    uint32_t                         i, j;
    int           bdmf_error = BDMF_ERR_NORES;

    *entry_index = *entry_sram_address = ip_addresses_entry->reference_count = 0;

    fc_flow_ip_addresses_table_ptr = ( RDD_FC_FLOW_IP_ADDRESSES_TABLE_DTS * )(DEVICE_ADDRESS( RUNNER_COMMON_1_OFFSET ) + FC_FLOW_IP_ADDRESSES_TABLE_ADDRESS - sizeof ( RUNNER_COMMON ));

    for( i = 0; i < RDD_FC_FLOW_IP_ADDRESSES_TABLE_SIZE; i++ )
    {
        entry = fc_flow_ip_addresses_table_ptr->entry + i;

        for ( j = 0, addr = curr.sa_da_addresses; j < RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_NUMBER; j++, addr++ )
            RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_READ(*addr, entry, j);

        if( !memcmp(curr.sa_da_addresses, ip_addresses_entry->sa_da_addresses, sizeof(curr.sa_da_addresses)) )
        {
            /* Entry is already in the table, update the reference count and return the entry index and address. */
            RDD_FC_FLOW_IP_ADDRESSES_ENTRY_REFERENCE_COUNT_READ( ip_addresses_entry->reference_count, entry);
            ip_addresses_entry->reference_count++;
            RDD_FC_FLOW_IP_ADDRESSES_ENTRY_REFERENCE_COUNT_WRITE( ip_addresses_entry->reference_count, entry);

            *entry_index = i;
            *entry_sram_address = FC_FLOW_IP_ADDRESSES_TABLE_ADDRESS + (i * sizeof(RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS));
            bdmf_error = BDMF_ERR_OK;
            break;
        }
    }

    if( bdmf_error != BDMF_ERR_OK )
    {
        memset((uint8_t *) &available, 0x00, sizeof(RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS));

        for( i = 0; i < RDD_FC_FLOW_IP_ADDRESSES_TABLE_SIZE; i++ )
        {
            entry = fc_flow_ip_addresses_table_ptr->entry + i;

            for ( j = 0, addr = curr.sa_da_addresses; j < RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_NUMBER; j++, addr++ )
                RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_READ(*addr, entry, j);

            if( !memcmp(curr.sa_da_addresses, available.sa_da_addresses, sizeof(curr.sa_da_addresses)) )
            {
                /* Add new entry */
                for ( j = 0, addr = ip_addresses_entry->sa_da_addresses; j < RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_NUMBER; j++, addr++ )
                {
                    RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_WRITE(*addr, entry, j);
                }
                ip_addresses_entry->reference_count = 1;
                RDD_FC_FLOW_IP_ADDRESSES_ENTRY_REFERENCE_COUNT_WRITE( ip_addresses_entry->reference_count, entry);
                RDD_FC_FLOW_IP_ADDRESSES_ENTRY_IS_IPV6_ADDRESS_WRITE( ip_addresses_entry->is_ipv6_address, entry );
                *entry_index = i;
                *entry_sram_address = FC_FLOW_IP_ADDRESSES_TABLE_ADDRESS + (i * sizeof(RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS));
                bdmf_error = BDMF_ERR_OK;
                break;
            }
        }
    }

    return bdmf_error;
}


int rdd_fc_flow_ip_addresses_get ( bdmf_index                          entry_index,
                                   RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS  *ip_addresses_entry,
                                   uint16_t                            *entry_sram_address )
{
    RDD_FC_FLOW_IP_ADDRESSES_TABLE_DTS *fc_flow_ip_addresses_table_ptr;
    RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS *entry;
    uint8_t                          *addr;
    uint32_t                         j;
    int           bdmf_error = BDMF_ERR_NOENT;

    *entry_sram_address = 0;
    memset( (uint8_t *) ip_addresses_entry, 0x00, sizeof(RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS));

    fc_flow_ip_addresses_table_ptr = ( RDD_FC_FLOW_IP_ADDRESSES_TABLE_DTS * )(DEVICE_ADDRESS( RUNNER_COMMON_1_OFFSET ) + FC_FLOW_IP_ADDRESSES_TABLE_ADDRESS - sizeof ( RUNNER_COMMON ));

    if( entry_index < RDD_FC_FLOW_IP_ADDRESSES_TABLE_SIZE )
    {
        entry = fc_flow_ip_addresses_table_ptr->entry + entry_index;

        RDD_FC_FLOW_IP_ADDRESSES_ENTRY_REFERENCE_COUNT_READ( ip_addresses_entry->reference_count, entry);
        RDD_FC_FLOW_IP_ADDRESSES_ENTRY_IS_IPV6_ADDRESS_READ( ip_addresses_entry->is_ipv6_address, entry );

        if( ip_addresses_entry->reference_count )
        {
            for ( j = 0, addr = ip_addresses_entry->sa_da_addresses; j < RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_NUMBER; j++, addr++ )
            {
                RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_READ(*addr, entry, j);
            }

            *entry_sram_address = FC_FLOW_IP_ADDRESSES_TABLE_ADDRESS + (entry_index * sizeof(RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS));

            bdmf_error = BDMF_ERR_OK;
        }
    }

    return bdmf_error;
}


int rdd_fc_flow_ip_addresses_delete_by_index ( bdmf_index entry_index )
{
    RDD_FC_FLOW_IP_ADDRESSES_TABLE_DTS *fc_flow_ip_addresses_table_ptr;
    RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS *entry;
    uint16_t                           reference_count;
    int             bdmf_error = BDMF_ERR_NOENT;

    fc_flow_ip_addresses_table_ptr = ( RDD_FC_FLOW_IP_ADDRESSES_TABLE_DTS * )(DEVICE_ADDRESS( RUNNER_COMMON_1_OFFSET ) + FC_FLOW_IP_ADDRESSES_TABLE_ADDRESS - sizeof ( RUNNER_COMMON ));

    if( entry_index < RDD_FC_FLOW_IP_ADDRESSES_TABLE_SIZE )
    {
        entry = fc_flow_ip_addresses_table_ptr->entry + entry_index;

        RDD_FC_FLOW_IP_ADDRESSES_ENTRY_REFERENCE_COUNT_READ( reference_count, entry);
        if( reference_count > 0 )
        {
            reference_count--;
            RDD_FC_FLOW_IP_ADDRESSES_ENTRY_REFERENCE_COUNT_WRITE( reference_count, entry);
        }

        if(reference_count == 0)
        {
            memset((uint8_t *) entry, 0x00, sizeof(RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS));
        }

        bdmf_error = BDMF_ERR_OK;
    }

    return bdmf_error;
}

int rdd_fc_flow_ip_addresses_delete_by_address ( RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS  *ip_addresses_entry )
{
    RDD_FC_FLOW_IP_ADDRESSES_TABLE_DTS *fc_flow_ip_addresses_table_ptr;
    RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS *entry, curr;
    uint16_t                           reference_count;
    uint32_t                           i, j;
    uint8_t                            *addr;
    int             bdmf_error = BDMF_ERR_NOENT;

    fc_flow_ip_addresses_table_ptr = ( RDD_FC_FLOW_IP_ADDRESSES_TABLE_DTS * )(DEVICE_ADDRESS( RUNNER_COMMON_1_OFFSET ) + FC_FLOW_IP_ADDRESSES_TABLE_ADDRESS - sizeof ( RUNNER_COMMON ));

    for( i = 0; i < RDD_FC_FLOW_IP_ADDRESSES_TABLE_SIZE; i++ )
    {
        entry = fc_flow_ip_addresses_table_ptr->entry + i;

        for ( j = 0, addr = curr.sa_da_addresses; j < RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_NUMBER; j++, addr++ )
            RDD_FC_FLOW_IP_ADDRESSES_ENTRY_SA_DA_ADDRESSES_READ(*addr, entry, j);

        if( !memcmp(curr.sa_da_addresses, ip_addresses_entry->sa_da_addresses, sizeof(curr.sa_da_addresses)) )
        {
            RDD_FC_FLOW_IP_ADDRESSES_ENTRY_REFERENCE_COUNT_READ( reference_count, entry);
            if( reference_count > 0 )
            {
                reference_count--;
                RDD_FC_FLOW_IP_ADDRESSES_ENTRY_REFERENCE_COUNT_WRITE( reference_count, entry);
            }

            if(reference_count == 0)
            {
                memset((uint8_t *) entry, 0x00, sizeof(RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS));
            }

            bdmf_error = BDMF_ERR_OK;
            break;
        }
    }

    return bdmf_error;
}

static inline uint32_t f_number_to_bit_mask_32( bdmf_index number )
{
    return ( 1 << number );
}

int rdd_ucast_ds_wan_udp_filter_get( bdmf_index                       entry_index,
                                     RDD_DS_WAN_UDP_FILTER_ENTRY_DTS  *ds_wan_udp_filter_entry )
{
    int bdmf_error = BDMF_ERR_NOENT;

    if( entry_index < RDD_DS_WAN_UDP_FILTER_TABLE_SIZE )
    {
        RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_DTS *ds_wan_udp_filter_control = ( RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_DTS * )( DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_WAN_UDP_FILTER_CONTROL_TABLE_ADDRESS );
        uint32_t valid_mask;

        RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_VALID_MASK_READ( valid_mask, ds_wan_udp_filter_control );

        if( f_number_to_bit_mask_32( entry_index ) & valid_mask )
        {
            RDD_DS_WAN_UDP_FILTER_ENTRY_DTS *ds_wan_udp_filter_table = ( RDD_DS_WAN_UDP_FILTER_ENTRY_DTS * )RDD_DS_WAN_UDP_FILTER_TABLE_PTR();

            ds_wan_udp_filter_table += entry_index;

            RDD_DS_WAN_UDP_FILTER_ENTRY_OFFSET_READ( ds_wan_udp_filter_entry->offset, ds_wan_udp_filter_table );
            RDD_DS_WAN_UDP_FILTER_ENTRY_VALUE_READ( ds_wan_udp_filter_entry->value, ds_wan_udp_filter_table );
            RDD_DS_WAN_UDP_FILTER_ENTRY_MASK_READ( ds_wan_udp_filter_entry->mask, ds_wan_udp_filter_table );
            RDD_DS_WAN_UDP_FILTER_ENTRY_HITS_READ( ds_wan_udp_filter_entry->hits, ds_wan_udp_filter_table );

            bdmf_error = BDMF_ERR_OK;
        }
    }

    return bdmf_error;
}

#if defined(FIRMWARE_INIT)
static inline int ffz(int mask)
{
    int bit = ffs(~mask);

    if(bit)
    {
        return bit - 1;
    }
    else
    {
        return -1;
    }
}
#endif

int rdd_ucast_ds_wan_udp_filter_add( RDD_DS_WAN_UDP_FILTER_ENTRY_DTS  *ds_wan_udp_filter_entry,
                                     bdmf_index                       *entry_index_res )
{
    int bdmf_error = BDMF_ERR_NORES;
    RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_DTS *ds_wan_udp_filter_control = ( RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_DTS * )( DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_WAN_UDP_FILTER_CONTROL_TABLE_ADDRESS );
    uint32_t valid_mask;
    int entry_index;

    RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_VALID_MASK_READ( valid_mask, ds_wan_udp_filter_control );

    entry_index = ffz( valid_mask );

    if(entry_index >= 0)
    {
        RDD_DS_WAN_UDP_FILTER_ENTRY_DTS *ds_wan_udp_filter_table = ( RDD_DS_WAN_UDP_FILTER_ENTRY_DTS * )RDD_DS_WAN_UDP_FILTER_TABLE_PTR();

        ds_wan_udp_filter_table += entry_index;

        RDD_DS_WAN_UDP_FILTER_ENTRY_OFFSET_WRITE( ds_wan_udp_filter_entry->offset, ds_wan_udp_filter_table );
        RDD_DS_WAN_UDP_FILTER_ENTRY_VALUE_WRITE( ds_wan_udp_filter_entry->value & ds_wan_udp_filter_entry->mask, ds_wan_udp_filter_table );
        RDD_DS_WAN_UDP_FILTER_ENTRY_MASK_WRITE( ds_wan_udp_filter_entry->mask, ds_wan_udp_filter_table );
        RDD_DS_WAN_UDP_FILTER_ENTRY_HITS_WRITE( 0, ds_wan_udp_filter_table );

        valid_mask |= f_number_to_bit_mask_32( entry_index );

        RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_VALID_MASK_WRITE( valid_mask, ds_wan_udp_filter_control );

        *entry_index_res = (bdmf_index)entry_index;

        bdmf_error = BDMF_ERR_OK;
    }

    return bdmf_error;
}

int rdd_ucast_ds_wan_udp_filter_delete( bdmf_index entry_index )
{
    int bdmf_error = BDMF_ERR_NOENT;

    if( entry_index < RDD_DS_WAN_UDP_FILTER_TABLE_SIZE )
    {
        RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_DTS *ds_wan_udp_filter_control = ( RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_DTS * )( DEVICE_ADDRESS( RUNNER_PRIVATE_0_OFFSET ) + DS_WAN_UDP_FILTER_CONTROL_TABLE_ADDRESS );
        uint32_t entry_mask = f_number_to_bit_mask_32( entry_index );
        uint32_t valid_mask;

        RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_VALID_MASK_READ( valid_mask, ds_wan_udp_filter_control );

        if( valid_mask & entry_mask )
        {
            valid_mask &= ~entry_mask;

            RDD_DS_WAN_UDP_FILTER_CONTROL_ENTRY_VALID_MASK_WRITE( valid_mask, ds_wan_udp_filter_control );

            bdmf_error = BDMF_ERR_OK;
        }
    }

    return bdmf_error;
}


#if defined(CC_RDD_ROUTER_DEBUG)
extern int g_dbg_lvl;
#define __debug_mcast(fmt, arg...)                          \
    if ( g_dbg_lvl > 0 )                                    \
        do {                                                \
            print(fmt, ##arg);                              \
        } while(0)

#else
#define __debug_mcast(fmt, arg...)
#endif


/* Finds out whether the IP address (IPv4/6) is zero or non-zero.
   Returns: 0 if IP address is zero,
            1 if IP address is non-zero
           -1 if IP address in not IPv4/6
*/
static inline int32_t is_ip_addr_non_zero( bdmf_ip_t *ip_addr_ptr )
{
     if ( ip_addr_ptr->family == bdmf_ip_family_ipv4 )
     {
         if ( ip_addr_ptr->addr.ipv4 )
            return 1;
         else
             return 0;
     }
     else if ( ip_addr_ptr->family == bdmf_ip_family_ipv6 )
     {
        if ( ip_addr_ptr->addr.ipv6.data[0] || ip_addr_ptr->addr.ipv6.data[1] ||
             ip_addr_ptr->addr.ipv6.data[2] || ip_addr_ptr->addr.ipv6.data[3] || 
             ip_addr_ptr->addr.ipv6.data[4] || ip_addr_ptr->addr.ipv6.data[5] || 
             ip_addr_ptr->addr.ipv6.data[6] || ip_addr_ptr->addr.ipv6.data[7] || 
             ip_addr_ptr->addr.ipv6.data[8] || ip_addr_ptr->addr.ipv6.data[9] || 
             ip_addr_ptr->addr.ipv6.data[10] || ip_addr_ptr->addr.ipv6.data[11] || 
             ip_addr_ptr->addr.ipv6.data[12] || ip_addr_ptr->addr.ipv6.data[13] || 
             ip_addr_ptr->addr.ipv6.data[14] || ip_addr_ptr->addr.ipv6.data[15] ) 
            return 1;
         else
            return 0;
     }

     return -1; /* should never reach here */
}


static inline void print_ipv6_addr( bdmf_ipv6_t *ipv6_addr_ptr )
{
    __debug_mcast("0x%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X:%02X%02X",
          ipv6_addr_ptr->data[0], ipv6_addr_ptr->data[1], ipv6_addr_ptr->data[2], ipv6_addr_ptr->data[3], 
          ipv6_addr_ptr->data[4], ipv6_addr_ptr->data[5], ipv6_addr_ptr->data[6], ipv6_addr_ptr->data[7], 
          ipv6_addr_ptr->data[8], ipv6_addr_ptr->data[9], ipv6_addr_ptr->data[10], ipv6_addr_ptr->data[11], 
          ipv6_addr_ptr->data[12], ipv6_addr_ptr->data[13], ipv6_addr_ptr->data[14], ipv6_addr_ptr->data[15] ); 
}

/* XXX : This function should be common for all ucast/mcast in future */
static inline int f_rdd_nat_cache_mcast_lkp_entry_alloc ( uint32_t                  hash_index,
                                                          uint8_t                   *new_lookup_entry_bytes,
                                                          uint32_t                  *tries_res )
{
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;
    uint32_t                  idx, tries = RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE;
    uint32_t                  nat_cache_entry_index;
    uint32_t                  nat_cache_lkp_entry_valid;
    RDD_NAT_CACHE_TABLE_DTS   *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;

    for ( idx = 0; idx < RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE; idx++ )
    {
        nat_cache_entry_index = hash_index + idx;

        nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ nat_cache_entry_index ] );

        RDD_NAT_CACHE_LKP_ENTRY_VALID_READ ( nat_cache_lkp_entry_valid, nat_cache_lkp_entry_ptr );

        if ( nat_cache_lkp_entry_valid )
        {
            /* if entry is valid, check if it matches entry being added */
            if ( memcmp((uint8_t*)nat_cache_lkp_entry_ptr, new_lookup_entry_bytes, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS) ) == 0)
            {
                return BDMF_ERR_ALREADY;
            }
        }
        else if ( tries == RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE )
        {
            tries = idx;
        }
    }

    *tries_res = tries;
    return BDMF_ERR_OK;
}

int rdd_fc_mcast_connection_entry_add(rdd_mcast_flow_t *rdd_mcast_flow)
{
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint8_t                      entry_bytes[ RDD_NAT_CACHE_LKP_ENTRY_SIZE ];
    uint32_t                     hash_index, tries = 0;
    uint32_t                     nat_cache_entry_index;
    uint32_t                     flow_entry_index;
    int                          bdmf_error;
    unsigned long                flags;
    int                          create_dup_key=0; /*NAT Cache errata workaround*/
    uint32_t                     is_mcast_mstr = (rdd_mcast_flow->key.entry_idx == 0);

    rdd_fc_mcast_compose_lkup_key(&rdd_mcast_flow->key, entry_bytes);
    /* key_compose function does not set valid bit */
    RDD_NAT_CACHE_MCAST_LKP_ENTRY_VALID_WRITE(1, entry_bytes);
    rdd_connection_hash_function(&hash_index, entry_bytes);

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );

    bdmf_error = f_rdd_nat_cache_mcast_lkp_entry_alloc ( hash_index, entry_bytes, &tries );

    if ( bdmf_error != BDMF_ERR_OK )
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return ( bdmf_error );
    }

    if ( tries == RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE )
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return BDMF_ERR_IGNORE;
    }

    /*Wrap index at 64K - Part of NAT Cache workaround below*/
    nat_cache_entry_index = (hash_index + tries) & (RDD_NAT_CACHE_TABLE_SIZE - 1);

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ nat_cache_entry_index ] );

    rdd_mcast_flow->context.fc_ucast_flow_context_entry.connection_table_index = nat_cache_entry_index;
    /* Not storing the direction for now */
    /* rdd_mcast_flow->context_entry.fc_ucast_flow_context_entry.connection_direction = direction; */

    bdmf_error = f_rdd_context_entry_add ( &rdd_mcast_flow->context, nat_cache_entry_index, is_mcast_mstr, &flow_entry_index );
    if (bdmf_error != BDMF_ERR_OK)
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return BDMF_ERR_NORES;
    }

    do
    {
        /* Key was already built in local array above -- just use it */
        memcpy(nat_cache_lkp_entry_ptr, entry_bytes, sizeof(entry_bytes));

        /* NAT cache workaround: the context table is wrap around at 64K while the key table is continuous */
        if (nat_cache_entry_index < RDD_NAT_CACHE_EXTENSION_TABLE_SIZE)
        {
            nat_cache_entry_index = RDD_NAT_CACHE_TABLE_SIZE + nat_cache_entry_index;
            nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &(nat_cache_table_ptr->entry[nat_cache_entry_index]);
            create_dup_key = 1;
        }
        else
        {
            nat_cache_entry_index = nat_cache_entry_index & (RDD_NAT_CACHE_TABLE_SIZE - 1);
            nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &(nat_cache_table_ptr->entry[nat_cache_entry_index]);
            create_dup_key = 0;
        }
    } while (create_dup_key);

    /* return the index of the entry in the table */
    rdd_mcast_flow->xo_entry_index = flow_entry_index;

    context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    context_cont_entry_ptr = &(context_cont_table_ptr->entry[ nat_cache_entry_index ] );
    RDD_CONTEXT_CONTINUATION_ENTRY_FLOW_INDEX_WRITE ( flow_entry_index, context_cont_entry_ptr );

#if defined(CC_RDD_ROUTER_DEBUG)
    {
        __debug("%s, %u: connection_table_index %u\n", __FUNCTION__, __LINE__, context_cont_entry_ptr->connection_table_index);
    }
#endif

    bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
    return BDMF_ERR_OK;
}
int rdd_fc_mcast_connection_entry_delete ( bdmf_index  flow_entry_index )
{
    RDD_NAT_CACHE_TABLE_DTS      *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr, nat_cache_lookup_entry;
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint32_t                     nat_cache_lkp_entry_valid;
    uint32_t                     context_cont_flow_index;
    uint32_t                     entry_index = RDD_NATC_CONTEXT_TABLE_SIZE;
    uint32_t                     context_entry_connection_table_index;
    unsigned long                flags;
    bdmf_error_t rc = BDMF_ERR_OK;
    uint32_t                     connection_direction;

    if ((g_free_flow_entries[flow_entry_index] & RDD_FLOW_ENTRY_VALID) == RDD_FLOW_ENTRY_VALID)
    {
        entry_index = g_free_flow_entries[flow_entry_index] & ~RDD_FLOW_ENTRY_VALID;
    }
    else
    {
        return BDMF_ERR_PARM;
    }

    if ( entry_index >= RDD_NATC_CONTEXT_TABLE_SIZE )
    {
        return BDMF_ERR_PARM;
    }

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );

    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ entry_index ] );

    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_TABLE_INDEX_READ ( context_entry_connection_table_index, context_cont_entry_ptr );
    RDD_CONTEXT_CONTINUATION_ENTRY_CONNECTION_DIRECTION_READ ( connection_direction, context_cont_entry_ptr );

    /* NAT cache workaround: the context table is wrap around at 64K while the key table is continuous */
    if (entry_index < RDD_NAT_CACHE_EXTENSION_TABLE_SIZE) {
        nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &(nat_cache_table_ptr->entry[RDD_NAT_CACHE_TABLE_SIZE + entry_index]);
        memset(nat_cache_lkp_entry_ptr, 0, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));
    }

    nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ context_entry_connection_table_index ] );

    RDD_NAT_CACHE_LKP_ENTRY_VALID_READ ( nat_cache_lkp_entry_valid, nat_cache_lkp_entry_ptr );
    RDD_CONTEXT_CONTINUATION_ENTRY_FLOW_INDEX_READ ( context_cont_flow_index, context_cont_entry_ptr );

    if ( nat_cache_lkp_entry_valid && ( flow_entry_index == context_cont_flow_index ) )
    {
        /* Remove flow context from DDR */
        memcpy(&nat_cache_lookup_entry, nat_cache_lkp_entry_ptr, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));

        memset(nat_cache_lkp_entry_ptr, 0, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS));

#if !defined(FIRMWARE_INIT)
        wmb();

        /* Delete the entry in the NAT cache internal memory */
        rdd_nat_cache_submit_command(natc_del, (uint32_t *)&nat_cache_lookup_entry, NULL, NULL);
#endif

        /* Delete continuation flow cache index from cam_lkp tbl */
        f_rdd_cpu_tx_send_message( LILAC_RDD_CPU_TX_MESSAGE_INVALIDATE_CONTEXT_INDEX_CACHE_ENTRY,
                           (connection_direction == rdpa_dir_ds) ?
                           PICO_RUNNER_A : FAST_RUNNER_B,
                           (connection_direction == rdpa_dir_ds) ?
                           RUNNER_PRIVATE_0_OFFSET : RUNNER_PRIVATE_1_OFFSET,
                           context_entry_connection_table_index, 0, 0, BL_LILAC_RDD_WAIT );

        f_rdd_free_context_entry ( entry_index );

        if (rc == BDMF_ERR_OK)
        {
            g_free_flow_entries[flow_entry_index] = 0;
            g_free_flow_entries_number++;
        }
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );

        return rc;
    }
    else
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return BDMF_ERR_INTERNAL;
    }
}

static int f_rdd_nat_cache_mcast_lkp_entry_lookup ( uint32_t                  hash_index,
                                                    uint8_t                  *lookup_entry,
                                                    uint32_t                  *tries_res )
{
    RDD_NAT_CACHE_LKP_ENTRY_DTS  *nat_cache_lkp_entry_ptr;
    uint32_t                  tries;
    uint32_t                  nat_cache_entry_index;
    uint32_t                  nat_cache_lkp_entry_valid;
    RDD_NAT_CACHE_TABLE_DTS   *nat_cache_table_ptr = (RDD_NAT_CACHE_TABLE_DTS *)NatCacheTableBase;

    for ( tries = 0; tries < RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE; tries++ )
    {
        nat_cache_entry_index = hash_index + tries;

        nat_cache_lkp_entry_ptr = (RDD_NAT_CACHE_LKP_ENTRY_DTS *) &( nat_cache_table_ptr->entry[ nat_cache_entry_index ] );

        RDD_NAT_CACHE_LKP_ENTRY_VALID_READ ( nat_cache_lkp_entry_valid, nat_cache_lkp_entry_ptr );

        if ( nat_cache_lkp_entry_valid )
        {
            /* if entry is valid, check if it matches the lookup entry */
            if ( memcmp((uint8_t*)nat_cache_lkp_entry_ptr, lookup_entry, sizeof(RDD_NAT_CACHE_LKP_ENTRY_DTS) ) == 0)
            {
                break;
            }
        }
    }

    *tries_res = tries;

    return BDMF_ERR_OK;
}

int rdd_fc_mcast_connection_entry_search ( rdd_mcast_flow_t  *rdd_mcast_flow,
                                           bdmf_index     *entry_index )
{
    RDD_CONTEXT_CONTINUATION_TABLE_DTS *context_cont_table_ptr = ( RDD_CONTEXT_CONTINUATION_TABLE_DTS * )ContextContTableBase;
    RDD_CONTEXT_CONTINUATION_ENTRY_DTS *context_cont_entry_ptr;
    uint8_t                   entry_bytes[ RDD_NAT_CACHE_LKP_ENTRY_SIZE ];
    uint32_t                  hash_index, tries = 0;
    uint32_t                  nat_cache_entry_index;
    uint16_t                  flow_entry_index;
    unsigned long             flags;

    rdd_fc_mcast_compose_lkup_key(&rdd_mcast_flow->key, entry_bytes);
    /* key_compose function does not set valid bit */
    RDD_NAT_CACHE_MCAST_LKP_ENTRY_KEY_EXTEND_WRITE(1, entry_bytes);
    rdd_connection_hash_function(&hash_index, entry_bytes);

    bdmf_fastlock_lock_irq ( &int_lock_irq, flags );

    f_rdd_nat_cache_mcast_lkp_entry_lookup ( hash_index, entry_bytes, &tries );

    if ( tries == RDD_NAT_CACHE_LOOKUP_DEPTH_SIZE )
    {
        bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
        return BDMF_ERR_NOENT;
    }

    nat_cache_entry_index = hash_index + tries;

    context_cont_entry_ptr = &( context_cont_table_ptr->entry[ nat_cache_entry_index ] );
    RDD_CONTEXT_CONTINUATION_ENTRY_FLOW_INDEX_READ ( flow_entry_index, context_cont_entry_ptr );

    *entry_index = flow_entry_index;

    bdmf_fastlock_unlock_irq ( &int_lock_irq, flags );
    return BDMF_ERR_OK;
}


