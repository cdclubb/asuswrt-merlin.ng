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

#include "boardparms.h"
#include "bcm_pinmux.h"
#include "bcm_led.h"

#include <linux/kernel.h>
#include <linux/module.h>
#include <bcm_map_part.h>
#include <linux/string.h>

void bcm_set_pinmux(unsigned int pin_num, unsigned int mux_num)
{
    unsigned int tp_blk_data_lsb;
    //printk("set pinmux %d to %d\n",pin_num, mux_num);

    tp_blk_data_lsb= 0;
    tp_blk_data_lsb |= pin_num;
    tp_blk_data_lsb |= (mux_num << PINMUX_DATA_SHIFT);
    GPIO->TestPortBlockDataMSB = 0;
    GPIO->TestPortBlockDataLSB = tp_blk_data_lsb;
    GPIO->TestPortCmd = LOAD_MUX_REG_CMD;
}

void bcm_init_pinmux_interface(unsigned int interface) {
    int i, n, errcnt;
    unsigned short Function[BP_PINMUX_MAX];
    unsigned int Muxinfo[BP_PINMUX_MAX];

    if (BP_SUCCESS != BpGetIfacePinmux (interface, BP_PINMUX_MAX, &n, &errcnt, Function, Muxinfo)) {
        return;
    }
    for (i = n-1 ; 0 <= i ; i--) {
        bcm_set_pinmux( Muxinfo[i] & BP_PINMUX_PIN_MASK, (Muxinfo[i] & BP_PINMUX_VAL_MASK) >> BP_PINMUX_VAL_SHIFT );
    }
}

int bcm_pinmux_update_optled_map(unsigned short led_gpio_num, unsigned int muxinfo)
{
    short *optled_map;
    int led_chn_num = led_gpio_num;
    
    optled_map = bcm_led_driver_get_optled_map();

    if (muxinfo & BP_PINMUX_OPTLED_VALID) {
        led_chn_num = (muxinfo & BP_PINMUX_OPTLED_MASK) >> BP_PINMUX_OPTLED_SHIFT;
        optled_map[led_gpio_num] = led_chn_num;
    } else {
        optled_map[led_gpio_num] = led_gpio_num;
    }

    return led_chn_num;
}

int bcm_init_pinmux(void)
{
    int i, n, errcnt, op;
    int lednum;
    unsigned int serial = 0;
    unsigned int ledsrc = 0;
    unsigned short Function[BP_PINMUX_MAX];
    unsigned int Muxinfo[BP_PINMUX_MAX];

    if (BP_SUCCESS != BpGetAllPinmux (BP_PINMUX_MAX, &n, &errcnt, Function, Muxinfo)) {
        return 0;
    }

    for (i = n-1 ; 0 <= i ; i--) {
        lednum = Function[i] & BP_GPIO_NUM_MASK;
        lednum = bcm_pinmux_update_optled_map(lednum, Muxinfo[i]);
        op = Muxinfo[i] & BP_PINMUX_OP_MASK;
        if (Function[i] & BP_GPIO_SERIAL) {
            serial |= 1 << (Function[i] & BP_GPIO_NUM_MASK);
            bcm_led_zero_flash_rate(Function[i] & BP_GPIO_NUM_MASK);
        } else {
            bcm_set_pinmux( Muxinfo[i] & BP_PINMUX_PIN_MASK, (Muxinfo[i] & BP_PINMUX_VAL_MASK) >> BP_PINMUX_VAL_SHIFT );
            if ((op == BP_PINMUX_HWLED) || (op == BP_PINMUX_SWLED)) {
                // zero the flash rate for any LED that needs to be on/off
                bcm_led_zero_flash_rate(lednum);
            }
        }
        if ((op == BP_PINMUX_HWLED) || (op == BP_PINMUX_PWMLED)) {
            ledsrc |= 1 << lednum;
        }
    }
    // count bits enabled for serial and add additional to byte boundary
    n = 0; 
    for (i = 0 ; i < 32 ; i++) {
        if (serial & (1 << i)) {
            n++; 
        }
    }
    i = 31;
    while (n % 8) {
        if (serial & (1 << i)) {
            printk("ERROR: could not append enough serial LEDs\n");
        } else {
            serial |= (1<<i);
        }
        i--;
        n++;
    }

    bcm_led_set_source(serial, ledsrc);

    return 0;
}

EXPORT_SYMBOL(bcm_set_pinmux);
EXPORT_SYMBOL(bcm_pinmux_update_optled_map);
