/*
    <:copyright-BRCM:2014:DUAL/GPL:standard
    
       Copyright (c) 2014 Broadcom 
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

#ifndef RDD_RUNNER_PROJ_DEFS_H_
#define RDD_RUNNER_PROJ_DEFS_H_

#define NUM_OF_LOCAL_REGS                                       24
#define NUM_OF_GLOBAL_REGS                                      8
#define NUM_OF_MAIN_RUNNER_THREADS                              16
#define NUM_OF_RUNNER_CORES                                     16

#define RDD_LAN0_VPORT       RDD_VPORT_ID_1
#define RDD_LAN1_VPORT       RDD_VPORT_ID_2
#define RDD_LAN2_VPORT       RDD_VPORT_ID_3
#define RDD_LAN3_VPORT       RDD_VPORT_ID_4
#define RDD_LAN4_VPORT       RDD_VPORT_ID_5
#define RDD_LAN5_VPORT       RDD_VPORT_ID_6
#define RDD_LAN6_VPORT       RDD_VPORT_ID_7
#define RDD_LAN7_VPORT       RDD_VPORT_ID_8
#define RDD_LAN_VPORT_LAST   RDD_LAN7_VPORT

#define RDD_CPU0_VPORT       (RDD_LAN_VPORT_LAST + 1)
#define RDD_CPU_VPORT_FIRST  RDD_CPU0_VPORT
#define RDD_CPU_VPORT_FIRST  RDD_CPU0_VPORT
#define RDD_CPU1_VPORT       (RDD_CPU_VPORT_FIRST + 1)
#define RDD_CPU2_VPORT       (RDD_CPU_VPORT_FIRST + 2)
#define RDD_CPU3_VPORT       (RDD_CPU_VPORT_FIRST + 3)
#define RDD_CPU4_VPORT       (RDD_CPU_VPORT_FIRST + 4)
#define RDD_WLAN0_VPORT      RDD_CPU4_VPORT
#define RDD_CPU5_VPORT       (RDD_CPU_VPORT_FIRST + 5)
#define RDD_WLAN1_VPORT      RDD_CPU5_VPORT
#define RDD_CPU6_VPORT       (RDD_CPU_VPORT_FIRST + 6)
#define RDD_WLAN2_VPORT      RDD_CPU6_VPORT
#define RDD_CPU_VPORT_FLOOD  (RDD_CPU_VPORT_FIRST + 7)
#define RDD_CPU_VPORT_LAST   RDD_CPU_VPORT_FLOOD
#define RDD_WAN1_VPORT       (RDD_VPORT_LAST - 3)
#define RDD_VIRTUAL_VPORT    (RDD_VPORT_LAST - 1)

#define RDD_BBH_QUEUE_TABLE_SIZE  40
#define RDD_TM_ACTION_PTR_TABLE_SIZE     RDD_DS_TM_TM_ACTION_PTR_TABLE_SIZE
#define RDD_BASIC_SCHEDULER_TABLE_SIZE   RDD_BASIC_SCHEDULER_TABLE_DS_SIZE
#define RDD_BASIC_RATE_LIMITER_TABLE_SIZE RDD_BASIC_RATE_LIMITER_TABLE_DS_SIZE


#endif /* RDD_RUNNER_PROJ_DEFS_H_ */

