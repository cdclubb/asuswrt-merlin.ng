/*
* <:copyright-BRCM:2014:DUAL/GPL:standard
* 
*    Copyright (c) 2014 Broadcom 
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

#ifndef _RDPA_GEM_H_
#define _RDPA_GEM_H_

/**
 * \defgroup gem GEM Flow Management
 * \ingroup xgpon
 * Objects in this group control GEM-related configuration
 * @{
 */

/**< Max number of GEM flows */
#if defined(XRDP) || defined(BCM_PON_XRDP)
#if !defined(BCM6878)
#define RDPA_MAX_GEM_FLOW 128 
#else
#define RDPA_MAX_GEM_FLOW 64
#endif
#else
#define RDPA_MAX_GEM_FLOW 256 
#endif

/** GEM Flow Type */
typedef enum {
    rdpa_gem_flow_ethernet, /**< Ethernet flow. MAC calculates Ethernet FCS */
    rdpa_gem_flow_omci /**< OMCI Flow */
} rdpa_gem_flow_type;

/** GEM Flow Upstream Configuration
 * Underlying type for gem_us_cfg aggregate
 */
typedef struct 
{
    bdmf_object_handle tcont; /**< TCONT ID */
    bdmf_boolean enc; /**< Encryption - used for XGPON */
} rdpa_gem_flow_us_cfg_t;

/** GEM Flow Downstream Configuration
 * Underlying type for gem_flow_ds_cfg_t aggregate
 */
typedef struct 
{
    rdpa_discard_prty discard_prty; /**< Discard priority */
    rdpa_flow_destination destination; /**< Flow destination */
} rdpa_gem_flow_ds_cfg_t;

/** GEM Flow Statistics 
 * Underlying type for gem_stat aggregate
 */
typedef struct 
{
    uint32_t rx_packets; /**< Rx Packets */
    uint32_t rx_bytes; /**< Rx Bytes */
    uint32_t tx_packets; /**< Tx Packets */
    uint32_t tx_bytes; /**< Tx bytes */
    uint32_t rx_packets_discard; /**< Rx Packet discard */  
    uint32_t tx_packets_discard; /**< Tx Packet discard */ 
} rdpa_gem_stat_t;

/** GEM def flow per port action */
typedef struct
{
    bdmf_object_handle vlan_action; /**< VLAN action object */
    bdmf_boolean drop; /**< Drop action - true/false */
} rdpa_gem_port_action_t;

/** @} end of gem Doxygen group */

#endif /* _RDPA_GEM_H_ */
