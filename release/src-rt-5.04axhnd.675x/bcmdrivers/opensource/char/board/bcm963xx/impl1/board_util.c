/*
* <:copyright-BRCM:2016:DUAL/GPL:standard
* 
*    Copyright (c) 2016 Broadcom 
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

#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <bcmnetlink.h>
#include <net/sock.h>

#include <bcmtypes.h>
#include <bcm_map_part.h>
#include <board.h>
#include <boardparms.h>
#include <boardparms_voice.h>
#include <flash_api.h>
#include <flash_common.h>
#include <shared_utils.h>
#include <bcm_pinmux.h>
#include <bcmpci.h>
#include <linux/bcm_log.h>
#include <bcmSpiRes.h>
#include "bcm_otp.h"

#include "board_util.h"
#include "board_image.h"
#include "board_dg.h"

#if defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148)
#if defined(CONFIG_SMP)
#include <linux/cpu.h>
#endif
#include "pmc_dsl.h"
#include "pmc_apm.h"
#endif

#if defined(CONFIG_BCM94908)
#include "clk_rst.h"
#endif

extern int g_ledInitialized;

// macAddrLock is used by kerSysGetMacAddress and kerSysReleaseMacAddress
// to protect access to g_pMacInfo
static PMAC_INFO g_pMacInfo = NULL;
static DEFINE_SPINLOCK(macAddrLock);
static PGPON_INFO g_pGponInfo = NULL;
static unsigned long g_ulSdramSize;

#define MAX_PAYLOAD_LEN 64
static struct sock *g_monitor_nl_sk;
static int g_monitor_nl_pid = 0 ;

static kerSysMacAddressNotifyHook_t kerSysMacAddressNotifyHook = NULL;

#if defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148)
/*SATA Test module callback */
int (*bcm_sata_test_ioctl_fn)(void *) = NULL; 
EXPORT_SYMBOL(bcm_sata_test_ioctl_fn);
#endif

/* A global variable used by Power Management and other features to determine if Voice is idle or not */
volatile int isVoiceIdle = 1;
EXPORT_SYMBOL(isVoiceIdle);

BOARD_IOC* board_ioc_alloc(void)
{
    BOARD_IOC *board_ioc =NULL;
    board_ioc = (BOARD_IOC*) kmalloc( sizeof(BOARD_IOC) , GFP_KERNEL );
    if(board_ioc)
    {
        memset(board_ioc, 0, sizeof(BOARD_IOC));
    }
    return board_ioc;
}

void board_ioc_free(BOARD_IOC* board_ioc)
{
    if(board_ioc)
    {
        kfree(board_ioc);
    }
}

int ConfigCs (BOARD_IOCTL_PARMS *parms)
{
    int                     retv = 0;
    return( retv );
}

int kerSysGetResetReason(void)
{
    int resetReason = 0;

#if !defined(CONFIG_BCM947189) && !defined(CONFIG_BCM963138) && !defined(CONFIG_BCM963148)
#if defined(CONFIG_BCM963158) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM96856) || defined (CONFIG_947622) || \
    defined (CONFIG_BCM963178) || defined(CONFIG_BCM94908)  || defined(CONFIG_BCM96858) || defined(CONFIG_BCM96878) || \
    defined(CONFIG_BCM96855) || defined(CONFIG_BCM96756)
    resetReason = TIMER->ResetReason;
#endif    
#endif    

    return resetReason;
}

int kerSysGetResetStatus(void)
{
    
    int resetStatus = 0;
#if !defined(CONFIG_BCM947189)

#if defined(CONFIG_BCM96846) || defined(CONFIG_BCM96878) || defined(CONFIG_BCM96856) || defined(CONFIG_947622) || \
    defined(CONFIG_BCM963178) || defined(CONFIG_BCM96855) || defined(CONFIG_BCM96756) || \
    (defined(CONFIG_BCM963158) && (CONFIG_BRCM_CHIP_REV != 0x63158A0))
    resetStatus = TOPCTRL->ResetStatus & RESET_STATUS_MASK;
#elif defined(CONFIG_BCM94908) || defined(CONFIG_BCM96858) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148)
    resetStatus = TIMER->ResetStatus & RESET_STATUS_MASK;
#endif

#endif

    return resetStatus;
}
EXPORT_SYMBOL(kerSysGetResetStatus);

void print_rst_status(void)
{
#if !defined(CONFIG_BCM947189)
    int resetStatus = kerSysGetResetStatus();
#if !defined(CONFIG_BCM963138) && !defined(CONFIG_BCM963148)
    int resetReason = kerSysGetResetReason();
#endif

    printk("Last RESET due to ");
    switch ( resetStatus )
    {
       case PCIE_RESET_STATUS:
          printk(KERN_CONT "PCIE reset\n");
          break;
       case SW_RESET_STATUS:
          printk(KERN_CONT "SW reset\n");
          break;
       case HW_RESET_STATUS:
          printk(KERN_CONT "HW reset\n");
          break;
       case POR_RESET_STATUS:
          printk(KERN_CONT "POR reset\n");
          break;
       default:
          printk(KERN_CONT "Unknown\n");
    }
#if !defined(CONFIG_BCM963138) && !defined(CONFIG_BCM963148)
    printk("RESET reason: 0x%08x\n", resetReason);
#endif
        
#endif    
}

int kerSysIsBatteryEnabled(void)
{
#if defined(CONFIG_BCM_BMU)
    unsigned short bmuen;

    if (BpGetBatteryEnable(&bmuen) == BP_SUCCESS) {
        return (bmuen);
    }
#endif
    return 0;
}

void __init kerSysInitBatteryManagementUnit(void)
{
#if defined(CONFIG_BCM_BMU)
    if (kerSysIsBatteryEnabled()) {
        pmc_apm_power_up();
#if defined(CONFIG_BCM963148)
        // APM_ANALOG_BG_BOOST and APM_LDO_VREGCNTL_7 default to 0 in 63148 and need to be set
        APM_PUB->reg_apm_analog_bg |= APM_ANALOG_BG_BOOST;
        APM_PUB->reg_codec_config_4 |= APM_LDO_VREGCNTL_7;
#endif
    }
#endif
}

PMAC_INFO get_mac_info(void)
{
    return  g_pMacInfo;
}

