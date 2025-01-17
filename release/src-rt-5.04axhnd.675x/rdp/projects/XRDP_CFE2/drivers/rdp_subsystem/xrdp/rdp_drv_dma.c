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
#include "rdp_subsystem_common.h"
#include "rdp_common.h"
#include "rdp_drv_dma.h"

#ifdef USE_BDMF_SHELL


static int drv_dma_cli_debug_info_get(bdmf_session_handle session, const bdmfmon_cmd_parm_t parm[], uint16_t n_parms)
{
    dma_id_e dma_id = parm[0].value.unumber;
    bdmf_error_t rc = BDMF_ERR_OK;
    dma_debug_info debug_info = {};
    uint8_t emac_index, i, value;
    uint32_t value_32;
    
    rc = ag_drv_dma_debug_info_get(dma_id, &debug_info);
    if (!rc)
    {
        bdmf_session_print(session, "%s debug info:\n\r", dma_id_enum_table[dma_id].name);
        bdmf_session_print(session, "====================\n\r");
        bdmf_session_print(session, "indirect read request valid bit: %d\n\r", debug_info.valid);
        bdmf_session_print(session, "read data valid bit:             %d\n\r", debug_info.ready);
        bdmf_session_print(session, "Selected source:                 %d\n\r", debug_info.sel_src);
        bdmf_session_print(session, "indirect read access address:    0x%x\n\r", debug_info.address);
        bdmf_session_print(session, "indirect read access data cs:    0x%x\n\r", debug_info.datacs);
        bdmf_session_print(session, "indirect read access chunk descriptors cs: 0x%x\n\r", debug_info.cdcs);
        bdmf_session_print(session, "indirect read access read requests cs: 0x%x\n\r", debug_info.rrcs);
    }

    for (emac_index = rdpa_emac0; emac_index < rdpa_emac__num_of; emac_index++)
    {
        bdmf_session_print(session, "Emac index : %d\n\r", emac_index);
        rc = ag_drv_dma_debug_req_cnt_rx_get(dma_id, emac_index, &value);
        if (!rc)
        {
            bdmf_session_print(session, "request counter rx:  %d\n\r", value);
        }
        rc = ag_drv_dma_debug_req_cnt_rx_acc_get(dma_id, emac_index, &value_32);
        if (!rc)
        {
            bdmf_session_print(session, "acc request counter rx:  %d\n\r", value_32);
        }
        rc = ag_drv_dma_debug_req_cnt_tx_get(dma_id, emac_index, &value);
        if (!rc)
        {
            bdmf_session_print(session, "request counter tx:  %d\n\r", value);
        }
        rc = ag_drv_dma_debug_req_cnt_tx_acc_get(dma_id, emac_index, &value_32);
        if (!rc)
        {
            bdmf_session_print(session, "acc request counter tx:  %d\n\r", value_32);
        }
    }

    for (i = 0; i < 4; i++)
    {
        rc = ag_drv_dma_debug_rddata_get(dma_id, i, &value_32);
        if (!rc)
        {
            bdmf_session_print(session, "RAM data. word: %d ; data:  0x%x\n\r", i, value_32);
        }
    }
    return rc;
}

static bdmfmon_handle_t bbh_dir;

void drv_dma_cli_init(bdmfmon_handle_t driver_dir)
{
    bbh_dir = ag_drv_dma_cli_init(driver_dir);

    BDMFMON_MAKE_CMD(bbh_dir, "debug_info", "dma debug information", drv_dma_cli_debug_info_get,
        BDMFMON_MAKE_PARM_ENUM("dma_id", "dma_id", dma_id_enum_table, 0));
}

void drv_dma_cli_exit(bdmfmon_handle_t driver_dir)
{
    if (bbh_dir)
    {
        bdmfmon_token_destroy(bbh_dir);
        bbh_dir = NULL;
    }
}
/******************************************************************************/
/*                                                                            */
/* Driver shell functions                                                     */
/*                                                                            */
/******************************************************************************/
/* 
    (DMA0, DMA1, SDMA0, SDMA1) 
    drv_dma_cli_debug_info_get 
    ag:
     ag_drv_dma_config_num_of_writes_get
     ag_drv_dma_config_num_of_reads_get
     ag_drv_dma_config_periph_source_get
*/

#endif /* USE_BDMF_SHELL */

