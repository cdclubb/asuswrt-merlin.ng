/*
* <:copyright-BRCM:2013:DUAL/GPL:standard
* 
*    Copyright (c) 2013 Broadcom 
*    All Rights Reserved
* 
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License, version 2, as published by
* the Free Software Foundation (the "GPL").
* 
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* 
* A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
* writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
* Boston, MA 02111-1307, USA.
* 
* :>
*/


#ifndef _RDPA_API_H_
#define _RDPA_API_H_

/*
 * Forward declarations of commonly-used types
 */

#include <bdmf_interface.h>
#include <rdpa_types.h>
#include <rdpa_config.h>

#include <rdpa_system.h>
#include <rdpa_port.h>
#include <rdpa_cpu_basic.h>
#include <rdpa_cpu.h>
#include <rdpa_ingress_class_basic.h>
#include <rdpa_ingress_class.h>
#include <rdpa_tcont.h>
#include <rdpa_llid.h>
#include <rdpa_mllid.h>
#include <rdpa_egress_tm.h>
#include <rdpa_vlan_action.h>
#include <rdpa_gem.h>
#include <rdpa_filter.h>

#include <rdpa_ag_system.h>
#include <rdpa_ag_port.h>
#include <rdpa_ag_cpu.h>
#include <rdpa_ag_ingress_class.h>
#include <rdpa_ag_tcont.h>
#include <rdpa_ag_llid.h>
#include <rdpa_ag_mllid.h>
#include <rdpa_ag_egress_tm.h>
#include <rdpa_ag_vlan_action.h>
#include <rdpa_ag_gem.h>

#if !defined(BCM_DSL_RDP) && !defined(BCM_DSL_XRDP) && !defined(RDP_UFC)
#include <rdpa_ip_class.h>
#include <rdpa_ag_ip_class.h>
#ifdef XRDP
#include <rdpa_l2_common.h>
#include <rdpa_l2_class.h>
#include <rdpa_ag_l2_class.h>
#endif
#endif

#include <rdpa_bridge.h>
#include <rdpa_vlan.h>
#include <rdpa_qos_mapper.h>
#include <rdpa_tm.h>
#if defined(CONFIG_WLAN_MCAST)
#include <rdpa_wlan_mcast.h>
#include <rdpa_ag_wlan_mcast.h>
#endif
#if defined(CONFIG_BCM_SPDSVC_SUPPORT) && (!defined(G9991) || defined(XRDP))
#include <rdpa_spdsvc.h>
#include <rdpa_ag_spdsvc.h>
#endif
#if defined(XRDP)
#include <rdpa_tunnel.h>
#include <rdpa_ag_tunnel.h>
#endif
#if defined(CONFIG_BCM_TCPSPDTEST_SUPPORT) || defined(CONFIG_BCM_UDPSPDTEST_SUPPORT)
#include <rdpa_spdtest_common.h>
#endif
#if defined(CONFIG_BCM_TCPSPDTEST_SUPPORT) && defined(XRDP)
#include <rdpa_tcpspdtest.h>
#include <rdpa_ag_tcpspdtest.h>
#endif
#if defined(CONFIG_BCM_UDPSPDTEST_SUPPORT)
#include <rdpa_udpspdtest.h>
#include <rdpa_ag_udpspdtest.h>
#endif
#if defined(CONFIG_RUNNER_IPSEC)
#include <rdpa_ipsec.h>
#endif
#if defined(BCM_DSL_RDP) || defined(BCM_DSL_XRDP) || defined(RDP_UFC)
#include <rdpa_ucast.h>
#include <rdpa_mcast.h>
#include <rdpa_l2_ucast.h>
#include <rdpa_xtm.h>
#else
#include <rdpa_iptv.h>
#endif /* DSL_138 */

#if defined(XRDP) && !defined(OPERATION_MODE_PRV) && !defined(G9991)
#include <rdpa_mcast_whitelist.h>
#endif

#ifdef CONFIG_DHD_RUNNER
#include <rdpa_dhd_helper.h>
#endif

#include <rdpa_ag_bridge.h>
#if defined(CONFIG_RUNNER_IPSEC)
#include <rdpa_ag_ipsec.h>
#endif
#if defined(BCM_DSL_RDP) || defined(BCM_DSL_XRDP)
#include <rdpa_ag_ucast.h>
#include <rdpa_ag_mcast.h>
#if !defined(BCM4912) && !defined(BCM6813)
#include <rdpa_ag_xtm.h>
#endif
#include <rdpa_ag_l2_ucast.h>
#else
#if defined(RDP_UFC)
#include <rdpa_ag_ucast.h>
#include <rdpa_ag_mcast.h>
#include <rdpa_ag_l2_ucast.h>
#else
#include <rdpa_ag_iptv.h>
#endif
#include <rdpa_ag_pbit_to_gem.h>
#include <rdpa_ag_pbit_to_queue.h>
#ifdef RULE_BASED_GRE
#include <rdpa_ag_pbit_to_dscp.h>
#endif
#include <rdpa_ag_tc_to_queue.h>
#endif /* DSL_138 */

#if defined(XRDP) && !defined(OPERATION_MODE_PRV) && !defined(G9991)
#include <rdpa_ag_mcast_whitelist.h>
#endif

#include <rdpa_ag_policer.h>
#include <rdpa_ag_dscp_to_pbit.h>
#include <rdpa_ag_vlan.h>
#include <rdpa_ag_filter.h>

#ifdef CONFIG_DHD_RUNNER
#include <rdpa_ag_dhd_helper.h>
#endif

#if defined(CONFIG_BCM_CAPWAP)
#include <rdpa_capwap.h>
#include <rdpa_ag_capwap.h>
#endif

#endif /* _RDPA_API_H_ */