static int getNvram_ulNumMacAddrs(void)
{
    char value[25];
    int addrs=0, ret=0;

    memset(value, '\0', sizeof(value));
    ret=envram_get_locked(NVRAM_ULNUMMACADDRS, value, sizeof(value));
    if( ret > 0)
    {
        sscanf(value, "%d", &addrs);
    }
return addrs;
}

void getNvram_ucaBaseMacAddr(unsigned char *ucaBaseMacAddr, int len)
{
    char value[50];
    int ret=0;

    memset(value, '\0', sizeof(value));
    ret=envram_get_locked(NVRAM_UCABASEMACADDR, value, sizeof(value));
    if( ret > 0)
    {
        sscanf(value, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx", &ucaBaseMacAddr[0],
            &ucaBaseMacAddr[1],&ucaBaseMacAddr[2],&ucaBaseMacAddr[3],
            &ucaBaseMacAddr[4],&ucaBaseMacAddr[5]);
    }
	
}

void __init set_mac_info( void )
{
    unsigned int ulNumMacAddrs;

    ulNumMacAddrs=getNvram_ulNumMacAddrs();

    if( ulNumMacAddrs > 0 && ulNumMacAddrs <= NVRAM_MAC_COUNT_MAX )
    {
        unsigned long ulMacInfoSize =
            sizeof(MAC_INFO) + ((sizeof(MAC_ADDR_INFO)) * (ulNumMacAddrs-1));

        g_pMacInfo = (PMAC_INFO) kmalloc( ulMacInfoSize, GFP_KERNEL );

        if( g_pMacInfo )
        {
            memset( g_pMacInfo, 0x00, ulMacInfoSize );
            g_pMacInfo->ulNumMacAddrs = ulNumMacAddrs;
            getNvram_ucaBaseMacAddr( g_pMacInfo->ucaBaseMacAddr, NVRAM_MAC_ADDRESS_LEN);
        }
        else
            printk("ERROR - Could not allocate memory for MAC data\n");
    }
    else
        printk("ERROR - Invalid number of MAC addresses (%d) is configured.\n",
        ulNumMacAddrs);
}

static int does_nvram_data_support_gpon_params(void)
{
    char value[10];
    int ret=0, ulVersion, r=0;

    r=envram_get_locked(NVRAM_ULVERSION, value, sizeof(value));
    if ( r > 0)
    {
        sscanf(value, "%d", &ulVersion);
        if(ulVersion > NVRAM_FULL_LEN_VERSION_NUMBER)
            ret=1;
    }
return ret;
}


static void get_gpon_params_from_nvram(PGPON_INFO g_pGponInfo)
{
char value[256];
int erased=1,i,r=0, len;

    memset(value, '\0', sizeof(value));
    r=envram_get_locked(NVRAM_GPONPASSWORD, value, sizeof(value));
    if ( r > 0) 
    {
        if(is_cfe_boot())
        {
            len = NVRAM_GPON_PASSWORD_LEN;
            for(i=0; i<NVRAM_GPON_PASSWORD_LEN-1; ++i) {
               if((value[i] != (char) 0xFF) &&
                    (value[i] != (char) 0x00)) {
                   erased = 0;
                   break;
               }
            }
        }
        else
        {
            len = NVRAM_XGPON_PASSWORD_LEN;
            erased = 0;
        }
        if(!erased)
        {
            strncpy( g_pGponInfo->gponPassword, value, len);
            g_pGponInfo->gponPassword[len-1]='\0';
        }
    }
    memset(value, '\0', sizeof(value));
    r=envram_get_locked(NVRAM_GPONSERIALNUMBER, value, sizeof(value));
    if (r > 0)
    {
        erased=1;
        if(is_cfe_boot())
        {
            for(i=0; i<NVRAM_GPON_SERIAL_NUMBER_LEN-1; ++i) {
               if((value[i] != (char) 0xFF) &&
                    (value[i] != (char) 0x00)) {
                   erased = 0;
                   break;
               }
            }
        }
        else
        {
                erased = 0;
        }
        if(!erased) {
            strncpy( g_pGponInfo->gponSerialNumber, value,
                    NVRAM_GPON_SERIAL_NUMBER_LEN );
            g_pGponInfo->gponSerialNumber[NVRAM_GPON_SERIAL_NUMBER_LEN-1]='\0';
        }
    }
}

void __init set_gpon_info( void )
{
    g_pGponInfo = (PGPON_INFO) kmalloc( sizeof(GPON_INFO), GFP_KERNEL );

    if( g_pGponInfo )
    {
        strcpy( g_pGponInfo->gponSerialNumber, DEFAULT_GPON_SN );
        strcpy( g_pGponInfo->gponPassword, DEFAULT_GPON_PW );
        if (!is_cfe_boot() || does_nvram_data_support_gpon_params())
        {
            //this cheks for the erased as well 
            get_gpon_params_from_nvram(g_pGponInfo);
        }
    }
    else
    {
        printk("ERROR - Could not allocate memory for GPON data\n");
    }
}

//**************************************************************************************
// Utitlities for dump memory, free kernel pages, mips soft reset, etc.
//**************************************************************************************

/***********************************************************************
* Function Name: dumpaddr
* Description  : Display a hex dump of the specified address.
***********************************************************************/
void dumpaddr( unsigned char *pAddr, int nLen )
{
    static char szHexChars[] = "0123456789abcdef";
    char szLine[80];
    char *p = szLine;
    unsigned char ch, *q;
    int i, j;
    unsigned int ul;

    while( nLen > 0 )
    {
        sprintf( szLine, "%8.8lx: ", (unsigned long) pAddr );
        p = szLine + strlen(szLine);

        for(i = 0; i < 16 && nLen > 0; i += sizeof(int), nLen -= sizeof(int))
        {
            ul = *(unsigned int *) &pAddr[i];
            q = (unsigned char *) &ul;
            for( j = 0; j < sizeof(int); j++ )
            {
                *p++ = szHexChars[q[j] >> 4];
                *p++ = szHexChars[q[j] & 0x0f];
                *p++ = ' ';
            }
        }

        for( j = 0; j < 16 - i; j++ )
            *p++ = ' ', *p++ = ' ', *p++ = ' ';

        *p++ = ' ', *p++ = ' ', *p++ = ' ';

        for( j = 0; j < i; j++ )
        {
            ch = pAddr[j];
            *p++ = (ch > ' ' && ch < '~') ? ch : '.';
        }

        *p++ = '\0';
        printk( "%s\r\n", szLine );

        pAddr += i;
    }
    printk( "\r\n" );
} /* dumpaddr */



