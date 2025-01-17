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

#ifndef DETECT_H_INCLUDED
#define DETECT_H_INCLUDED

#include "opticaldet_ioctl.h"


#define EPON2G (1 << 31)
#define RDPA_WAN_MASK 0xF


#define OPTICALDET_IOCTL_DETECT 1
#define OPTICALDET_IOCTL_SD 2

#define OPTICALDET_SUCCESS      0
#define OPTICALDET_INVPARM      1
#define OPTICALDET_NOBUS        2
#define OPTICALDET_NOSFP        3
#define OPTICALDET_INVSFP       4

#define SMTC_VENDOR_PN          "GN28L96 A"
#define TRX_EEPROM_OFFSET_PN    40
#define TRX_EEPROM_LEN_PN       16

extern int trx_get_supported_wan_type_bm(int bus, SUPPORTED_WAN_TYPES_BITMAP *wan_type_bm);
extern int trx_get_lbe_polarity(int bus, TRX_SIG_ACTIVE_POLARITY *lbe_polarity_p);
extern int trx_get_tx_sd_polarity(int bus, TRX_SIG_ACTIVE_POLARITY *tx_sd_polarity_p);
extern int trx_get_vendor_name_part_num(int bus, char *vendor_name_p, int vendor_name_len,
                                 char *part_num_p, int part_num_len);
extern int trx_get_tx_sd_supported(int bus, TRX_SIG_PRESENCE *signal_supported_p);
extern int trx_get_type(int bus, TRX_TYPE *trx_type);
extern int trx_get_full_info(int bus, TRX_INFOMATION *trx_info);

#ifdef CONFIG_BP_PHYS_INTF
extern int opticaldet_get_i2c_bus_num(unsigned short intf_type, int intf_idx, int* bus);
#endif
extern int opticaldet_get_xpon_i2c_bus_num(int* bus);
extern int opticaldet_get_sgmii_i2c_bus_num(int* bus);
extern int opticaldet_is_xpon_sfp_present(void);

#endif /* DETECT_H_INCLUDED */
