/*
   Copyright (c) 2015 Broadcom Corporation
   All Rights Reserved

   <:label-BRCM:2015:DUAL/GPL:standard
   
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
 * lport_mdio.c
 *
 *  Created on: 24 Sep 2015
 *      Author: yonatani
 */

#include "bcm6858_drivers_lport_ag.h"
#include "lport_defs.h"
#include "bcm6858_lport_mdio_ag.h"
#include "lport_mdio.h"
#include "lport_compat.h"

typedef enum
{
    MDIO_CL45 = 0,
    MDIO_CL22,
} E_MDIO_CL_TYPE;

typedef enum
{
    MDIO_CL45_ADDRESS =0,
    MDIO_WRITE,
    MDIO_CL45_RDINC,
    MDIO_CL22_RD = MDIO_CL45_RDINC,
    MDIO_CL45_RD,
} E_MDIO_OPCODE;

#define LPORT_ACCESS_MDIO_TRANSACTION_RETRY 1000
#define LPORT_ACCESS_MDIO_TRANSACTION_TIMEOUT_MS 1000

#if LPORT_MDIO_TRANS_LOCKED
#include <linux/mutex.h>
#define MDIO_CHECK_CNTX_LOCK do{ \
    if(in_interrupt()) BUG(); \
    mutex_lock(&mdio_mtx); \
}while(0);

#define MDIO_CNTX_UNLOCK mutex_unlock(&mdio_mtx)
DEFINE_MUTEX(mdio_mtx);
#else
#define MDIO_CHECK_CNTX_LOCK
#define MDIO_CNTX_UNLOCK
#endif

#if LPORT_MDIO_TRANS_INT
DECLARE_COMPLETION(mdio_done);
static uint32_t mdio_timeout;
#endif

#if LPORT_MDIO_TRANS_INT
static void mdio_trans_done_isr(const lport_intr_info_s *info, void *priv)
{
    struct completion *mdio_done_isr = (struct completion *)priv;
    lport_mdio_intr_enable(LPORT_MDIO_DONE,0);
    lport_mdio_intr_clear(LPORT_MDIO_DONE);
    complete(mdio_done_isr);
}

