/*
 * <:copyright-BRCM:2013:DUAL/GPL:standard
 * 
 *    Copyright (c) 2013 Broadcom 
 *    All Rights Reserved
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License, version 2, as published by
 * the Free Software Foundation (the "GPL").
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * 
 * A copy of the GPL is available at http://www.broadcom.com/licenses/GPLv2.php, or by
 * writing to the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 * 
 * :>
 */
// BCMFORMAT: notabs reindent:uncrustify:bcm_minimal_i4.cfg

/*
  If pinmux changes are needed after Linux init, support should be added to the board 
  driver including any necessary locking.
*/

#include "bcm_otp.h"
#include "shared_utils.h"

#include <bcm_map_part.h>
#include <linux/string.h>
#include <linux/spinlock.h>
static DEFINE_SPINLOCK(otp_spinlock);

#define OTP_DEBUG_IF    0
#define OTP_DBG_ENABLE  0

#if OTP_DBG_ENABLE
#if (INC_BTRM_BUILD==1)
#define OTP_DBG(... ) 
#else
#   define OTP_DBG_LEVEL      KERN_DEBUG
#   define OTP_DBG(fmt, args...) printk( OTP_DBG_LEVEL "OTP_drv: " fmt, ## args)
#endif /* INC_BTRM_BUILD==1 */
#else
#   define OTP_DBG(fmt, args...) /* not DBGging: nothing */
#endif /* OTP_DBG_ENABLE */


/************************************************************
 *  OTP CORE API                                            *
 ************************************************************/

#if OTP_DEBUG_IF
uint32_t otp_array[100] = {0};
#else
static int otp_wait_status( volatile uint32 * status_reg, int status_mask, int status_val )
{
   int cntr = BTRM_OTP_READ_TIMEOUT_CNT;
   while( cntr && ( (*status_reg & status_mask) != status_val ) )
   {
      cntr--;
   }

   if( cntr )
      return 0;
   else
      return -1;
}
#endif /* OTP_DEBUG_IF */

static int otp_get_cpu_lock( void )
{
    int ret = 0; 
    /* Get the hardware spinlock for OTP */
#if defined(_BCM96878_) || defined(CONFIG_BCM96878)   || \
    defined(_BCM947622_) || defined(CONFIG_BCM947622) || \
    defined(_BCM963178_) || defined(CONFIG_BCM963178) || \
    defined(_BCM96756_)  || defined(CONFIG_BCM96756)
    JTAG_OTP->WOTP_CPU_LOCK = WOTP_CPU_SOFT_LOCK_MASK;
    ret =  otp_wait_status( &JTAG_OTP->WOTP_CPU_LOCK, 
                WOTP_CPU_SOFT_LOCK_MASK, WOTP_CPU_SOFT_LOCK_MASK);
#endif
   
#if defined(_BCM94912_) || defined(CONFIG_BCM94912) || \
    defined(_BCM96813_) || defined(CONFIG_BCM96813) || \
    defined(_BCM963146_) || defined(CONFIG_BCM963146)
    JTAG_OTP->cpu_lock = OTP_CPU_LOCK_MASK;
    ret =  otp_wait_status( &JTAG_OTP->cpu_lock, 
                OTP_CPU_LOCK_MASK, OTP_CPU_LOCK_MASK);
#endif    
    return ret;
}

static int otp_release_cpu_lock( void )
{
    int ret = 0; 
    /* Release the hardware spinlock for OTP */
#if defined(_BCM96878_) || defined(CONFIG_BCM96878)   || \
    defined(_BCM947622_) || defined(CONFIG_BCM947622) || \
    defined(_BCM963178_) || defined(CONFIG_BCM963178) || \
    defined(_BCM96756_)  || defined(CONFIG_BCM96756)
    JTAG_OTP->WOTP_CPU_LOCK = 0;
#endif
   
#if defined(_BCM94912_) || defined(CONFIG_BCM94912) || \
    defined(_BCM96813_) || defined(CONFIG_BCM96813) || \
    defined(_BCM963146_) || defined(CONFIG_BCM963146)
    JTAG_OTP->cpu_lock = 0;
#endif    
    return ret;
}

/************************************************************
 *  OTP CORE API for All Devices                            *
 ************************************************************/