/* This is the low level hardware reset function. Normally called from kernel_restart,
 * the generic linux way of rebooting, which calls a notifier list, stop other cpu, disable 
 * local irq and lets sub-systems know that system is rebooting, and then calls machine_restart, 
 * which eventually call kerSysSoftReset. Do not call this function directly.
 */
void kerSysSoftReset(void)
{
    unsigned long cpu;
    cpu = smp_processor_id();
    printk(KERN_INFO "kerSysSoftReset: called on cpu %lu\n", cpu);
    // FIXME - Once in many thousands of reboots, this function could 
    // fail to complete a reboot.  Arm the watchdog just in case.

    // give enough time(25ms) for resetPwrmgmtDdrMips and other function to finish
    // 4908 need to access some BPCM register which takes very long time to read/write
    bcmbca_wd_start(25000);

    resetPwrmgmtDdrMips();
}

extern void stop_other_cpu(void);  // in arch/mips/kernel/smp.c

/* this function is only called in SPI nor kernel flash update */
void stopOtherCpu(void)
{
#if defined(CONFIG_BCM96858) || defined(CONFIG_BCM94908) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96856) || defined(CONFIG_BCM963146) || defined(CONFIG_BCM94912) || defined(CONFIG_BCM96813)
#if defined(CONFIG_SMP)
    /* This cause call stack dump unless we hack the system_state to reboot. See
       ipi_cpu_stop() in arch/arm64/kernel/smp.c. But not a big deal as this function
       is only used in SPI nor which is not offically supported in 63158/4908/6858 */
    smp_send_stop();
#endif

#elif defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148)
#if defined(CONFIG_SMP)
    /* in ARM, CPU#0 should be the last one to get shut down, and for
     * both 63138 and 63148, we have dualcore system, so we can hardcode
     * cpu_down() on CPU#1. Also, if this function is handled by the 
     * CPU which is going to be shut down, kernel will transfer the
     * current task to another CPU.  Thus when we return from cpu_down(),
     * the task is still running. */
    cpu_down(1);
#endif
#elif defined(CONFIG_BCM947189)
#elif defined(CONFIG_BCM96846)
#elif defined(CONFIG_BCM947622)
#elif defined(CONFIG_BCM963178)
#elif defined(CONFIG_BCM96878)
#elif defined(CONFIG_BCM96855)
#elif defined(CONFIG_BCM96756)    
    // FIXMET 6846 47622 63178 6878 6855
#else
#if defined(CONFIG_SMP)
    stop_other_cpu();
#endif
#endif /* !defined(CONFIG_BCM963138) && !defined(CONFIG_BCM963148) */
}

#if defined(CONFIG_BCM947622)

#define BCA_2x2AX_IOMAP_SIZE_BYTES (16 * 1024 * 1024) /**< one linear 16 MB region */
#define WLAN_SLICE_A_PHYS_ADDR 0x85000000
#define WLAN_SLICE_A_D11_MWR0_ADDR (WLAN_SLICE_A_PHYS_ADDR + 0x101000)
#define D11_MWR0_IOCTL_OFFSET 0x408
#define D11_MWR0_RESET_OFFSET 0x800

static void bcm47622a0_war(void)
{
    volatile unsigned char *regs = ioremap_nocache(WLAN_SLICE_A_D11_MWR0_ADDR, 4096);

    if (regs == NULL) {
        return;
    }
    /* resets WLAN slice-A mac core for boot-from-TXFIFO */
    *(volatile unsigned int*)(regs + D11_MWR0_RESET_OFFSET) = 0x1;
    *(volatile unsigned int*)(regs + D11_MWR0_IOCTL_OFFSET) = 0x3;
    mdelay(1);
    *(volatile unsigned int*)(regs + D11_MWR0_RESET_OFFSET) = 0x0;
}

#endif /* CONFIG_BCM947622 */

void resetPwrmgmtDdrMips(void)
{
#if defined(CONFIG_BCM947622)
    bcm47622a0_war();
#endif /* CONFIG_BCM947622 */
#if defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148)
    /* stop SF2 switch from sending packet to runner, or the DMA might get stuck.
     * Also give it time to complete the ongoing DMA transaction. */
    ETHSW_CORE->imp_port_state &= ~ETHSW_IPS_LINK_PASS;
#endif

#if defined(CONFIG_BCM94908)
    /* reset the pll manually to bypass mode if strap for slow clock */
    if (MISC->miscStrapBus&MISC_STRAP_BUS_CPU_SLOW_FREQ)
    {
        bcm_change_cpu_clk(BCM_CPU_CLK_LOW);
    }
#endif

    // let UART finish printing
    udelay(100);

#if defined(CONFIG_BCM947189)
    GPIO_WATCHDOG->watchdog = 1;
#else
    bcmbca_wd_start(1);
#endif

    for(;;) {} // spin and wait soft reset to take effect
}

unsigned long kerSysGetMacAddressType( unsigned char *ifName )
{
    unsigned long macAddressType = MAC_ADDRESS_ANY;

    if(strstr(ifName, IF_NAME_ETH))
    {
        macAddressType = MAC_ADDRESS_ETH;
    }
    else if(strstr(ifName, IF_NAME_USB))
    {
        macAddressType = MAC_ADDRESS_USB;
    }
    else if(strstr(ifName, IF_NAME_WLAN))
    {
        macAddressType = MAC_ADDRESS_WLAN;
    }
    else if(strstr(ifName, IF_NAME_ATM))
    {
        macAddressType = MAC_ADDRESS_ATM;
    }
    else if(strstr(ifName, IF_NAME_PTM))
    {
        macAddressType = MAC_ADDRESS_PTM;
    }
    else if(strstr(ifName, IF_NAME_GPON) || strstr(ifName, IF_NAME_VEIP))
    {
        macAddressType = MAC_ADDRESS_GPON;
    }
    else if(strstr(ifName, IF_NAME_EPON))
    {
        macAddressType = MAC_ADDRESS_EPON;
    }

    return macAddressType;
}

