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
/*
 * pmc_wan.c
 *
 *  Created on: Nov 30 2015
 *      Author: yonatani
 */

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/delay.h>
#include "pmc_drv.h"
#include "BPCM.h"
#include "pmc_wan.h"
#include "bcm_ubus4.h"
#include "boardparms.h"

static int wan_xpon_zones[] = XPON_POWER_ZONES;
static int wan_xdsl_zones[] = XDSL_POWER_ZONES;
static int wan_aeth_zones[] = AETH_POWER_ZONES;
static int wan_eth_zones[]  = EWAN_POWER_ZONES;

/* Manual/Force power control of the zones

   devAddr : PMB device address
   zone    : zone number
   on      : 1 = Power ON. 0 = Power OFF
*/
int manual_zone_power_control(int devAddr, int zone, int on)
{
    BPCM_PWR_ZONE_N_CONTROL reg;
    int status = 0;

    status = ReadBPCMRegister(devAddr, BPCMRegOffset(zones[zone].control), &reg.Reg32);
    if (status == kPMC_NO_ERROR) {
       if (on && reg.Bits.pwr_on_state == 0) {
          /* Requesting to power ON */
          reg.Bits.pwr_dn_req = 0;
          reg.Bits.pwr_up_req = 1;
          reg.Bits.dpg_ctl_en = 1;
          reg.Bits.mem_pwr_ctl_en = 1;
          reg.Bits.manual_ctl = 0;
          reg.Bits.manual_clk_en = 0;
          reg.Bits.manual_reset_ctl = 0;
          reg.Bits.manual_mem_pwr = 0;
          reg.Bits.manual_iso_ctl = 0;
          status = WriteBPCMRegister(devAddr, BPCMRegOffset(zones[zone].control), reg.Reg32);
       }
       else if(!on && reg.Bits.pwr_off_state == 0) {
          /* Requesting to power OFF */
          reg.Bits.pwr_dn_req = 1;
          reg.Bits.pwr_up_req = 0;
          reg.Bits.manual_ctl = 1;
          reg.Bits.manual_clk_en = 0;
          reg.Bits.manual_reset_ctl = 1;
          reg.Bits.manual_mem_pwr = 0;
          reg.Bits.manual_iso_ctl = 1;
          status = WriteBPCMRegister(devAddr, BPCMRegOffset(zones[zone].control), reg.Reg32);
       }
    }

    return status;
}

/*
  Power ON/OFF zones, specific to WAN interface.

  interface: WAN interface
  ctrl     : 1 = Power ON. 0 = Power OFF request
*/
int pmc_wan_interface_power_control(WAN_INTF interface, int ctrl)
{
   int *zones = NULL;
   int i, status = 0;

   /* Find the power zones for the given interface */
   switch (interface){
   case WAN_INTF_XPON:
      zones = wan_xpon_zones;
      break;
   case WAN_INTF_XDSL:
      zones = wan_xdsl_zones;
      break;
   case WAN_INTF_AETH:
      zones = wan_aeth_zones;
      break;
   case WAN_INTF_ETH:
      zones = wan_eth_zones;
      break;
   default:
      status = -1;
   }

   for (i = 0; zones && zones[i] != -1; i++){
      status += manual_zone_power_control(PMB_ADDR_WAN, zones[i], ctrl);
   }

   return status;
}