/************************************************************
 *  int bcm_otp_fuse_row 
 *  Input parameters: 
 *     row   - Row address
 *     value - 32-bit OTP value
 *  Return value:
 *      returns 0 if successful
 ***********************************************************/
int bcm_otp_fuse_row(int row, unsigned int val)
{
    return bcm_otp_fuse_row_ecc(row, val, 0);
}
/************************************************************
 *  int bcm_otp_fuse_row_ecc 
 *  Input parameters: 
 *     row   - Row address
 *     ecc   - row 7 bit ecc  
 *     value - 32-bit OTP value
 *  Return value:
 *      returns 0 if successful
 ***********************************************************/
int bcm_otp_fuse_row_ecc(int row, unsigned int val, unsigned int ecc)
{
   int ret = -1;
#if OTP_DEBUG_IF
   otp_array[addr] |= data;
   ret = 0;
#else      
   int i;
   int authVal[4] = {0xf,0x4,0x8,0xd};
   unsigned long flags;
   spin_lock_irqsave(&otp_spinlock, flags);

   /* Get the hardware spinlock for OTP */
   ret = otp_get_cpu_lock();
   if( ret )
   {
      OTP_DBG("%s: Error! Timed out waiting for OTP CPU lock!\n", __FUNCTION__);
      goto exit_fuse;
   }

   /* Enable CPU side programming of OTP */
   JTAG_OTP->ctrl1 |= JTAG_OTP_CTRL_CPU_MODE;

   /* Clear row register. A non-empty row register results in a failed prog-enable sequence on some SoCs */
   JTAG_OTP->ctrl3 = 0x0; 

   /* Put OTP in program mode --> prog-enable sequence */
   for (i=0;i<4;i++)
   {
      JTAG_OTP->ctrl2 = authVal[i];
      JTAG_OTP->ctrl0 = JTAG_OTP_CTRL_START | JTAG_OTP_CTRL_CMD_OTP_PROG_EN | JTAG_OTP_CTRL_PROG_EN;
      ret = otp_wait_status( &JTAG_OTP->status1, JTAG_OTP_STATUS_1_CMD_DONE, JTAG_OTP_STATUS_1_CMD_DONE);
      if( ret )
      {
         OTP_DBG("%s: Error! Timed out waiting for OTP command completion (PROG)! status:0x%08x\n", __FUNCTION__, JTAG_OTP->status1);
         goto exit_fuse;
      }
      JTAG_OTP->ctrl0 = 0x0;
   }

   /* Write OTP row */
   if ((JTAG_OTP->status1 & JTAG_OTP_STATUS_1_PROG_OK) == JTAG_OTP_STATUS_1_PROG_OK)
   {
      JTAG_OTP->ctrl2 = val;
#if defined(_BCM96878_) || defined(CONFIG_BCM96878)  || \
   defined(_BCM96855_) || defined(CONFIG_BCM96855)  || \
   defined(_BCM963158_) || defined(CONFIG_BCM96158)  || \
   defined(_BCM96856_)  || defined(CONFIG_BCM9656)   || \
   defined(_BCM947622_) || defined(CONFIG_BCM947622) || \
   defined(_BCM963178_) || defined(CONFIG_BCM963178) || \
   defined(_BCM96846_)  || defined(CONFIG_BCM9646) || \
   defined(_BCM96756_)  || defined(CONFIG_BCM96756)
      if (ecc) {
          JTAG_OTP->ctrl2_hi = ecc;
      }
#endif
      JTAG_OTP->ctrl3 = row;

      if( row == OTP_JTAG_CUST_LOCK_ROW )
         JTAG_OTP->ctrl0 = JTAG_OTP_CTRL_START | JTAG_OTP_CTRL_CMD_PROG_LOCK | JTAG_OTP_CTRL_ACCESS_MODE | JTAG_OTP_CTRL_PROG_EN;
      else
         JTAG_OTP->ctrl0 = JTAG_OTP_CTRL_START | JTAG_OTP_CTRL_CMD_PROG | JTAG_OTP_CTRL_ACCESS_MODE | JTAG_OTP_CTRL_PROG_EN;

      ret = otp_wait_status( &JTAG_OTP->status1, JTAG_OTP_STATUS_1_CMD_DONE, JTAG_OTP_STATUS_1_CMD_DONE);
      if( ret )
      {
         OTP_DBG("%s: Error! Timed out waiting for OTP command completion (WRITE)! status: 0x%08x\n", __FUNCTION__, JTAG_OTP->status1);
         goto exit_fuse;
      }
      JTAG_OTP->ctrl0 = 0x0;
      OTP_DBG("OTP fusing has completed as expected\n");
      ret = 0;
   }
   else
   {
      ret = -1;
      OTP_DBG("OTP fusing didn't complete as expected\n");
   }

   JTAG_OTP->ctrl1 &= ~JTAG_OTP_CTRL_CPU_MODE;

exit_fuse:

   /* Release hardware spinlock for OTP */
   otp_release_cpu_lock();

   spin_unlock_irqrestore(&otp_spinlock, flags);
      
#endif  /* OTP_DEBUG_IF */
   return ret;
}