static inline void kerSysMacAddressNotify(unsigned char *pucaMacAddr, MAC_ADDRESS_OPERATION op)
{
    if(kerSysMacAddressNotifyHook)
    {
        kerSysMacAddressNotifyHook(pucaMacAddr, op);
    }
}

int kerSysMacAddressNotifyBind(kerSysMacAddressNotifyHook_t hook)
{
    int nRet = 0;

    if(hook && kerSysMacAddressNotifyHook)
    {
        printk("ERROR: kerSysMacAddressNotifyHook already registered! <0x%p>\n",
               kerSysMacAddressNotifyHook);
        nRet = -EINVAL;
    }
    else
    {
        kerSysMacAddressNotifyHook = hook;
    }

    return nRet;
}

static void getNthMacAddr( unsigned char *pucaMacAddr, unsigned long n)
{
    unsigned long macsequence = 0;
    /* Work with only least significant three bytes of base MAC address */
    macsequence = (pucaMacAddr[3] << 16) | (pucaMacAddr[4] << 8) | pucaMacAddr[5];
    macsequence = (macsequence + n) & 0xffffff;
    pucaMacAddr[3] = (macsequence >> 16) & 0xff;
    pucaMacAddr[4] = (macsequence >> 8) & 0xff;
    pucaMacAddr[5] = (macsequence ) & 0xff;

}
static unsigned long getIdxForNthMacAddr( const unsigned char *pucaBaseMacAddr, unsigned char *pucaMacAddr)
{
    unsigned long macSequence = 0;
    unsigned long baseMacSequence = 0;
    
    macSequence = (pucaMacAddr[3] << 16) | (pucaMacAddr[4] << 8) | pucaMacAddr[5];
    baseMacSequence = (pucaBaseMacAddr[3] << 16) | (pucaBaseMacAddr[4] << 8) | pucaBaseMacAddr[5];

    return macSequence - baseMacSequence;
}
/* Allocates requested number of consecutive MAC addresses */
int kerSysGetMacAddresses( unsigned char *pucaMacAddr, unsigned int num_addresses, unsigned long ulId )
{
    int nRet = -EADDRNOTAVAIL;
    PMAC_ADDR_INFO pMai = NULL;
    PMAC_ADDR_INFO pMaiFreeId = NULL, pMaiFreeIdTemp;
    unsigned long i = 0, j = 0, ulIdxId = 0;

    spin_lock(&macAddrLock);

    /* Start with the base address */
    memcpy( pucaMacAddr, g_pMacInfo->ucaBaseMacAddr, NVRAM_MAC_ADDRESS_LEN);

#if defined(CONFIG_BCM_PON)
    /*As epon mac should not be dynamicly changed, always use last 1(SLLID) or 8(MLLID) mac address(es)*/
    if (ulId == MAC_ADDRESS_EPONONU)
    {
        i = g_pMacInfo->ulNumMacAddrs - num_addresses; 

        for (j = 0, pMai = &g_pMacInfo->MacAddrs[i]; j < num_addresses; j++) {
            pMaiFreeIdTemp = pMai + j;
            if (pMaiFreeIdTemp->chInUse != 0 && pMaiFreeIdTemp->ulId != MAC_ADDRESS_EPONONU) {
                printk("kerSysGetMacAddresses: epon mac address allocate failed, g_pMacInfo[%ld] reserved by 0x%lx\n", i+j, pMaiFreeIdTemp->ulId);    
                break;
            }
        }
        
        if (j >= num_addresses) {
            pMaiFreeId = pMai;
            ulIdxId = i;
        }
    }
    else
#endif    
    {
        for( i = 0, pMai = g_pMacInfo->MacAddrs; i < g_pMacInfo->ulNumMacAddrs;
            i++, pMai++ )
        {
            if( ulId == pMai->ulId || ulId == MAC_ADDRESS_ANY )
            {
                /* This MAC address has been used by the caller in the past. */
                getNthMacAddr( pucaMacAddr, i );
                pMai->chInUse = 1;
                pMaiFreeId = NULL;
                nRet = 0;
                break;
            } else if( pMai->chInUse == 0 ) {
                /* check if it there are num_addresses to be checked starting from found MAC address */
                if ((i + num_addresses - 1) >= g_pMacInfo->ulNumMacAddrs) {
                    break;
                }
    
                for (j = 1; j < num_addresses; j++) {
                    pMaiFreeIdTemp = pMai + j;
                    if (pMaiFreeIdTemp->chInUse != 0) {
                        break;
                    }
                }
                if (j == num_addresses) {
                    pMaiFreeId = pMai;
                    ulIdxId = i;
                    break;
                }
            }
        }
    }

    if(pMaiFreeId )
    {
        /* An available MAC address was found. */
        getNthMacAddr( pucaMacAddr, ulIdxId );
        pMaiFreeIdTemp = pMai;
        for (j = 0; j < num_addresses; j++) {
            pMaiFreeIdTemp->ulId = ulId;
            pMaiFreeIdTemp->chInUse = 1;
            pMaiFreeIdTemp++;
        }
        nRet = 0;
    }

    spin_unlock(&macAddrLock);

    return( nRet );
} /* kerSysGetMacAddr */
int kerSysGetMacAddress( unsigned char *pucaMacAddr, unsigned long ulId )
{
    return kerSysGetMacAddresses(pucaMacAddr,1,ulId); /* Get only one address */
} /* kerSysGetMacAddr */


int kerSysReleaseMacAddresses( unsigned char *pucaMacAddr, unsigned int num_addresses )
{
    int i, nRet = -EINVAL;
    unsigned long ulIdx = 0;

    spin_lock(&macAddrLock);

    ulIdx = getIdxForNthMacAddr(g_pMacInfo->ucaBaseMacAddr, pucaMacAddr);

    if( ulIdx < g_pMacInfo->ulNumMacAddrs )
    {
        for(i=0; i<num_addresses; i++) {
            if ((ulIdx + i) < g_pMacInfo->ulNumMacAddrs) {
                PMAC_ADDR_INFO pMai = &g_pMacInfo->MacAddrs[ulIdx + i];
                if( pMai->chInUse == 1 )
                {
                    pMai->chInUse = 0;
                    nRet = 0;
                }
            } else {
                printk("Request to release %d addresses failed as "
                    " the one or more of the addresses, starting from"
                    " %dth address from given address, requested for release"
                    " is not in the list of available MAC addresses \n", num_addresses, i);
                break;
            }
        }
    }

    spin_unlock(&macAddrLock);

    return( nRet );
} /* kerSysReleaseMacAddr */