static uint32_t mdio_set_and_wait_polling(lport_mdio_control *control)
{
    int rc = LPORT_ERR_OK;
    uint32_t retries = LPORT_ACCESS_MDIO_TRANSACTION_RETRY;

    /* Poll for transaction end & not error */
    do
    {
        UDELAY(10);
        rc = ag_drv_lport_mdio_control_get(control);
    } while ((!rc) && retries-- && control->start_busy && (!control->fail));

    if (!retries)
    {
        pr_err( "%s(%d):LPORT MDIO write transaction passed too many retries rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control->fail, control->start_busy);
        return LPORT_ERR_IO;
    }
    else if (control->fail || control->start_busy || rc)
    {
        pr_err( "%s(%d):LPORT MDIO write transaction failed or busy rc=%d,fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control->fail, control->start_busy);
        return LPORT_ERR_IO;
    }

    return rc;
}

static uint32_t mdio_set_and_wait(lport_mdio_control *control)
{
    int rc = LPORT_ERR_OK;
    int rv = 0;

    reinit_completion(&mdio_done);

    /* First Arm the mdio interrupt */
    lport_mdio_intr_clear(LPORT_MDIO_DONE);
    lport_mdio_intr_enable(LPORT_MDIO_DONE, 1);

    ag_drv_lport_mdio_control_set(control);

    rv = wait_for_completion_interruptible_timeout(&mdio_done, mdio_timeout);
    if (rv == -ERESTARTSYS)
    {
        /* Try to wait again as polling on this time, Wake up by unexpected interrupt signal from kernel. */
        pr_err("%s(%d):LPORT MDIO Received -ERESTARTSYS, Try to wait again as polling on this time, rc=%d\n",
            __FUNCTION__, __LINE__, rc);

        rc = mdio_set_and_wait_polling(control);
        if (rc || control->fail || control->start_busy)
        {
            pr_err("%s(%d):LPORT MDIO interface is not ready rc=%d, fail=%d, busy=%d\n",
                __FUNCTION__, __LINE__, rc, control->fail, control->start_busy);
            rc =  LPORT_ERR_IO;
        }
        goto done;
    }
    else if (rv == 0)
    {
        rc =  LPORT_ERR_IO;
        goto done;
    }

    rc = ag_drv_lport_mdio_control_get(control);
    if (rc || control->fail || control->start_busy)
    {
        pr_err("%s(%d):LPORT MDIO interface is not ready rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control->fail, control->start_busy);
        rc =  LPORT_ERR_IO;
    }

done:
    return rc;
}
#else
static uint32_t mdio_set_and_wait(lport_mdio_control *control)
{
    int rc = LPORT_ERR_OK;
    uint32_t retries = LPORT_ACCESS_MDIO_TRANSACTION_RETRY;

    rc = ag_drv_lport_mdio_control_set(control);
    if (rc)
    {
        pr_err("%s(%d):LPORT MDIO interface is not ready, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, control->fail, control->start_busy);
        return LPORT_ERR_IO;

    }

    /* Poll for transaction end & not error */
    do
    {
        UDELAY(10);
        rc = ag_drv_lport_mdio_control_get(control);
    }while ((!rc) && retries-- && control->start_busy && (!control->fail));

    if (!retries)
    {
        pr_err(
            "%s(%d):LPORT MDIO write transaction passed too many retries rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control->fail, control->start_busy);
        return LPORT_ERR_IO;
    }
    else if (control->fail || control->start_busy || rc)
    {
        pr_err(
            "%s(%d):LPORT MDIO write transaction failed or busy rc=%d,fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control->fail, control->start_busy);
        return LPORT_ERR_IO;
    }
    return rc;
}
#endif

int lport_mdio_bus_init(void)
{
    int rc = LPORT_ERR_OK;
    uint8_t free_run_clk_enable;
    uint8_t supress_preamble;
    uint8_t mdio_clk_divider;
    uint8_t mdio_clause;

#if LPORT_MDIO_TRANS_LOCKED
    mutex_init(&mdio_mtx);
#endif
#if LPORT_MDIO_TRANS_INT
    init_completion(&mdio_done);
    lport_mdio_intr_register(LPORT_MDIO_DONE,mdio_trans_done_isr, &mdio_done);
    mdio_timeout = msecs_to_jiffies(LPORT_ACCESS_MDIO_TRANSACTION_TIMEOUT_MS);
    pr_debug ("LPORT MDIO on Interrupt mode\n");
#endif

    rc = ag_drv_lport_mdio_cfg_get(&free_run_clk_enable,&supress_preamble,&mdio_clk_divider,&mdio_clause);
    /*
     * Reference clock (typically 250 MHz) is divided by 2x(mdio_clk_divider+1) to generate MDIO clock(MDC),
     * For example: 0 = 125MHz, 9 = 12.5MHz,  12 = 9.6MHz, 63 = 1.95MHz, 127 = 0.98MHz, 255 = 0.49MHz
     */
    mdio_clk_divider = 12;
    free_run_clk_enable = 1;
    rc = rc ? rc: ag_drv_lport_mdio_cfg_set(free_run_clk_enable,supress_preamble,mdio_clk_divider,mdio_clause);

    return rc;
}

int lport_mdio22_wr(uint16_t phyid,uint16_t addr, uint16_t data)
{
    uint8_t free_run_clk_enable;
    uint8_t supress_preamble;
    uint8_t mdio_clk_divider;
    uint8_t mdio_clause;
    lport_mdio_control control;
    int rc = LPORT_ERR_OK;

    MDIO_CHECK_CNTX_LOCK;

    rc = ag_drv_lport_mdio_control_get(&control);
    if (rc || control.start_busy)
    {
        pr_err("%s(%d):LPORT MDIO interface is not ready rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__,__LINE__, rc, control.fail, control.start_busy);
        rc =  LPORT_ERR_IO;
        goto done;
    }
    rc = ag_drv_lport_mdio_cfg_get(&free_run_clk_enable,&supress_preamble,&mdio_clk_divider,&mdio_clause);

    mdio_clause = MDIO_CL22;

    rc = rc ? rc: ag_drv_lport_mdio_cfg_set(free_run_clk_enable,supress_preamble,mdio_clk_divider,mdio_clause);

    control.phy_prt_addr = phyid;
    control.reg_dev_addr = addr;
    control.data_addr = data;
    control.start_busy = 1;
    control.op_code =MDIO_WRITE;
    control.fail = 0;

    if ( mdio_set_and_wait(&control) )
    {
        pr_err("%s(%d):LPORT MDIO transaction failed rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__,__LINE__, rc, control.fail, control.start_busy);
        rc =  LPORT_ERR_IO;
        goto done;
    }

done:
    MDIO_CNTX_UNLOCK;
    return rc;
}
EXPORT_SYMBOL(lport_mdio22_wr);

int lport_mdio22_rd(uint16_t phyid,uint16_t addr, uint16_t *data)
{
    uint8_t free_run_clk_enable;
    uint8_t supress_preamble;
    uint8_t mdio_clk_divider;
    uint8_t mdio_clause;
    lport_mdio_control control;
    int rc = LPORT_ERR_OK;

    MDIO_CHECK_CNTX_LOCK;
    rc = ag_drv_lport_mdio_control_get(&control);
    if(rc /* || control.fail */ || control.start_busy)
    {
        pr_err("%s(%d):LPORT MDIO interface is not ready rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__,__LINE__, rc, control.fail, control.start_busy);
        rc =  LPORT_ERR_IO;
        goto done;
    }
    rc = ag_drv_lport_mdio_cfg_get(&free_run_clk_enable,&supress_preamble,&mdio_clk_divider,&mdio_clause);

    mdio_clause = MDIO_CL22;

    rc = rc ? rc: ag_drv_lport_mdio_cfg_set(free_run_clk_enable,supress_preamble,mdio_clk_divider,mdio_clause);

    control.phy_prt_addr = phyid;
    control.reg_dev_addr = addr;
    control.start_busy = 1;
    control.op_code =MDIO_CL22_RD;
    control.fail = 0;

    if ( mdio_set_and_wait(&control) )
    {
        pr_err("%s(%d):LPORT MDIO transaction failed rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__,__LINE__, rc, control.fail, control.start_busy);
        rc =  LPORT_ERR_IO;
        goto done;
    }

    //read the result,mdio_set_and_wait also fetch the result
    *data = control.data_addr;

done:
    MDIO_CNTX_UNLOCK;
    return rc;
}
EXPORT_SYMBOL(lport_mdio22_rd);

int lport_mdio45_rd(uint16_t phyid, uint16_t devid, uint16_t addr, uint16_t *data)
{
    uint8_t free_run_clk_enable;
    uint8_t supress_preamble;
    uint8_t mdio_clk_divider;
    uint8_t mdio_clause;
    lport_mdio_control control;
    int rc = LPORT_ERR_OK;

    MDIO_CHECK_CNTX_LOCK;
    rc = ag_drv_lport_mdio_control_get(&control);
    if (rc || control.start_busy)
    {
        pr_err(
            "%s(%d):LPORT MDIO interface is not ready rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control.fail, control.start_busy);
        rc = LPORT_ERR_IO;
        goto done;
    }
    rc = ag_drv_lport_mdio_cfg_get(&free_run_clk_enable,&supress_preamble, &mdio_clk_divider,
        &mdio_clause);

    mdio_clause = MDIO_CL45;

    rc = rc ?
        rc :
        ag_drv_lport_mdio_cfg_set(free_run_clk_enable,supress_preamble, mdio_clk_divider,
            mdio_clause);

    //write the CL45 address
    control.phy_prt_addr = phyid;
    control.reg_dev_addr = devid;
    control.data_addr = addr;
    control.start_busy = 1;
    control.op_code = MDIO_CL45_ADDRESS;
    control.fail = 0;

    if (mdio_set_and_wait(&control))
    {
        pr_err(
            "%s(%d):LPORT MDIO transaction failed rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control.fail, control.start_busy);
        rc = LPORT_ERR_IO;
        goto done;
    }

    //write the read request
    control.start_busy = 1;
    control.op_code = MDIO_CL45_RD;

    if (mdio_set_and_wait(&control))
    {
        pr_err(
            "%s(%d):LPORT MDIO transaction failed rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control.fail, control.start_busy);
        rc = LPORT_ERR_IO;
        goto done;
    }

    //read the result,mdio_set_and_wait also fetch the result
    *data = control.data_addr;
done:
    MDIO_CNTX_UNLOCK;
    return rc;
}
EXPORT_SYMBOL(lport_mdio45_rd);

int lport_mdio45_wr(uint16_t phyid, uint16_t devid, uint16_t addr,
    uint16_t data)
{
    uint8_t free_run_clk_enable;
    uint8_t supress_preamble;
    uint8_t mdio_clk_divider;
    uint8_t mdio_clause;
    lport_mdio_control control;
    int rc = LPORT_ERR_OK;

    MDIO_CHECK_CNTX_LOCK;
    rc = ag_drv_lport_mdio_control_get(&control);
    if (rc || control.start_busy)
    {
        pr_err( "%s(%d):LPORT MDIO interface is not ready rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control.fail, control.start_busy);
        rc = LPORT_ERR_IO;
        goto done;
    }
    rc = ag_drv_lport_mdio_cfg_get(&free_run_clk_enable,&supress_preamble, &mdio_clk_divider,
        &mdio_clause);

    mdio_clause = MDIO_CL45;

    rc = rc ?
        rc :
        ag_drv_lport_mdio_cfg_set(free_run_clk_enable,supress_preamble, mdio_clk_divider,
            mdio_clause);

    //write the CL45 address
    control.phy_prt_addr = phyid;
    control.reg_dev_addr = devid;
    control.data_addr = addr;
    control.start_busy = 1;
    control.op_code = MDIO_CL45_ADDRESS;
    control.fail = 0;

    if (mdio_set_and_wait(&control))
    {
        pr_err(
            "%s(%d):LPORT MDIO transaction failed rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control.fail, control.start_busy);
        rc = LPORT_ERR_IO;
        goto done;
    }

    //write the read request
    control.start_busy = 1;
    control.op_code = MDIO_WRITE;
    control.data_addr = data;

    if (mdio_set_and_wait(&control))
    {
        pr_err(
            "%s(%d):LPORT MDIO transaction failed rc=%d, fail=%d, busy=%d\n",
            __FUNCTION__, __LINE__, rc, control.fail, control.start_busy);
        rc = LPORT_ERR_IO;
        goto done;
    }

done:
    MDIO_CNTX_UNLOCK;
    return rc;
}
EXPORT_SYMBOL(lport_mdio45_wr);
