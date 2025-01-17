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


#include "bdmf_shell.h"
#ifdef RDP_SIM
#include "rdd_platform.h"
#endif
#include "access_macros.h"
#include "rdd_runner_reg_dump.h"

void dump_RDD_IPTV_DDR_PORT_BUFFER_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register IPTV_DDR_PORT_BUFFER_ENTRY\n");

	bdmf_session_print(session, "\theader                   =\n\t");
	for (i=0,j=0; i<56; i++)
	{
		MREAD_I_8((uint8_t *)(p), i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	MREAD_32((uint8_t *)(p) + 56, (r));
	bdmf_session_print(session, "\tcontext_0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 60, (r));
	bdmf_session_print(session, "\tcontext_1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_IPTV_DDR_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register IPTV_DDR_CONTEXT_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tvalid                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\tip_ver                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 5, 1, (r));
	bdmf_session_print(session, "\tany_vid                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 4, 1, (r));
	bdmf_session_print(session, "\tany_src_ip               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p), 0, 12, (r));
	bdmf_session_print(session, "\tvid                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tnext_entry_idx           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tssid_vector_0_or_flooding_vport= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tssid_vector_1            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tssid_vector_2            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 10, 5, 3, (r));
	bdmf_session_print(session, "\tradio_dhd_vector         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 10, 0, 5, (r));
	bdmf_session_print(session, "\trdd_vport                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 11, 7, 1, (r));
	bdmf_session_print(session, "\twlan_mcast_proxy_enabled = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 11, 0, 7, (r));
	bdmf_session_print(session, "\twlan_mcast_index         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 12, 7, 1, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 12, 4, 3, (r));
	bdmf_session_print(session, "\twlan_mcast_tx_prio       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 12, 0, 4, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 13, 6, 2, (r));
	bdmf_session_print(session, "\tpool_num                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 13, 0, 6, (r));
	bdmf_session_print(session, "\treplications             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 14, 2, 6, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 14, 0, 10, (r));
	bdmf_session_print(session, "\tcntr_id                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tegress_ports_vector      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tsrc_ip                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tsrc_ipv6_addr            =\n\t");
	for (i=0,j=0; i<16; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 24, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tdst_ipv6_addr            =\n\t");
	for (i=0,j=0; i<16; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 40, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tresult                   =\n\t");
	for (i=0,j=0; i<32; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 56, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_WLAN_MCAST_DHD_LIST_ENTRY_ARRAY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register WLAN_MCAST_DHD_LIST_ENTRY_ARRAY\n");

	bdmf_session_print(session, "\tdhd_station              =\n\t");
	for (i=0,j=0; i<64; i++)
	{
		MREAD_I_8((uint8_t *)(p), i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_WLAN_MCAST_DHD_LIST_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register WLAN_MCAST_DHD_LIST_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tvalid                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 7, (r));
	bdmf_session_print(session, "\tindex                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_PROCESSING_TX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PROCESSING_TX_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tvalid                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\theadroom                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 5, 1, (r));
	bdmf_session_print(session, "\tdont_agg                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 4, 1, (r));
	bdmf_session_print(session, "\tmc_copy                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 3, 1, (r));
	bdmf_session_print(session, "\treprocess                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 2, 1, (r));
	bdmf_session_print(session, "\tcolor                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 1, 1, (r));
	bdmf_session_print(session, "\tforce_copy               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p), 0, 9, (r));
	bdmf_session_print(session, "\tsecond_level_q_codel_ts  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 2, 7, 9, (r));
	bdmf_session_print(session, "\tfirst_level_q            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 6, 1, (r));
	bdmf_session_print(session, "\tflag_1588                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 5, 1, (r));
	bdmf_session_print(session, "\tcoherent                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 0, 5, (r));
	bdmf_session_print(session, "\thn                       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 4, 6, 10, (r));
	bdmf_session_print(session, "\tserial_num               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 5, 5, 1, (r));
	bdmf_session_print(session, "\tpriority                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 5, 4, 1, (r));
	bdmf_session_print(session, "\tingress_cong             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 5, 3, 1, (r));
	bdmf_session_print(session, "\tabs                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 4, 14, 5, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 6, 0, 14, (r));
	bdmf_session_print(session, "\tpacket_length            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 7, 1, (r));
	bdmf_session_print(session, "\tdrop                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 6, 1, (r));
	bdmf_session_print(session, "\ttarget_mem_1             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 4, 2, (r));
	bdmf_session_print(session, "\tcong_state_stream        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 3, 1, (r));
	bdmf_session_print(session, "\tlan                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 8, 3, 8, (r));
	bdmf_session_print(session, "\tingress_port             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 8, 0, 19, (r));
	bdmf_session_print(session, "\tunion3                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 12, 7, 1, (r));
	bdmf_session_print(session, "\tagg_pd                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 12, 6, 1, (r));
	bdmf_session_print(session, "\ttarget_mem_0             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 12, 0, 30, (r));
	bdmf_session_print(session, "\tpayload_offset_sop       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SCHEDULING_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SCHEDULING_QUEUE_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\trate_limit_enable        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\tblock_type               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 5, 1, (r));
	bdmf_session_print(session, "\tprefetch_pd              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 4, 1, (r));
	bdmf_session_print(session, "\tenable                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p), 6, 6, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 0, 6, (r));
	bdmf_session_print(session, "\tbbh_queue_index          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tscheduler_index          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tqueue_bit_mask           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\trate_limiter_index       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 5, (r));
	bdmf_session_print(session, "\tquantum_number           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tdeficit_counter          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_BASIC_SCHEDULER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register BASIC_SCHEDULER_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\trate_limit_enable        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\tcomplex_scheduler_exists = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 4, 2, (r));
	bdmf_session_print(session, "\tdwrr_offset              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 4, (r));
	bdmf_session_print(session, "\tparent_index_2           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tslot_budget_bit_vector   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 3, 5, (r));
	bdmf_session_print(session, "\tparent_index_1           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 0, 3, (r));
	bdmf_session_print(session, "\tlast_served_queue        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tstatus_bit_vector        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\trate_limiter_index       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 5, (r));
	bdmf_session_print(session, "\tquantum_number           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tdeficit_counter          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tqueue_index              =\n\t");
	for (i=0,j=0; i<8; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 8, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_PACKET_BUFFER(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register PACKET_BUFFER\n");

	bdmf_session_print(session, "\tpacket_header            =\n\t");
	for (i=0,j=0; i<112; i++)
	{
		MREAD_I_8((uint8_t *)(p), i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tpd                       =\n\t");
	for (i=0,j=0; i<16; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 112, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tparser_result            =\n\t");
	for (i=0,j=0; i<104; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 128, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tscratch                  =\n\t");
	for (i=0,j=0; i<104; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 232, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tresolution_context       =\n\t");
	for (i=0,j=0; i<16; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 336, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tclassification_results   =\n\t");
	for (i=0,j=0; i<7; i++)
	{
		MREAD_I_32((uint8_t *)(p) + 352, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\treserved                 =\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 380, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tclassification_contexts_list=\n\t");
	for (i=0,j=0; i<128; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 384, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_LAYER2_GRE_TUNNEL_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register LAYER2_GRE_TUNNEL_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tsrc_ip                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tdst_ip                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\tidentification           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tdst_mac1_4               =\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 16, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tdst_mac5_6               =\n\t");
	for (i=0,j=0; i<2; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 20, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tsrc_mac1_2               =\n\t");
	for (i=0,j=0; i<2; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 22, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tsrc_mac3_6               =\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 24, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_COMPLEX_SCHEDULER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register COMPLEX_SCHEDULER_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\tis_positive_budget       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 6, (r));
	bdmf_session_print(session, "\tbbh_queue                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 7, 1, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 0, 7, (r));
	bdmf_session_print(session, "\trate_limiter_index       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 5, 3, (r));
	bdmf_session_print(session, "\tdwrr_offset_pir          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 2, 3, (r));
	bdmf_session_print(session, "\tdwrr_offset_sir          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 2, 5, 5, (r));
	bdmf_session_print(session, "\tlast_served_block_pir    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 0, 5, (r));
	bdmf_session_print(session, "\tlast_served_block_sir    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tstatus_bit_vector        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tslot_budget_bit_vector_0 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tslot_budget_bit_vector_1 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tis_scheduler_slot        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tis_scheduler_basic       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 24, 7, 1, (r));
	bdmf_session_print(session, "\tovl_rl_en                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 24, 6, 1, (r));
	bdmf_session_print(session, "\trate_limit_enable        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 24, 5, 1, (r));
	bdmf_session_print(session, "\tparent_scheduler_exists  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 24, 1, 4, (r));
	bdmf_session_print(session, "\tparent_scheduler_index   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 24, 4, 5, (r));
	bdmf_session_print(session, "\tparent_scheduler_slot_index= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 25, 0, 4, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 26, (r));
	bdmf_session_print(session, "\tdeficit_counter          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tquantum_number           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\treserved3                =\n\t");
	for (i=0,j=0; i<3; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 29, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tblock_index              =\n\t");
	for (i=0,j=0; i<32; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 32, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_VPORT_CFG_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register VPORT_CFG_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tloopback_en              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\tmirroring_en             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 5, 1, (r));
	bdmf_session_print(session, "\tsa_lookup_en             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 4, 1, (r));
	bdmf_session_print(session, "\tda_lookup_en             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 3, 1, (r));
	bdmf_session_print(session, "\tegress_isolation_en      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 2, 1, (r));
	bdmf_session_print(session, "\tingress_isolation_en     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 1, 1, (r)) /*defined by rdd_bridge_and_vlan_ctx_ingress_lookup_method enumeration*/;
	bdmf_session_print(session, "\tbridge_and_vlan_ingress_lookup_method= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 1, (r)) /*defined by rdd_bridge_and_vlan_ctx_egress_lookup_method enumeration*/;
	bdmf_session_print(session, "\tbridge_and_vlan_egress_lookup_method= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 4, 4, (r));
	bdmf_session_print(session, "\tprotocol_filters_dis     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 2, 2, (r)) /*defined by rdd_action enumeration*/;
	bdmf_session_print(session, "\tsa_lookup_miss_action    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 0, 2, (r)) /*defined by rdd_action enumeration*/;
	bdmf_session_print(session, "\tda_lookup_miss_action    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 7, 1, (r));
	bdmf_session_print(session, "\tcongestion_flow_control  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 6, 1, (r));
	bdmf_session_print(session, "\tdiscard_prty             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 0, 6, (r));
	bdmf_session_print(session, "\tingress_filter_profile   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 7, 1, (r));
	bdmf_session_print(session, "\tmcast_whitelist_skip     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 6, 1, (r));
	bdmf_session_print(session, "\tdos_attack_detection_disable= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 4, 2, (r));
	bdmf_session_print(session, "\treserved3                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 1, 3, (r));
	bdmf_session_print(session, "\tnatc_tbl_id              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 0, 1, (r));
	bdmf_session_print(session, "\tls_fc_cfg                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tegress_isolation_map     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_TM_FLOW_CNTR_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register TM_FLOW_CNTR_ENTRY\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tcntr_id                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_TX_FLOW_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register TX_FLOW_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tvalid                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 7, (r));
	bdmf_session_print(session, "\tqos_table_ptr            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_CBS_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register CBS_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tcommitted_burst_size     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_BYTE_1(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register BYTE_1\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tbits                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_BBH_TX_WAKE_UP_DATA_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register BBH_TX_WAKE_UP_DATA_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 3, 5, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p), 8, 19, (r));
	bdmf_session_print(session, "\tbytes_in_bbh             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tqueue                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SPDTEST_GEN_CFG(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SPDTEST_GEN_CFG\n");

	FIELD_MREAD_8((uint8_t *)(p), 4, 4, (r));
	bdmf_session_print(session, "\ttest_type                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 3, 1, (r));
	bdmf_session_print(session, "\tis_on                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 2, 1, (r));
	bdmf_session_print(session, "\tis_endless_tx            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 1, 1, (r));
	bdmf_session_print(session, "\tnot_valid_license        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 1, (r));
	bdmf_session_print(session, "\tiperf3_64bit_pktid       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 0, 0, 24, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_RX_FLOW_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register RX_FLOW_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 3, 5, (r));
	bdmf_session_print(session, "\tvirtual_port             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 2, 1, (r));
	bdmf_session_print(session, "\tflow_dest                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 1, 1, (r));
	bdmf_session_print(session, "\texception                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 1, (r));
	bdmf_session_print(session, "\tis_lan                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tcntr_id                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_BYTES_4(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register BYTES_4\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tbits                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_FLUSH_CFG_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register FLUSH_CFG_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tenable                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\tdrain_q                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 5, 1, (r));
	bdmf_session_print(session, "\thw_flush_en              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 5, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tpd_num                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tflush_aggr               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tqm_queue                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_HW_IPTV_CONFIGURATION(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register HW_IPTV_CONFIGURATION\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tfpm_base_token_size      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 7, 1, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 0, 7, (r));
	bdmf_session_print(session, "\thn_size1                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 7, 1, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 0, 7, (r));
	bdmf_session_print(session, "\thn_size0                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 3, 5, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 4, 0, 11, (r));
	bdmf_session_print(session, "\tddr_sop_offset0          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 6, 3, 5, (r));
	bdmf_session_print(session, "\treserved3                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 6, 0, 11, (r));
	bdmf_session_print(session, "\tddr_sop_offset1          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SPDSVC_ANALYZER_PARAMS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SPDSVC_ANALYZER_PARAMS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tstream                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tstream1                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tstream2                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tstream3                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_BASIC_RATE_LIMITER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register BASIC_RATE_LIMITER_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\trl_type                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p), 10, 21, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 0, 2, (r));
	bdmf_session_print(session, "\tblock_type               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tblock_index              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tcurrent_budget           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 8, 2, 14, (r));
	bdmf_session_print(session, "\talloc_mantissa           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 9, 0, 2, (r));
	bdmf_session_print(session, "\talloc_exponent           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 10, 2, 14, (r));
	bdmf_session_print(session, "\tlimit_mantissa           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 11, 0, 2, (r));
	bdmf_session_print(session, "\tlimit_exponent           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_FW_POLICER_BUDGET_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register FW_POLICER_BUDGET_ENTRY\n");

	FIELD_MREAD_16((uint8_t *)(p), 2, 14, (r));
	bdmf_session_print(session, "\tbudget_mantissa          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 0, 2, (r));
	bdmf_session_print(session, "\tbudget_exponent          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_INGRESS_FILTER_CTRL(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register INGRESS_FILTER_CTRL\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p), 0, 31, (r));
	bdmf_session_print(session, "\tenable_vector            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 7, 1, (r));
	bdmf_session_print(session, "\tcpu_bypass               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 4, 0, 31, (r));
	bdmf_session_print(session, "\taction_vector            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_VPORT_CFG_EX_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register VPORT_CFG_EX_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tloopback_en              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\tmirroring_en             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 6, (r));
	bdmf_session_print(session, "\tingress_filter_profile   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 5, 3, (r));
	bdmf_session_print(session, "\tport_mac_addr_idx        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 2, 3, (r));
	bdmf_session_print(session, "\temac_idx                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 1, 1, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 0, 13, 4, (r));
	bdmf_session_print(session, "\tviq                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 4, 1, (r));
	bdmf_session_print(session, "\trate_limit_unknown_da    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 3, 1, (r));
	bdmf_session_print(session, "\trate_limit_broadcast     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 2, 1, (r));
	bdmf_session_print(session, "\trate_limit_multicast     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 1, 1, (r));
	bdmf_session_print(session, "\trate_limit_all_traffic   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 0, 1, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 7, 1, (r));
	bdmf_session_print(session, "\tport_dbg_stat_en         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 3, 0, 7, (r));
	bdmf_session_print(session, "\tpolicer_idx              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_BYTES_2(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register BYTES_2\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tbits                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_QUEUE_DYNAMIC_MNG_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register QUEUE_DYNAMIC_MNG_ENTRY\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tqm_queue_us_start        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tqm_queue_us_end          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tqm_queue_ds_start        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tqm_queue_ds_end          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tqm_queue_epon_start      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 5, (r));
	bdmf_session_print(session, "\tqm_queue_sq_start        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DEF_FLOW_CONTEXT_DDR_ADDR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DEF_FLOW_CONTEXT_DDR_ADDR\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tlow                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\thigh                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_NATC_TBL_CONFIGURATION(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register NATC_TBL_CONFIGURATION\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tkey_addr_low             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tkey_addr_high            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tres_addr_low             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tres_addr_high            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 16, 1, 7, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 16, 0, 1, (r));
	bdmf_session_print(session, "\tmiss_cache_enable        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 17, (r));
	bdmf_session_print(session, "\tkey_size                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 18, (r));
	bdmf_session_print(session, "\tcontext_size             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 19, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\treserved1                =\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 20, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_FPM_POOL_NUMBER(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register FPM_POOL_NUMBER\n");

	FIELD_MREAD_8((uint8_t *)(p), 2, 6, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 2, (r));
	bdmf_session_print(session, "\tpool_number              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_UPDATE_FIFO_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register UPDATE_FIFO_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tvalid                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p), 0, 14, (r));
	bdmf_session_print(session, "\tpd_fifo_write_ptr        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 2, 1, 7, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 2, 0, 9, (r));
	bdmf_session_print(session, "\tqueue_number             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_EMAC_FLOW_CTRL_BUDGET_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register EMAC_FLOW_CTRL_BUDGET_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tbudget                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_BYTES_8(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register BYTES_8\n");

	bdmf_session_print(session, "\tbits                     =\n\t");
	for (i=0,j=0; i<2; i++)
	{
		MREAD_I_32((uint8_t *)(p), i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_BBH_QUEUE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register BBH_QUEUE_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 2, 6, (r));
	bdmf_session_print(session, "\thw_bbh_qid               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 1, 1, (r));
	bdmf_session_print(session, "\tmirroring_en             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 1, (r));
	bdmf_session_print(session, "\tpriority                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 1, 7, (r));
	bdmf_session_print(session, "\tscheduler_index          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 0, 1, (r));
	bdmf_session_print(session, "\tscheduler_type           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tbb_destination           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tingress_counter          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_MIRRORING_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register MIRRORING_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tmirror_en                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 1, 6, (r));
	bdmf_session_print(session, "\tdst_vport                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p), 0, 9, (r));
	bdmf_session_print(session, "\tdst_queue                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_CPU_REDIRECT_MODE_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register CPU_REDIRECT_MODE_ENTRY\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tmode                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_IPTV_CLASSIFICATION_CFG_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register IPTV_CLASSIFICATION_CFG_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tda_prefix_mode_mac       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 6, 1, (r));
	bdmf_session_print(session, "\tda_prefix_mode_ip        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 5, 1, (r));
	bdmf_session_print(session, "\tiptv_en                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 5, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SYSTEM_CONFIGURATION_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SYSTEM_CONFIGURATION_ENTRY\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tds_drop_precedence_eligibility_vector= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tus_drop_precedence_eligibility_vector= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 7, 1, (r));
	bdmf_session_print(session, "\tfull_flow_cache_mode     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 6, 1, (r));
	bdmf_session_print(session, "\tl2_flow_cache_mode       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 5, 1, (r));
	bdmf_session_print(session, "\tiptv_lookup_miss_action  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 4, 1, (r));
	bdmf_session_print(session, "\tcongestion_ctrl          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 1, 3, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 0, 1, (r));
	bdmf_session_print(session, "\ttcp_pure_ack_flows       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SPDSVC_BBH_TX_PARAMS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SPDSVC_BBH_TX_PARAMS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tprocessing_tx_pd_3       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tspdsvc_sent              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tspdsvc_bbh_id            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_FPM_GLOBAL_CFG(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register FPM_GLOBAL_CFG\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tfpm_base_low             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tfpm_base_high            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tfpm_token_size           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\tfpm_token_shift          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 11, (r));
	bdmf_session_print(session, "\tfpm_token_add_shift      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tfpm_token_inv_mant       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 14, (r));
	bdmf_session_print(session, "\tfpm_token_inv_exp        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 15, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_TCAM_IC_CFG(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register TCAM_IC_CFG\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tres_offset               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tcontext_offset           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\treserve_2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tscratch_offset           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 5, 3, (r));
	bdmf_session_print(session, "\ttable_id                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 8, 0, 13, (r));
	bdmf_session_print(session, "\tkey_size                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tclassification_result    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_CPU_RING_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register CPU_RING_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 3, 5, (r));
	bdmf_session_print(session, "\tsize_of_entry            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p), 0, 11, (r));
	bdmf_session_print(session, "\tnumber_of_entries        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tinterrupt_id             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tdrop_counter             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\twrite_idx                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tbase_addr_low            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tread_idx                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 14, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 15, (r));
	bdmf_session_print(session, "\tbase_addr_high           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DEBUG_PRINT_INFO(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DEBUG_PRINT_INFO\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\taddr_low                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\taddr_high                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tsize                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\ttable_id                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 12, 0, 24, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_TUNNELS_PARSING_CFG(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register TUNNELS_PARSING_CFG\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\ttunneling_enable         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tres_offset               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_IPTV_CFG(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register IPTV_CFG\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tres_offset               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tcontext_offset           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tkey_offset               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\thash_tbl_idx             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 7, (r));
	bdmf_session_print(session, "\tl2_mcast                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_IPTV_DDR_CTX_TABLE_ADDRESS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register IPTV_DDR_CTX_TABLE_ADDRESS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tlow                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\thigh                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_MULTICAST_KEY_MASK_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register MULTICAST_KEY_MASK_ENTRY\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tvlan_mask                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tetype_mask               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_NAT_CACHE_CFG(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register NAT_CACHE_CFG\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tres_offset               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tcontext_offset           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tkey_offset               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 6, 3, 5, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 6, 2, 1, (r));
	bdmf_session_print(session, "\tthree_tuple_enable       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 6, 1, 1, (r));
	bdmf_session_print(session, "\tesp_filter_action        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 6, 0, 1, (r));
	bdmf_session_print(session, "\tesp_filter_enable        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_FLUSH_CFG_ENABLE_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register FLUSH_CFG_ENABLE_ENTRY\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tenable_fw                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tenable_cpu               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_INGRESS_FILTER_CFG(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register INGRESS_FILTER_CFG\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tres_offset               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_FC_FLOW_IP_ADDRESSES_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register FC_FLOW_IP_ADDRESSES_ENTRY\n");

	bdmf_session_print(session, "\tsa_da_addresses          =\n\t");
	for (i=0,j=0; i<32; i++)
	{
		MREAD_I_8((uint8_t *)(p), i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\treserved0                =\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 32, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\treference_count          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\treserved1                =\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 40, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	MREAD_32((uint8_t *)(p) + 44, (r));
	bdmf_session_print(session, "\tis_ipv6_address          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_TRACE_EVENT(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register TRACE_EVENT\n");

	FIELD_MREAD_16((uint8_t *)(p), 4, 12, (r));
	bdmf_session_print(session, "\ttimestamp                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 2, 2, (r));
	bdmf_session_print(session, "\tevent_id                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 0, 0, 18, (r));
	bdmf_session_print(session, "\ttrace_event_info         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_COMPLETE_COMMON_RADIO_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register DHD_COMPLETE_COMMON_RADIO_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\trx_complete_fr_base_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\trx_complete_fr_base_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\trx_complete_fr_rd_idx_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\trx_complete_fr_rd_idx_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\trx_complete_fr_wr_idx_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\trx_complete_fr_wr_idx_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\ttx_complete_fr_base_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\ttx_complete_fr_base_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\ttx_complete_fr_rd_idx_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\ttx_complete_fr_rd_idx_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 40, (r));
	bdmf_session_print(session, "\ttx_complete_fr_wr_idx_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 44, (r));
	bdmf_session_print(session, "\ttx_complete_fr_wr_idx_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 48, (r));
	bdmf_session_print(session, "\trx_post_fr_base_ptr_low  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 52, (r));
	bdmf_session_print(session, "\trx_post_fr_base_ptr_high = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 56, (r));
	bdmf_session_print(session, "\trx_post_fr_rd_idx_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 60, (r));
	bdmf_session_print(session, "\trx_post_fr_rd_idx_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 64, (r));
	bdmf_session_print(session, "\trx_post_fr_wr_idx_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 68, (r));
	bdmf_session_print(session, "\trx_post_fr_wr_idx_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 72, (r));
	bdmf_session_print(session, "\tdhd_doorbell_low         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 76, (r));
	bdmf_session_print(session, "\tdhd_doorbell_high        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 80, (r));
	bdmf_session_print(session, "\trx_complete_rd_idx       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 82, (r));
	bdmf_session_print(session, "\trx_complete_wr_idx       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 84, (r));
	bdmf_session_print(session, "\trx_complete_wr_idx_rsrv  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 86, (r));
	bdmf_session_print(session, "\ttx_complete_rd_idx       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 88, (r));
	bdmf_session_print(session, "\ttx_complete_wr_idx       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 90, (r));
	bdmf_session_print(session, "\ttx_complete_wr_idx_rsrv  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 92, (r));
	bdmf_session_print(session, "\trx_post_wr_idx           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 94, (r));
	bdmf_session_print(session, "\trx_post_wr_idx_rsrv      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 96, 5, 3, (r));
	bdmf_session_print(session, "\tflow_ring_format         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 96, 4, 1, (r));
	bdmf_session_print(session, "\tidma_active              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 96, 0, 4, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 97, (r));
	bdmf_session_print(session, "\tidma_group_shift         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 98, (r));
	bdmf_session_print(session, "\tidma_last_group_fr       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 100, (r));
	bdmf_session_print(session, "\tfr_ptrs_size_shift       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\treserved1                =\n\t");
	for (i=0,j=0; i<3; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 101, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tscratchpad               =\n\t");
	for (i=0,j=0; i<3; i++)
	{
		MREAD_I_32((uint8_t *)(p) + 104, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\treserved2                =\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 116, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_PROCESSING_RX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PROCESSING_RX_DESCRIPTOR\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tpd_info                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 4, 6, 10, (r));
	bdmf_session_print(session, "\tserial_num               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 5, 5, 1, (r));
	bdmf_session_print(session, "\tploam                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 5, 4, 1, (r));
	bdmf_session_print(session, "\tingress_cong             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 5, 3, 1, (r));
	bdmf_session_print(session, "\tabs_or_dsl               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 5, 2, 1, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 4, 14, 4, (r));
	bdmf_session_print(session, "\terror_type_or_cpu_tx     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 6, 0, 14, (r));
	bdmf_session_print(session, "\tpacket_length            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 7, 1, (r));
	bdmf_session_print(session, "\terror                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 6, 1, (r));
	bdmf_session_print(session, "\ttarget_mem_1             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 4, 2, (r));
	bdmf_session_print(session, "\tcong_state               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 3, 1, (r));
	bdmf_session_print(session, "\tlan                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 8, 3, 8, (r));
	bdmf_session_print(session, "\tingress_port             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 8, 0, 19, (r));
	bdmf_session_print(session, "\tbn1_last_or_abs1         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 12, 7, 1, (r));
	bdmf_session_print(session, "\tagg_pd                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 12, 6, 1, (r));
	bdmf_session_print(session, "\ttarget_mem_0             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 12, 0, 30, (r));
	bdmf_session_print(session, "\tpayload_offset_sop       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_RX_COMPLETE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_RX_COMPLETE_DESCRIPTOR\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tmsg_type                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tif_id                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tcommon_hdr_flags         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tepoch                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\trequest_id               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tcompl_msg_hdr_status     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\tflow_ring_id             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tmeta_buf_len             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 14, (r));
	bdmf_session_print(session, "\tdata_len                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tdata_offset              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 18, (r));
	bdmf_session_print(session, "\tflags                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\trx_status_0              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\trx_status_1              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tdma_done_mark            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_RX_POST_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_RX_POST_DESCRIPTOR\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tmsg_type                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tif_id                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tcommon_hdr_flags         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tepoch                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\trequest_id               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tmeta_buf_len             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\tdata_len                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tmetadata_buf_addr_low    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tmetadata_buf_addr_hi     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tdata_buf_addr_low        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tdata_buf_addr_hi         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_TX_COMPLETE_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_TX_COMPLETE_DESCRIPTOR\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tmsg_type                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tif_id                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tcommon_hdr_flags         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tepoch                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\trequest_id               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tstatus                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\tflow_ring_id             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tdma_done_mark            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_HW_CONFIGURATION(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_HW_CONFIGURATION\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\taggr_timer_period        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 4, 3, 5, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 4, 0, 11, (r));
	bdmf_session_print(session, "\tddr_sop_offset           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\trx_post_fpm_pool         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 7, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tfpm_thresholds_low       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\tfpm_thresholds_high      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tfpm_thresholds_excl      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 14, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_OVERALL_RATE_LIMITER_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register OVERALL_RATE_LIMITER_DESCRIPTOR\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tbbh_queue_en_vec         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tcurrent_budget           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 8, 2, 14, (r));
	bdmf_session_print(session, "\talloc_mantissa           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 9, 0, 2, (r));
	bdmf_session_print(session, "\talloc_exponent           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 10, 2, 14, (r));
	bdmf_session_print(session, "\tlimit_mantissa           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 11, 0, 2, (r));
	bdmf_session_print(session, "\tlimit_exponent           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_RING_SIZE(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_RING_SIZE\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tvalue                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_DOORBELL(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_DOORBELL\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tdoorbell_value           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DDR_ADDRESS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DDR_ADDRESS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tlow                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\thigh                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_MAC_TYPE_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register MAC_TYPE_ENTRY\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\ttype                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SPDSVC_WLAN_GEN_PARAMS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SPDSVC_WLAN_GEN_PARAMS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tcomplete_tracked         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\ttx_copies                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tspdsvc_free_idx          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_CPU_TX_DBG_CNTRS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register CPU_TX_DBG_CNTRS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tSBPM_NO_NEXT             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tSBPM_NO_FIRST            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tTX_FLOW_DISABLE          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tNO_FPM                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tTASK_EXIT                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tSYNC_WAIT                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tNO_DISPATCHER_SCHEDULER  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tRECYCLE_FIFO_FULL        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\tDROP_PKT                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\tTASK_START               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 40, (r));
	bdmf_session_print(session, "\tNO_FWD                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\treserved                 =\n\t");
	for (i=0,j=0; i<5; i++)
	{
		MREAD_I_32((uint8_t *)(p) + 44, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_CPU_INTERRUPT_COALESCING_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register CPU_INTERRUPT_COALESCING_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\ttimer_period             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tnot_empty_or_int_vec     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tscratch                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\trecycle_timer_cnt        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 14, (r));
	bdmf_session_print(session, "\trecycle_timer_factor     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_RING_CPU_TX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register RING_CPU_TX_DESCRIPTOR\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tis_egress                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p), 6, 9, (r));
	bdmf_session_print(session, "\tfirst_level_q            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 0, 8, 14, (r));
	bdmf_session_print(session, "\tpacket_length            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tsk_buf_ptr_high          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tsk_buf_ptr_low_or_data_1588= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 7, 1, (r));
	bdmf_session_print(session, "\tcolor                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 6, 1, (r));
	bdmf_session_print(session, "\tdo_not_recycle           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 5, 1, (r));
	bdmf_session_print(session, "\tflag_1588                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 8, 4, 1, (r));
	bdmf_session_print(session, "\tlan                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 8, 4, 8, (r));
	bdmf_session_print(session, "\twan_flow_source_port_union= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 9, 3, 1, (r));
	bdmf_session_print(session, "\tfpm_fallback             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 9, 2, 1, (r));
	bdmf_session_print(session, "\tsbpm_copy                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 9, 1, 1, (r));
	bdmf_session_print(session, "\ttarget_mem_0             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 9, 0, 1, (r));
	bdmf_session_print(session, "\tabs                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 10, 6, 2, (r));
	bdmf_session_print(session, "\tlag_index                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 10, 2, 4, (r));
	bdmf_session_print(session, "\tssid                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 10, 1, 1, (r));
	bdmf_session_print(session, "\tegress_dont_drop         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 10, 0, 1, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 11, (r));
	bdmf_session_print(session, "\tpkt_buf_ptr_high         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tpkt_buf_ptr_low_or_fpm_bn0= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_CPU_TX_SYNC_FIFO_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register CPU_TX_SYNC_FIFO_ENTRY\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\twrite_ptr                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tread_ptr                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tfifo                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_CPU_RING_INTERRUPT_COUNTER_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register CPU_RING_INTERRUPT_COUNTER_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tcounter                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tmax_size                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_CPU_TX_RING_INDICES(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register CPU_TX_RING_INDICES\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tread_idx                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\twrite_idx                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_PKTGEN_TX_STREAM_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PKTGEN_TX_STREAM_ENTRY\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_size         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_offset       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_reserved     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_1        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_2        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_3        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_4        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_5        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_6        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_7        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 40, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_8        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 44, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_9        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 48, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_10       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 52, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_11       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 56, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_12       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 60, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_13       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 64, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_14       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 68, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_15       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 72, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_16       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 76, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_17       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 80, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_18       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 84, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_19       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 88, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_20       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 92, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_21       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 96, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_22       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 100, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_23       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 104, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_24       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 108, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_25       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 112, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_26       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 116, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_27       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 120, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_28       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 124, (r));
	bdmf_session_print(session, "\tREF_PKT_HDR_hdr_29       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 128, (r));
	bdmf_session_print(session, "\tENTRY_PARMS_wan_flow     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 130, (r));
	bdmf_session_print(session, "\tENTRY_PARMS_tx_qm_queue  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 132, (r));
	bdmf_session_print(session, "\tENTRY_PARMS_tcp_udp_parms= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_TCPSPDTEST_STREAM(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register TCPSPDTEST_STREAM\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_CONN_INFO_cpu_rx_rdd_queue= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_CONN_INFO_up_pppoe_hdr_ofs= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_CONN_INFO_up_peer_rx_scale= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_CONN_INFO_sack_permitted= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_CONN_INFO_up_tx_mss= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_CONN_INFO_up_tx_max_pd_len= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_rx_pkts= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_txed_pkts= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_freed_pkts= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_ack_seq= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_tx_seq= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_bad_pkts= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_bad_bytes= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_bad_bytes_1= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 40, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_rx_bytes= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 44, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_rx_bytes_1= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 48, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_expected_bytes= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 52, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_expected_bytes_1= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 56, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_to_send_bytes= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 60, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_to_send_bytes_1= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 64, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_no_credits= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 68, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_cwnd= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 72, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_cwnd_thr= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 76, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_cwnd_budget= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 80, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_last_ack_seq= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 84, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_last_ack_time= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 88, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_dup_ack_cnt= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 92, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_dup_ack_seq_done= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 96, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_dup_ack_total_pkts_cnt= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 98, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_fast_retrans_cnt= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 100, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_reserved1= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 102, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_dup_ack_state= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 103, 3, 5, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_reserved2= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 103, 2, 1, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_is_rx_win_stop= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 103, 1, 1, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_is_timeout= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 103, 0, 1, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_TCB_up_is_active= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 104, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_PKT_DROP_is_drop= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 105, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_PKT_DROP_is_win_full= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 106, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_PKT_DROP_num_errs= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 108, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_PKT_DROP_wr_ofs= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 110, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_PKT_DROP_rd_ofs= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_PKT_DROP_seq=\n\t");
	for (i=0,j=0; i<32; i++)
	{
		MREAD_I_32((uint8_t *)(p) + 112, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	MREAD_32((uint8_t *)(p) + 240, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_tx_seq_addr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 244, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_tx_seq_addr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 248, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_tx_seq_send_cnt= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 252, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_tx_seq_drop_cnt= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 256, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_retrans_addr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 260, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_retrans_addr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 264, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_retrans_receive_cnt= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 268, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_scratchpad_metadata_wr_ofs= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 270, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_reserved1= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 272, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_tx_seq_coalescing_timeout_cnt= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 276, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_tx_seq_coalescing_fill_pkt_cnt= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 280, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_tx_seq_coalescing_last_time= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 284, (r));
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_reserved2= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_scratchpad=\n\t");
	for (i=0,j=0; i<8; i++)
	{
		MREAD_I_32((uint8_t *)(p) + 288, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tTCPSPDTEST_ENGINE_RTO_ring_scratchpad_metadata=\n\t");
	for (i=0,j=0; i<16; i++)
	{
		MREAD_I_32((uint8_t *)(p) + 320, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_CPU_RX_METER_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register CPU_RX_METER_ENTRY\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tcurrent_budget           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tbudget_limit             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tallocated_budget         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tbudget_residue           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 7, (r));
	bdmf_session_print(session, "\tcurrent_cycle            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_CSO_CONTEXT_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register CSO_CONTEXT_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tcsum_value               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tcam_result               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tcrc_result               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tsaved_pkt_desc_0         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tsaved_pkt_desc_1         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tsaved_pkt_desc_2         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tsaved_pkt_desc_3         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tparser_result            =\n\t");
	for (i=0,j=0; i<24; i++)
	{
		MREAD_I_32((uint8_t *)(p) + 32, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	MREAD_32((uint8_t *)(p) + 128, (r));
	bdmf_session_print(session, "\tsaved_ret_address        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 132, (r));
	bdmf_session_print(session, "\tgood_csum_packets        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 136, (r));
	bdmf_session_print(session, "\tno_cso_support_packets   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 140, (r));
	bdmf_session_print(session, "\tbad_ipv4_hdr_csum_packets= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 144, (r));
	bdmf_session_print(session, "\tbad_tcp_udp_csum_packets = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 148, (r));
	bdmf_session_print(session, "\tsaved_buffer_number      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 150, (r));
	bdmf_session_print(session, "\tsaved_packet_length      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_UDPSPDT_STREAM_RX_STAT(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register UDPSPDT_STREAM_RX_STAT\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\trx_bytes_0               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\trx_bytes_1               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\trx_packets_0             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\trx_packets_1             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tts_first                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tts_last_0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tts_last_1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 28, 7, 1, (r));
	bdmf_session_print(session, "\tts_first_set             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 28, 0, 15, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 30, (r));
	bdmf_session_print(session, "\tbad_proto_cntr           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\tiperf3_rx_packet_lost_0  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\tiperf3_rx_packet_lost_1  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 40, (r));
	bdmf_session_print(session, "\tiperf3_rx_out_of_order_0 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 44, (r));
	bdmf_session_print(session, "\tiperf3_rx_out_of_order_1 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SPDSVC_GEN_PARAMS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SPDSVC_GEN_PARAMS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tprocessing_tx_pd_0       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tprocessing_tx_pd_1       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\treserved3                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tprocessing_tx_pd_2       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tprocessing_tx_pd_3       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\ttotal_copies             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\tbucket                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 40, (r));
	bdmf_session_print(session, "\ttimer_period             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 42, (r));
	bdmf_session_print(session, "\ttotal_length             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 44, (r));
	bdmf_session_print(session, "\ttx_packets               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 48, (r));
	bdmf_session_print(session, "\ttx_dropped               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 52, (r));
	bdmf_session_print(session, "\ttokens                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 56, (r));
	bdmf_session_print(session, "\tbucket_size              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_UDPSPDT_STREAM_TX_STAT(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register UDPSPDT_STREAM_TX_STAT\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\ttx_packets_1             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\ttx_packets_0             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\ttx_drops_no_spbm         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tfirst_ts                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tlast_ts_1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tlast_ts_0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tiperf3_ts_sec            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tiperf3_ts_usec           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\tbad_proto_cntr           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 34, (r));
	bdmf_session_print(session, "\ttime_slice_expire        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\ttx_drops_no_sbpm_timer_stop= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 38, 1, 15, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 39, 0, 1, (r));
	bdmf_session_print(session, "\tfirst_ts_set             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_TX_ABS_RECYCLE_COUNTERS_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register TX_ABS_RECYCLE_COUNTERS_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\ttotal                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tspdsvc                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_UDPSPDT_TX_PARAMS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register UDPSPDT_TX_PARAMS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\ttotal_num_of_pkts        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tpacket_size              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tcurr_bucket              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tbucket_budget            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tmax_bucket_size          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_TCPSPDTEST_ENGINE_GLOBAL_INFO(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register TCPSPDTEST_ENGINE_GLOBAL_INFO\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tnum_streams              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tnum_bns                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tstream_vector            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tup_bucket_tokens         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tup_bucket_full_tokens    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tup_bucket_tokens_fill_rate= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 18, (r));
	bdmf_session_print(session, "\tup_next_stream_id        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 19, 1, 7, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 19, 0, 1, (r));
	bdmf_session_print(session, "\tup_is_timer_active       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_PKTGEN_SBPM_HDR_BN(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PKTGEN_SBPM_HDR_BN\n");

	FIELD_MREAD_16((uint8_t *)(p), 2, 14, (r));
	bdmf_session_print(session, "\tfirst_bn                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 1, 0, 2, (r));
	bdmf_session_print(session, "\text_idx                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SPDSVC_RX_TS_STAT(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SPDSVC_RX_TS_STAT\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tts_first                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tts_last                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 8, 1, 31, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 11, 0, 1, (r));
	bdmf_session_print(session, "\tts_first_set             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_SPDSVC_TCPSPDTEST_COMMON_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SPDSVC_TCPSPDTEST_COMMON_ENTRY\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tspdsvc_task_owner        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tcpu_rx_copy_is_tcpspdtest_timeout_wakeup= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_PKTGEN_TX_PARAMS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PKTGEN_TX_PARAMS\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tbbmsg_sbpm_mcast_inc_req_0= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tbbmsg_sbpm_mcast_inc_req_1= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tref_pd_0                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tref_pd_1                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tref_pd_2                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\tref_pd_3                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 24, 4, 4, (r));
	bdmf_session_print(session, "\ttask_num                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 24, 0, 28, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 30, (r));
	bdmf_session_print(session, "\tbad_tx_num_of_bns        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_PKTGEN_FPM_UG_MGMT_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PKTGEN_FPM_UG_MGMT_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tfpm_ug_cnt_dummy         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tfpm_ug_cnt               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tfpm_ug_cnt_reg_addr      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 12, 4, 28, (r));
	bdmf_session_print(session, "\tfpm_ug_threshold         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 15, 0, 4, (r));
	bdmf_session_print(session, "\tfpm_tokens_quantum       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\tbudget                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_PKTGEN_SBPM_EXT(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PKTGEN_SBPM_EXT\n");

	FIELD_MREAD_16((uint8_t *)(p), 2, 14, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_32((uint8_t *)(p) + 0, 14, 4, (r));
	bdmf_session_print(session, "\tnum_of_bns               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 2, 0, 14, (r));
	bdmf_session_print(session, "\tbn1                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_PKTGEN_TX_STREAM_SCRATCH_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PKTGEN_TX_STREAM_SCRATCH_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tcsum_value               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_FLOW_RING_CACHE_CTX_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_FLOW_RING_CACHE_CTX_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tflow_ring_base_low       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tflow_ring_base_high      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 5, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tshadow_wr_idx            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\tsize                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\tssid                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 11, (r));
	bdmf_session_print(session, "\tflags                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\trd_idx                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 14, (r));
	bdmf_session_print(session, "\twr_idx                   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_AUX_INFO_CACHE_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_AUX_INFO_CACHE_ENTRY\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tbackup_first_index       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tbackup_last_index        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tbackup_num_entries       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\tphy_size                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\twindow_ts                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 10, (r));
	bdmf_session_print(session, "\tdrop_interval            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\tcodel_control_word       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 14, (r));
	bdmf_session_print(session, "\tcodel_drop_counter       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_TX_POST_DESCRIPTOR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_TX_POST_DESCRIPTOR\n");

	MREAD_8((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tmsg_type                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 1, (r));
	bdmf_session_print(session, "\tif_id                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tcommon_hdr_flags         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 3, (r));
	bdmf_session_print(session, "\tepoch                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\trequest_id               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\ttx_eth_hdr_0             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\ttx_eth_hdr_1             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\ttx_eth_hdr_2             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\ttx_eth_hdr_3             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 22, (r));
	bdmf_session_print(session, "\tflags                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 23, (r));
	bdmf_session_print(session, "\tseg_cnt                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tmetadata_buf_addr_low    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tmetadata_buf_addr_hi     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\tdata_buf_addr_low        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\tdata_buf_addr_hi         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 40, (r));
	bdmf_session_print(session, "\tmeta_buf_len             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 42, (r));
	bdmf_session_print(session, "\tdata_len                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 44, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_WLAN_MCAST_DHD_STATION_CTX_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register WLAN_MCAST_DHD_STATION_CTX_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 4, 4, (r));
	bdmf_session_print(session, "\treserved0                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 0, 4, (r));
	bdmf_session_print(session, "\tssid                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_WLAN_MCAST_DHD_STATION_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register WLAN_MCAST_DHD_STATION_ENTRY\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tmac_address_high         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tmac_address_mid          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tmac_address_low          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 6, 6, 2, (r));
	bdmf_session_print(session, "\tradio_index              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 6, 5, 1, (r));
	bdmf_session_print(session, "\tvalid                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 6, 2, 3, (r));
	bdmf_session_print(session, "\ttx_priority              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 6, 0, 10, (r));
	bdmf_session_print(session, "\tflowring_index           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_POST_COMMON_RADIO_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register DHD_POST_COMMON_RADIO_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\ttx_post_mgmt_fr_base_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\ttx_post_mgmt_fr_base_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 8, (r));
	bdmf_session_print(session, "\ttx_post_fr_wr_idx_base_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 12, (r));
	bdmf_session_print(session, "\ttx_post_fr_wr_idx_base_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 16, (r));
	bdmf_session_print(session, "\ttx_post_fr_rd_idx_base_ptr_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 20, (r));
	bdmf_session_print(session, "\ttx_post_fr_rd_idx_base_ptr_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 24, (r));
	bdmf_session_print(session, "\tbackup_index_fifo_base_low= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 28, (r));
	bdmf_session_print(session, "\tbackup_index_fifo_base_high= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 32, (r));
	bdmf_session_print(session, "\tdhd_doorbell_low         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 36, (r));
	bdmf_session_print(session, "\tdhd_doorbell_high        = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 40, (r));
	bdmf_session_print(session, "\ttx_post_wr_idx           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 42, (r));
	bdmf_session_print(session, "\ttx_post_qd               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 44, (r));
	bdmf_session_print(session, "\ttx_post_rd_idx           = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 46, (r));
	bdmf_session_print(session, "\tidma_last_group_fr       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 48, (r));
	bdmf_session_print(session, "\tcam_rslt                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 52, 7, 1, (r));
	bdmf_session_print(session, "\tadd_llcsnap_header       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 52, 6, 1, (r));
	bdmf_session_print(session, "\taggregation_bypass_cpu_tx= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 52, 5, 1, (r));
	bdmf_session_print(session, "\taggregation_bypass_non_udp_tcp= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 52, 2, 3, (r));
	bdmf_session_print(session, "\tflow_ring_format         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 52, 1, 1, (r));
	bdmf_session_print(session, "\tidma_active              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 52, 0, 1, (r));
	bdmf_session_print(session, "\tcodel_active             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 53, (r));
	bdmf_session_print(session, "\taggregation_bypass_tcp_pktlen= 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 54, (r));
	bdmf_session_print(session, "\tcache_ctx_next_write_idx = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 55, (r));
	bdmf_session_print(session, "\tbackup_cache_idx         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tper_ac_aggregation_thresholds=\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 56, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tper_ac_aggregation_timeouts=\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 60, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\tper_ac_aggregation_timeout_cntrs=\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 64, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	MREAD_32((uint8_t *)(p) + 68, (r));
	bdmf_session_print(session, "\tdoorbell_value_address   = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tscratchpad               =\n\t");
	for (i=0,j=0; i<7; i++)
	{
		MREAD_I_32((uint8_t *)(p) + 72, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	MREAD_16((uint8_t *)(p) + 100, (r));
	bdmf_session_print(session, "\tbackup_rd_idx            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 102, (r));
	bdmf_session_print(session, "\tbackup_wr_idx            = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 104, 7, 1, (r));
	bdmf_session_print(session, "\tpacket_valid             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 104, 6, 1, (r));
	bdmf_session_print(session, "\tpacket_abs_addr          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 104, 0, 14, (r));
	bdmf_session_print(session, "\tpacket_data_len          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 106, 5, 3, (r));
	bdmf_session_print(session, "\tpacket_prio              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 106, 4, 1, (r));
	bdmf_session_print(session, "\tbuffer_prio              = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 106, 2, 2, (r));
	bdmf_session_print(session, "\treserved2                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 106, 0, 2, (r));
	bdmf_session_print(session, "\tpacket_l4_protocol       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 107, (r));
	bdmf_session_print(session, "\trsv_address_high         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 108, (r));
	bdmf_session_print(session, "\tfpm_address_low          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 112, (r));
	bdmf_session_print(session, "\trequest_id               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 116, (r));
	bdmf_session_print(session, "\taggr_timer_scratchpad    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 118, (r));
	bdmf_session_print(session, "\tcpu_msg_done             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 119, (r));
	bdmf_session_print(session, "\tcoalescing_max_count     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\tdoorbell_counters        =\n\t");
	for (i=0,j=0; i<16; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 120, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
	MREAD_8((uint8_t *)(p) + 136, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 137, (r));
	bdmf_session_print(session, "\tcoalescing_timeout       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 138, (r));
	bdmf_session_print(session, "\tcoalescing_timeout_cntr  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 139, (r));
	bdmf_session_print(session, "\tcur_frg_id               = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 140, 7, 1, (r));
	bdmf_session_print(session, "\ttx_mirroring_en          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p) + 140, 1, 6, (r));
	bdmf_session_print(session, "\tdst_vport                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p) + 140, 0, 9, (r));
	bdmf_session_print(session, "\tdst_queue                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 142, (r));
	bdmf_session_print(session, "\tcodel_max_seq_drops      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 144, (r));
	bdmf_session_print(session, "\tfr_ptrs_size_shift       = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 145, (r));
	bdmf_session_print(session, "\tidma_group_shift         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	bdmf_session_print(session, "\treserved5                =\n\t");
	for (i=0,j=0; i<2; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 146, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
	bdmf_session_print(session, "\treserved6                =\n\t");
	for (i=0,j=0; i<4; i++)
	{
		MREAD_I_8((uint8_t *)(p) + 148, i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_WLAN_MCAST_SSID_MAC_ADDRESS_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register WLAN_MCAST_SSID_MAC_ADDRESS_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tmac_address_high         = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tmac_address_low          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 6, (r));
	bdmf_session_print(session, "\treference_count          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_8((uint8_t *)(p) + 7, (r));
	bdmf_session_print(session, "\treserved1                = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_WLAN_MCAST_SSID_STATS_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register WLAN_MCAST_SSID_STATS_ENTRY\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tpackets                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\tbytes                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_CODEL_BIAS_SLOPE(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_CODEL_BIAS_SLOPE\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tbias                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_16((uint8_t *)(p) + 2, (r));
	bdmf_session_print(session, "\tslope                    = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_BACKUP_IDX_CACHE_TABLE(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	int i,j;

	bdmf_session_print(session, "  Register DHD_BACKUP_IDX_CACHE_TABLE\n");

	bdmf_session_print(session, "\tindexes                  =\n\t");
	for (i=0,j=0; i<16; i++)
	{
		MREAD_I_16((uint8_t *)(p), i, (r));
		bdmf_session_print(session, "0x%08x ", (unsigned int)r);
		j++;
		if (j >= 8)
		{
			j = 0;
			bdmf_session_print(session, "\n\t");
		}
	}
	bdmf_session_print(session, "\n");
}

void dump_RDD_SPDSVC_WLAN_TXPOST_PARAMS(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register SPDSVC_WLAN_TXPOST_PARAMS\n");

	MREAD_16((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tspdsvc_free_idx          = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_DHD_FLOW_RING_CACHE_LKP_ENTRY(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register DHD_FLOW_RING_CACHE_LKP_ENTRY\n");

	FIELD_MREAD_8((uint8_t *)(p), 7, 1, (r));
	bdmf_session_print(session, "\tinvalid                  = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_8((uint8_t *)(p), 2, 5, (r));
	bdmf_session_print(session, "\treserved                 = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	FIELD_MREAD_16((uint8_t *)(p), 0, 10, (r));
	bdmf_session_print(session, "\tflow_ring_id             = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

void dump_RDD_PHYS_ADDR_64_PTR(bdmf_session_handle session, unsigned char *p)
{
	unsigned int r;
	bdmf_session_print(session, "  Register PHYS_ADDR_64_PTR\n");

	MREAD_32((uint8_t *)(p), (r));
	bdmf_session_print(session, "\tlow                      = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

	MREAD_32((uint8_t *)(p) + 4, (r));
	bdmf_session_print(session, "\thigh                     = 0x%08x", (unsigned int)r);
	bdmf_session_print(session, "\n");

}