int kerSysReleaseMacAddress( unsigned char *pucaMacAddr )
{
    return kerSysReleaseMacAddresses(pucaMacAddr,1); /* Release only one MAC address */

} /* kerSysReleaseMacAddr */


void kerSysGetGponSerialNumber( unsigned char *pGponSerialNumber )
{
    strncpy(pGponSerialNumber, g_pGponInfo->gponSerialNumber, NVRAM_GPON_SERIAL_NUMBER_LEN);
    pGponSerialNumber[NVRAM_GPON_SERIAL_NUMBER_LEN - 1] = 0;
}

void kerSysGetGponPassword( unsigned char *pGponPassword )
{
    strncpy(pGponPassword, g_pGponInfo->gponPassword, NVRAM_XGPON_PASSWORD_LEN - 1);
    pGponPassword[NVRAM_XGPON_PASSWORD_LEN - 1] = 0;
}

unsigned long kerSysGetSdramSize( void )
{
    return( g_ulSdramSize );
} /* kerSysGetSdramSize */
int kerSysGetAfeId( unsigned int *afeId )
{
    char value[50];
    int r;

    memset(value, '\0', sizeof(value));

    r=envram_get_locked(NVRAM_AFEID, value, sizeof(value));
    if ( r > 0)
       sscanf(value, "%x;%x", &afeId [0], &afeId[1]);
    else
        return -1;

    return 0;
}

#if !defined(CONFIG_BCM_BCA_LEGACY_LED_API)
void kerSysLedCtrl(BOARD_LED_NAME ledName, BOARD_LED_STATE ledState)
{
    if (g_ledInitialized)
       boardLedCtrl(ledName, ledState);
}
#endif

/*functionto receive message from usersapce
 * Currently we dont expect any messages fromm userspace
 */
void kerSysRecvFrmMonitorTask(struct sk_buff *skb)
{

   /*process the message here*/
   printk(KERN_WARNING "unexpected skb received at %s \n",__FUNCTION__);
   kfree_skb(skb);
   return;
}

void kerSysInitMonitorSocket( void )
{
#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)
   g_monitor_nl_sk = netlink_kernel_create(&init_net, NETLINK_BRCM_MONITOR, 0, kerSysRecvFrmMonitorTask, NULL, THIS_MODULE);
#else
   struct netlink_kernel_cfg cfg = {
       .input  = kerSysRecvFrmMonitorTask,
   };
   g_monitor_nl_sk = netlink_kernel_create(&init_net, NETLINK_BRCM_MONITOR, &cfg);
#endif

   if(!g_monitor_nl_sk)
   {
      printk(KERN_ERR "Failed to create a netlink socket for monitor\n");
      return;
   }

}

void kerSysSetMonitorTaskPid(int pid)
{
    g_monitor_nl_pid = pid;
    return;
}

void kerSysSendtoMonitorTask(int msgType, char *msgData, int msgDataLen)
{

   struct sk_buff *skb =  NULL;
   struct nlmsghdr *nl_msgHdr = NULL;
   unsigned int nl_msgLen;

   if(!g_monitor_nl_pid)
   {
      printk(KERN_INFO "message received before monitor task is initialized %s \n",__FUNCTION__);
      return;
   } 

   if(msgData && (msgDataLen > MAX_PAYLOAD_LEN))
   {
      printk(KERN_ERR "invalid message len in %s",__FUNCTION__);
      return;
   } 

   nl_msgLen = NLMSG_SPACE(msgDataLen);

   /*Alloc skb ,this check helps to call the fucntion from interrupt context */

   if(in_atomic())
   {
      skb = alloc_skb(nl_msgLen, GFP_ATOMIC);
   }
   else
   {
      skb = alloc_skb(nl_msgLen, GFP_KERNEL);
   }

   if(!skb)
   {
      printk(KERN_ERR "failed to alloc skb in %s",__FUNCTION__);
      return;
   }

   nl_msgHdr = (struct nlmsghdr *)skb->data;
   nl_msgHdr->nlmsg_type = msgType;
   nl_msgHdr->nlmsg_pid=0;/*from kernel */
   nl_msgHdr->nlmsg_len = nl_msgLen;
   nl_msgHdr->nlmsg_flags =0;

   if(msgData)
   {
      memcpy(NLMSG_DATA(nl_msgHdr),msgData,msgDataLen);
   }

#if LINUX_VERSION_CODE < KERNEL_VERSION(3,7,0)
   NETLINK_CB(skb).pid = 0; /*from kernel */
#endif

   skb->len = nl_msgLen; 

   netlink_unicast(g_monitor_nl_sk, skb, g_monitor_nl_pid, MSG_DONTWAIT);
   return;
}

void __exit kerSysCleanupMonitorSocket(void)
{
   g_monitor_nl_pid = 0 ;
   sock_release(g_monitor_nl_sk->sk_socket);
}


/***********************************************************************
 * Function Name: kerSysBlParmsGetInt
 * Description  : Returns the integer value for the requested name from
 *                the boot loader parameter buffer.
 * Returns      : 0 - success, -1 - failure
 ***********************************************************************/
int kerSysBlParmsGetInt( char *name, int *pvalue )
{
    char *p2, *p1 = (char*)bcm_get_blparms();
    int ret = -1;

    *pvalue = -1;

    /* The g_blparms_buf buffer contains one or more contiguous NULL termianted
     * strings that ends with an empty string.
     */
    while( *p1 )
    {
        p2 = p1;

        while( *p2 != '=' && *p2 != '\0' )
            p2++;

        if( *p2 == '=' )
        {
            *p2 = '\0';

            if( !strcmp(p1, name) )
            {
                *p2++ = '=';
                *pvalue = simple_strtol(p2, &p1, 0);
                if( *p1 == '\0' )
                    ret = 0;
                break;
            }

            *p2 = '=';
        }

        p1 += strlen(p1) + 1;
    }

    return( ret );
}

/***********************************************************************
 * Function Name: kerSysBlParmsGetStr
 * Description  : Returns the string value for the requested name from
 *                the boot loader parameter buffer.
 * Returns      : 0 - success, -1 - failure
 ***********************************************************************/
