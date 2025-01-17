/*
<:copyright-BRCM:2011:DUAL/GPL:standard

   Copyright (c) 2011 Broadcom 
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
#if (defined(CONFIG_BCM_BPM) || defined(CONFIG_BCM_BPM_MODULE))

//#include <linux/version.h>
//#include <linux/module.h>
//#include <linux/kernel.h>
#include <linux/types.h>
//#include <linux/interrupt.h>
//#include <linux/ioport.h>
//#include <linux/slab.h>
//#include <linux/init.h>
//#include <linux/delay.h>
//#include <linux/netdevice.h>
//#include <linux/etherdevice.h>
//#include <linux/skbuff.h>
//#include <linux/rtnetlink.h>
//#include <linux/ethtool.h>
//#include <linux/if_arp.h>
//#include <linux/ppp_channel.h>
//#include <linux/ppp_defs.h>
//#include <linux/if_ppp.h>
//#include <linux/atm.h>
//#include <linux/atmdev.h>
//#include <linux/atmppp.h>
//#include <linux/blog.h>
//#include <linux/proc_fs.h>
#include <linux/string.h>
//#include <linux/etherdevice.h>
//#include <linux/ip.h>
#include <bcmtypes.h>
//#include <bcm_map_part.h>
//#include <bcm_intr.h>
//#include <board.h>
//#include "bcmnet.h"
//#include "bcmxtmcfg.h"
//#include "bcmxtmrt.h"
//#include <asm/io.h>
//#include <asm/uaccess.h>
//#include <linux/nbuff.h>
//#include "bcmxtmrtimpl.h"
#include "bcmPktDma.h"
#include "xtmrt_dma.h"
#include "xtmrt_bpm.h"

/**** Externs ****/

extern BcmPktDma_Bds *bcmPktDma_Bds_p;


/**** Globals ****/

/* Sanity checks */

/* Storage passed to gbpm_alloc_mult_buf() for returning "void pointers" */
void * xtm_alloc_buf_addr[BPM_XTM_BULK_ALLOC_COUNT];


/**** Prototypes ****/


/**** Statics ****/



/* dump the BPM status, stats */
void xtm_bpm_status(void)
{
    int chnl;

    for(chnl=0; chnl < XTM_RX_CHANNELS_MAX; chnl++)
    {
        PBCMXTMRT_GLOBAL_INFO pGi = &g_GlobalInfo;
        BcmPktDma_XtmRxDma *pktDmaRxInfo_p = &pGi->rxdma[chnl]->pktDmaRxInfo;


        printk("[HOST] XTM  %4d %10u %10u %5u %4u %4u",
               chnl, (unsigned int) pktDmaRxInfo_p->alloc,
               (unsigned int) pktDmaRxInfo_p->free,
               (unsigned int) pktDmaRxInfo_p->rxAssignedBds,
               (unsigned int) pktDmaRxInfo_p->allocTrig,
               (unsigned int) pktDmaRxInfo_p->bulkAlloc
               );
    }
}

/* Allocate the buffer ring for an XTM RX channel */
int xtm_bpm_alloc_buf_ring(BcmXtm_RxDma *rxdma, UINT32 num)
{
    UINT8 *pData;
    FkBuff_t *pFkBuf;
    UINT32 context = 0;
    UINT32 buf_ix;

    RECYCLE_CONTEXT(context)->channel = rxdma->pktDmaRxInfo.channel;

    for (buf_ix=0; buf_ix < num; buf_ix++)
    {
        /* gbpm_alloc_buf() returns a pointer to a data buf. 
         * [FkBuff_t][BCM_PKT_HEADROOM][data buffer][Tail room][skb_shared_info]
         *                             ^
         *                             gbpm_alloc_buf()
         * BPM data buffers alignment is defined by sizeof(FkBuff_t)
         * BPM data buffers are not in cache. No need for cache-ops.
         */

        /* Align data buffers on 16-byte boundary - Apr 2010 */
        if( (pData = (UINT8 *) gbpm_alloc_buf()) == NULL )
        {
            BCM_XTM_ERROR(" Low memory.");
            return GBPM_ERROR;
        }

        /* Locate the FkBuff_t structure preceeding the BPM data buf */
        pFkBuf = PDATA_TO_PFKBUFF(pData, BCM_PKT_HEADROOM);

        /* Pre-initialize the FkBuff_t object at pFkBuf */
        fkb_preinit((UINT8 *)pFkBuf, (RecycleFuncP)bcmxtmrt_recycle, context);

        /* BPM allocated buffers do not need cache invalidate, redundant */
        cache_flush_region(pData, (UINT8 *)pFkBuf + BCM_PKTBUF_SIZE);
        bcmPktDma_XtmFreeRecvBuf(&rxdma->pktDmaRxInfo, (unsigned char *)pData);
    }

    return GBPM_SUCCESS;
}


