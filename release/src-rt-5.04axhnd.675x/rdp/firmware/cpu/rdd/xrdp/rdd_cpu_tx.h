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

#ifndef _RDD_CPU_TX_H_
#define _RDD_CPU_TX_H_


typedef struct
{
    void *sysb;             /**< Buffer pointer */
    void *data;             /**< Buffer pointer */
    uint32_t fpm_bn;        /**< Buffer number */
    uint16_t offset;        /**< Buffer offset */
    uint16_t length;        /**< Buffer length */
    uint8_t abs_flag:1;       /**< ABS/FPM */
    uint8_t sbpm_copy:1;      /**< copy to SBPM/FPM */
    uint8_t fpm_fallback:1;   /**< if no SBPM copy to FPM */
    uint8_t reserve:5;
} pbuf_t;


typedef union
{
    uint32_t bn1_or_abs2_or_1588         :18  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
    uint32_t data_1588                   :18  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
#ifndef FIRMWARE_LITTLE_ENDIAN
    struct
    {
        uint32_t ssid                    :4  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint32_t fpm_fallback            :1  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint32_t sbpm_copy               :1  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint32_t bn1_or_abs2             :12 __PACKING_ATTRIBUTE_FIELD_LEVEL__;
    };
#else
    struct
    {
        uint32_t bn1_or_abs2             :12 __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint32_t sbpm_copy               :1  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint32_t fpm_fallback            :1  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint32_t ssid                    :4  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
    };
#endif
#ifndef FIRMWARE_LITTLE_ENDIAN
    struct
    {
        uint32_t lag_index               :2  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint32_t reserved2               :16 __PACKING_ATTRIBUTE_FIELD_LEVEL__;
    };
#else
    struct
    {
        uint32_t reserved2               :16 __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint32_t lag_index               :2  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
    };
#endif
} cpu_tx_bn1_or_abs2_or_1588;


typedef union
{
    uint8_t wan_flow_source_port        :8  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
#ifndef FIRMWARE_LITTLE_ENDIAN
    struct
    {
        uint8_t is_vport                :1  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint8_t flow_or_port_id         :7  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
    };
#else
    struct
    {
        uint8_t flow_or_port_id         :7  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
        uint8_t is_vport                :1  __PACKING_ATTRIBUTE_FIELD_LEVEL__;
    };
#endif
} cpu_tx_wan_flow_source_port;



typedef union 
{
    uint32_t sk_buf_ptr_low:32;
#ifndef FIRMWARE_LITTLE_ENDIAN
    struct
    {
        uint32_t data_1588:18;  /* reserved for 1588 data */
        uint32_t reserved1:14;
    };
#else
    struct
    {
        uint32_t data_1588:18;  /* reserved for 1588 data */
        uint32_t reserved1:14;
    };
#endif
} sk_buf_ptr_low_or_data_1588_t;

static inline void rdd_cpu_tx_set_ring_descriptor(const rdpa_cpu_tx_info_t *info, pbuf_t *pbuf, RING_CPU_TX_DESCRIPTOR_STRUCT *ring_cpu_tx_descriptor)
{
    uintptr_t data_phys_addr;
    uintptr_t sysb_phys_addr;

    ring_cpu_tx_descriptor->abs = pbuf->abs_flag;
    ring_cpu_tx_descriptor->fpm_fallback = pbuf->fpm_fallback;
    ring_cpu_tx_descriptor->sbpm_copy = pbuf->sbpm_copy;
    ring_cpu_tx_descriptor->packet_length = pbuf->length;

#if (defined(CONFIG_BCM_SPDTEST) || defined(CONFIG_BCM_SPDTEST_MODULE)) && defined(CONFIG_BCM_TCPSPDTEST_SUPPORT)
    if (info->spdt_so_mark)
    {
        /* set 1588 bit (dont drop) -> must be copied to FPM buffer */
        ring_cpu_tx_descriptor->egress_dont_drop = 1;
        ring_cpu_tx_descriptor->sbpm_copy = 0;
    }
#endif

    ring_cpu_tx_descriptor->target_mem_0 = 0;
    if (!ring_cpu_tx_descriptor->abs)
    {
        ring_cpu_tx_descriptor->fpm_bn0 = pbuf->fpm_bn;
        ring_cpu_tx_descriptor->fpm_sop = pbuf->offset;

#if defined(CONFIG_BCM_PTP_1588)
        /*igor :todo add data_1588 to ring descriptor*/
        if (unlikely(info->ptp_info))
        {
            sk_buf_ptr_low_or_data_1588_t sk_buf_ptr_low_or_data_1588 = {};
            ring_cpu_tx_descriptor->flag_1588 = 1;
            ring_cpu_tx_descriptor->sbpm_copy = 0;
            sk_buf_ptr_low_or_data_1588.data_1588 = info->ptp_info; /*only 18 bits will be copied */
            ring_cpu_tx_descriptor->sk_buf_ptr_low_or_data_1588 = sk_buf_ptr_low_or_data_1588.sk_buf_ptr_low;
        }
#endif        
    }
    else
    {
        data_phys_addr = RDD_VIRT_TO_PHYS(pbuf->data);
        sysb_phys_addr = RDD_VIRT_TO_PHYS(pbuf->sysb);
        GET_ADDR_HIGH_LOW(ring_cpu_tx_descriptor->pkt_buf_ptr_high, ring_cpu_tx_descriptor->pkt_buf_ptr_low_or_fpm_bn0, data_phys_addr);
        GET_ADDR_HIGH_LOW(ring_cpu_tx_descriptor->sk_buf_ptr_high, ring_cpu_tx_descriptor->sk_buf_ptr_low_or_data_1588, sysb_phys_addr);
    }
}
#endif /* _RDD_CPU_TX_H_ */