int kerSysBlParmsGetStr( char *name, char *pvalue, int size )
{
    char *p2, *p1 = (char*)bcm_get_blparms();
    int ret = -1;

    /* The g_blparms_buf buffer contains one or more contiguous NULL termianted
     * strings that ends with an empty string.
     */
    while( *p1 )
    {
        p2 = p1;

        while( *p2 != '=' && *p2 != '\0' )
            p2++;

        if( *p2 == '=' )
        {
            *p2 = '\0';

            if( !strcmp(p1, name) )
            {
                *p2++ = '=';
                strncpy(pvalue, p2, size);
                ret = 0;
                break;
            }

            *p2 = '=';
        }

        p1 += strlen(p1) + 1;
    }

    return( ret );
}

#ifndef CONFIG_DT_SUPPORT_ONLY
static DEFINE_SPINLOCK(pinmux_spinlock);

void kerSysInitPinmuxInterface(unsigned int interface) {
    unsigned long flags;
    spin_lock_irqsave(&pinmux_spinlock, flags); 
#if defined(CONFIG_BCM963138) || defined(CONFIG_BCM963148) || defined(CONFIG_BCM94908) || defined(CONFIG_BCM963158) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM96878) || defined(CONFIG_BCM96855)
    bcm_init_pinmux_interface(interface);
#endif
    spin_unlock_irqrestore(&pinmux_spinlock, flags); 
}
#endif


/***************************************************************************
 * Function Name: kerSysGetUbusFreq
 * Description  : Chip specific computation.
 * Returns      : the UBUS frequency value in MHz.
 ***************************************************************************/
unsigned int kerSysGetUbusFreq(unsigned int miscStrapBus)
{
   unsigned int ubus = UBUS_BASE_FREQUENCY_IN_MHZ;


   return (ubus);

}  /* kerSysGetUbusFreq */


/***************************************************************************
 * Function Name: kerSysGetChipId
 * Description  : Map id read from device hardware to id of chip family
 *                consistent with  BRCM_CHIP
 * Returns      : chip id of chip family
 ***************************************************************************/
int kerSysGetChipId() { 
        int r;
#if defined(CONFIG_BCM96858)
        r = 0x6858;
#elif defined(CONFIG_BCM96846)
        r = 0x68460;
#elif defined(CONFIG_BCM96878)
        r = 0x6878;
#elif defined(CONFIG_BCM96855)
        r = 0x6855;
#elif defined(CONFIG_BCM96856)
        r = 0x68560;
#elif defined(CONFIG_BCM947189)
        r = 0x47189;
#else
        r = UtilGetChipId();
#endif

        return(r);
}

/***************************************************************************
 * Function Name: kerSysGetDslPhyEnable
 * Description  : returns true if device should permit Phy to load
 * Returns      : true/false
 ***************************************************************************/
int kerSysGetDslPhyEnable() {
#if IS_ENABLED(CONFIG_BCM_ADSL)
    uint32 id = ((PERF->RevID & CHIP_ID_MASK) >> CHIP_ID_SHIFT);

    if ((id != 0x63169) && (id != 0x63269) && ((id & 0xffff0) != 0x6750))
        return 1;
#endif
    return 0;
}

/***************************************************************************
 * Function Name: kerSysGetChipName
 * Description  : fills buf with the human-readable name of the device
 * Returns      : pointer to buf
 ***************************************************************************/
char *kerSysGetChipName(char *buf, int n) {
    return(UtilGetChipName(buf, n));
}

int kerSysGetPciePortEnable(int port)
{
    int ret = 1;
#ifndef CONFIG_DT_SUPPORT_ONLY
    int dual_lane;
    unsigned short pci_dis = 0;
#endif
#if defined( CONFIG_BCM947622 ) || defined (CONFIG_BCM94912) || defined(CONFIG_BCM96813) || defined (CONFIG_BCM96756)
    unsigned int otp_value = 0;
    if( bcm_otp_is_pcie_port_disabled(port, &otp_value) == 0 && otp_value )
        return 0;
#endif
		    
#if defined (CONFIG_BCM96858)
    unsigned int chipId;
    bcm_otp_get_chipid(&chipId);

    switch (chipId)
    {
        case 0:
        case 1:     // 68580X
        case 8:     // 62119
        case 9:     // 68580XP
        case 10:    // 62119P
        case 13:    // 68580XF
            if ((port == 0) || (port == 1) || ((port == 2) && (MISC->miscStrapBus & MISC_STRAP_BUS_PCIE_SATA_MASK)))
                ret = 1;
            else            
                ret = 0;
            break;
        case 3:     // 68580H
            if ((port == 0) || (port == 1))
                ret = 1;
            else
                ret = 0;
            break;
        case 2:     // 55040
        case 5:     // 55045
            if (port == 0)
                ret = 1;
            else
                ret = 0;
            break;
        case 4:     // 55040P
        case 11:    // 55040B
        case 12:    // 55040M
                ret = 0;
            break;
        case 7:     // 49508
                ret = 1;
            break;
        default:
            ret = 0;
            break;
    }
#elif defined (CONFIG_BCM963158)
    if ((port == 0) || (port == 1) || (port == 3)
        || ((port == 2) && (MISC->miscStrapBus & MISC_STRAP_BUS_PCIE_SATA_MASK))
       )
        ret = 1;
    else
        ret = 0;
#elif defined (CONFIG_BCM96846)
    unsigned int chipId = (PERF->RevID & CHIP_ID_MASK) >> CHIP_ID_SHIFT;

    switch (chipId)
    {
        case 0x68460:
        case 0x68461:
        case 0x68464:    // 68461S
            if ((port==0) || (port==1))
                ret = 1;
            else
                ret = 0;
            break;
        case 0x68462:
        case 0x68463:    // 6846U
            ret = 0;
            break;
        default:
            ret = 0;
            break;
    }
#elif defined (CONFIG_BCM96878)
    unsigned int chipId = (PERF->RevID & CHIP_ID_MASK) >> CHIP_ID_SHIFT;

    switch (chipId)
    {
        case 0x68780:    // 68780
        case 0x68782:    // 68782
        case 0x6878A:    // 68782G
        case 0x6878C:    // 687789
        case 0x6878E:    // 68782N
            if (port==0)
                ret = 1;
            else
                ret = 0;
            break;
        case 0x68781:    // 68781
        case 0x6878D:    // 68781G
        case 0x68789:    // 68781H
            ret = 0;
            break;
        default:
            ret = 0;
            break;
    }
#elif defined (CONFIG_BCM96856) || defined(CONFIG_BCM963146)
    unsigned int chipId = UtilGetChipId();

    if (chipId==0x68560B)
        ret = 0;
    else
    {
        if ((port==0) || (port==1) || (port==2))
            ret = 1;
        else
            ret = 0;
    }
#elif defined (CONFIG_BCM96855)
    unsigned int chipId = UtilGetChipId();

     switch (chipId)
    {
        case 0x06753:    // 6753
        case 0x68252d:    // 68252R
        case 0x68552:    // 68552
        case 0x68252:    // 68252
            if ((port==0) || (port==1))
                ret = 1;
            else
                ret = 0;
            break;
        case 0x68552c:
        case 0x68252c:
            if (port==0)
                ret = 1;
            else
                ret = 0;
            break;
        default:
            ret = 0;
            break;
    }

#endif

#ifndef CONFIG_DT_SUPPORT_ONLY
    /* In case of dual lane on PCIe0, PCIe1 isn't used */
    if (port == 1 && (BpGetPciPortDualLane(0, &dual_lane) == BP_SUCCESS) && dual_lane)
        ret = 0;

    if (BpGetPciDis(&pci_dis) == BP_SUCCESS && pci_dis)
        ret = 0;
#endif
    return ret;
}
EXPORT_SYMBOL(kerSysGetPciePortEnable);

