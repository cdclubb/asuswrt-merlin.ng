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
 * Phy driver for lport SerDes: SGMII/HSGMII/XFI
 */

#include "bus_drv.h"
#include "phy_drv.h"
#include "bcm6858_lport_srds_ag.h"
#include "serdes_access.h"
#include "lport_drv.h"

static uint32_t enabled_ports = 0xffffffff;

static int _phy_power_get(phy_dev_t *phy_dev, int *enable)
{
    uint32_t port = (uint64_t)phy_dev->priv;

    *enable = enabled_ports & (1 << port);

    return 0;
}

static int _phy_power_set(phy_dev_t *phy_dev, int enable)
{
    uint32_t port = (uint64_t)phy_dev->priv;

    if (enable)
        enabled_ports |= (1 << port);
    else
        enabled_ports &= ~(1 << port);

    return 0;
}

static int _get_serdes_link(uint32_t port, int *sig, int *lnk)
{
    int rc = LPORT_ERR_OK;
    uint8_t msk = 0x2;
    lport_srds_dual_serdes_0_status srds_0_status = {};
    lport_srds_dual_serdes_1_status srds_1_status = {};

    switch (port)
    {
    case 0:
    case 7:
        msk = 0x1;
    case 1:
    case 4:
        rc = ag_drv_lport_srds_dual_serdes_0_status_get(&srds_0_status);
        *sig = !(srds_0_status.ext_sig_det & msk) ? 1 : 0; 
        *lnk = (srds_0_status.link_status & msk) ? 1 : 0; 
        break;
    case 2:
    case 5:
        msk = 0x1;
    case 3:
    case 6:
        rc = ag_drv_lport_srds_dual_serdes_1_status_get(&srds_1_status);
        *sig = !(srds_1_status.ext_sig_det & msk) ? 1 : 0; 
        *lnk = (srds_1_status.link_status & msk) ? 1 : 0; 
        break;
    }

    return rc;
}

static int _get_serdes_speed(uint32_t port, phy_speed_t *speed)
{
    lport_port_status_s port_status;
    int ret;

    if ((ret = lport_serdes_get_status(port, &port_status)))
        return ret;

    if (!port_status.port_up)
        return 1;

    if (port_status.rate == LPORT_RATE_10G)
        *speed = PHY_SPEED_10000;
    else if (port_status.rate == LPORT_RATE_2500MB)
        *speed = PHY_SPEED_2500;
    else if (port_status.rate == LPORT_RATE_1000MB)
        *speed = PHY_SPEED_1000;
    else if (port_status.rate == LPORT_RATE_100MB)
        *speed = PHY_SPEED_100;
    else if (port_status.rate == LPORT_RATE_10MB)
        *speed = PHY_SPEED_10;

    return 0;
}

#if defined(LPORT_SERDES_SPEED_DETECT)
static LPORT_PORT_MUX_SELECT _get_next_mux(phy_dev_t *phy_dev, LPORT_PORT_MUX_SELECT mux)
{
    if (mux != PORT_UNAVAIL)
        return mux -1;

    if (phy_dev->mii_type == PHY_MII_TYPE_XFI)
        return PORT_XFI;
    if (phy_dev->mii_type == PHY_MII_TYPE_HSGMII)
        return PORT_HSGMII;
    if (phy_dev->mii_type == PHY_MII_TYPE_SGMII)
        return PORT_SGMII_AN_MASTER;

    return PORT_UNAVAIL;
}

static int _set_next_mux(uint32_t port, phy_dev_t *phy_dev)
{
    int ret;
    LPORT_PORT_MUX_SELECT prt_mux_sel;

    if ((ret = lport_get_port_mux(port, &prt_mux_sel)))
        return ret;

    prt_mux_sel = _get_next_mux(phy_dev, prt_mux_sel);

    if ((ret = lport_set_port_mux(port, prt_mux_sel)))
        return ret;

    return 0;
}
#elif defined(LPORT_SERDES_EXTERNAL_SIGNAL_DETECT)
static int _get_phy_speed(phy_dev_t *phy_dev, phy_speed_t *speed)
{
    if (phy_dev->mii_type == PHY_MII_TYPE_XFI)
        *speed = PHY_SPEED_10000;
    else if (phy_dev->mii_type == PHY_MII_TYPE_HSGMII)
        *speed = PHY_SPEED_2500;
    if (phy_dev->mii_type == PHY_MII_TYPE_SGMII)
        *speed = PHY_SPEED_1000;

    return 0;
}
#endif

static int _phy_read_status(phy_dev_t *phy_dev)
{
    uint32_t port = (uint64_t)phy_dev->priv;
    int sig = 0, lnk = 0, ret;

    phy_dev->link = 0;
    phy_dev->speed = PHY_SPEED_UNKNOWN;
    phy_dev->duplex = PHY_DUPLEX_UNKNOWN;

    if (!(enabled_ports & (1 << port)))
        return 0;

    if ((ret = _get_serdes_link(port, &sig, &lnk)))
        return ret;

#if defined(LPORT_SERDES_EXTERNAL_SIGNAL_DETECT)
    if (!sig)
        return 0;
#endif

    if (lnk)
    {
        if ((ret = _get_serdes_speed(port, &phy_dev->speed)))
            return ret;

        phy_dev->link = 1;
        phy_dev->duplex = PHY_DUPLEX_FULL;
    }
    else
    {
#if defined(LPORT_SERDES_SPEED_DETECT)
        if ((ret = _set_next_mux(port, phy_dev)))
            return ret;
#elif defined(LPORT_SERDES_EXTERNAL_SIGNAL_DETECT)
        phy_dev->link = 1;
        phy_dev->duplex = PHY_DUPLEX_FULL;

        if ((ret = _get_phy_speed(phy_dev, &phy_dev->speed)))
            return ret;
#endif
    }

    return 0;
}

