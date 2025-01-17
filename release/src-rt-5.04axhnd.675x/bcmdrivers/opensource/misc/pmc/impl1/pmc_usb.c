/*
<:copyright-BRCM:2013:DUAL/GPL:standard 

   Copyright (c) 2013 Broadcom 
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
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include "pmc_drv.h"
#include "BPCM.h"
#include "pmc_usb.h"
#include "bcm_ubus4.h"
#include <board.h>

/*TODO add functions to power on/off the USB blocks selectively */
int pmc_usb_power_up(unsigned int usb_block)
{
    int ret;

#if defined CONFIG_BCM963138 || defined CONFIG_BCM963148
    if( usb_block == PMC_USB_HOST_ALL)
    {
        ret = PowerOnDevice(PMB_ADDR_USB30_2X);
    }
#elif defined CONFIG_BCM94908
    if( usb_block == PMC_USB_HOST_ALL)
    {
        /*TODO check if this will power on USB device also */
        ret = PowerOnDevice(PMB_ADDR_USB30_2X);
    }
#elif defined(CONFIG_BCM96858) || defined(CONFIG_BCM96856)
    if( usb_block == PMC_USB_HOST_ALL)
    {
        ret = PowerOnDevice(PMB_ADDR_USB30_2X);
        ubus_register_port(UCB_NODE_ID_SLV_USB);
        ubus_register_port(UCB_NODE_ID_MST_USB);
    }
#elif defined(CONFIG_BCM96846) || defined(CONFIG_BCM96878) || defined(CONFIG_BCM96855)
    if( usb_block == PMC_USB_HOST_ALL)
    {
        ret = PowerOnDevice(PMB_ADDR_USB20_2X);
    }
#elif defined(CONFIG_BCM963158) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM963146)|| defined(CONFIG_BCM94912) || defined(CONFIG_BCM96813)
    if( usb_block == PMC_USB_HOST_ALL)
    {
        ret = PowerOnDevice(PMB_ADDR_USB30_2X);
    }
#elif defined(CONFIG_BCM947622) || defined(CONFIG_BCM96756)
    if( usb_block == PMC_USB_HOST_ALL)
    {
        ret = PowerOnDevice(PMB_ADDR_USB31_20);
    }
#endif
    else {
        printk("pmc_usb_power_up: Error unsupported usb_block=%u\n",usb_block);
        return -1;
    }

#if defined CONFIG_BCM963158 || defined CONFIG_BCM96858
    apply_ubus_credit_each_master(UBUS_PORT_ID_USB);
#endif

#if defined(CONFIG_BCM_UBUS4_DCM)
    ubus_cong_threshold_wr(UBUS_PORT_ID_USB, 0);
#endif

#if defined(CONFIG_BCM_UBUS_DECODE_REMAP)
    ubus_master_remap_port(UBUS_PORT_ID_USB);
#endif

    return ret;
}
EXPORT_SYMBOL(pmc_usb_power_up);

int pmc_usb_power_down(unsigned int usb_block)
{
#if defined CONFIG_BCM963138 || defined CONFIG_BCM963148
	// Powering-down zone 0 doesn't power-down the whole device;
	// Individually power-down each zone
	int zone, status;

    if( usb_block == PMC_USB_HOST_ALL)
    {
        for (zone = 0; zone < PMB_ZONES_USB30_2X; zone++) {
            status = PowerOffZone(PMB_ADDR_USB30_2X, zone);
            if (status) return status;
        }
        return 0;
    }
#elif defined CONFIG_BCM94908
    if( usb_block == PMC_USB_HOST_ALL)
    {
        /*TODO check if this will power off USB device also */
        return PowerOffDevice(PMB_ADDR_USB30_2X, 0);
    }
#elif defined(CONFIG_BCM96858) || defined(CONFIG_BCM96856)
    if( usb_block == PMC_USB_HOST_ALL)
    {
        ubus_deregister_port(UCB_NODE_ID_SLV_USB);
        ubus_deregister_port(UCB_NODE_ID_MST_USB);
        return PowerOffDevice(PMB_ADDR_USB30_2X, 0);
    }
#elif defined CONFIG_BCM96846 || defined CONFIG_BCM96878 || defined(CONFIG_BCM96855)
    if( usb_block == PMC_USB_HOST_ALL)
    {
        return PowerOffDevice(PMB_ADDR_USB20_2X,0);
    }
#elif defined (CONFIG_BCM963158) || defined(CONFIG_BCM963178) || defined(CONFIG_BCM963146)|| defined(CONFIG_BCM94912) || defined(CONFIG_BCM96813)
    if( usb_block == PMC_USB_HOST_ALL)
    {
        return PowerOffDevice(PMB_ADDR_USB30_2X, 0);
    }
#elif defined(CONFIG_BCM947622) || defined(CONFIG_BCM96756)
    if( usb_block == PMC_USB_HOST_ALL)
    {
        return PowerOffDevice(PMB_ADDR_USB31_20, 0);
    }
#endif
    {
        printk("pmc_usb_power_down: Error unsupported usb_block=%u\n",usb_block);
        return -1;
    }
}
EXPORT_SYMBOL(pmc_usb_power_down);