int bcm_otp_get_row(int row, unsigned int* val)
{
   return bcm_otp_get_row_ecc(row, val, NULL);
}
/***********************************************************
 *  int bcm_otp_get_row_ecc
 *  Input parameters: 
 *     row    - Row address
 *     *val - Pointer to 32-bit OTP value
 *     *val_hi - Pointer to 32-bit OTP hi word data (typically ecc)
 *  Return value:
 *      returns 0 if successful, value in *value
 ***********************************************************/
int bcm_otp_get_row_ecc(int row, unsigned int* val, unsigned int* val_hi)
{
#if defined(CONFIG_BRCM_IKOS)
   *val =0;
    return 0;
#else
   int ret = -1;
#if OTP_DEBUG_IF
   *value = otp_array[row];
   ret = 0;
#else      
   unsigned long flags;
   
   spin_lock_irqsave(&otp_spinlock, flags);

   /* Get the hardware spinlock for OTP */
   ret = otp_get_cpu_lock();
   if( ret )
   {
      OTP_DBG("%s: Error! Timed out waiting for OTP CPU lock!\n", __FUNCTION__);
      goto exit_read;
   }

   /* turn on cpu mode, set up row addr, activate read word */
   JTAG_OTP->ctrl1 |= JTAG_OTP_CTRL_CPU_MODE;
   JTAG_OTP->ctrl3 = row;
   JTAG_OTP->ctrl0 = JTAG_OTP_CTRL_START | JTAG_OTP_CTRL_PROG_EN | JTAG_OTP_CTRL_ACCESS_MODE;

   /* Wait for low CMD_DONE (current operation has begun), reset countdown, wait for retrieval to complete */
   ret = otp_wait_status( &JTAG_OTP->status1, JTAG_OTP_STATUS_1_CMD_DONE, 0);

   /* Wait for high CMD_DONE */
   ret = otp_wait_status( &JTAG_OTP->status1, JTAG_OTP_STATUS_1_CMD_DONE, JTAG_OTP_STATUS_1_CMD_DONE);
   if( ret )
   {
      OTP_DBG("%s: Error! Timed out waiting for OTP command completion (READ)! status: 0x%08x\n", __FUNCTION__, JTAG_OTP->status1);
      goto exit_read;
   }

   /* If read was successful, retrieve data */
   if( ret == 0 )
   {
      *val = JTAG_OTP->status0;
#if defined(_BCM96878_) || defined(CONFIG_BCM96878)  || \
   defined(_BCM96855_)  || defined(CONFIG_BCM9655)   || \
   defined(_BCM963158_) || defined(CONFIG_BCM96158)  || \
   defined(_BCM96856_)  || defined(CONFIG_BCM9656)   || \
   defined(_BCM947622_) || defined(CONFIG_BCM947622) || \
   defined(_BCM963178_) || defined(CONFIG_BCM963178) || \
   defined(_BCM96846_)  || defined(CONFIG_BCM9646) || \
   defined(_BCM96756_)  || defined(CONFIG_BCM96756)  
      if (val_hi) {
         *val_hi = JTAG_OTP->status0_hi;
      }
#endif
   }

   /* zero out the ctrl_0 reg, turn off cpu mode, return results */
   JTAG_OTP->ctrl0 = 0;
   JTAG_OTP->ctrl1 &= ~JTAG_OTP_CTRL_CPU_MODE;

exit_read:

   /* Release hardware spinlock for OTP */
   otp_release_cpu_lock();

   spin_unlock_irqrestore(&otp_spinlock, flags);
      
#endif  /* OTP_DEBUG_IF */
   return ret;
#endif /* CONFIG_BRCM_IKOS */
}

