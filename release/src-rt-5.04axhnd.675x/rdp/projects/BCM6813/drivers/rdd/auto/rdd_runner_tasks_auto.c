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


#include "rdd_runner_tasks_auto.h"


char *image_task_names[7][16] = {
	{"IMAGE_0_TIMER_COMMON", "IMAGE_0_BUDGET_ALLOCATION_DS", "IMAGE_0_SERVICE_QUEUES_BUDGET_ALLOCATOR", "IMAGE_0_UPDATE_FIFO", "IMAGE_0_TX_TASK_DS", "IMAGE_0_TX_TASK_DS_1", "IMAGE_0_SERVICE_QUEUES_UPDATE_FIFO", "IMAGE_0_SERVICE_QUEUES_TX", "IMAGE_0_PROCESSING0", "IMAGE_0_PROCESSING1", "IMAGE_0_PROCESSING2", "IMAGE_0_PROCESSING3", "", "", "", ""},
	{"IMAGE_1_BUDGET_ALLOCATION_US", "IMAGE_1_OVL_BUDGET_ALLOCATION_US", "IMAGE_1_UPDATE_FIFO", "IMAGE_1_TX_TASK_US", "IMAGE_1_TX_TASK_US_1", "IMAGE_1_DHD_TX_COMPLETE_0", "IMAGE_1_DHD_TX_COMPLETE_1", "IMAGE_1_DHD_TX_COMPLETE_2", "IMAGE_1_PROCESSING0", "IMAGE_1_PROCESSING1", "IMAGE_1_PROCESSING2", "IMAGE_1_PROCESSING3", "IMAGE_1_DHD_RX_COMPLETE_0", "IMAGE_1_DHD_RX_COMPLETE_1", "IMAGE_1_DHD_RX_COMPLETE_2", ""},
	{"IMAGE_2_INTERRUPT_COALESCING", "IMAGE_2_CPU_RECYCLE", "", "", "", "", "IMAGE_2_CPU_TX_0", "IMAGE_2_CPU_TX_1", "IMAGE_2_PROCESSING0", "IMAGE_2_PROCESSING1", "IMAGE_2_PROCESSING2", "IMAGE_2_PROCESSING3", "IMAGE_2_PROCESSING4", "IMAGE_2_PROCESSING5", "IMAGE_2_PROCESSING6", "IMAGE_2_PROCESSING7"},
	{"", "IMAGE_3_CPU_RX_METER_BUDGET_ALLOCATOR", "IMAGE_3_INTERRUPT_COALESCING", "IMAGE_3_CPU_RX", "IMAGE_3_CPU_RECYCLE", "IMAGE_3_CPU_RX_COPY", "IMAGE_3_COMMON_REPROCESSING", "IMAGE_3_SPDSVC_GEN", "IMAGE_3_PROCESSING0", "IMAGE_3_PROCESSING1", "IMAGE_3_PROCESSING2", "IMAGE_3_PROCESSING3", "IMAGE_3_PROCESSING4", "IMAGE_3_PROCESSING5", "IMAGE_3_PROCESSING6", "IMAGE_3_PROCESSING7"},
	{"IMAGE_4_DHD_TIMER", "IMAGE_4_DHD_TX_POST_UPDATE_FIFO", "IMAGE_4_DHD_TX_POST_0", "IMAGE_4_DHD_TX_POST_1", "IMAGE_4_DHD_TX_POST_2", "IMAGE_4_DHD_MCAST", "", "", "IMAGE_4_PROCESSING0", "IMAGE_4_PROCESSING1", "IMAGE_4_PROCESSING2", "IMAGE_4_PROCESSING3", "IMAGE_4_PROCESSING4", "IMAGE_4_PROCESSING5", "IMAGE_4_PROCESSING6", "IMAGE_4_PROCESSING7"},
	{"", "", "", "", "", "", "", "", "IMAGE_5_PROCESSING0", "IMAGE_5_PROCESSING1", "IMAGE_5_PROCESSING2", "IMAGE_5_PROCESSING3", "IMAGE_5_PROCESSING4", "IMAGE_5_PROCESSING5", "IMAGE_5_PROCESSING6", "IMAGE_5_PROCESSING7"},
	{"", "", "", "", "", "", "", "", "IMAGE_6_PROCESSING0", "IMAGE_6_PROCESSING1", "IMAGE_6_PROCESSING2", "IMAGE_6_PROCESSING3", "IMAGE_6_PROCESSING4", "IMAGE_6_PROCESSING5", "IMAGE_6_PROCESSING6", "IMAGE_6_PROCESSING7"}
	};

