/*
<:copyright-BRCM:2018:DUAL/GPL:standard 

   Copyright (c) 2018 Broadcom 
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
#include <linux/kernel.h>

#include "pmc_drv.h"
#include "pmc_wlan.h"
#include "BPCM.h"
#include "bcm_ubus4.h"
#include "shared_utils.h"

#define MAX_WLAN_PMB_ADDR   8
#if defined(CONFIG_BCM947622) || defined(CONFIG_BCM96756)
#define MAX_WLAN_UNIT       2
#elif defined(CONFIG_BCM963178) || defined(CONFIG_BCM96878) || defined(CONFIG_BCM96855)
#define MAX_WLAN_UNIT       1
#endif


static int pmc_wlan_pmb_addr[][MAX_WLAN_PMB_ADDR]= {
#if defined(CONFIG_BCM947622) || defined(CONFIG_BCM96756)
	{ PMB_ADDR_WLAN0, PMB_ADDR_WLAN0_PHY1, PMB_ADDR_WLAN0_PHY2, -1},
	{ PMB_ADDR_WLAN1, PMB_ADDR_WLAN1_PHY1, PMB_ADDR_WLAN1_PHY2, -1},
#elif defined(CONFIG_BCM963178) || defined(CONFIG_BCM96855)
	{ PMB_ADDR_WLAN0, PMB_ADDR_WLAN0_PHY1, PMB_ADDR_WLAN0_PHY2, -1},
#elif defined(CONFIG_BCM96878)
	{ PMB_ADDR_WLAN0, -1},
#endif
};

#if defined(CONFIG_BCM_UBUS_DECODE_REMAP)
int pmc_wlan_ubus_mport[MAX_WLAN_UNIT] = {
	UBUS_PORT_ID_WIFI,
#if defined(CONFIG_BCM947622) || defined(CONFIG_BCM96756)
	UBUS_PORT_ID_WIFI1,
#endif /* CONFIG_BCM947622 */
};
#endif /* CONFIG_BCM_UBUS_DECODE_REMAP */

int pmc_wlan_power_up(int unit)
{
	int *wlan_pmb_addr, addr, i, rc = 0;
#if defined(CONFIG_BCM947622)
	BPCM_CLKRST_CONTROL control;
#endif

	if (unit >= MAX_WLAN_UNIT) {
		printk("pmc_wlan_power_up invalid unit %d!\n", unit);
		return -1;
	}

	wlan_pmb_addr = pmc_wlan_pmb_addr[unit];
	for (i = 0; i < MAX_WLAN_PMB_ADDR; i++) {
		addr = wlan_pmb_addr[i];
		if (addr == -1)
			break;
		rc = PowerOnDevice(addr);
		if (rc)
			printk("pmc_wlan_power_up %d power on device 0x%x failed return %d\n", unit, addr, rc);

		rc = WriteBPCMRegister(addr, BPCMRegOffset(sr_control), 0);
		if (rc)
			printk("pmc_wlan_power_up %d reset control on device 0x%x failed return %d\n", unit, addr, rc);
	}

#if defined(CONFIG_BCM947622)
	/* Workaround for A0: turn on the WLAN RF clock */
	if (UtilGetChipRev() == 0xa0) {
		rc = ReadBPCMRegister(PMB_ADDR_CHIP_CLKRST, CLKRSTBPCMRegOffset(clkrst_control), &control.Reg32); 
		if (unit == 0)
			control.Bits.wl0_rf_enable = 1;
		else if (unit == 1)
			control.Bits.wl1_rf_enable = 1;
		rc = WriteBPCMRegister(PMB_ADDR_CHIP_CLKRST, CLKRSTBPCMRegOffset(clkrst_control), control.Reg32);
	}
#endif

#if defined(CONFIG_BCM_UBUS_DECODE_REMAP)
    ubus_master_remap_port(pmc_wlan_ubus_mport[unit]);
#endif

	return rc; 
}

int pmc_wlan_power_down(int unit)
{
	int *wlan_pmb_addr, addr, i, rc = 0;
#if defined(CONFIG_BCM947622)
	BPCM_CLKRST_CONTROL control;
#endif
	if (unit >= MAX_WLAN_UNIT) {
		printk("pmc_wlan_power_down invalid unit %d!\n", unit);
		return -1;
	}
#if defined(CONFIG_BCM947622)
	/* turn off the WLAN RF clock */
	if (UtilGetChipRev() == 0xa0) {
		rc = ReadBPCMRegister(PMB_ADDR_CHIP_CLKRST, CLKRSTBPCMRegOffset(clkrst_control), &control.Reg32); 
		if (unit == 0)
			control.Bits.wl0_rf_enable = 0;
		else if (unit == 1)
			control.Bits.wl1_rf_enable = 0;
		rc = WriteBPCMRegister(PMB_ADDR_CHIP_CLKRST, CLKRSTBPCMRegOffset(clkrst_control), control.Reg32);
	}
#endif
	wlan_pmb_addr = pmc_wlan_pmb_addr[unit];
	for (i = 0; i < MAX_WLAN_PMB_ADDR; i++) {
		addr = wlan_pmb_addr[i];
		if (addr == -1)
			break;

		rc = WriteBPCMRegister(addr, BPCMRegOffset(sr_control), 1);
		if (rc)
			printk("pmc_wlan_power_down %d reset control on device 0x%x failed return %d\n", unit, addr, rc);

		rc = PowerOffDevice(addr, 0);
		if (rc)
			printk("pmc_wlan_power_down %d power on device 0x%x failed return %d\n", unit, addr, rc);
	}

	return rc; 
}



void pcm_wlan_power_init(void)
{
	int max_unit = MAX_WLAN_UNIT;
	int i;

	for (i = 0; i < max_unit; i++ )
		pmc_wlan_power_up(i);

	return;
}

EXPORT_SYMBOL(pmc_wlan_power_up);
EXPORT_SYMBOL(pmc_wlan_power_down);

