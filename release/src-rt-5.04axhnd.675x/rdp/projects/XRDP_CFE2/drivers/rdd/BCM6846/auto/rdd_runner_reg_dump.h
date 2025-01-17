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


#ifndef __RDD_RUNNER_REG_DUMP_H__
#define __RDD_RUNNER_REG_DUMP_H__

#include "bdmf_shell.h"

typedef struct
{
#ifndef USE_BDMF_SHELL
	void  (*callback)(unsigned char *xi_value, int rw, int unionreq);
#else
	void  (*callback)(bdmf_session_handle session, unsigned char *value);
#endif
	unsigned int starts;
} ENTRY_STRUCT;

typedef struct
{
	int length; /* length of each entry in bytes */
	ENTRY_STRUCT entries[];
} DUMP_RUNNERREG_STRUCT;

typedef struct
{
	char * table_name;
	int tbldmp; /* boolean */
	int segment;
	DUMP_RUNNERREG_STRUCT * entries;
    int size_rows; /* Number of rows in table */
    int size_rows_d2;/* If table's entries are tables by themselfves, number of rows in each entry table (dimention 2)*/
    int size_rows_d3; /* Like above, dimention 3 */
} TABLE_STRUCT;

typedef struct
{
    char * table_name;
    int core;
	uint32_t base_address;
    int size;
} TABLE_STACK_STRUCT;

#ifndef STT_PRINTF
	#if defined LINUX_KERNEL
		#define STT_PRINTF printk
	#else
		#define STT_PRINTF printf
	#endif
#endif


void dump_RDD_PACKETS_AND_BYTES(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BBH_TX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTES_4(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BB_DESTINATION_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BYTE_1(bdmf_session_handle session, unsigned char *p);
void dump_RDD_BBH_TX_EGRESS_COUNTER_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PROCESSING_RX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_RX_FLOW_ENTRY(bdmf_session_handle session, unsigned char *p);
void dump_RDD_PROCESSING_TX_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);
void dump_RDD_CPU_RING_DESCRIPTOR(bdmf_session_handle session, unsigned char *p);

#endif /* __RDD_RUNNER_REG_DUMP_H__ */
