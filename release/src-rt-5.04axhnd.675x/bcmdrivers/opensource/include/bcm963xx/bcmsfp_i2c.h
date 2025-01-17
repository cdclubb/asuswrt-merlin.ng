/*
 
 Copyright (c) 2008 Broadcom Corporation 
* <:copyright-BRCM:2012:DUAL/GPL:standard 
* 
*    Copyright (c) 2012 Broadcom 
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
/***********************************************************************/
/*                                                                     */
/*   MODULE   bcmsfp_i2c.h                                             */
/*   DATE:    07/23/08                                                 */
/*   PURPOSE: BCM SFP Transceiver reg access API                       */
/*                                                                     */
/***********************************************************************/
#ifndef __BCMSFP_I2C_H
#define __BCMSFP_I2C_H

#ifdef __KERNEL__
#include <linux/notifier.h>
#include "pmd.h"

#define MAX_I2C_BUS          2

#define MAX_TRANSACTION_SIZE    32
#define MAX_SFP_I2C_ADDR        3

#define MAX_CLIENT_NUM          8
#define PCA954x_NUM_DEVICES     8
#define MAX_I2C_BUS_INCLUDE_MUX (MAX_I2C_BUS+PCA954x_NUM_DEVICES) 

/* to full 8 bit i2c address */
#define I2C_FULL_ADDRESS(addr)  ((addr)<<1)

/* XFP/SFP/SFF I2C client address. These addresses are 7-bit addresses without the LSB bit */
#define SFP_I2C_EEPROM_ADDR     0x50
#define SFP_I2C_DIAG_ADDR       0x51 /* SFP/SFF only */
#define SFP_I2C_PHY_ADDR        0x56 /* SFP/SFF only */
#define SFP_I2C_SMTC_EEPROMLESS_ADDR        0x55 /* SMTC only */

/* SFP/SFF I2C client number assignment for above address */
#define SFP_CLIENT_EEPROM       0x0
#define SFP_CLIENT_DIAG         0x1
#define SFP_CLIENT_PHY          0x2
#define SFP_CLIENT_SMTC_EEPROMLESS          0x3

/* monitoring information based on INF specs 8472, 8074, 8077 */
#define TRANSCEIVER_IDENTIFIER_OFFSET          0
#define TRANSCEIVER_IDENTIFIER_SFF             2
#define TRANSCEIVER_IDENTIFIER_SFP             3
#define TRANSCEIVER_IDENTIFIER_XFP             6 /* INF 8077 */
#define TRANSCEIVER_AUX_MON_OFFSET             222
#define TRANSCEIVER_AUX_MON_TYPE_VOLT          0b0001
#define TRANSCEIVER_AUX_MON_DATA1_MSB_OFFSET   106
#define TRANSCEIVER_AUX_MON_DATA2_MSB_OFFSET   108
#define LASER_DEV_NP_TX_PWR_MSB_OFFSET         102
#define LASER_DEV_NP_TX_PWR_LSB_OFFSET         103
#define LASER_DEV_NP_TX_PWR_OFFSET             LASER_DEV_NP_TX_PWR_MSB_OFFSET
#define LASER_DEV_NP_RX_PWR_MSB_OFFSET         104
#define LASER_DEV_NP_RX_PWR_LSB_OFFSET         105
#define LASER_DEV_NP_RX_PWR_OFFSET             LASER_DEV_NP_RX_PWR_MSB_OFFSET
#define LASER_DEV_NP_TEMP_MSB_OFFSET           96
#define LASER_DEV_NP_TEMP_LSB_OFFSET           97
#define LASER_DEV_NP_TEMP_OFFSET               LASER_DEV_NP_TEMP_MSB_OFFSET
#define LASER_DEV_NP_VOLTAGE_MSB_OFFSET        98
#define LASER_DEV_NP_VOLTAGE_LSB_OFFSET        99
#define LASER_DEV_NP_VOLTAGE_OFFSET            LASER_DEV_NP_VOLTAGE_MSB_OFFSET
#define LASER_DEV_NP_BIAS_CURRENT_MSB_OFFSET   100
#define LASER_DEV_NP_BIAS_CURRENT_LSB_OFFSET   101
#define LASER_DEV_NP_BIAS_CURRENT_OFFSET       LASER_DEV_NP_BIAS_CURRENT_MSB_OFFSET
#define STATUS_CONTROL                         0x6E


/* BCM PMD I2C client address. These addresses are 7-bit addresses without the LSB bit */
#define PMD_I2C_REG_ADDR        0x50
#define PMD_I2C_IRAM_ADDR       0x51
#define PMD_I2C_DRAM_ADDR       0x52


/* BCM PMD I2C client number assignment for above address */
#define PMD_CLIENT_REG          pmd_reg_map
#define PMD_CLIENT_IRAM         pmd_iram_map
#define PMD_CLIENT_DRAM         pmd_dram_map

#define SFP_STATUS_INVALID      -1
#define SFP_STATUS_REMOVED      0
#define SFP_STATUS_INSERTED     1
#define SFP_STATUS_PROBING      2
#define SFP_STATUS_ERROR        3

