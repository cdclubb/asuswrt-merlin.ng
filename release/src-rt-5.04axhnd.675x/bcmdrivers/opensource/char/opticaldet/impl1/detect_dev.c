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

#include <linux/module.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/uaccess.h>
#define USE_BCMI2C
#ifdef USE_BCMI2C
#include "bcmsfp_i2c.h"
#endif
#include "opticaldet.h"
#include "detect_dev_trx_data.h"

#ifdef USE_BCMI2C
static int i2c_sfp_cb(struct notifier_block *nb, unsigned long action, void *data);
static struct notifier_block i2c_sfp_nb = {
    .notifier_call = i2c_sfp_cb,
};
#endif

static int _file_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int _file_release(struct inode *inode, struct file *file)
{
    return 0;
}

static long _file_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    switch (cmd)
    {
        case OPTDETECT_IOCTL_GET_TRX_INFO:
            {
                TRX_INFOMATION trx_info;

                if (trx_get_full_info(0, &trx_info))
                {
                    return -1;
                }

                if (copy_to_user((void *)arg, (void *)&trx_info, sizeof(TRX_INFOMATION)))
                {
                    printk(KERN_ERR "%s: failed copy data to user!\n", __FUNCTION__);
                    return -1;
                }
            }
            break;

        default:
            printk(KERN_ERR "%s: ERR! unknown ioctl cmd\n", __FUNCTION__);
            return -1;
    }
    return 0;
}

static const struct file_operations detect_file_ops =
{
    .owner = THIS_MODULE,
    .open = _file_open,
    .release = _file_release,
    .unlocked_ioctl = _file_ioctl,
#if defined(CONFIG_COMPAT)
    .compat_ioctl = _file_ioctl,
#endif
};

#ifdef USE_BCMI2C
static void trx_init(int bus) 
{
    if( bus >= MAX_I2C_BUS_INCLUDE_MUX )
        return;

    if( i2c_read_trx_data(bus) == 0 ) {
        trx_fixup(bus);
        trx_activate (bus);
    }
    return;
}

static void trx_deinit(int bus) 
{
    if( bus >= MAX_I2C_BUS_INCLUDE_MUX )
        return;

    i2c_clear_trx_data(bus);
    return;
}

static int i2c_sfp_cb(struct notifier_block *nb, unsigned long action, void *data)
{
    int bus = (long)data;

    if( action == SFP_STATUS_INSERTED )
        trx_init(bus);
    else 
        trx_deinit(bus);

    return NOTIFY_OK;
}
#endif


#define OPTICAL_DET_DEV_MAJOR 320
#define OPTICAL_DET_DEV_CLASS "opticaldetect"

int __init detect_init(void)
{
    int ret;
#ifdef USE_BCMI2C
    int i;
    bcm_i2c_sfp_register_notifier(&i2c_sfp_nb);

    for( i = 0; i < MAX_I2C_BUS_INCLUDE_MUX; i++ ) {
        if ( bcm_i2c_sfp_get_status(i) == SFP_STATUS_INSERTED ) {
            trx_init(i);
        }
    }
#endif

    ret = register_chrdev(OPTICAL_DET_DEV_MAJOR, OPTICAL_DET_DEV_CLASS, &detect_file_ops);
    if (ret) {
        printk(KERN_ALERT "\nOptical detection module failed to load.\n");
    } else {
        printk(KERN_INFO "\nOptical detection module loaded.\n");
    }

    return ret;
}
module_init(detect_init);

static void __exit detect_exit(void)
{
#ifdef USE_BCMI2C
    bcm_i2c_sfp_unregister_notifier(&i2c_sfp_nb);
#endif

    unregister_chrdev(OPTICAL_DET_DEV_MAJOR, OPTICAL_DET_DEV_CLASS);
    printk(KERN_INFO "\nOptical detection module unloaded.\n");
}
module_exit(detect_exit);

MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Optical device detection driver");
MODULE_LICENSE("GPL");
