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
#ifndef __PCIE_BCM963XX_H
#define __PCIE_BCM963XX_H

#ifdef __cplusplus
extern "C" {
#endif
#include <linux/of_pci.h>
#include <linux/of_irq.h>

#include <bcm_map_part.h>
#include <bcm_intr.h>

/*
 * +-----------------------------------------------------
 *  Defines
 * +-----------------------------------------------------
 */

/* Hardware registers */
#define BCM963XX_PCIE_PHYS_SIZE                    0x00010000
#define BCM963XX_PCIE_MEMS_SIZE                    0x10000000
#define BCM963XX_DDR_UBUS_ADDRESS_BASE             0x00000000

/* PCIe core register blocks */
#define PCIE_RC_CFG_VENDOR_REGS_OFFSET             0x0180
#define PCIE_RC_CFG_L1SUB_REGS_OFFSET              0x0240
#define PCIE_BLK_404_REGS_OFFSET                   0x0404
#define PCIE_BLK_428_REGS_OFFSET                   0x0428
#define PCIE_BLK_800_REGS_OFFSET                   0x0800
#define PCIE_BLK_1000_REGS_OFFSET                  0x1000
#define PCIE_BLK_1800_REGS_OFFSET                  0x1800
#define PCIE_MISC_REGS_OFFSET                      0x4000
#define PCIE_MISC_HARD_REGS_OFFSET                 0x4200
#define PCIE_MISC_PERST_REGS_OFFSET                0x4100
#define PCIE_MISC_HARD_REGS_OFFSET                 0x4200
#define PCIE_L2_INTR_CTRL_REGS_OFFSET              0x4300
#define PCIE_DMA_REGS_OFFSET                       0x4400
#define PCIE_MSI_INTR2_REGS_OFFSET                 0x4500 /* rev >= 3.03 */
#define PCIE_EXT_CFG_DEV_OFFSET                    0x8000
#define PCIE_EXT_CFG_REGS_OFFSET                   0x9000
#define PCIE_UBUS_L2_INTR_CTRL_REGS_OFFSET         0x9100
#define PCIE_IPI_L2_INTR_CTRL_REGS_OFFSET          0x9200
#define PCIE_PCIE_INTR1_REGS_OFFSET                0x9300
#define PCIE_CPU_INTR1_REGS_OFFSET                 0x9400
#define PCIE_G3_PLL_REGS_OFFSET                    0xA010

/* RC_CFG_TYPE1 */
#define RC_CFG_TYPE1_DEVICE_VENDOR_ID_OFFSET       (0x0000)
#define RC_CFG_TYPE1_REV_ID_CLASS_CODE_OFFSET      (0x0008)
#define RC_CFG_PCIE_DEVICE_STATUS_CONTROL_OFFSET   (0x00B4)
#define RC_CFG_PCIE_LINK_CAPABILITY_OFFSET         (0x00B8)
#define RC_CFG_PCIE_LINK_CAP_LINK_SPEED(cap)       ((cap) & 0xF)
#define RC_CFG_PCIE_LINK_CAP_LINK_WIDTH(cap)       ((cap & 0x3F0)>>4)
#define RC_CFG_PCIE_LINK_STATUS_CONTROL_OFFSET     (0x00BC)
#define RC_CFG_PCIE_LINK_STAT_LINK_WIDTH(stat)     ((stat & 0x3F00000)>>20)
#define RC_CFG_PCIE_LINK_STAT_LINK_SPEED(stat)     ((stat & 0xF0000)>>16)
#define RC_CFG_PCIE_LINK_STATUS_CONTROL_2_OFFSET   (0x00DC)
#define RC_CFG_PCIE_LINK_CTRL_TGT_LINK_SPEED_MASK  0x00000003

/* RC_CFG_PRIV1 */
#define RC_CFG_PRIV1_ID_VAL3_OFFSET                (PCIE_BLK_428_REGS_OFFSET+0x0014)
#define RC_CFG_PRIV1_ID_VAL3_REVISION_ID_MASK      0xff000000
#define RC_CFG_PRIV1_DEVICE_CAPABILITY_OFFSET      (PCIE_BLK_428_REGS_OFFSET+0x00AC)
#define RC_CFG_PRIV1_LINK_CAPABILITY_OFFSET        (PCIE_BLK_428_REGS_OFFSET+0x00B4)
#define RC_CFG_PRIV1_LINK_CAP_MAX_LINK_WIDTH_SHIFT 4
#define RC_CFG_PRIV1_LINK_CAP_MAX_LINK_WIDTH_MASK  0x000001F0
#define RC_CFG_PRIV1_LINK_CAP_LINK_SPEED_MASK      0x0000000F

/* RC_TL */
#define RC_TL_FCIMM_NP_LIMIT_OFFSET                (PCIE_BLK_800_REGS_OFFSET+0x0210)
#define RC_TL_FCIMM_NP_LIMIT_ENA_FC_NP_UPD_10US     (0x02000000)
#define RC_TL_FCIMM_NP_LIMIT_FC_NP_USCNT_MASK       (0x01E00000)
#define RC_TL_FCIMM_NP_LIMIT_FC_NP_USCNT_SHIFT      (21)
#define RC_TL_FCIMM_NP_LIMIT_ENA_FC_NP_IMMEDIATE    (0x00100000)
#define RC_TL_FCIMM_NP_LIMIT_FC_NPH_IMM_LIMIT_MASK  (0x000FF000)
#define RC_TL_FCIMM_NP_LIMIT_FC_NPH_IMM_LIMIT_SHIFT (12)
#define RC_TL_FCIMM_NP_LIMIT_FC_NPD_IMM_LIMIT_MASK  (0x00000FFF)
#define RC_TL_FCIMM_NP_LIMIT_FC_NPD_IMM_LIMIT_SHIFT (0)
#define RC_TL_FCIMM_P_LIMIT_OFFSET                 (PCIE_BLK_800_REGS_OFFSET+0x0214)
#define RC_TL_FCIMM_P_LIMIT_ENA_FC_P_UPD_10US       (0x02000000)
#define RC_TL_FCIMM_P_LIMIT_FC_P_USCNT_MASK         (0x01E00000)
#define RC_TL_FCIMM_P_LIMIT_FC_P_USCNT_SHIFT        (21)
#define RC_TL_FCIMM_P_LIMIT_ENA_FC_P_IMMEDIATE      (0x00100000)
#define RC_TL_FCIMM_P_LIMIT_FC_PH_IMM_LIMIT_MASK    (0x000FF000)
#define RC_TL_FCIMM_P_LIMIT_FC_PH_IMM_LIMIT_SHIFT   (12)
#define RC_TL_FCIMM_P_LIMIT_FC_PD_IMM_LIMIT_MASK    (0x00000FFF)
#define RC_TL_FCIMM_P_LIMIT_FC_PD_IMM_LIMIT_SHIFT   (0)

/* RC_DL */
#define RC_DL_PDL_CONTROL0_OFFSET                  (PCIE_BLK_1000_REGS_OFFSET+0x0000)
#define RC_DL_PDL_CONTROL1_OFFSET                  (PCIE_BLK_1000_REGS_OFFSET+0x0004)
#define RC_DL_PDL_CONTROL2_OFFSET                  (PCIE_BLK_1000_REGS_OFFSET+0x0008)
#define RC_DL_PDL_CONTROL2_EN_ACK_LAT_TIMER         (1 << 3)
#define RC_DL_PDL_CONTROL3_OFFSET                  (PCIE_BLK_1000_REGS_OFFSET+0x000C)
#define RC_DL_PDL_CONTROL4_OFFSET                  (PCIE_BLK_1000_REGS_OFFSET+0x0010)
#define RC_DL_PDL_CONTROL4_NPH_FC_INIT_MASK         (0xFF000000)
#define RC_DL_PDL_CONTROL4_NPH_FC_INIT_SHIFT        (24)
#define RC_DL_PDL_CONTROL4_PD_FC_INIT_MASK          (0x00FFF000)
#define RC_DL_PDL_CONTROL4_PD_FC_INIT_SHIFT         (12)
#define RC_DL_PDL_CONTROL4_NPD_FC_INIT_MASK         (0x00000FFF)
#define RC_DL_PDL_CONTROL4_NPD_FC_INIT_SHIFT        (0)
#define RC_DL_PDL_CONTROL5_OFFSET                  (PCIE_BLK_1000_REGS_OFFSET+0x0014)
#define RC_DL_PDL_CONTROL5_APSM_L1_GAP_MASK         (0x007F0000)
#define RC_DL_PDL_CONTROL5_APSM_L1_GAP_SHIFT        (16)
#define RC_DL_PDL_CONTROL5_GLOOPBACK                (1 << 9)
#define RC_DL_PDL_CONTROL5_DOWNSTREAM_PORT          (1 << 8)
#define RC_DL_PDL_CONTROL5_PH_INIT_MASK             (0x000000FF)
#define RC_DL_PDL_CONTROL5_PH_INIT_SHIFT            (0)
#define RC_DL_MDIO_ADDR_OFFSET                     (PCIE_BLK_1000_REGS_OFFSET+0x0100)
#define RC_DL_MDIO_WR_DATA_OFFSET                  (PCIE_BLK_1000_REGS_OFFSET+0x0104)
#define RC_DL_MDIO_RD_DATA_OFFSET                  (PCIE_BLK_1000_REGS_OFFSET+0x0108)
#define RC_DL_DL_STATUS_OFFSET                     (PCIE_BLK_1000_REGS_OFFSET+0x0048)
#define RC_DL_DL_STATUS_PHYLINKUP_MASK              (0x00002000)

/* RC_PL */
#define RC_PL_REG_PHY_CTL_1_OFFSET                 (PCIE_BLK_1800_REGS_OFFSET+0x0004)
#define RC_PL_REG_PHY_CTL_1_PWRDN_ENA_NOSYNC       0x00000008

/* PCI-E Miscellaneous Registers */
#define MISC_CTRL_OFFSET                           (PCIE_MISC_REGS_OFFSET+0x0008)
#define MISC_CTRL_MAX_BURST_SIZE_64B               (0 << 20)
#define MISC_CTRL_MAX_BURST_SIZE_128B              (1 << 20)
#define MISC_CTRL_MAX_BURST_SIZE_MASK              (3 << 20)
#define MISC_CTRL_BURST_ALIGN_MASK(rev)            ((rev >= 0x0310) ? (7 << 17) : (1 << 19))
#define MISC_CTRL_BURST_ALIGN(rev, b)              ((rev >= 0x0310) ? (b << 17) : (b << 19))
#define MISC_CTRL_CFG_READ_UR_MODE                 (1 << 13)
#define MISC_CTRL_PCIE_IN_WR_COMBINE               (1 << 11)
#define MISC_CTRL_PCIE_RCB_MPS_MODE                (1 << 10)
#define MISC_CTRL_PCIE_RCB_64B_MODE                (1 << 7)
#define MISC_MSI_BAR_CONFIG_LO_OFFSET              (PCIE_MISC_REGS_OFFSET+0x0044)
#define MISC_MSI_BAR_CONFIG_LO_MATCH_ADDR_MASK     0xfffffffc
#define MISC_MSI_BAR_CONFIG_LO_ENABLE_MASK         0x00000001
#define MISC_MSI_BAR_CONFIG_HI_OFFSET              (PCIE_MISC_REGS_OFFSET+0x0048)
#define MISC_MSI_DATA_CONFIG_OFFSET                (PCIE_MISC_REGS_OFFSET+0x004C)
#define MISC_MSI_DATA_CONFIG_MATCH_MASK            0xffff0000
#define MISC_MSI_DATA_CONFIG_MATCH_SHIFT           16
#define MISC_RC_BAD_ADDR_LO_OFFSET                 (PCIE_MISC_REGS_OFFSET+0x0050)
#define MISC_RC_BAD_ADDR_HI_OFFSET                 (PCIE_MISC_REGS_OFFSET+0x0054)
#define MISC_REVISION_OFFSET                       (PCIE_MISC_REGS_OFFSET+0x006C)
#define MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_OFFSET (PCIE_MISC_REGS_OFFSET+0x0070)
#define MISC_CPU_2_PCIE_MEM_WIN_BASE_LIMIT_OFFSET(win) \
	(MISC_CPU_2_PCIE_MEM_WIN0_BASE_LIMIT_OFFSET+(win)*4)
#define MISC_CPU_2_PCIE_MEM_WIN1_BASE_LIMIT_OFFSET (PCIE_MISC_REGS_OFFSET+0x0074)
#define MISC_CPU_2_PCIE_MEM_WIN2_BASE_LIMIT_OFFSET (PCIE_MISC_REGS_OFFSET+0x0078)
#define MISC_CPU_2_PCIE_MEM_WIN3_BASE_LIMIT_OFFSET (PCIE_MISC_REGS_OFFSET+0x007C)
#define MISC_CPU_2_PCI_MEM_WIN_LO_BASE_LIMIT_LIMIT_MASK  0xfff00000
#define MISC_CPU_2_PCI_MEM_WIN_LO_BASE_LIMIT_LIMIT_SHIFT 20
#define MISC_CPU_2_PCI_MEM_WIN_LO_BASE_LIMIT_BASE_SHIFT  4
#define MISC_CPU_2_PCIE_MEM_WIN0_LO_OFFSET         (PCIE_MISC_REGS_OFFSET+0x000C)
#define MISC_CPU_2_PCI_MEM_WIN_LO_BASE_ADDR_MASK   0xfff00000
#define MISC_CPU_2_PCIE_MEM_WIN_LO_OFFSET(win)     (MISC_CPU_2_PCIE_MEM_WIN0_LO_OFFSET+(win)*8)
#define MISC_CPU_2_PCIE_MEM_WIN0_HI_OFFSET         (PCIE_MISC_REGS_OFFSET+0x0010)
#define MISC_CPU_2_PCIE_MEM_WIN_HI_OFFSET(win)     (MISC_CPU_2_PCIE_MEM_WIN0_HI_OFFSET+(win)*8)
#define MISC_CPU_2_PCIE_MEM_WIN1_LO_OFFSET         (PCIE_MISC_REGS_OFFSET+0x0014)
#define MISC_CPU_2_PCIE_MEM_WIN1_HI_OFFSET         (PCIE_MISC_REGS_OFFSET+0x0018)
#define MISC_CPU_2_PCIE_MEM_WIN2_LO_OFFSET         (PCIE_MISC_REGS_OFFSET+0x001C)
#define MISC_CPU_2_PCIE_MEM_WIN2_HI_OFFSET         (PCIE_MISC_REGS_OFFSET+0x0020)
#define MISC_CPU_2_PCIE_MEM_WIN3_LO_OFFSET         (PCIE_MISC_REGS_OFFSET+0x0024)
#define MISC_CPU_2_PCIE_MEM_WIN3_HI_OFFSET         (PCIE_MISC_REGS_OFFSET+0x0028)
#define MISC_RC_BAR1_CONFIG_LO_OFFSET              (PCIE_MISC_REGS_OFFSET+0x002C)
#define MISC_RC_BAR_CONFIG_LO_SIZE_MAX             0x14
#define MISC_RC_BAR_CONFIG_LO_SIZE_2GB             0x10
#define MISC_RC_BAR_CONFIG_LO_MATCH_ADDRESS_MASK   0xfff00000
#define MISC_RC_BAR1_CONFIG_HI_OFFSET              (PCIE_MISC_REGS_OFFSET+0x0030)
#define MISC_RC_BAR2_CONFIG_LO_OFFSET              (PCIE_MISC_REGS_OFFSET+0x0034)
#define MISC_RC_BAR2_CONFIG_HI_OFFSET              (PCIE_MISC_REGS_OFFSET+0x0038)
#define MISC_RC_BAR3_CONFIG_LO_OFFSET              (PCIE_MISC_REGS_OFFSET+0x003C)
#define MISC_RC_BAR3_CONFIG_HI_OFFSET              (PCIE_MISC_REGS_OFFSET+0x0040)
#define MISC_PCIE_CTRL_OFFSET                      (PCIE_MISC_REGS_OFFSET+0x0064)
#define MISC_PCIE_CTRL_PCIE_PERSTB                 (1 << 2)
#define MISC_UBUS_CTRL_OFFSET                      (PCIE_MISC_REGS_OFFSET+0x00A4)
#define MISC_UBUS_CTRL_UBUS_WR_WITH_REPLY          (1 << 14)
#define MISC_UBUS_BAR1_CONFIG_REMAP_OFFSET         (PCIE_MISC_REGS_OFFSET+0x00AC)
#define MISC_UBUS_BAR_CONFIG_ACCESS_EN             (1 << 0)
#define MISC_UBUS_BAR1_CONFIG_REMAP_HI_OFFSET      (PCIE_MISC_REGS_OFFSET+0x00B0)
#define MISC_UBUS_BAR2_CONFIG_REMAP_OFFSET         (PCIE_MISC_REGS_OFFSET+0x00B4)
#define MISC_UBUS_BAR2_CONFIG_REMAP_HI_OFFSET      (PCIE_MISC_REGS_OFFSET+0x00B8)
#define MISC_UBUS_BAR3_CONFIG_REMAP_OFFSET         (PCIE_MISC_REGS_OFFSET+0x00BC)
#define MISC_UBUS_BAR3_CONFIG_REMAP_HI_OFFSET      (PCIE_MISC_REGS_OFFSET+0x00C0)
#define MISC_HARD_DEBUG_OFFSET                     (PCIE_MISC_HARD_REGS_OFFSET+0x0004)
#define MISC_HARD_DEBUG_REFCLK_OVERRIDE_OUT        (1 << 20)
#define MISC_HARD_DEBUG_REFCLK_OVERRIDE_IN_MASK    (7 << 17)
#define MISC_HARD_DEBUG_REFCLK_OVERRIDE_IN(x)      (x << 17)
#define MISC_HARD_DEBUG_REFCLK_OVERRIDE            (1 << 16)

/* PCIE EXTERNAL CFG Registers */
#define EXT_CFG_PCIE_EXT_CFG_INDEX_OFFSET          (PCIE_EXT_CFG_REGS_OFFSET+0x0000)
#define EXT_CFG_BUS_NUM_SHIFT                      20
#define EXT_CFG_DEV_NUM_SHIFT                      15
#define EXT_CFG_FUNC_NUM_SHIFT                     12

/* INTR2: PCI-E L2 Interrupt Controller Registers */
#define INTR2_CPU_STATUS_OFFSET                    (PCIE_L2_INTR_CTRL_REGS_OFFSET+0x0000)
#define INTR2_CPU_CLEAR_OFFSET                     (PCIE_L2_INTR_CTRL_REGS_OFFSET+0x0008)
#define INTR2_CPU_MASK_STATUS_OFFSET               (PCIE_L2_INTR_CTRL_REGS_OFFSET+0x000C)
#define INTR2_CPU_MASK_SET_OFFSET                  (PCIE_L2_INTR_CTRL_REGS_OFFSET+0x0010)
#define INTR2_CPU_MASK_CLEAR_OFFSET                (PCIE_L2_INTR_CTRL_REGS_OFFSET+0x0014)
#define INTR2_CPU_PCIE_TGT_BAD_ADDR(rev)           (((rev) >= 0x303) ? (1 << 18) : (1 << 8))
#define INTR2_CPU_PCIE_TGT_BAD_ACCESS(rev)         (((rev) >= 0x303) ? (1 << 19) : (1 << 9))
#define INTR2_CPU_PCIE_MSTR_UR_ATTN(rev)           (((rev) >= 0x303) ? (1 << 22) : (1 << 12))
#define INTR2_CPU_PCIE_MSTR_CA_ATTN(rev)           (((rev) >= 0x303) ? (1 << 23) : (1 << 13))
#define INTR2_CPU_PCIE_MSTR_RETRY_TIMEOUT(rev)     (((rev) >= 0x303) ? (1 << 24) : (1 << 14))
#define INTR2_CPU_PCIE_MSTR_FWD_ERR(rev)           (((rev) >= 0x303) ? (1 << 25) : (1 << 15))
#define INTR2_CPU_PCIE_INTR_MASK(rev)              (\
	INTR2_CPU_PCIE_TGT_BAD_ADDR(rev)       | INTR2_CPU_PCIE_TGT_BAD_ACCESS(rev) |  \
	INTR2_CPU_PCIE_MSTR_UR_ATTN(rev)       | INTR2_CPU_PCIE_MSTR_CA_ATTN(rev)   |  \
	INTR2_CPU_PCIE_MSTR_RETRY_TIMEOUT(rev) | INTR2_CPU_PCIE_MSTR_FWD_ERR(rev))
