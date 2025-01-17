/*
   Copyright (c) 2016 Broadcom Corporation
   All Rights Reserved

    <:label-BRCM:2016:DUAL/GPL:standard
    
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
 *  Created on: Aug 2017
 *      Author: dima.mamut@broadcom.com
 */

#include "bus_drv.h"
#include "mdio_drv_impl5.h"

/* Internal MDIO bus */
static int bus_mdio_v1_int_c22_read(uint32_t addr, uint16_t reg, uint16_t *val)
{
    return mdio_read_c22_register(MDIO_INT, addr, reg, val);
}

static int bus_mdio_v1_int_c22_write(uint32_t addr, uint16_t reg, uint16_t val)
{
    return mdio_write_c22_register(MDIO_INT, addr, reg, val);
}

static int bus_mdio_v1_int_c45_read(uint32_t addr, uint16_t dev, uint16_t reg, uint16_t *val)
{
    return mdio_read_c45_register(MDIO_INT, addr, dev, reg, val);
}

static int bus_mdio_v1_int_c45_write(uint32_t addr, uint16_t dev, uint16_t reg, uint16_t val)
{
    return mdio_write_c45_register(MDIO_INT, addr, dev, reg, val);
}

bus_drv_t bus_mdio_v1_int_drv =
{
    .c22_read = bus_mdio_v1_int_c22_read,
    .c22_write = bus_mdio_v1_int_c22_write,
    .c45_read = bus_mdio_v1_int_c45_read,
    .c45_write = bus_mdio_v1_int_c45_write,
};


/* External MDIO bus */
static int bus_mdio_v1_ext_c22_read(uint32_t addr, uint16_t reg, uint16_t *val)
{
    return mdio_read_c22_register(MDIO_EXT, addr, reg, val);
}

static int bus_mdio_v1_ext_c22_write(uint32_t addr, uint16_t reg, uint16_t val)
{
    return mdio_write_c22_register(MDIO_EXT, addr, reg, val);
}

static int bus_mdio_v1_ext_c45_read(uint32_t addr, uint16_t dev, uint16_t reg, uint16_t *val)
{
    return mdio_read_c45_register(MDIO_EXT, addr, dev, reg, val);
}

static int bus_mdio_v1_ext_c45_write(uint32_t addr, uint16_t dev, uint16_t reg, uint16_t val)
{
    return mdio_write_c45_register(MDIO_EXT, addr, dev, reg, val);
}

bus_drv_t bus_mdio_v1_ext_drv =
{
    .c22_read = bus_mdio_v1_ext_c22_read,
    .c22_write = bus_mdio_v1_ext_c22_write,
    .c45_read = bus_mdio_v1_ext_c45_read,
    .c45_write = bus_mdio_v1_ext_c45_write,
};
