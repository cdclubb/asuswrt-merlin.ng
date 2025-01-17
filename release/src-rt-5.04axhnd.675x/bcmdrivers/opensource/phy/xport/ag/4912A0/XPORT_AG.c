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

#include "ru.h"

/******************************************************************************
 * Chip: 
 ******************************************************************************/
const ru_block_rec *RU_XPORT_BLOCKS[] =
{
    &XPORT_XLMAC_CORE_BLOCK,
    &XPORT_MIB_CORE_BLOCK,
    &XPORT_TOP_BLOCK,
    &XPORT_XLMAC_REG_BLOCK,
    &XPORT_MIB_REG_BLOCK,
    &XPORT_INTR_BLOCK,
    &XPORT_MAB_BLOCK,
    &XPORT_PORTRESET_BLOCK,
    NULL
};

/* End of file .c */