static int _phy_caps_get(phy_dev_t *phy_dev, int caps_type, uint32_t *pcaps)
{
    uint32_t caps = 0;
    uint32_t port = (uint64_t)phy_dev->priv;
    LPORT_PORT_RATE port_rate;

    if ((caps_type != CAPS_TYPE_ADVERTISE) 
        && (caps_type != CAPS_TYPE_SUPPORTED))
        return 0;

    port_rate = lport_speed_get(port);
    switch (port_rate)
    {
    case LPORT_RATE_10MB: /* 10M */
        caps |= PHY_CAP_10_HALF | PHY_CAP_10_FULL;
        break;
    case LPORT_RATE_100MB: /* 100Mbps */
        caps |= PHY_CAP_100_HALF | PHY_CAP_100_FULL;
        break;
    case LPORT_RATE_1000MB: /* 1000Mbps */
        caps |= PHY_CAP_1000_HALF | PHY_CAP_1000_FULL;
        break;
    case LPORT_RATE_2500MB: /* 2500Mbps */
        caps |= PHY_CAP_2500;
        break;
    case LPORT_RATE_10G: /* 5000/10000Mbps */
        caps |= PHY_CAP_10000;
        break;
    default:
        break;
    }

    if (phy_dev->pause_rx && phy_dev->pause_tx)
        caps |= PHY_CAP_PAUSE;
    else if (phy_dev->pause_rx)
        caps |= PHY_CAP_PAUSE | PHY_CAP_PAUSE_ASYM;
    else if (phy_dev->pause_tx)
        caps |= PHY_CAP_PAUSE_ASYM;

    *pcaps = caps;
    return 0;
}

static int _phy_caps_set(phy_dev_t *phy_dev, uint32_t caps)
{
    phy_dev->link = 0;
    phy_dev->pause_rx = 0; 
    phy_dev->pause_tx = 0; 

    if (caps & PHY_CAP_PAUSE)
    {
        phy_dev->pause_rx = 1; 
        phy_dev->pause_tx = (caps & PHY_CAP_PAUSE_ASYM) ? 0 : 1;
    }
    else if (caps & PHY_CAP_PAUSE_ASYM)
    {
        phy_dev->pause_tx = 1; 
    }

    return 0;
}

static dt_gpio_desc tx_dis_gpiod[LPORT_NUM_OF_PORTS];

extern int lport_serdes_tx_disable_gpio_assign(int port, void *priv);
extern void lport_serdes_tx_disable_gpio_ctrl_set(void (*_tx_disable_gpio_ctrl)(void *priv, int value));

static void _lport_gpio_set_value(void *priv, int value)
{
    phy_dev_t *phy_dev = priv;
    dt_gpio_desc desc;

    if (!phy_dev)
        return;

    desc = tx_dis_gpiod[phy_dev->addr];
    if (dt_gpio_exists(desc))
        dt_gpio_set_value(desc, value);
}

static int _phy_drv_dt_priv(const dt_handle_t handle, uint32_t addr, uint32_t phy_mode, void **_priv)
{
    int rc = 0;

    dt_gpio_desc desc;

    rc = dt_gpio_request_by_name_optional(handle, "tx-disable", 0, "TX disable", &desc);
    if (rc)
        return rc;

    if (dt_gpio_exists(desc))
    {
        tx_dis_gpiod[addr] = desc;
        dt_gpio_set_direction_output(desc, 0);
    }

    *_priv = (void*)(uint64_t)addr;

    return rc;
}

static int _phy_drv_init(phy_drv_t *phy_drv)
{
    lport_serdes_tx_disable_gpio_ctrl_set(_lport_gpio_set_value);

    return 0;
}

static int _phy_init(phy_dev_t *phy_dev)
{
    if (phy_dev->addr < LPORT_NUM_OF_PORTS)
        lport_serdes_tx_disable_gpio_assign(phy_dev->addr, phy_dev);

    return 0;
}

extern int lport_led_init(void *leds_info);

static int _phy_leds_init(phy_dev_t *phy_dev, void *leds_info)
{
    return lport_led_init(leds_info);
}

phy_drv_t phy_drv_lport_serdes =
{
    .phy_type = PHY_TYPE_LPORT_SERDES,
    .name = "SERDES",
    .power_get = _phy_power_get,
    .power_set = _phy_power_set,
    .read_status = _phy_read_status,
    .caps_get = _phy_caps_get,
    .caps_set = _phy_caps_set,
    .init = _phy_init,
    .dt_priv = _phy_drv_dt_priv,
    .leds_init = _phy_leds_init,
    .drv_init = _phy_drv_init,
};
