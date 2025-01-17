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


#ifndef _RDD_AG_PROCESSING_H_
#define _RDD_AG_PROCESSING_H_

typedef struct rdd_vport_cfg_entry_s
{
    bdmf_boolean loopback_en;
    bdmf_boolean mirroring_en;
    uint8_t ingress_filter_profile;
    uint8_t natc_tbl_id;
    uint8_t emac_idx;
    bdmf_boolean port_dbg_stat_en;
    bdmf_boolean congestion_flow_control;
    bdmf_boolean ingress_rate_limit;
    bdmf_boolean mcast_whitelist_skip;
    bdmf_boolean dos_attack_detection_disable;
} rdd_vport_cfg_entry_t;

int rdd_ag_processing_vport_cfg_entry_get(uint32_t _entry, rdd_vport_cfg_entry_t *vport_cfg_entry);
int rdd_ag_processing_vport_cfg_entry_set(uint32_t _entry, rdd_vport_cfg_entry_t *vport_cfg_entry);
int rdd_ag_processing_vport_to_lookup_port_mapping_table_set(uint32_t _entry, uint8_t bits);
int rdd_ag_processing_vport_to_lookup_port_mapping_table_get(uint32_t _entry, uint8_t *bits);
int rdd_ag_processing_vport_cfg_table_loopback_en_set(uint32_t _entry, bdmf_boolean loopback_en);
int rdd_ag_processing_vport_cfg_table_loopback_en_get(uint32_t _entry, bdmf_boolean *loopback_en);
int rdd_ag_processing_vport_cfg_table_mirroring_en_set(uint32_t _entry, bdmf_boolean mirroring_en);
int rdd_ag_processing_vport_cfg_table_mirroring_en_get(uint32_t _entry, bdmf_boolean *mirroring_en);
int rdd_ag_processing_vport_cfg_table_ingress_filter_profile_set(uint32_t _entry, uint8_t ingress_filter_profile);
int rdd_ag_processing_vport_cfg_table_ingress_filter_profile_get(uint32_t _entry, uint8_t *ingress_filter_profile);
int rdd_ag_processing_vport_cfg_table_natc_tbl_id_set(uint32_t _entry, uint8_t natc_tbl_id);
int rdd_ag_processing_vport_cfg_table_natc_tbl_id_get(uint32_t _entry, uint8_t *natc_tbl_id);
int rdd_ag_processing_vport_cfg_table_emac_idx_set(uint32_t _entry, uint8_t emac_idx);
int rdd_ag_processing_vport_cfg_table_emac_idx_get(uint32_t _entry, uint8_t *emac_idx);
int rdd_ag_processing_vport_cfg_table_viq_set(uint32_t _entry, uint8_t viq);
int rdd_ag_processing_vport_cfg_table_viq_get(uint32_t _entry, uint8_t *viq);
int rdd_ag_processing_vport_cfg_table_port_dbg_stat_en_set(uint32_t _entry, bdmf_boolean port_dbg_stat_en);
int rdd_ag_processing_vport_cfg_table_port_dbg_stat_en_get(uint32_t _entry, bdmf_boolean *port_dbg_stat_en);
int rdd_ag_processing_vport_cfg_table_congestion_flow_control_set(uint32_t _entry, bdmf_boolean congestion_flow_control);
int rdd_ag_processing_vport_cfg_table_congestion_flow_control_get(uint32_t _entry, bdmf_boolean *congestion_flow_control);
int rdd_ag_processing_vport_cfg_table_ingress_rate_limit_set(uint32_t _entry, bdmf_boolean ingress_rate_limit);
int rdd_ag_processing_vport_cfg_table_ingress_rate_limit_get(uint32_t _entry, bdmf_boolean *ingress_rate_limit);
int rdd_ag_processing_vport_cfg_table_mcast_whitelist_skip_set(uint32_t _entry, bdmf_boolean mcast_whitelist_skip);
int rdd_ag_processing_vport_cfg_table_mcast_whitelist_skip_get(uint32_t _entry, bdmf_boolean *mcast_whitelist_skip);
int rdd_ag_processing_vport_cfg_table_dos_attack_detection_disable_set(uint32_t _entry, bdmf_boolean dos_attack_detection_disable);
int rdd_ag_processing_vport_cfg_table_dos_attack_detection_disable_get(uint32_t _entry, bdmf_boolean *dos_attack_detection_disable);
int rdd_ag_processing_codel_num_queues_set(uint16_t bits);
int rdd_ag_processing_codel_num_queues_get(uint16_t *bits);
int rdd_ag_processing_codel_enable_table_set(uint32_t _entry, uint32_t bits);
int rdd_ag_processing_codel_enable_table_get(uint32_t _entry, uint32_t *bits);
int rdd_ag_processing_spdtest_num_of_udp_rx_flows_set(uint8_t bits);
int rdd_ag_processing_spdtest_num_of_udp_rx_flows_get(uint8_t *bits);
int rdd_ag_processing_policer_params_table_factor_bytes_set(uint32_t _entry, uint8_t factor_bytes);
int rdd_ag_processing_policer_params_table_factor_bytes_get(uint32_t _entry, uint8_t *factor_bytes);
int rdd_ag_processing_policer_params_table_dei_mode_set(uint32_t _entry, bdmf_boolean dei_mode);
int rdd_ag_processing_policer_params_table_dei_mode_get(uint32_t _entry, bdmf_boolean *dei_mode);
int rdd_ag_processing_tcam_generic_fields_offset_set(uint32_t _entry, uint8_t offset);
int rdd_ag_processing_tcam_generic_fields_offset_get(uint32_t _entry, uint8_t *offset);
int rdd_ag_processing_tcam_generic_fields_layer_set(uint32_t _entry, uint8_t layer);
int rdd_ag_processing_tcam_generic_fields_layer_get(uint32_t _entry, uint8_t *layer);
int rdd_ag_processing_tcam_table_cfg_table_generic_1_set(uint32_t _entry, bdmf_boolean generic_1);
int rdd_ag_processing_tcam_table_cfg_table_generic_1_get(uint32_t _entry, bdmf_boolean *generic_1);
int rdd_ag_processing_tcam_table_cfg_table_generic_2_set(uint32_t _entry, bdmf_boolean generic_2);
int rdd_ag_processing_tcam_table_cfg_table_generic_2_get(uint32_t _entry, bdmf_boolean *generic_2);
int rdd_ag_processing_tcam_table_cfg_table_generic_3_set(uint32_t _entry, bdmf_boolean generic_3);
int rdd_ag_processing_tcam_table_cfg_table_generic_3_get(uint32_t _entry, bdmf_boolean *generic_3);
int rdd_ag_processing_tcam_table_cfg_table_generic_4_set(uint32_t _entry, bdmf_boolean generic_4);
int rdd_ag_processing_tcam_table_cfg_table_generic_4_get(uint32_t _entry, bdmf_boolean *generic_4);
int rdd_ag_processing_tcam_table_cfg_table_ingress_port_set(uint32_t _entry, bdmf_boolean ingress_port);
int rdd_ag_processing_tcam_table_cfg_table_ingress_port_get(uint32_t _entry, bdmf_boolean *ingress_port);
int rdd_ag_processing_tcam_table_cfg_table_gem_set(uint32_t _entry, bdmf_boolean gem);
int rdd_ag_processing_tcam_table_cfg_table_gem_get(uint32_t _entry, bdmf_boolean *gem);
int rdd_ag_processing_tcam_table_cfg_table_network_layer_set(uint32_t _entry, bdmf_boolean network_layer);
int rdd_ag_processing_tcam_table_cfg_table_network_layer_get(uint32_t _entry, bdmf_boolean *network_layer);
int rdd_ag_processing_tcam_table_cfg_table_ssid_set(uint32_t _entry, bdmf_boolean ssid);
int rdd_ag_processing_tcam_table_cfg_table_ssid_get(uint32_t _entry, bdmf_boolean *ssid);

#endif /* _RDD_AG_PROCESSING_H_ */