#define INTR2_CPU_MSI_INTR_MASK                    0xFF000000
#define INTR2_CPU_MSI_INTR_SHIFT                   24

/* MSI_INTR2: PCI-E MSI L2 Interrupt Controller Registers */
/* MSI interrupts as a seperate block (rev >= 3.03) */
#define MSI_INTR2_CPU_STATUS_OFFSET                (PCIE_MSI_INTR2_REGS_OFFSET+0x0000)
#define MSI_INTR2_CPU_CLEAR_OFFSET                 (PCIE_MSI_INTR2_REGS_OFFSET+0x0008)
#define MSI_INTR2_CPU_MASK_SET_OFFSET              (PCIE_MSI_INTR2_REGS_OFFSET+0x0010)
#define MSI_INTR2_CPU_MASK_CLEAR_OFFSET            (PCIE_MSI_INTR2_REGS_OFFSET+0x0014)
#define MSI_INTR2_CPU_MSI_INTR_MASK                0xFFFFFFFF
#define MSI_INTR2_CPU_MSI_INTR_SHIFT               0

/* UBUS_INTR2: PCI-E UBUS L2 Interrupt Controller Registers */
#define UBUS_INTR2_CPU_STATUS_OFFSET               (PCIE_UBUS_L2_INTR_CTRL_REGS_OFFSET+0x0000)
#define UBUS_INTR2_PCIE_LINKUP_INTR                (1 << 0)
#define UBUS_INTR2_PCIE_LINKDOWN_INTR              (1 << 1)
#define UBUS_INTR2_PCIE_INV_CMD_ERR_INTR           (1 << 2)
#define UBUS_INTR2_PCIE_ADDR_RANGE_ERR_INTR        (1 << 3)
#define UBUS_INTR2_PCIE_UBUS_TOUT_ERR_INTR         (1 << 4)
#define UBUS_INTR2_PCIE_REG_ACC_ERR_INTR           (1 << 5)
#define UBUS_INTR2_PCIE_REG_DLEN_ERR_INTR          (1 << 6)
#define UBUS_INTR2_PCIE_MEM_ACC_ERR_INTR           (1 << 7)
#define UBUS_INTR2_PCIE_MEM_WIN_CRSS_ERR_INTR      (1 << 8)
#define UBUS_INTR2_PCIE_PCIE_TGT_RD_RPLY_ERR_INTR  (1 << 9)
#define UBUS_INTR2_PCIE_PCIE_TGT_WR_RPLY_ERR_INTR  (1 << 10)
#define UBUS_INTR2_PCIE_MEM_INV_SWAP_ERR_INTR      (1 << 11)
#define UBUS_INTR2_PCIE_PCIE_INV_SWAP_ERR_INTR     (1 << 12)
#define UBUS_INTR2_PCIE_UBUS_SPARSE_ERR_INTR       (1 << 13)
#define UBUS_INTR2_PCIE_UBUS_SEC_ERR_INTR          (1 << 14)
#define UBUS_INTR2_PCIE_UBUS_WRAP_ERR_INTR         (1 << 15)
#define UBUS_INTR2_PCIE_INTR_MASK                  (0x0000FFFF)
#define UBUS_INTR2_CPU_SET_OFFSET                  (PCIE_UBUS_L2_INTR_CTRL_REGS_OFFSET+0x0004)
#define UBUS_INTR2_CPU_CLEAR_OFFSET                (PCIE_UBUS_L2_INTR_CTRL_REGS_OFFSET+0x0008)
#define UBUS_INTR2_CPU_MASK_STATUS_OFFSET          (PCIE_UBUS_L2_INTR_CTRL_REGS_OFFSET+0x000C)
#define UBUS_INTR2_CPU_MASK_SET_OFFSET             (PCIE_UBUS_L2_INTR_CTRL_REGS_OFFSET+0x0010)
#define UBUS_INTR2_CPU_MASK_CLEAR_OFFSET           (PCIE_UBUS_L2_INTR_CTRL_REGS_OFFSET+0x0014)

