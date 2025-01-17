/*
    <:copyright-BRCM:2015:DUAL/GPL:standard
    
       Copyright (c) 2015 Broadcom 
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

/*
 * cpu_tx_ring.h
 */

#ifndef _CPU_TX_RING_H_
#define _CPU_TX_RING_H_

#if defined(XRDP_MANAGE_SBPM)
int rdd_cpu_tx_new(uint8_t *buffer, uint32_t length, uint8_t tx_port);
#else
int rdd_cpu_tx(uint32_t length, uint16_t bn0, uint16_t bn1, uint8_t bns_num, uint8_t tx_port);
#endif

#endif /* _CPU_TX_RING_H_ */