/************************************************************
 *  OTP utility functions                                   *
 ************************************************************/

#if defined(_BCM94908_) || defined(CONFIG_BCM94908) || defined(_BCM96858_) || defined(CONFIG_BCM96858) || \
    defined(_BCM963158_) || defined(CONFIG_BCM963158) || defined(_BCM96846_) || defined(CONFIG_BCM96846) || \
    defined(_BCM96856_) || defined(CONFIG_BCM96856) || defined(_BCM963178_) || defined(CONFIG_BCM963178) || \
    defined(_BCM947622_) || defined(CONFIG_BCM947622) || defined(_BCM96756_)  || defined(CONFIG_BCM96756)

/***********************************************************
 *  int sotp_sec89_both_readlocked(void)
 *  Input parameters: 
 *      none
 *  Return value:
 *      returns 1 if both sotp sections 8 and 9 are locked down from being read
 **********************************************************/
int sotp_sec89_both_readlocked(void)
{
   int rval = 0;
   uint32_t sotpOtpRegionRdLockReg  = *((uint32_t *)(SOTP_BASE + SOTP_OTP_REGION_RD_LOCK));

   /* Check to see if the SOTP register set is even accessible.         */
   if (sotpOtpRegionRdLockReg == 0xdeadbeef)
      rval = 1;
   else
   {
      /* regions 10 thru 12 are section 8; regions 13 thru 15 are section 9 */
      /* so a mask of 0x3f is enough bits to check both sections in one shot*/
      if (((sotpOtpRegionRdLockReg >> 10) & 0x3f) == 0x3f)
         rval = 1;
   }
   return rval;
}
#endif

/***********************************************************
 *  int bcm_otp_fld_secure_rows(void)
 *  Input parameters: 
 *      none
 *  Return value:
 *      returns 1 if rows fld are fused and readlocked 
 **********************************************************/
int bcm_otp_fld_secure_rows(void)
{
#if defined(_BCM94908_) || defined(CONFIG_BCM94908) || defined(_BCM96858_) || defined(CONFIG_BCM96858) || \
    defined(_BCM963158_) || defined(CONFIG_BCM963158) || defined(_BCM96846_) || defined(CONFIG_BCM96846) || \
    defined(_BCM96856_) || defined(CONFIG_BCM96856) || defined(_BCM963178_) || defined(CONFIG_BCM963178) || \
    defined(_BCM947622_) || defined(CONFIG_BCM947622) || defined(_BCM96756_) || defined(CONFIG_BCM96756)
    return !sotp_sec89_both_readlocked();
#elif defined(_BCM96878_) || defined(CONFIG_BCM96878) || defined(_BCM96855_) || defined(CONFIG_BCM96855)
    return !((*(volatile uint32_t*)(SEC_KEY_OBJ_BASE+SEC_KEY_OBJ_KEY0_STATUS_OFFSET) >> SEC_KEY_OBJ_KEY0_STATUS_SHIFT) & SEC_KEY_OBJ_KEY0_STATUS_MASK );
#else
    return -1;
#endif 
}
int bcm_is_btrm_boot(void)
{
    int rval = 0;
    unsigned int row;

#if !defined(_BCM963148_) && !defined(CONFIG_BCM963148)

#if defined(_BCM96858_) || defined(CONFIG_BCM96858)
    uint32 bootsel = ((MISC->miscStrapBus & MISC_STRAP_BUS_BOOT_SEL0_4_MASK) >> MISC_STRAP_BUS_BOOT_SEL0_4_SHIFT) |
                     ((MISC->miscStrapBus & MISC_STRAP_BUS_BOOT_SEL5_MASK) >> BOOT_SEL5_STRAP_ADJ_SHIFT);
    if ( ((bootsel & BOOT_SEL_STRAP_BOOT_SEL_MASK) != BOOT_SEL_STRAP_SPI_NOR) ||
          !(MISC->miscStrapBus & MISC_STRAP_BUS_BOOROM_BOOT_N) )
#elif defined(_BCM963138_) || defined(CONFIG_BCM963138)
    if ((MISC->miscStrapBus & MISC_STRAP_BUS_SW_BOOT_NORMAL_MASK) == 0)
#elif defined(_BCM94908_) || defined(CONFIG_BCM94908) || defined(_BCM963158_) || defined(CONFIG_BCM963158) || \
      defined(_BCM96846_) || defined(CONFIG_BCM96846) || defined(_BCM96856_) || defined(CONFIG_BCM96856) || \
      defined(_BCM96878_) || defined(CONFIG_BCM96878) || defined(_BCM96855_) || defined(CONFIG_BCM96855)
    if ((MISC->miscStrapBus & MISC_STRAP_BUS_BOOTROM_BOOT_N) == 0)
#elif defined(_BCM963178_) || defined(CONFIG_BCM963178) || defined(_BCM947622_) || defined(CONFIG_BCM947622) || \
      defined(_BCM96756_)  || defined(CONFIG_BCM96756)
    if (MISC->miscStrapBus & MISC_STRAP_BUS_BOOTROM_BOOT)
#endif
    {
        return 1;
    }
#endif

    rval = bcm_otp_get_row(OTP_BRCM_BTRM_BOOT_ENABLE_ROW, &row);
    if ( !rval && (row & OTP_BRCM_BTRM_BOOT_ENABLE_MASK) )
    {
        rval = bcm_otp_get_row( OTP_CUST_BTRM_BOOT_ENABLE_ROW, &row);
        if ( !rval && (row & OTP_CUST_BTRM_BOOT_ENABLE_MASK) )
            rval = 1;
        else
            rval = 0;
    }
    else
        rval = 0;

    return rval;
}