/* CPU_INTR1: PCIE CPU L1 Interrupt Controller Registers */
#define CPU_INTR1_INTR_INTR_STATUS_OFFSET          (PCIE_CPU_INTR1_REGS_OFFSET+0x0000)
#define CPU_INTR1_INTR_MASK_STATUS_OFFSET          (PCIE_CPU_INTR1_REGS_OFFSET+0x0004)
#define CPU_INTR1_INTR_MASK_SET_OFFSET             (PCIE_CPU_INTR1_REGS_OFFSET+0x0008)
#define CPU_INTR1_INTR_MASK_CLEAR_OFFSET           (PCIE_CPU_INTR1_REGS_OFFSET+0x000C)
#define CPU_INTR1_PCIE_INTA_CPU_INTR               (1 << 1)
#define CPU_INTR1_PCIE_INTB_CPU_INTR               (1 << 2)
#define CPU_INTR1_PCIE_INTC_CPU_INTR               (1 << 3)
#define CPU_INTR1_PCIE_INTD_CPU_INTR               (1 << 4)
#define CPU_INTR1_PCIE_INTR_CPU_INTR               (1 << 5)
#define CPU_INTR1_PCIE_NMI_CPU_INTR                (1 << 6)
#define CPU_INTR1_PCIE_UBUS_CPU_INTR               (1 << 7)
#define CPU_INTR1_PCIE_MSI_INTR_CPU_INTR           (1 << 9)

