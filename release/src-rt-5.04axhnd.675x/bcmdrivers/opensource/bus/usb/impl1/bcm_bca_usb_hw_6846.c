/*
<:copyright-BRCM:2020:DUAL/GPL:standard 

   Copyright (c) 2020 Broadcom 
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
#include <linux/types.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/io.h>
#include <linux/module.h>
#include <linux/version.h>
#include <linux/dma-mapping.h>
#include <linux/platform_device.h>
#include <linux/clkdev.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/bug.h>
#include <linux/of_device.h>
#include <linux/of_address.h>

#include <pmc_usb.h>
#include "bcm_bca_usb_ctrl.h"
#include "bcm_bca_usb_utils.h"

typedef struct usb_ctrl{
    uint32_t setup;
#define USBH_IPP                (1<<5)
#define USBH_IOC                (1<<4)
#define USBH_STRAP_IPP_SEL      (1<<25)
#define USB2_OC_DISABLE_PORT0   (1<<28)
#define USB2_OC_DISABLE_PORT1   (1<<29)
#define USB3_OC_DISABLE_PORT0   (1<<30)
#define USB3_OC_DISABLE_PORT1   (1<<31)
    uint32_t pll_ctl;
    uint32_t fladj_value;
    uint32_t bridge_ctl;
#define USB_BRCTL_OHCI_MEM_REQ_DIS (1<<16)
    uint32_t spare1;
    uint32_t mdio;
    uint32_t mdio2;
    uint32_t test_port_control;
    uint32_t usb_simctl;
    uint32_t usb_testctl;
    uint32_t usb_testmon;
    uint32_t utmi_ctl_1;
    uint32_t utmi_ctl_2;
    uint32_t usb_pm;
#define XHC_SOFT_RESETB         (1<<22)
#define USB_PWRDWN              (1<<31)
    uint32_t usb_pm_status;
    uint32_t spare3;
    uint32_t pll_ldo_ctl;
    uint32_t pll_ldo_pllbias;
    uint32_t pll_afe_bg_cntl;
    uint32_t afe_usbio_tst;
    uint32_t pll_ndiv_frac;
    uint32_t tp_diag;
    uint32_t ahb_capture_fifo;
    uint32_t spare4;
    uint32_t usb30_ctl1;
#define PHY3_PLL_SEQ_START      (1<<4)
    uint32_t usb30_ctl2;
    uint32_t usb30_ctl3;
    uint32_t usb30_ctl4;
    uint32_t usb30_pctl;
    uint32_t usb30_ctl5;
    uint32_t spare5;
    uint32_t spare6;
    uint32_t spare7;
    uint32_t unsused1[3];
    uint32_t usb_device_ctl1;
    uint32_t usb_device_ctl2;
    uint32_t unsused2[22];
    uint32_t usb20_id;
    uint32_t usb30_id;
    uint32_t bdc_coreid;
    uint32_t usb_revid;
} usb_ctrl_t;

int hw_init(struct bcm_bca_usb_ctrl *bca_usb)
{
    usb_ctrl_t *usb_ctrl = (usb_ctrl_t *)bca_usb->usb_ctrl;
    uint32_t val;
    dev_info(&bca_usb->pdev->dev, "---- Powering up USB blocks\n");

    if(pmc_usb_power_up(PMC_USB_HOST_ALL))
    {
        dev_err(&bca_usb->pdev->dev,"+++ Failed to Power Up USB Host\n");
        return -1;
    }

    mdelay(1);

    if (bca_usb->pwrflt_p_high)
        usb_ctrl->setup &= ~(USBH_IOC);
    else
        usb_ctrl->setup |= USBH_IOC;

    /*by default we use strap to determine polarity of port power - the strap is opposite from all previous platforms */
    if (usb_ctrl->setup & USBH_STRAP_IPP_SEL)
    {
        usb_ctrl->setup &= ~(USBH_STRAP_IPP_SEL);// to set bit 5 need  ippsel = 0 => strap ipp0: ipp = rctl_ipp (setup[5]) 
        if (bca_usb->pwron_p_high)
            usb_ctrl->setup &= ~(USBH_IPP);
        else
            usb_ctrl->setup |= USBH_IPP;
    }

    usb_ctrl->utmi_ctl_1 |= (1 << 8) | (1 << 24);

    /*enable USB PHYs*/
    mdelay(1);
    usb_ctrl->usb_pm &= ~(USB_PWRDWN);
    mdelay(1);

    /*adjust the default AFE settings for better eye diagrams */
    usb2_eye_fix(&usb_ctrl->mdio);

    /*initialize EHCI & OHCI settings*/
    /* no swap for data & desciptors */    
    usb_ctrl->bridge_ctl &= ~(0xf); /*clear lower 4 bits */

    /* reset host controllers for possible fake overcurrent indications */ 
    val = usb_ctrl->usb_pm;
    usb_ctrl->usb_pm = 0;
    usb_ctrl->usb_pm = val;
    mdelay(1);

    return 0;
}

void hw_uninit(struct bcm_bca_usb_ctrl *bca_usb)
{
    dev_info(&bca_usb->pdev->dev, "---- Powering DOWN USB blocks\n");
    pmc_usb_power_down(PMC_USB_HOST_ALL);
    mdelay(1);
}