int bcm_otp_is_boot_secure(void)
{
    int rval;
#if defined(_BCM96838_)

   rval = bcm_is_btrm_boot();
   if (rval)
   {
      rval = ((*(uint32_t *)(OTP_BASE + OTP_SHADOW_ADDR_MARKET_ID_CUST_ROW)) & OTP_MFG_MRKTID_OTP_BITS_MASK) >> OTP_MFG_MRKTID_OTP_BITS_SHIFT;
      if (rval) 
         rval = 1;
   }

#else
    unsigned int bcmBtrmEn, cusBtrmEn, cusMtkid;

#if defined(_BTRM_DEVEL_)
    return ROM_ARG_ISSET(ROM_ARG_SEC_FLD_DEVEL);
#endif
    rval = bcm_otp_get_row(OTP_BRCM_BTRM_BOOT_ENABLE_ROW, &bcmBtrmEn);
    rval |= bcm_otp_get_row( OTP_CUST_BTRM_BOOT_ENABLE_ROW, &cusBtrmEn);
    rval |= bcm_otp_get_row( OTP_CUST_MFG_MRKTID_ROW, &cusMtkid);
    
    if ( !rval && (bcmBtrmEn & OTP_BRCM_BTRM_BOOT_ENABLE_MASK) &&
          (cusBtrmEn & OTP_CUST_BTRM_BOOT_ENABLE_MASK) && 
          (cusMtkid & OTP_CUST_MFG_MRKTID_MASK) )
    {
        rval = 1;
#if defined(_BCM94908_) || defined(CONFIG_BCM94908) || defined(_BCM96858_) || defined(CONFIG_BCM96858) || \
    defined(_BCM963158_) || defined(CONFIG_BCM963158) || \
    defined(_BCM96856_) || defined(CONFIG_BCM96856) || defined(_BCM96846_) || defined(CONFIG_BCM96846)
        /* For these targets, the mode still might be mfg secure if sotp section 8 or 9 are not readlocked */
        if (bcm_otp_fld_secure_rows())
           rval = 0;
#endif
    }
    else
        rval = 0;

#endif

    return rval;
}


