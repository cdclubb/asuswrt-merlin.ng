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

#ifndef _BL_LILAC_DRV_RUNNER_H
#define _BL_LILAC_DRV_RUNNER_H

#if defined(FIRMWARE_INIT)

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include "netinet/in.h"

#define CACHED_MALLOC(x) ((uint32_t) x)

#else

#include "bl_os_wraper.h"

#ifdef LINUX_KERNEL

#include <access_macros.h>
#include <linux/string.h>

#else

#include "access_macros.h"

#endif /* LINUX_KERNEL */

#endif /* defined(FIRMWARE_INIT) */


#if defined(_CFE_)
#include "bcm_mm.h"
#define PHYS_TO_VIRT(_addr)             PHYS_TO_CACHED(_addr)
#define RDP_CPU_RING_MAX_QUEUES         1
#define RDP_WLAN_MAX_QUEUES             0

#elif defined(__KERNEL__)
#include "bcm_mm.h"
#define PHYS_TO_VIRT(_addr)             PHYS_TO_CACHED(_addr)
#define RDP_CPU_RING_MAX_QUEUES         RDPA_CPU_MAX_QUEUES
#define RDP_WLAN_MAX_QUEUES             RDPA_WLAN_MAX_QUEUES

#else
#define VIRT_TO_PHYS(_addr)             ((uint32_t)_addr)
#define PHYS_TO_VIRT(_addr)             (_addr)
#endif

#define RDD_VIRT_TO_PHYS(_addr) VIRT_TO_PHYS(_addr)
#define RDD_PHYS_TO_VIRT(_addr) PHYS_TO_VIRT(_addr)

#if defined(__KERNEL__)
#include "bcm_rsvmem.h"
#define RDD_RSV_VIRT_TO_PHYS(_vbase, _pbase, _addr) BcmMemReserveVirtToPhys(_vbase, _pbase, _addr)
#define RDD_RSV_PHYS_TO_VIRT(_vbase, _pbase, _addr) BcmMemReservePhysToVirt(_vbase, _pbase, _addr)
#else
#define RDD_RSV_VIRT_TO_PHYS(_vbase, _pbase, _addr) RDD_VIRT_TO_PHYS(_addr)
#define RDD_RSV_PHYS_TO_VIRT(_vbase, _pbase, _addr) RDD_PHYS_TO_VIRT(_addr)
#endif


#ifndef __PACKING_ATTRIBUTE_STRUCT_END__
#include "packing.h"
#endif

#ifdef RDD_BASIC
#include "rdp_runner.h"
#include "rdpa_types.h"


#else
#if !defined(FIRMWARE_INIT) || defined(BDMF_SYSTEM_SIM)
#include "bdmf_system.h"
#else
#define bdmf_sysb void *
static inline void *bdmf_sysb_data(const bdmf_sysb sysb)
{
    return ((void *)sysb);
}
#endif
#include "rdp_runner.h"
#include "rdpa_types.h"
#include "rdpa_ip_class_basic.h"
#include "rdpa_ingress_class_basic.h"
#include "rdpa_cpu_basic.h"
#include "rdpa_mcast.h" /* DSL */
#if defined(CONFIG_RUNNER_IPSEC)
#include "rdpa_ipsec.h"
#endif
#include "rdpa_l2_ucast.h"
#endif

#if !defined(FIRMWARE_INIT) || defined(BDMF_SYSTEM_SIM)

#include "rdp_drv_bpm.h"

/* temporary until complete stratosphere removal */

#ifndef RDD_BASIC

#undef malloc
/* Full RDD as part of RDPA */
#define malloc(s) bdmf_alloc(s)

#else

#define bdmf_fastlock int
#define DEFINE_BDMF_FASTLOCK(lock) int lock = 0
#define bdmf_fastlock_lock(_lock)       (*_lock = 0)
#define bdmf_fastlock_unlock(_lock)     (*_lock = 0)
#define bdmf_fastlock_lock_irq(_lock, _flag)   (_flag = *_lock)
#define bdmf_fastlock_unlock_irq(_lock, _flag) (*_lock = _flag)

#if !defined _CFE_

#undef malloc
#undef printf
/* Minimal RDD for builtr-in kernel drivers */
#define malloc(s) kmalloc(s, GFP_KERNEL)
#define printf    printk

#endif /* !defined _CFE_ */

#endif /* RDD_BASIC */

#else

#define bdmf_fastlock int
#define DEFINE_BDMF_FASTLOCK(lock) int lock = 0

#endif /* !defined(FIRMWARE_INIT) */

#if !defined(BDMF_SYSTEM_SIM)
#define rdd_print(fmt, args...) printk(fmt, ##args)
#else
#define rdd_print(fmt, args...) printf(fmt, ##args)
#endif

/* task addresses labels from fw compilation */
#include "rdd_runner_a_labels.h"
#include "rdd_runner_b_labels.h"
#include "rdd_runner_c_labels.h"
#include "rdd_runner_d_labels.h"

#include "rdd_defs.h"
#include "rdd_runner_defs_auto.h"
#include "rdd_runner_defs.h"
#include "rdd_data_structures_auto.h"
#include "rdd_data_structures.h"
#include "rdd_common.h"
#if defined(CONFIG_RUNNER_IPSEC)
#include "rdd_ipsec.h"
#endif
#include "rdd_cpu.h"
#include "rdd_init.h"
#ifdef CONFIG_WLAN_MCAST
#include "rdd_wlan_mcast.h"
#endif
#ifndef RDD_BASIC
#include "rdd_router.h"
#include "rdd_l2_ucast.h"
#include "rdd_bridge.h"
#include "rdd_interworking.h"
#endif
#include "rdd_lookup_engine.h"
#include "rdd_tm.h"
#include "rdd_platform.h"
#include "rdd_simulator.h"

/* priority range according to classification type : acl 128-191, flow 64-127, qos 0-63, ip_flow 192-255  */
#define RDPA_QOS_PRTY_OFFSET 0
#define RDPA_FLOW_PRTY_OFFSET 64
#define RDPA_ACL_PRTY_OFFSET 128
#define RDPA_IP_FLOW_PRTY_OFFSET 192

/* Alignment to new XRDP auto generated structs */
#define FC_UCAST_FLOW_CONTEXT_ENTRY_STRUCT RDD_FC_UCAST_FLOW_CONTEXT_ENTRY_DTS
#define FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_STRUCT RDD_FC_UCAST_FLOW_CONTEXT_ETH_XTM_ENTRY_DTS
#define FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY_STRUCT RDD_FC_UCAST_FLOW_CONTEXT_WFD_NIC_ENTRY_DTS
#define FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY_STRUCT RDD_FC_UCAST_FLOW_CONTEXT_WFD_DHD_ENTRY_DTS
#define FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_STRUCT RDD_FC_UCAST_FLOW_CONTEXT_RNR_DHD_ENTRY_DTS
#define FC_FLOW_IP_ADDRESSES_ENTRY_STRUCT RDD_FC_FLOW_IP_ADDRESSES_ENTRY_DTS

#endif /* _BL_LILAC_DRV_RUNNER_H */