/****************************************************************************/
/* Writes count number of bytes from buf on to the I2C bus                  */
/* Returns:                                                                 */
/*   number of bytes written on success, negative value on failure.         */
/* Notes: 1. The count > 32 is not yet supported                            */
/*        2. The buf[0] should be the offset where write starts             */
/****************************************************************************/
ssize_t bcmsfp_write(u8 bus_num, u8 client_num, char *buf, size_t count);

/****************************************************************************/
/* Reads count number of bytes from sfp                                     */
/* Returns:                                                                 */
/*   number of bytes read on success, negative value on failure.            */
/* Notes: 1. The count > 32 is not yet supported                            */
/*        2. The buf[0] should be the offset where read starts              */
/****************************************************************************/
ssize_t bcmsfp_read(u8 bus_num, u8 client_num, char *buf, size_t count);

/****************************************************************************/
/* Write Register: Writes the val into sfp register                         */
/* Returns:                                                                 */
/*   0 on success, negative value on failure.                               */
/* Notes: 1. The offset should be DWORD aligned                             */
/****************************************************************************/
int bcmsfp_write_reg(u8 bus_num, u8 client_num, u8 offset, u32 val);

/****************************************************************************/
/* Read Register: Read the sfp register at given offset                     */
/* Returns:                                                                 */
/*   value on success, negative value on failure.                           */
/* Notes: 1. The offset should be DWORD aligned                             */
/****************************************************************************/
int bcmsfp_read_reg(u8 bus_num, u8 client_num, u8 offset, u32* val);

/****************************************************************************/
/* Write Word: Writes the val into LSB 2 bytes of Register                  */ 
/* Returns:                                                                 */
/*   0 on success, negative value on failure.                               */
/* Notes: 1. The offset should be WORD aligned                              */
/****************************************************************************/
int bcmsfp_write_word(u8 bus_num, u8 client_num, u8 offset, u16 val);

/****************************************************************************/
/* Read Word: Reads the LSB 2 bytes of Register                             */ 
/* Returns:                                                                 */
/*   value on success, negative value on failure.                           */
/* Notes: 1. The offset should be WORD aligned                              */
/****************************************************************************/
int bcmsfp_read_word(u8 bus_num, u8 client_num, u8 offset, u16* val);

/****************************************************************************/
/* Write Byte: Writes the byte val into offset                              */ 
/* Returns:                                                                 */
/*   0 on success, negative value on failure.                               */
/****************************************************************************/
int bcmsfp_write_byte(u8 bus_num, u8 client_num, u8 offset, u8 val);

/****************************************************************************/
/* Read Byte: Reads a byte from offset                                      */ 
/* Returns:                                                                 */
/*   value on success, negative value on failure.                           */
/****************************************************************************/
int bcmsfp_read_byte(u8 bus_num, u8 client_num, u8 offset, u8* val);

/****************************************************************************/
/* Return the default bus as it was set by /sysfs or /procfs                */
/* Returns:                                                                 */
/*   value on success, negative value on failure (value was not set).       */
/****************************************************************************/
int bcmsfp_get_def_bus(void);

int bcmsfp_get_page_info(u8 bus_num, u8* page_a0, u8* page_a2);
int bcmsfp_read_page(u8 bus_num, u8 client_num, u8* val);

int bcm_i2c_sfp_get_status(int bus);
int bcm_i2c_sfp_rescan(int bus);
#ifdef CONFIG_BP_PHYS_INTF
int bcm_i2c_sfp_get_bus_num(unsigned short intf_type, int intf_idx, int *bus);
int bcm_i2c_sfp_get_intf(int bus, unsigned short* intf_type, int* intf_idx);
#endif

int bcm_i2c_sfp_register_notifier(struct notifier_block* nb);
int bcm_i2c_sfp_unregister_notifier(struct notifier_block* nb);

/* PON Optics Type Settings */
int bcm_i2c_pon_optics_type_get(unsigned short *pusValue);
/* PON SFP Signal Detect */
int bcm_i2c_pon_optics_sd_get(unsigned char *sig_det);
#endif
#define BCM_I2C_PON_OPTICS_TYPE_LEGACY          0
#define BCM_I2C_PON_OPTICS_TYPE_PMD             1
#define BCM_I2C_PON_OPTICS_TYPE_NON_BRCM_PMD    2
#define BCM_I2C_PON_OPTICS_TYPE_SMTC            3

#define SMTC_CALIBRATION_FILE_PATH "/data/smtc_calibration" /*keeps smtc calibration values */
#define BCM_I2C_PROC_DIR "driver/bcm_i2c_pon_optics_type"

static inline int bcm_i2c_optics_rx_control(int enable __attribute__((unused))) { return 0; } /* Deprecated function */
int bcm_i2c_optics_tx_control(int enable);
#define BCM_I2C_OPTICS_ENABLE 1
#define BCM_I2C_OPTICS_DISABLE 0

int bcm_i2c_pon_has_rogue_get(void);

#endif