#if defined(_BCM94908_) || defined(CONFIG_BCM94908) || defined(_BCM96858_) || defined(CONFIG_BCM96858) || \
    defined(_BCM963158_) || defined(CONFIG_BCM963158) || defined(_BCM96878_) || defined(CONFIG_BCM96878) || \
    defined(_BCM96846_) || defined(CONFIG_BCM96846) || defined(_BCM96856_) || defined(CONFIG_BCM96856) || \
    defined(_BCM963178_) || defined(CONFIG_BCM963178) || defined(_BCM947622_) || defined(CONFIG_BCM947622) || \
    defined(_BCM96855_) || defined(CONFIG_BCM96855) || defined(_BCM96756_) || defined(CONFIG_BCM96756)
int bcm_otp_is_boot_mfg_secure(void)
{
    int rval;
    unsigned int bcmBtrmEn, cusBtrmEn, cusMtkid;

#if defined(_BTRM_DEVEL_)
    return ROM_ARG_ISSET(ROM_ARG_SEC_MFG_DEVEL);
#endif

    rval = bcm_otp_get_row(OTP_BRCM_BTRM_BOOT_ENABLE_ROW, &bcmBtrmEn);
    rval |= bcm_otp_get_row( OTP_CUST_BTRM_BOOT_ENABLE_ROW, &cusBtrmEn);
    rval |= bcm_otp_get_row( OTP_CUST_MFG_MRKTID_ROW, &cusMtkid);
    
    if ( !rval && (bcmBtrmEn & OTP_BRCM_BTRM_BOOT_ENABLE_MASK) &&
          (cusBtrmEn & OTP_CUST_BTRM_BOOT_ENABLE_MASK) )
    {
       if (cusMtkid & OTP_CUST_MFG_MRKTID_MASK)
       {
          if (!bcm_otp_fld_secure_rows())
             rval = 0; /* field secure */
          else
             rval = 1; /* mfg secure */
       }
       else
          rval = 1; /* mfg secure */
    }
    else
       rval = 0; /* unsecure */

    return rval;
}
#endif

#if defined(_BCM94908_) || defined(CONFIG_BCM94908) || defined(_BCM947622_) || defined(CONFIG_BCM947622)
int bcm_otp_is_sgmii_disabled(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_SGMII_DISABLE_ROW, &row);
    *val = (row & OTP_SGMII_DISABLE_MASK) >> OTP_SGMII_DISABLE_SHIFT;

    return rval;
}
#endif

#if defined(_BCM96858_) || defined(CONFIG_BCM96858) || defined(_BCM96878_) || defined(CONFIG_BCM96878) || \
    defined(_BCM96846_) || defined(CONFIG_BCM96846) || defined(_BCM96856_) || defined(CONFIG_BCM96856) || \
    defined(_BCM947622_) || defined(CONFIG_BCM947622)
int bcm_otp_get_cpu_clk(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_CPU_CLOCK_FREQ_ROW, &row);
    *val = (row & OTP_CPU_CLOCK_FREQ_MASK) >> OTP_CPU_CLOCK_FREQ_SHIFT; 

    return rval;
}
#endif

int bcm_otp_is_usb3_disabled(unsigned int* val)
{
    int rval = 0; 
#if defined(_BCM947622_) || defined(CONFIG_BCM947622) || defined(_BCM96756_) || defined(CONFIG_BCM96756)
    unsigned int row;
    rval = bcm_otp_get_row(OTP_USB3_DISABLE_ROW, &row);

    if(row & OTP_USB3_DISABLE_MASK)
        *val = 1;
    else
        *val = 0;
#else
    *val = 0;
#endif

    return rval;
}

#if defined(_BCM96856_) || defined(CONFIG_BCM96856)
int bcm_otp_get_chipvar(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_SEC_CHIPVAR_ROW, &row);
    *val = (row & OTP_SEC_CHIPVAR_MASK) >> OTP_SEC_CHIPVAR_SHIFT;

    return rval;
}
#endif

#if defined(_BCM96858_) || defined(CONFIG_BCM96858)
int bcm_otp_get_chipid(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_SEC_CHIPVAR_ROW, &row);
    *val = (row & OTP_SEC_CHIPVAR_MASK) >> OTP_SEC_CHIPVAR_SHIFT;

    return rval;
}

