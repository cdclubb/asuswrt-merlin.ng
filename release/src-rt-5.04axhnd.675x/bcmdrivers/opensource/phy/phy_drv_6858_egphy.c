/*
   Copyright (c) 2015 Broadcom Corporation
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

/*
 *  Created on: Dec 2015
 *      Author: yuval.raviv@broadcom.com
 */

/*
 *  Phy driver for 6858 internal quad 1G phy
 */

#include "bus_drv.h"
#include "phy_drv.h"
#include "phy_drv_mii.h"
#include "phy_drv_brcm.h"

#define CORE_SHD18_000          0x0028 /* Auxiliary Control */
#define CORE_BASE1E             0x000e /* Test1_Register */
#define CORE_EXPB0              0x00b0 /* Bias Control 0 */
#define DSP_TAP10               0x0125 /* PLL Bandwidth Control */
#define AFE_RXCONFIG_2          0x01e2 /* AFE RXCONFIG 2 */
#define AFE_HPF_TRIM_OTHERS     0x01e8 /* HPF trim and RXCONFIG 49:48 and reserved bits */
#define DSP_TAP33_C2            0x0152 /* EEE LPI Timers */
#define DSP_TAP34_C2            0x0156 /* EEE 100TX Mode BW control */
#define DSP_FFE_ZERO_DET_CTL    0x0166 /* FFE Zero Detection Control */

static int _phy_afe(phy_dev_t *phy_dev)
{
    int ret;

    /* Enable the dsp clock */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | CORE_SHD18_000, 0x0c30)))
        goto Exit;

    /* +1 RCAL codes for RL centering for both LT and HT conditions; default was -2 */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | AFE_RXCONFIG_2, 0xd003)))
        goto Exit;

    /* Cut master bias current by 2% to compensate for RCAL code offset */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | DSP_TAP10, 0x791b)))
        goto Exit;

    /* Improve hybrid leakage */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | AFE_HPF_TRIM_OTHERS, 0x10e3)))
        goto Exit;

    /* rx_on_tune 8 -> 0xf */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | DSP_TAP33_C2, 0x87f6)))
        goto Exit;

    /* 100tx EEE bandwidth */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | DSP_TAP34_C2, 0x017d)))
        goto Exit;

    /* Enable ffe zero det for Vitesse interop */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | DSP_FFE_ZERO_DET_CTL, 0x0015)))
        goto Exit;

    /* Reset R_CAL/RC_CAL Engine */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | CORE_EXPB0, 0x0010)))
        goto Exit;

    /* Disable Reset R_CAL/RC_CAL Engine */
    if ((ret = phy_dev_write(phy_dev, RDB_ACCESS | CORE_EXPB0, 0x0000)))
        goto Exit;

Exit:
    return ret;
}

static int _phy_init(phy_dev_t *phy_dev)
{
    int ret;

    if ((ret = mii_init(phy_dev)))
        goto Exit;

    /* AFE workaround */
    if ((ret = _phy_afe(phy_dev)))
        goto Exit;

    if ((ret = brcm_egphy_force_auto_mdix_set(phy_dev, 1)))
        goto Exit;

    if ((ret = brcm_egphy_eth_wirespeed_set(phy_dev, 1)))
        goto Exit;

Exit:
    return ret;
}

extern int lport_led_init(void *leds_info);

static int _phy_leds_init(phy_dev_t *phy_dev, void *leds_info)
{
    return lport_led_init(leds_info);
}

extern uint16_t lport_qgphy_base_addr_get(void);
extern phy_drv_t phy_drv_6858_egphy;

static int _phy_afe_all(void)
{
    int i, ret = 0;
    phy_dev_t phy_dev = {};
    phy_dev.phy_drv = &phy_drv_6858_egphy;
    uint16_t base_addr = lport_qgphy_base_addr_get();

    for (i = 0; i < 4; i++)
    {
        phy_dev.addr = base_addr + i;
        ret |= _phy_afe(&phy_dev);
    }

    return ret;
}

static int _phy_drv_init(phy_drv_t *phy_drv)
{
    if (_phy_afe_all())
    {
        printk("Failed to initialize the phy AFE settings\n");
        return -1;
    }

    phy_drv->initialized = 1;

    return 0;
}

phy_drv_t phy_drv_6858_egphy =
{
    .phy_type = PHY_TYPE_6858_EGPHY,
    .name = "EGPHY",
    .read = brcm_egphy_read,
    .write = brcm_egphy_write,
    .power_get = mii_power_get,
    .power_set = mii_power_set,
    .apd_get = brcm_egphy_apd_get,
    .apd_set = brcm_egphy_apd_set,
    .eee_get = brcm_egphy_eee_get,
    .eee_set = brcm_egphy_eee_set,
    .eee_resolution_get = brcm_egphy_eee_resolution_get,
    .read_status = brcm_read_status,
    .speed_set = mii_speed_set,
    .caps_get = mii_caps_get,
    .caps_set = mii_caps_set,
    .phyid_get = mii_phyid_get,
    .auto_mdix_set = brcm_egphy_force_auto_mdix_set,
    .auto_mdix_get = brcm_egphy_force_auto_mdix_get,
    .wirespeed_set = brcm_egphy_eth_wirespeed_set,
    .wirespeed_get = brcm_egphy_eth_wirespeed_get,
    .leds_init = _phy_leds_init,
    .cable_diag_run = brcm_cable_diag_run,
    .init = _phy_init,
    .drv_init = _phy_drv_init,
};