/* UBUS_G3_PLL: PCIE GEN3 PLL Control Registers */
#define G3_PLL_PLL_RESETS_OFFSET                   (PCIE_G3_PLL_REGS_OFFSET+0x0000)
#define G3_PLL_PLL_RESETS_RESETB                   (1 << 0)
#define G3_PLL_PLL_RESETS_POST_RESETB              (1 << 1)
#define G3_PLL_PLL_NDIV_OFFSET                     (PCIE_G3_PLL_REGS_OFFSET+0x000c)
#define G3_PLL_PLL_NDIV_INT_MASK                   (0x3FF)
#define G3_PLL_PLL_NDIV_INT(d)                     ((d) & G3_PLL_PLL_NDIV_INT_MASK)
#define G3_PLL_PLL_STAT_OFFSET                     (PCIE_G3_PLL_REGS_OFFSET+0x002c)
#define G3_PLL_PLL_STAT_PLL_LOCK                   (1 << 31)
#define G3_16FF_PLL_PLL_SSC_LIMIT_SSC_MODE_OFFSET  (PCIE_G3_PLL_REGS_OFFSET+0x0030) /* 16ff viper */
#define G3_PLL_PLL_SSC_LIMIT_SSC_MODE_DOWNSPREAD   (1 << 25)
#define G3_PLL_PLL_SSC_STEP_OFFSET                 (PCIE_G3_PLL_REGS_OFFSET+0x0034) /* 16ff viper */
#define G3_PLL_PLL_SSC_STEP_PLL_SSC_STEP_MASK      (0xFFFF)
#define G3_PLL_PLL_NDIV_FRAC_HOLDALL_OFFSET        (PCIE_G3_PLL_REGS_OFFSET+0x004c)
#define G3_PLL_PLL_NDIV_FRAC_HOLDALL_HOLA_ALL      (1 << 24)
#define G3_PLL_PLL_NDIV_FRAC_HOLDALL_FRAC_MASK     (0xFFFFFF)
#define G3_PLL_PLL_NDIV_FRAC_HOLDALL_NDIV_FRAC(f)  ((f) & 0xFFFFFF)
#define G3_PLL_PLL_SSC_LIMIT_SSC_MODE_OFFSET       (PCIE_G3_PLL_REGS_OFFSET+0x0050)
#define G3_PLL_PLL_SSC_LIMIT_SSC_MODE_MODE         (1 << 24)
#define G3_PLL_PLL_SSC_LIMIT_SSC_MODE_LIMIT_MASK   (0x3FFFFF)
#define G3_PLL_PLL_SSC_LIMIT_SSC_MODE_LIMIT(l)     ((l) & 0x3FFFFF)
#define G3_PLL_PLL_SSC_STEP_VCOGAIN_OFFSET         (PCIE_G3_PLL_REGS_OFFSET+0x0054)
#define G3_PLL_PLL_SSC_STEP_VCOGAIN_VCO_GAIN_MASK  (0x000F0000)
#define G3_PLL_PLL_SSC_STEP_VCOGAIN_VCO_GAIN(g)    (((g) & 0xF) << 16)
#define G3_PLL_PLL_SSC_STEP_VCOGAIN_SSC_STEP_MASK  (0xFFFF)
#define G3_PLL_PLL_SSC_STEP_VCOGAIN_SSC_STEP(s)    ((s) & 0xFFFF)