/***************************************************************************
 * Function Name: kerSysGetPciePortMode
 * Description  : returns PCIe port Mode for port#0 
 * Returns      : 1: RC mode (default), 0: EP mode
 ***************************************************************************/
int kerSysGetPciePortMode(int port)
{
    int ret = 1;

	/* SoC's with PCIE0 EP/RC mode option defines MISC_STRAP_BUS_PCIE0_RC_MODE */
#if defined(MISC_STRAP_BUS_PCIE0_RC_MODE)
    if (port == 0) {
        ret = (MISC->miscStrapBus & MISC_STRAP_BUS_PCIE0_RC_MODE) ? 1 : 0;
    }
#endif /* MISC_STRAP_BUS_PCIE0_RC_MODE */

	/* SoC's with PCIE3 EP/RC mode option defines MISC_STRAP_BUS_PCIE3_RC_MODE */
#if defined(MISC_STRAP_BUS_PCIE3_RC_MODE)
    if (port == 3) {
        ret = (MISC->miscStrapBus & MISC_STRAP_BUS_PCIE3_RC_MODE) ? 1 : 0;
    }
#endif /* MISC_STRAP_BUS_PCIE3_RC_MODE */

    return ret;
}
EXPORT_SYMBOL(kerSysGetPciePortMode);

int kerSysGetSataPortEnable(void)
{
#ifndef CONFIG_DT_SUPPORT_ONLY
    unsigned short sata_dis = 0;
#endif
    
#if defined(CONFIG_BCM96858) || defined (CONFIG_BCM963158)
	/* check if port is configured for SATA */
    if(MISC->miscStrapBus & MISC_STRAP_BUS_PCIE_SATA_MASK)
	{
	    /*confgured for PCIe */
		return 0;
	}
#endif    

#if defined(CONFIG_BCM96858) || defined(CONFIG_BCM94908)
    {
        unsigned int otp_value = 0;
        if( bcm_otp_is_sata_disabled(&otp_value) == 0 && otp_value )
        { 
            return 0;
        }
    }
#endif       

#ifndef CONFIG_DT_SUPPORT_ONLY
#pragma message "!!!!! Warning: Using boardparams functionality deprecated and should not be used anymore. Consider using the Device tree instead !!!!!"
    if (BpGetSataDis(&sata_dis) == BP_SUCCESS && sata_dis)
        return 0;
#endif

    return 1;
}
EXPORT_SYMBOL(kerSysGetSataPortEnable);

int kerSysGetUsbHostPortEnable(int port)
{
    int ret = 1;
#ifndef CONFIG_DT_SUPPORT_ONLY
    unsigned short usb_dis = 0;
#endif
#if defined (CONFIG_BCM96858)
    unsigned int chipId;
    unsigned int port_disable;

    bcm_otp_get_usb_port_disabled(port, &port_disable);

    if(port_disable)
        return 0;

    bcm_otp_get_chipid(&chipId);

    switch (chipId)
    {
        case 0:
        case 1:    // 68580X
        case 3:    // 68580H
        case 7:    // 49508
        case 8:    // 62119
        case 9:    // 68580XP
        case 10:   // 62119P
        case 13:   // 68580XF
            ret = 1;
            break;
        case 2:    // 55040
        case 4:    // 55040P
        case 11:   // 55040B
            ret = 0;
            break;
        case 12:   // 55040M
            if (port==0)
            	ret = 1;
            else ret = 0;
            break;
        default:
            ret = 0;
            break;
    }
#elif defined(CONFIG_BCM96846)
    unsigned int chipId = (PERF->RevID & CHIP_ID_MASK) >> CHIP_ID_SHIFT;

    switch (chipId)
    {
        case 0x68460:
        case 0x68461:
        case 0x68463:    // 6846U
        case 0x68464:    // 68461S
            if ((port==0) || (port==1))
                ret = 1;
            else
                ret = 0;
            break;
        case 0x68462:
            if (port==1)
                ret = 1;
            else
                ret = 0;
            break;
        default:
            ret = 0;
            break;
    }
#elif defined(CONFIG_BCM96878)
    unsigned int chipId = (PERF->RevID & CHIP_ID_MASK) >> CHIP_ID_SHIFT;

    switch (chipId)
    {
        case 0x68780:    // 68780
        case 0x68782:    // 68782
        case 0x6878A:    // 68782G
        case 0x6878C:    // 68789
        case 0x6878E:    // 68782H
        case 0x6878D:    // 68781G
            if ((port==0) || (port==1))
                ret = 1;
            else
                ret = 0;
            break;
        case 0x68781:    // 68781
        case 0x68789:    // 68781H
            if (port==0)
                ret = 1;
            else
                ret = 0;
            break;
        default:
            ret = 0;
            break;
    }
#elif defined(CONFIG_BCM96856)
    unsigned int chipId = UtilGetChipId();

    if (chipId==0x68560B)
        ret = 0;
    else
    {
        if ((port==0) || (port==1))
            ret = 1;
        else
            ret = 0;
    }
#elif defined(CONFIG_BCM96855)
    unsigned int chipId = UtilGetChipId();

    switch (chipId)
    {
        case 0x68552:    // 68552
        case 0x68552C:   // 68552C
        case 0x68252:    // 68252
        case 0x68252C:   // 68252C
        case 0x68252d:   // 68252R
        case 0x06753:   // 6753
            if ((port==0) || (port==1))
                ret = 1;
            else
                ret = 0;
            break;
        default:
            ret = 0;
            break;
    }
#endif	

#ifndef CONFIG_DT_SUPPORT_ONLY
#pragma message "!!!!! Warning: Using boardparams functionality deprecated and should not be used anymore. Consider using the Device tree instead !!!!!"
    if (BpGetUsbDis(&usb_dis) == BP_SUCCESS && usb_dis)
        ret = 0;
#endif

    return ret;
}
EXPORT_SYMBOL(kerSysGetUsbHostPortEnable);

