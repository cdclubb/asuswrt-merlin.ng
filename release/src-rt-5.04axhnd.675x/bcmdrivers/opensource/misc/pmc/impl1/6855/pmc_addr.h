/*
<:copyright-BRCM:2019:DUAL/GPL:standard 

   Copyright (c) 2019 Broadcom 
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

#ifndef PMC_ADDR_H__
#define PMC_ADDR_H__

#define PMB_BUS_MAX              2
#define PMB_BUS_ID_SHIFT         12

#define PMB_BUS_PERIPH           0
#define PMB_ADDR_PERIPH          (0 | PMB_BUS_PERIPH << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PERIPH         4

#define PMB_BUS_CHIP_CLKRST      0
#define PMB_ADDR_CHIP_CLKRST     (1 | PMB_BUS_CHIP_CLKRST << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_CHIP_CLKRST    0

#define PMB_BUS_SYSPLL           0
#define PMB_ADDR_SYSPLL          (3 | PMB_BUS_SYSPLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_SYSPLL         0

#define PMB_BUS_PVTMON           1
#define PMB_ADDR_PVTMON          (6 | PMB_BUS_PVTMON << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PVTMON         0

#define PMB_BUS_MEMC             0
#define PMB_ADDR_MEMC            (8 | PMB_BUS_MEMC << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_MEMC           1

#define PMB_BUS_USB20_2X         1
#define PMB_ADDR_USB20_2X        (10 | PMB_BUS_USB20_2X << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_USB20_2X       4

#define PMB_BUS_WAN              1
#define PMB_ADDR_WAN             (11 | PMB_BUS_WAN << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_WAN            6

#define PMB_BUS_XRDP              1
#define PMB_ADDR_XRDP             (12 | PMB_BUS_XRDP << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_XRDP            3

#define PMB_BUS_PCIE0             1
#define PMB_ADDR_PCIE0            (17 | PMB_BUS_PCIE0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE0           1

#define PMB_BUS_PCIE1             1
#define PMB_ADDR_PCIE1            (18 | PMB_BUS_PCIE1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_PCIE1           1

#define PMB_BUS_WLAN0            1
#define PMB_ADDR_WLAN0           (19 | PMB_BUS_WLAN0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_WLAN0          1

#define PMB_BUS_WLAN0_PHY1       1
#define PMB_ADDR_WLAN0_PHY1      (20 | PMB_BUS_WLAN0_PHY1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_WLAN0_PHY1     1

#define PMB_BUS_WLAN0_PHY2       1
#define PMB_ADDR_WLAN0_PHY2      (21 | PMB_BUS_WLAN0_PHY2 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_WLAN0_PHY2     1

#define PMB_BUS_ORION_CPU0       0
#define PMB_ADDR_ORION_CPU0      (32 | PMB_BUS_ORION_CPU0 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_CPU0     1

#define PMB_BUS_ORION_CPU1       0
#define PMB_ADDR_ORION_CPU1      (33 | PMB_BUS_ORION_CPU1 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_CPU1     1

#define PMB_BUS_ORION_CPU2       0
#define PMB_ADDR_ORION_CPU2      (34 | PMB_BUS_ORION_CPU2 << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_CPU2     1

#define PMB_BUS_ORION_NONCPU     0
#define PMB_ADDR_ORION_NONCPU    (36 | PMB_BUS_ORION_NONCPU << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_ORION_NONCPU   1

#define PMB_BUS_BIU_PLL          0
#define PMB_ADDR_BIU_PLL         (38 | PMB_BUS_BIU_PLL << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_BIU_PLL        0

#define PMB_BUS_BIU_BPCM         0
#define PMB_ADDR_BIU_BPCM        (39 | PMB_BUS_BIU_BPCM << PMB_BUS_ID_SHIFT)
#define PMB_ZONES_BIU_BPCM       1

#include "pmc_sysfs.h" 
static const struct bpcm_device bpcm_devs[] = {
        /* name                dev                         zones                      */
        { "periph",            PMB_ADDR_PERIPH,            PMB_ZONES_PERIPH            },
        { "chip_clkrst",       PMB_ADDR_CHIP_CLKRST,       PMB_ZONES_CHIP_CLKRST       },
        { "syspll",            PMB_ADDR_SYSPLL,            PMB_ZONES_SYSPLL            },
        { "pvtmon",            PMB_ADDR_PVTMON,            PMB_ZONES_PVTMON            },
        { "memc",              PMB_ADDR_MEMC,              PMB_ZONES_MEMC              },
        { "usb20",             PMB_ADDR_USB20_2X,          PMB_ZONES_USB20_2X,         },
        { "wan",               PMB_ADDR_WAN,               PMB_ZONES_WAN,              },
        { "xrdp",              PMB_ADDR_XRDP,              PMB_ZONES_XRDP,             },
        { "pcie0",             PMB_ADDR_PCIE0,             PMB_ZONES_PCIE0             },
        { "pcie1",             PMB_ADDR_PCIE1,             PMB_ZONES_PCIE1             },
        { "wlan0",             PMB_ADDR_WLAN0,             PMB_ZONES_WLAN0             },
        { "wlan0_phy1",        PMB_ADDR_WLAN0_PHY1,        PMB_ZONES_WLAN0_PHY1        },
        { "wlan0_phy2",        PMB_ADDR_WLAN0_PHY2,        PMB_ZONES_WLAN0_PHY2        },
        { "orion_cpu0",        PMB_ADDR_ORION_CPU0,        PMB_ZONES_ORION_CPU0        },
        { "orion_cpu1",        PMB_ADDR_ORION_CPU1,        PMB_ZONES_ORION_CPU1        },
        { "orion_cpu2",        PMB_ADDR_ORION_CPU2,        PMB_ZONES_ORION_CPU2        },
        { "orion_noncpu",      PMB_ADDR_ORION_NONCPU,      PMB_ZONES_ORION_NONCPU      },
        { "biu_pll",           PMB_ADDR_BIU_PLL,           PMB_ZONES_BIU_PLL           },
        { "biu",               PMB_ADDR_BIU_BPCM,          PMB_ZONES_BIU_BPCM          },
};


static const pmb_init_t xrdp_pmb[] = {
    /* name      dev                reset value  */
    {"xrdp",     PMB_ADDR_XRDP,     0xfffffff8},
    {"wan",      PMB_ADDR_WAN,      PMB_NO_RESET}
};

#endif