/* Free the buffer ring for an XTM RX channel */
void xtm_bpm_free_buf_ring( BcmXtm_RxDma *rxdma )
{
    unsigned long rxAddr = 0; 

    while (bcmPktDma_XtmRecvBufGet(&rxdma->pktDmaRxInfo, (uint32 *)&rxAddr) == TRUE)
   {
        if ((UINT8 *) rxAddr != NULL)
            xtm_bpm_free_buf(rxdma, (UINT8 *) rxAddr);
    }
}


/*
 *-----------------------------------------------------------------------------
 * function   : xtm_bpm_txq_thresh
 * description: configures the queue thresholds
 *-----------------------------------------------------------------------------
 */
int xtm_bpm_txq_thresh( PBCMXTMRT_DEV_CONTEXT pDevCtx,
                        PXTMRT_TRANSMIT_QUEUE_ID pTxQId)
{
    UINT32 qid = pTxQId->ulQueueIndex;
    UINT32 usSpeed;
    int nr_tx_bds;

#if 0
    /* For bonding traffic types, assume twice the link speed - sub optimal *
     * For Non-bonding, take the current speed into account. */
    if ((pDevCtx->Addr.ulTrafficType == TRAFFIC_TYPE_PTM_BONDED) ||
        (pDevCtx->Addr.ulTrafficType == TRAFFIC_TYPE_ATM_BONDED))
       usSpeed = ((pDevCtx->MibInfo.ulIfSpeed*2) >> 20) + 1;   /* US in Mbps */
    else
#endif
       usSpeed = (pDevCtx->MibInfo.ulIfSpeed >> 20) + 1;   /* US in Mbps */

    pTxQId->ulLoThresh = XTM_BPM_TXQ_LO_THRESH(usSpeed);
    pTxQId->ulHiThresh = XTM_BPM_TXQ_HI_THRESH(usSpeed);

    pTxQId->ulDropped = 0;

    BCM_XTM_DEBUG("XTM Tx qId[%d] ulIfSpeed=%d, usSpeed=%d",
        qid, (int) pDevCtx->MibInfo.ulIfSpeed, (int) usSpeed);

    BCM_XTM_DEBUG("XTM Tx qId[%d] ulLoThresh=%d, ulHiThresh=%d",
        qid, (int) pTxQId->ulLoThresh, (int) pTxQId->ulHiThresh);


    nr_tx_bds = bcmPktDma_Bds_p->host.xtm_txbds[qid];

    pTxQId->usQueueSize = nr_tx_bds;

    return GBPM_SUCCESS;
}


/* dumps the BPM TxQ thresholds */
void xtm_bpm_dump_txq_thresh(void)
{
    PBCMXTMRT_GLOBAL_INFO pGi = &g_GlobalInfo;
    PBCMXTMRT_DEV_CONTEXT pDevCtx;
    BcmPktDma_XtmTxDma   *txdma;
    UINT32 i, j;

    for( i = 0; i < MAX_DEV_CTXS; i++ )
    {
        pDevCtx = pGi->pDevCtxs[i];
        if ( pDevCtx != (PBCMXTMRT_DEV_CONTEXT) NULL )
        {
            if ( pDevCtx->ulLinkState == LINK_UP )
            {
                for (j = 0; j < pDevCtx->ulTxQInfosSize; j++)
                {
                    txdma = pDevCtx->txdma[j];

                    if (txdma->txEnabled == 1)
                    {
                        printk( "[HOST] XTM  %4d %5d %5d %10u",
                               (int) j, (int) txdma->ulLoThresh,
                               (int) txdma->ulHiThresh,
                               (unsigned int) txdma->ulDropped
                               );
                    }
                    printk( "\n" );
                }
            }
        }
    }
}
#endif