int bcm_otp_get_usb_port_disabled(int port, unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_USB_DISABLE_ROW, &row);
    switch (port)
    {
        case 0:
            *val = (row & OTP_USB_DISABLE0_MASK) >> OTP_USB_DISABLE0_SHIFT;
            break;
        case 1:
            *val = (row & OTP_USB_DISABLE1_MASK) >> OTP_USB_DISABLE1_SHIFT;
            break;
        default:
            *val = (row & OTP_USB_DISABLE_XHCI_MASK) >> OTP_USB_DISABLE_XHCI_SHIFT;
    }

    return rval;
}
#endif

#if defined(_BCM96858_) || defined(CONFIG_BCM96858) || \
    defined(_BCM94908_) || defined(CONFIG_BCM94908) || \
    defined(_BCM963158_) || defined(CONFIG_BCM963158) || \
    defined(_BCM96846_) || defined(CONFIG_BCM96846) || \
    defined(_BCM96878_) || defined(CONFIG_BCM96878) || \
    defined(_BCM96855_) || defined(CONFIG_BCM96855) || \
    defined(_BCM96856_) || defined(CONFIG_BCM96856) || \
    defined(_BCM963178_) || defined(CONFIG_BCM963178) || \
    defined(_BCM947622_) || defined(CONFIG_BCM947622) || \
    defined(_BCM96756_) || defined(CONFIG_BCM96756)  

#if defined(_BCM96846_) || defined(CONFIG_BCM96846)
extern unsigned int UtilGetChipRev(void);
#endif

int bcm_otp_get_nr_cpus(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_CPU_CORE_CFG_ROW, &row);
    *val = (row & OTP_CPU_CORE_CFG_MASK) >> OTP_CPU_CORE_CFG_SHIFT;

#if defined(_BCM963158_) || defined(CONFIG_BCM963158)
     {
         if(UtilGetChipId() == CHIP_63152_ID_HEX)
             *val = 2;
     }
#endif

#if defined(_BCM96858_) || defined(CONFIG_BCM96858)
    {
        unsigned int chipId = 0;

        bcm_otp_get_chipid(&chipId);
        if (chipId == 0x5 || chipId == 0x2 || chipId == 0xb)
            *val = 2;
    }
#endif
#if defined(_BCM96846_) || defined(CONFIG_BCM96846)
    {
        if (UtilGetChipRev() == 0xA0)
            *val = 1;
        else 
            *val = 0;
    }
#endif
#if defined(_BCM96855_) || defined(CONFIG_BCM96855)
    if ((*val>=0) && (*val<=5))
        *val = 0;
    else if (*val==6)
        *val = 1;
    else if (*val==7)
        *val = 2;
#endif

    return rval;
}

#if defined(_BCM96858_) || defined(CONFIG_BCM96858)
int bcm_otp_get_pmc_boot_sts(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_PMC_BOOT_ROW, &row);
    *val = (row & OTP_PMC_BOOT_MASK) >> OTP_PMC_BOOT_SHIFT;

    return rval;
}
#endif

#if !defined(_BCM96846_) && !defined(CONFIG_BCM96846) && !defined(_BCM96856_) && !defined(CONFIG_BCM96856) && \
    !defined(_BCM963178_) && !defined(CONFIG_BCM963178) && !defined(_BCM947622_) && !defined(CONFIG_BCM947622) && \
    !defined(_BCM96878_) && !defined(CONFIG_BCM96878) && !defined(_BCM96855_) && !defined(CONFIG_BCM96855) && \
    !defined(_BCM96756_) && !defined(CONFIG_BCM96756)
int bcm_otp_is_sata_disabled(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_SATA_DISABLE_ROW, &row);
    *val = (row & OTP_SATA_DISABLE_MASK) >> OTP_SATA_DISABLE_SHIFT;

    return rval;
}
#endif
int bcm_otp_is_pcm_disabled(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_PCM_DISABLE_ROW, &row);
    *val = (row & OTP_PCM_DISABLE_MASK) >> OTP_PCM_DISABLE_SHIFT;

    return rval;
}
#endif

#if defined(_BCM947622_) || defined(CONFIG_BCM947622) || defined(_BCM94912_) || defined(CONFIG_BCM94912) || \
    defined(_BCM96813_) || defined(CONFIG_BCM96813) || defined(_BCM96756_) || defined(CONFIG_BCM96756)
