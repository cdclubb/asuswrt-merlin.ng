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

#include "boardparms.h"
#include "bcm_gpio.h"

#include <linux/kernel.h>
#include <linux/module.h>
#include <bcm_map_part.h>
#include <linux/string.h>

/*
  The Linux board driver handles any necessary locking so these functions should not be called
  directly from elsewhere.
*/

unsigned int bcm_gpio_get_dir(unsigned int gpio_num)
{
    return (GPIO->GPIODir[GPIO_NUM_TO_ARRAY_IDX(gpio_num)] & (GPIO_NUM_TO_MASK(gpio_num))) >> GPIO_NUM_TO_ARRAY_SHIFT(gpio_num);
}
EXPORT_SYMBOL(bcm_gpio_get_dir);

void bcm_gpio_set_dir(unsigned int gpio_num, unsigned int dir)
{
#ifndef CONFIG_BRCM_QEMU    
    if(dir)	
        GPIO->GPIODir[GPIO_NUM_TO_ARRAY_IDX(gpio_num)] |= GPIO_NUM_TO_MASK(gpio_num);	
    else
        GPIO->GPIODir[GPIO_NUM_TO_ARRAY_IDX(gpio_num)] &= ~GPIO_NUM_TO_MASK(gpio_num);
#endif        	
}
EXPORT_SYMBOL(bcm_gpio_set_dir);

unsigned int bcm_gpio_get_data(unsigned int gpio_num)
{
    return (GPIO->GPIOio[GPIO_NUM_TO_ARRAY_IDX(gpio_num)] & (GPIO_NUM_TO_MASK(gpio_num))) >> GPIO_NUM_TO_ARRAY_SHIFT(gpio_num);
}
EXPORT_SYMBOL(bcm_gpio_get_data);

void bcm_gpio_set_data(unsigned int gpio_num, unsigned int data)
{
#ifndef CONFIG_BRCM_QEMU     
    if (data)	
        GPIO->GPIOio[GPIO_NUM_TO_ARRAY_IDX(gpio_num)] |= GPIO_NUM_TO_MASK(gpio_num);	
    else
        GPIO->GPIOio[GPIO_NUM_TO_ARRAY_IDX(gpio_num)] &= ~GPIO_NUM_TO_MASK(gpio_num);
#endif    
}
EXPORT_SYMBOL(bcm_gpio_set_data);

/*  *********************************************************************
    *  bcm_common_gpio_init()
    *
    *  Initialize the gpio pin state. Some board require bootloader to set
    *  certain GPIO to known state
    *
    *  Input parameters: none
    *
    *  Return value:
    *      nothing
    ********************************************************************* */
int bcm_common_gpio_init(void)
{
    uint16_t gpio;
    unsigned short gpio_state;
    void* token = NULL;

    while( BpEnumGpioInitState(&token, &gpio) == BP_SUCCESS ) {
        bcm_gpio_set_dir(gpio, 1);
        if ( gpio & BP_ACTIVE_LOW )
            gpio_state = 0;
        else
            gpio_state = 1;
        bcm_gpio_set_data(gpio, gpio_state);

        //printk("gpio init state for num 0x%x state %d\n", gpio, gpio_state);
    }

    return 0;
}

subsys_initcall(bcm_common_gpio_init);