int pmc_wan_init(void)
{
    int status = 0;
#if defined (CONFIG_BCM96858) || defined(_BCM96858_)
    BPCM_SR_CONTROL sreset;
#endif

    // In 63158, WAN block is alreday powered ON in CFE to configure
    // VREG. Powering it again would reset the VREG settings.
#if !(defined(CONFIG_BCM963158) || defined(_BCM963158_))
    // To avoid glitch due to warm reboot, powerdown the block first.
    status  = PowerOffDevice(PMB_ADDR_WAN, 0);
    status += PowerOnDevice(PMB_ADDR_WAN);
#endif

#if defined (CONFIG_BCM96858) || defined(_BCM96858_)
    ubus_register_port(UCB_NODE_ID_SLV_WAN);

    // take pins out of reset
    // can be modified later for smaller granularity
    sreset.Bits_Wantop.wan_main_rst_n = 0;
    sreset.Bits_Wantop.wan_top_bb_rst_n = 0;
    sreset.Bits_Wantop.epon_core_rst_n = 0;
    sreset.Bits_Wantop.epon_rx_rclk16_sw_reset_n = 0;
    sreset.Bits_Wantop.epon_rx_rbc125_sw_reset_n = 0;
    sreset.Bits_Wantop.epon_tx_tclk16_sw_reset_n = 0;
    sreset.Bits_Wantop.epon_tx_clk125_sw_reset_n = 0;
    sreset.Bits_Wantop.gpon_main_rst_n = 0;
    sreset.Bits_Wantop.gpon_rx_rst_n = 0;
    sreset.Bits_Wantop.gpon_tx_rst_n = 0;
    sreset.Bits_Wantop.gpon_8khz_rst_n = 0;
    sreset.Bits_Wantop.ngpon_main_rst_n = 0;
    sreset.Bits_Wantop.ngpon_rx_rst_n = 0;
    sreset.Bits_Wantop.ngpon_tx_rst_n = 0;
    sreset.Bits_Wantop.ngpon_8khz_rst_n = 0;
    sreset.Bits_Wantop.gpon_nco_rst_n = 0;
    sreset.Bits_Wantop.apm_rst_n = 0;

    status += WriteBPCMRegister(PMB_ADDR_WAN, BPCMRegOffset(sr_control), sreset.Reg32);
#endif

#ifdef CONFIG_BP_PHYS_INTF
    /* Power ON interfaces that this platform is configured with.
       Otherwise turn OFF the interfaces to save power */
    if (BpGetPhyIntfNumByType(BP_INTF_TYPE_xPON)) {
        status += pmc_wan_interface_power_control(WAN_INTF_XPON, 1);
        status += pmc_wan_interface_power_control(WAN_INTF_AETH, 1);
    } else {
        status += pmc_wan_interface_power_control(WAN_INTF_XPON, 0);
        status += pmc_wan_interface_power_control(WAN_INTF_AETH, 0);
    }

    if (BpGetPhyIntfNumByType(BP_INTF_TYPE_xDSL)) {
        status += pmc_wan_interface_power_control(WAN_INTF_XDSL, 1);
    } else {
        status += pmc_wan_interface_power_control(WAN_INTF_XDSL, 0);
    }

    if (BpHasEthWanIntf()){
        status += pmc_wan_interface_power_control(WAN_INTF_ETH, 1);
    } else {
        status += pmc_wan_interface_power_control(WAN_INTF_ETH, 0);
    }
#endif
    return status;
}

#if defined (CONFIG_BCM963158)
int pmc_wan_ae_reset(void)
{
    BPCM_SR_CONTROL sreset;
    int status;

    status = ReadBPCMRegister(PMB_ADDR_WAN, BPCMRegOffset(sr_control), &sreset.Reg32);
    if( status != kPMC_NO_ERROR )
        return status;

    sreset.Bits_Wantop.ae_rx_rclk16_sw_reset_n = 1;
    sreset.Bits_Wantop.ae_rx_rbc125_sw_reset_n = 1;
    sreset.Bits_Wantop.ae_tx_tclk16_sw_reset_n = 1;
    sreset.Bits_Wantop.ae_tx_clk125_sw_reset_n = 1;

    status = WriteBPCMRegister(PMB_ADDR_WAN, BPCMRegOffset(sr_control), sreset.Reg32);
    if( status != kPMC_NO_ERROR )
        return status;

    udelay(5);

    sreset.Bits_Wantop.ae_rx_rclk16_sw_reset_n = 0;
    sreset.Bits_Wantop.ae_rx_rbc125_sw_reset_n = 0;
    sreset.Bits_Wantop.ae_tx_tclk16_sw_reset_n = 0;
    sreset.Bits_Wantop.ae_tx_clk125_sw_reset_n = 0;
    
    status = WriteBPCMRegister(PMB_ADDR_WAN, BPCMRegOffset(sr_control), sreset.Reg32);

    return status;
}

int pmc_wan_power_up(void)
{
    return  PowerOnDevice(PMB_ADDR_WAN);
}
#endif

int pmc_wan_power_down(void)
{
#if defined (CONFIG_BCM96858) || defined(_BCM96858_)
    ubus_deregister_port(UCB_NODE_ID_SLV_WAN);
#endif

    return  PowerOffDevice(PMB_ADDR_WAN, 0);
}
EXPORT_SYMBOL(pmc_wan_init);
EXPORT_SYMBOL(pmc_wan_power_down);
EXPORT_SYMBOL(pmc_wan_interface_power_control);
#if defined (CONFIG_BCM963158)
EXPORT_SYMBOL(pmc_wan_ae_reset);
EXPORT_SYMBOL(pmc_wan_power_up);
#endif
arch_initcall(pmc_wan_init);

