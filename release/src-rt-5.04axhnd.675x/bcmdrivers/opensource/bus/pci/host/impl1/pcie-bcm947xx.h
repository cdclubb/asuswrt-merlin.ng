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
#ifndef __PCIE_BCM947XX_H
#define __PCIE_BCM947XX_H

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
#define BCM947XX_PCIE_DEV_NAME                   "bcm947xx-pcie"
#define BCM947XX_PCIE_DRV_NAME                   BCM947XX_PCIE_DEV_NAME


/* RC_CFG_TYPE1 */
#define RC_CFG_TYPE1_DEVICE_VENDOR_ID_OFFSET     (0x0000)
#define RC_CFG_TYPE1_REV_ID_CLASS_CODE_OFFSET    (0x0008)
#define RC_CFG_PCIE_DEVICE_STATUS_CONTROL_OFFSET (0x00B4)
#define RC_CFG_PCIE_LINK_STATUS_CONTROL_2_OFFSET (0x00DC)
	#define RC_CFG_PCIE_LINK_CTRL_TGT_LINK_SPEED_MASK  0x00000003

#if defined(PCIE0_PHYS_BASE) && defined(PCIE1_PHYS_BASE) && defined(PCIE2_PHYS_BASE)
#define NUM_CORE                                 3
#elif defined(PCIE0_PHYS_BASE) && defined(PCIE1_PHYS_BASE)
#define NUM_CORE                                 2
#else
#define NUM_CORE                                 1
#endif
#define PCI_BAR_MAX                              6
#define PCR_RSVDA_MAX                            2
#define MAXFUNCS                                 2
#define MAX_SOC_D11                              2
#define D11_CORE0_IDX                            1
#define D11_CORE1_IDX                            10

#define OFFSETOF(_type, _member)                 ((unsigned int) &((_type *)NULL)->_member)

/*
 * +-----------------------------------------------------
 *  Macros
 * +-----------------------------------------------------
 */

/*
 * +-----------------------------------------------------
 *  Structures
 * +-----------------------------------------------------
 */
/* various PCIE class definition */
typedef enum {
	PCI_CLASS_OLD = 0,
	PCI_CLASS_DASDI,
	PCI_CLASS_NET,
	PCI_CLASS_DISPLAY,
	PCI_CLASS_MMEDIA,
	PCI_CLASS_MEMORY,
	PCI_CLASS_BRIDGE,
	PCI_CLASS_COMM,
	PCI_CLASS_BASE,
	PCI_CLASS_INPUT,
	PCI_CLASS_DOCK,
	PCI_CLASS_CPU,
	PCI_CLASS_SERIAL,
	PCI_CLASS_INTELLIGENT = 0xe,
	PCI_CLASS_SATELLITE,
	PCI_CLASS_CRYPT,
	PCI_CLASS_DSP,
	PCI_CLASS_XOR = 0xfe
} pci_classes;

/* various PCIE subclass definition */
typedef enum {
	PCI_NET_ETHER,
	PCI_NET_TOKEN,
	PCI_NET_FDDI,
	PCI_NET_ATM,
	PCI_NET_OTHER = 0x80
} pci_net_subclasses;

/* various PCIE header definition */
typedef enum {
	PCI_HEADER_NORMAL,
	PCI_HEADER_BRIDGE,
	PCI_HEADER_CARDBUS
} pci_header_types;

/* Structure to manupulate PCIE config space for internal D11 */
typedef struct pci_config_regs_t {
	uint16	vendor;
	uint16	device;
	uint16	command;
	uint16	status;
	uint8	rev_id;
	uint8	prog_if;
	uint8	sub_class;
	uint8	base_class;
	uint8	cache_line_size;
	uint8	latency_timer;
	uint8	header_type;
	uint8	bist;
	uint32	base[PCI_BAR_MAX];
	uint32	cardbus_cis;
	uint16	subsys_vendor;
	uint16	subsys_id;
	uint32	baserom;
	uint32	rsvd_a[PCR_RSVDA_MAX];
	uint8	int_line;
	uint8	int_pin;
	uint8	min_gnt;
	uint8	max_lat;
	uint8	dev_dep[192];
} pci_config_regs;

/* Emulated configuration space */
typedef struct {
	int	n;
	uint32	size[PCI_BAR_MAX];
} si_bar_cfg_t;

typedef struct {
	pci_config_regs emu;	/* emulated PCI config */
	si_bar_cfg_t bar;	/* region sizes */
} si_pci_cfg_t;

#ifdef __cplusplus
}
#endif

#endif /* __PCIE_BCM947XX_H */