int bcm_otp_is_pcie_port_disabled(unsigned int pcie_port_num, unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_PCIE_PORT_DISABLE_ROW, &row);
    row &= (OTP_PCIE_PORT_DISABLE_MASK);
    row = row >> OTP_PCIE_PORT_DISABLE_SHIFT;
    *val = row & (1 << pcie_port_num);
    return rval;
}
#endif

#if defined(_BCM947622_) || defined(CONFIG_BCM947622) || defined(_BCM963178_) || defined(CONFIG_BCM963178) || \
    defined(_BCM96756_) || defined(CONFIG_BCM96756)
int bcm_otp_get_ldo_trim(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_LDO_TRIM_ROW, &row);

    *val = (row & OTP_LDO_TRIM_MASK) >> OTP_LDO_TRIM_SHIFT;

    return rval;
}
#endif

#if defined(_BCM96756_) || defined(CONFIG_BCM96756)
int bcm_otp_is_rescal_enabled(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_RESCAL_ENABLE_ROW, &row);

    *val = (row & OTP_RESCAL_ENABLE_MASK) >> OTP_RESCAL_ENABLE_SHIFT;

    return rval;
}
#endif

#if defined(CONFIG_BCM94912) || defined(_BCM94912_) || defined(_BCM96813_) || defined(CONFIG_BCM96813)
int bcm_otp_get_dgasp_trim(unsigned int* val)
{
    unsigned int row;
    int rval = bcm_otp_get_row(OTP_DGASP_TRIM_ROW, &row);

    *val = (row & OTP_DGASP_TRIM_MASK) >> OTP_DGASP_TRIM_SHIFT;

    return rval;
}
#endif

#if defined(CONFIG_BCM94912) || defined(_BCM94912_) || defined(_BCM96813_) || defined(CONFIG_BCM96813)
EXPORT_SYMBOL(bcm_otp_get_dgasp_trim);
#endif

EXPORT_SYMBOL(bcm_is_btrm_boot);
EXPORT_SYMBOL(bcm_otp_is_boot_secure);

EXPORT_SYMBOL(bcm_otp_get_row);
EXPORT_SYMBOL(bcm_otp_fuse_row);
EXPORT_SYMBOL(bcm_otp_fuse_row_ecc);
EXPORT_SYMBOL(bcm_otp_get_row_ecc);

#if defined (CONFIG_BCM96858) || defined(CONFIG_BCM94908) || \
    defined(CONFIG_BCM963158) || defined(CONFIG_BCM96878) || \
    defined(CONFIG_BCM96846) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM96855)
EXPORT_SYMBOL(bcm_otp_get_nr_cpus);
EXPORT_SYMBOL(bcm_otp_is_boot_mfg_secure);
EXPORT_SYMBOL(bcm_otp_is_pcm_disabled);

#if defined(_BCM94908_) || defined(CONFIG_BCM94908) || defined(_BCM947622_) || defined(CONFIG_BCM947622)
EXPORT_SYMBOL(bcm_otp_is_sgmii_disabled);
#endif

#if defined (CONFIG_BCM96858) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM96878) || defined(CONFIG_BCM96856) || \
    defined(CONFIG_BCM947622)
EXPORT_SYMBOL(bcm_otp_get_cpu_clk);
#endif

EXPORT_SYMBOL(bcm_otp_is_usb3_disabled);

#if defined(_BCM96858_) || defined(CONFIG_BCM96858)
EXPORT_SYMBOL(bcm_otp_get_usb_port_disabled);
EXPORT_SYMBOL(bcm_otp_get_pmc_boot_sts);
#endif

#if !defined(CONFIG_BCM96846) && !defined(CONFIG_BCM96856) && !defined(CONFIG_BCM96878) && !defined(CONFIG_BCM963178) && \
    !defined(CONFIG_BCM947622) && !defined(CONFIG_BCM96855) && !defined(CONFIG_BCM96756)
EXPORT_SYMBOL(bcm_otp_is_sata_disabled);
#endif

#if defined(CONFIG_BCM96856)
EXPORT_SYMBOL(bcm_otp_get_chipvar);
#endif

#endif

