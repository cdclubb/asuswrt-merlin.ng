/*
    Copyright (c) 2017 Broadcom
    All Rights Reserved

    <:label-BRCM:2017:DUAL/GPL:standard
    
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

#include <wl_thread.h>

#if defined(WL_ALL_PASSIVE) && (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 4, 0))
#include <linux/kthread.h>

#include <wl_dbg.h>
#include <wlc_cfg.h>
#include <wlc_channel.h>
#include <wlc_pub.h>
#include <wl_linux.h>
#include <wl_pktc.h>
#if defined(BCM_AWL)
#include <wl_awl.h>
#endif /* BCM_AWL */

extern void wl_dpc_rxwork(struct wl_task *task);
extern void wl_start_txqwork(wl_task_t *task);
#if !defined(BCM_PKTFWD)
extern void BCMFASTPATH wl_start_txchain_txqwork(pktc_info_t *pktci);
#endif



static int
wl_worker_thread_func(void *data)
{
	struct wl_info *wl = (struct wl_info *) data;

	while (1)
	{
		wait_event_interruptible(wl->kthread_wqh,
		                            (wl->txq_dispatched ||
		                             wl->rxq_dispatched ||
#if defined(PKTC_TBL)
		                             wl->txq_txchain_dispatched ||
#endif
#if defined(BCM_AWL) && defined(WL_AWL_RX)
		                             wl->awl_sp_rxq_dispatched ||
#endif /* BCM_AWL && WL_AWL_RX */
		                             kthread_should_stop()));
		if (kthread_should_stop())
		{
			printk(KERN_INFO "kthread_should_stop detected on wl%d\n", wl->unit);
			break;
		}
		if (wl->rxq_dispatched)
			wl_dpc_rxwork(&wl->wl_dpc_task);
		if (wl->txq_dispatched)
			wl_start_txqwork(&wl->txq_task);

#if defined(BCM_AWL) && defined(WL_AWL_RX)
		if (wl->awl_sp_rxq_dispatched)
			wl_awl_process_slowpath_rxpkts(wl);
#endif /* BCM_AWL && WL_AWL_RX */

#if defined(PKTC_TBL)
#if defined(BCM_PKTFWD)
        wl_pktfwd_dnstream(wl); /* independent of txq_txchain_dispatched */
#else  /* ! BCM_PKTFWD */
        {
	        struct wl_if * wlif;
		    wlif  = wl->if_list;
		    while (wlif != NULL) {
                if (wlif->pktci && wlif->pktci->_txq_txchain_dispatched) {
                    wl_start_txchain_txqwork(wlif->pktci);
    			}
    			wlif = wlif->next;
    		}
        }
#endif /* ! BCM_PKTFWD */
#endif /* PKTC_TBL */

		/*
		 * If this thread is running with Real Time priority, be nice
		 * to other threads by yielding the CPU after each batch of packets.
		 */
		if (current->policy == SCHED_FIFO || current->policy == SCHED_RR)
			yield();
	}

	return 0;
}

void wl_thread_schedule_work(struct wl_info *wl)
{
	wake_up_interruptible(&wl->kthread_wqh);
}

int wl_thread_attach(struct wl_info *wl)
{
	int ret = 0;
	char kthrd_namebuf[32] = {0};

	init_waitqueue_head(&wl->kthread_wqh);
	sprintf(kthrd_namebuf, "wl%d-kthrd", wl->unit);
	printk(KERN_INFO "wl%d: creating kthread %s\n", wl->unit, kthrd_namebuf);
	wl->kthread = kthread_create(wl_worker_thread_func, wl, kthrd_namebuf);
	if (IS_ERR(wl->kthread)) {
		WL_ERROR(("wl%d: failed to create kernel thread\n", wl->unit));
		ret = -1;
	}
	if (WL_CONFIG_SMP() && num_online_cpus() > 1) 
	{
		unsigned long flags;
		wl->processor_id = wl->unit%num_online_cpus(); 
		kthread_bind(wl->kthread, wl->processor_id);
		raw_spin_lock_irqsave(&(wl->kthread->pi_lock), flags);
		wl->kthread->flags &= (~PF_NO_SETAFFINITY);
		raw_spin_unlock_irqrestore(&(wl->kthread->pi_lock), flags);
	}
	else
		wl->processor_id = 0; /* wl0 -> cpu0 */

	wake_up_process(wl->kthread);
	return ret;
}

void wl_thread_detach(struct wl_info *wl)
{
	kthread_stop(wl->kthread);
	wl->kthread = NULL;
}



#endif /* WL_ALL_PASSIVE && LINUX >= 3.4 */
