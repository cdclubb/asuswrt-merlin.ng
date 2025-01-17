/*
* <:copyright-BRCM:2015:DUAL/GPL:standard
* 
*    Copyright (c) 2015 Broadcom 
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

#ifndef _RDPA_WLAN_MCAST_H_
#define _RDPA_WLAN_MCAST_H_

#include "rdpa_cmd_list.h"

/** \defgroup wlan_mcast WLAN Multicast Flow Management
 *  \ingroup mcast
 *  
 *  
 *  RDP supports packet acceleration for up to three WLAN radios using two methods: 
 *  
 *  WFD multicast (forwarding through host CPU)
 *    - One replication per radio.The host CPU may perform further
 *      replications according to the corresponding SSID vector.
 *    - Two priority queues per radio.
 *    - Up to 16 SSIDs per radio.

 *  DHD multicast (forwarding directly to Dongle device)
 *    - Replication per WLAN station
 *    - Multicast->unicast translation for each replication
 *    - Proxy support
 *
 *  It is possible to replicate the same channel using both WDF and DHD acceleration modes. 
 *       
 *  ::rdpa_wlan_mcast_fwd_table_t structure is referenced by the wlan_mcast_index field of ::rdpa_iptv_channel_key_t
 *  structure and used by both WDF and DHD acceleration modes. 
 * @{ 
 */

#define RDPA_WLAN_MCAST_MAX_FLOWS                  64
#define RDPA_WLAN_MCAST_MAX_DHD_STATIONS           64
#define RDPA_WLAN_MCAST_MAX_SSID_MAC_ADDRESSES     48
#define RDPA_WLAN_MCAST_MAX_SSID_STATS             48

#define RDPA_WLAN_MCAST_DHD_STATION_INDEX_INVALID  RDPA_WLAN_MCAST_MAX_DHD_STATIONS
#define RDPA_WLAN_MCAST_FWD_TABLE_INDEX_INVALID    RDPA_WLAN_MCAST_MAX_FLOWS

#define RDPA_WLAN_MCAST_SSID_MAC_ADDRESS_ENTRY_INDEX(_radio_index, _ssid) \
    ((((_radio_index) & 0x3) << 4) | ((_ssid) & 0xF))

#define RDPA_WLAN_MCAST_SSID_STATS_ENTRY_INDEX(_radio_index, _ssid) \
    ((((_radio_index) & 0x3) << 4) | ((_ssid) & 0xF))

#ifdef CONFIG_WLAN_MCAST

/** Wi-Fi Station information is only used when DHD mode is enabled.\n
 */
typedef struct {
    bdmf_mac_t mac_address;          /**< MAC address for multicast->unicast translation */
    uint8_t radio_index;             /**< Radio index that the station is connected to */
    uint8_t ssid;                    /**< SSID index that the station is connected to */
    uint16_t flowring_index;         /**< FlowRing index */
    uint8_t tx_priority;             /**< Packet egress priority */
    uint8_t reference_count;         /**< Reference count (READ ONLY) */
} rdpa_wlan_mcast_dhd_station_t;

/** WLAN Multicast Forwarding Table is used in both WFD and DHD modes.\n
 */
typedef struct {
    uint8_t is_proxy_enabled;        /**< Proxy enable - controls if MAC SA is remarked */
    uint8_t wfd_tx_priority;         /**< WLAN egress queue (skb->mark) */
    uint8_t wfd_0_priority;          /**< WFD0 priority queue, 0 for high 1 for low */
    uint8_t wfd_1_priority;          /**< WFD1 priority queue, 0 for high 1 for low */
    uint8_t wfd_2_priority;          /**< WFD2 priority queue, 0 for high 1 for low */
    uint16_t wfd_0_ssid_vector;      /**< WFD0 SSID vector to be replicated by WFD driver */
    uint16_t wfd_1_ssid_vector;      /**< WFD1 SSID vector to be replicated by WFD driver */
    uint16_t wfd_2_ssid_vector;      /**< WFD2 SSID vector to be replicated by WFD driver */
    bdmf_index dhd_station_index;    /**< DHD new DHD station index */
    uint8_t dhd_station_count;       /**< DHD station count */
    uint8_t dhd_station_list_size;   /**< DHD station list size */
    uint8_t dhd_station_list[RDPA_WLAN_MCAST_MAX_DHD_STATIONS];  /**< DHD station list (READ ONLY) */
} rdpa_wlan_mcast_fwd_table_t;

/** SSID MAC Address Table.\n
 */
typedef struct {
    uint8_t radio_index;             /**< Radio index that the station is connected to */
    uint8_t ssid;                    /**< SSID index that the station is connected to */
    bdmf_mac_t mac_address;          /**< SSID MAC address for proxy mode */
    uint8_t reference_count;         /**< Reference count (READ ONLY) */
} rdpa_wlan_mcast_ssid_mac_address_t;

/** SSID Statistics Table.\n
 */
typedef struct {
    uint8_t radio_index;             /**< Radio index that the station is connected to */
    uint8_t ssid;                    /**< SSID index that the station is connected to */
    uint32_t packets;                /**< Packets (READ ONLY) */
    uint32_t bytes;                  /**< Bytes (READ ONLY) */
} rdpa_wlan_mcast_ssid_stats_t;

/** @} end of mcast Doxygen group. */

#endif

#endif /* _RDPA_WLAN_MCAST_H_ */