int kerSysGetUsbDeviceEnable(void)
{
    int ret = 1;
#if defined(CONFIG_BCM96858) || defined(CONFIG_BCM96846) || defined(CONFIG_BCM96856) || defined (CONFIG_BCM96878) || defined(CONFIG_BCM96855)
    ret = 0;
#endif    

    return ret;
}
EXPORT_SYMBOL(kerSysGetUsbDeviceEnable);

int kerSysGetUsb30HostEnable(void)
{
    int ret = 1;
    
#if defined(CONFIG_BCM947622)
	{
		unsigned int usb3_disable = 0;
		bcm_otp_is_usb3_disabled(&usb3_disable);
		if(usb3_disable)
			ret = 0;
    }
#elif defined (CONFIG_BCM96855)
    unsigned int chipId = UtilGetChipId();

    switch (chipId)
    {
    case 0x68252d:      // 68252R
    case 0x68252c:      // 68252C
        ret = 0;
    default:
        break;
    }
#endif

    return ret;
}
EXPORT_SYMBOL(kerSysGetUsb30HostEnable);

extern const struct obs_kernel_param __setup_start[], __setup_end[];
extern const struct kernel_param __start___param[], __stop___param[];

void kerSysSetBootParm(char *name, char *value)
{
    const struct obs_kernel_param *okp = __setup_start;
    const struct kernel_param *kp = __start___param;

    do {
        if (!strcmp(name, okp->str)) {
            if (okp->setup_func) {
                okp->setup_func(value);
                return;
            }
        }
        okp++;
    } while (okp < __setup_end);

    do {
        if (!strcmp(name, kp->name)) {
            if (kp->ops->set) {
                kp->ops->set(value, kp);
                return;
            }
        }
        kp++;
    } while (kp < __stop___param);
}
EXPORT_SYMBOL(kerSysSetBootParm);

int kerSysSetSdhciBaseClkSrc(int set_pll)
{
	int clk_sel = 0;
#ifdef MISC_PERIPH_CTRL_SDIO_EMMC_CLK_SEL_MASK	
	if( set_pll )
		MISC->miscPeriphCtrl |= MISC_PERIPH_CTRL_SDIO_EMMC_CLK_SEL_MASK;
	else
		MISC->miscPeriphCtrl &= ~(MISC_PERIPH_CTRL_SDIO_EMMC_CLK_SEL_MASK);

	clk_sel = MISC->miscPeriphCtrl & MISC_PERIPH_CTRL_SDIO_EMMC_CLK_SEL_MASK;
#endif		
	return clk_sel;
}
EXPORT_SYMBOL(kerSysSetSdhciBaseClkSrc);

int board_ioctl_mem_access(BOARD_MEMACCESS_IOCTL_PARMS* parms, char* kbuf, int len)
{
    int i, j;
    unsigned char *cp,*bcp;
    unsigned short *sp,*bsp;
    unsigned int *ip,*bip;
    void *va;

    bcp = (unsigned char *)kbuf;
    bsp = (unsigned short *)bcp;
    bip = (unsigned int *)bcp;

    switch(parms->space) {
        case BOARD_MEMACCESS_IOCTL_SPACE_REG:
            va = ioremap_nocache((long)parms->address, len);
            break;
        case BOARD_MEMACCESS_IOCTL_SPACE_KERN:
            va = (void*)(uintptr_t)parms->address;
            break;
        default:
            va = NULL;
            return EFAULT;
    }
    // printk("memacecssioctl address started %08x mapped to %08x size is %d count is %d\n",(int)parms.address, (int)va,parms.size, parms.count);
    cp = (unsigned char *)va;
    sp = (unsigned short *)((long)va & ~1);
    ip = (unsigned int *)((long)va & ~3);
    for (i=0; i < parms->count; i++) {
        if ((parms->op == BOARD_MEMACCESS_IOCTL_OP_WRITE) 
            || (parms->op == BOARD_MEMACCESS_IOCTL_OP_FILL)) {
            j = 0;
            if (parms->op == BOARD_MEMACCESS_IOCTL_OP_WRITE) 
            {
                j = i;
            }
            switch(parms->size) {
                case 1:
                    cp[i] = bcp[j];
                    break;
                case 2:
                    sp[i] = bsp[j];
                    break;
                case 4:
                    ip[i] = bip[j];
                    break;
            }
        } else {
                switch(parms->size) {
                case 1:
                    bcp[i] = cp[i];
                    break;
                case 2:
                    bsp[i] = sp[i];
                    break;
                case 4:
                    bip[i] = ip[i];
                    break;
            }
        }
    }
    
    if (va != (void*)(uintptr_t)parms->address)
    {
        iounmap(va);
    }
    return 0;
}

void __init board_util_init(void)
{
    g_ulSdramSize = getMemorySize();
    set_mac_info();
    set_gpon_info();

    /* Print status of last reset */
    print_rst_status();

     kerSysInitMonitorSocket();
     kerSysInitDyingGaspHandler();
     kerSysInitBatteryManagementUnit();

    return;
}

void __exit board_util_deinit(void)
{
    kerSysDeinitDyingGaspHandler();
    kerSysCleanupMonitorSocket();
    return;
}