/*
 * +-----------------------------------------------------
 * SERDES: GEN2 Registers
 * +-----------------------------------------------------
 */
#define SERDES_PCIE_BLK0_OFFSET                    (0x1000)
#define SERDES_PCIE_BLK_SIZE                       (0x0100)
#define SERDES_PCIE_BLK1_OFFSET                    (0x1100)
#define SERDES_PCIE_BLK2_OFFSET                    (0x1200)
#define SERDES_PCIE_BLK3_OFFSET                    (0x1300)
#define SERDES_PCIE_BLK4_OFFSET                    (0x1400)
#define SERDES_PCIE_BLK5_OFFSET                    (0x1500)
#define SERDES_PCIE_BLK6_OFFSET                    (0x1600) /* 16ff viper */
#define SERDES_PLL_AFE0_OFFSET                     (0x2000)
#define SERDES_PLL_AFE_SIZE                        (0x0100)
#define SERDES_PLL_AFE1_OFFSET                     (0x2100)
#define SERDES_PLL_AFE2_OFFSET                     (0x2200)
#define SERDES_PLL_AFE3_OFFSET                     (0x2300)
#define SERDES_PLL_STABLE_TMR_CTRL_OFFSET          (0x2400)
#define SERDES_PLL_PLL_CTRL_OFFSET                 (0x2500)
#define SERDES_PLL_SSC_CTRL_OFFSET                 (0x2600)
#define SERDES_TX_AFE_BLOCK_OFFSET                 (0x4000)
#define SERDES_TX_CTR1_LN0_OFFSET                  (SERDES_TX_AFE_BLOCK_OFFSET + 0x0000)
#define SERDES_TX_CTR1_LN_SIZE                     0x0010
#define SERDES_TX_DFE_BLOCK_OFFSET                 (0x5000)
#define SERDES_TX_DFE0_LN0_OFFSET                  (SERDES_TX_DFE_BLOCK_OFFSET + 0x0000)
#define SERDES_TX_DFE0_LN_SIZE                     0x0010


#if defined(PCIE0_PHYS_BASE) && defined(PCIE1_PHYS_BASE) && defined(PCIE2_PHYS_BASE) && \
	defined(PCIE3_PHYS_BASE)
#define NUM_CORE                                   4
#elif defined(PCIE0_PHYS_BASE) && defined(PCIE1_PHYS_BASE) && defined(PCIE2_PHYS_BASE)
#define NUM_CORE                                   3
#elif defined(PCIE0_PHYS_BASE) && defined(PCIE1_PHYS_BASE)
#define NUM_CORE                                   2
#else
#define NUM_CORE                                   1
#endif


/*
 * +-----------------------------------------------------
 *  Structures
 * +-----------------------------------------------------
 */

#ifdef __cplusplus
}
#endif

#endif /* __PCIE_BCM963XX_H */
