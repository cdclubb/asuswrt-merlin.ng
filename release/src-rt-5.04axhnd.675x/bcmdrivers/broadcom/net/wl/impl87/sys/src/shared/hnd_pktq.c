/*
 * HND generic pktq operation primitives
 *
 * Copyright (C) 2021, Broadcom. All Rights Reserved.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *
 * <<Broadcom-WL-IPTag/Open:>>
 *
 * $Id: hnd_pktq.c 805645 2021-12-03 03:05:42Z $
 */

#include <typedefs.h>
#include <osl.h>
#include <osl_ext.h>
#include <bcmutils.h>
#include <hnd_pktq.h>
#ifdef HNDPQP
#include <hnd_pqp.h>
#endif /* HNDPQP */

/*
 * osl multiple-precedence packet queue
 * hi_prec is always >= the number of the highest non-empty precedence
 */

/** @param pq   Multi-priority packet queue */
void * BCMFASTPATH
pktq_penq(struct pktq *pq, int prec, void *p)
{
	struct pktq_prec *q;			/**< single precedence packet queue */

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	ASSERT(prec >= 0 && prec < pq->num_prec);
	ASSERT(PKTLINK(p) == NULL);		/* queueing chains not allowed */

	ASSERT(!pktq_full(pq));
	ASSERT(!pktqprec_full(pq, prec));

	q = &pq->q[prec];

	if (q->head)
		PKTSETLINK(q->tail, p);
	else
		q->head = p;

	q->tail = p;
	q->n_pkts++;

	pq->n_pkts_tot++;

	if (pq->hi_prec < prec)
		pq->hi_prec = (uint8)prec;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** osl simple, non-priority packet queue */
void * BCMFASTPATH
spktq_enq(struct spktq *spq, void *p)
{
	struct pktq_prec *q;			/**< single precedence packet queue */

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	ASSERT(!spktq_full(spq));

	PKTSETLINK(p, NULL);

	q = &spq->q;

	if (q->head)
		PKTSETLINK(q->tail, p);
	else
		q->head = p;

	q->tail = p;
	q->n_pkts++;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
void * BCMFASTPATH
pktq_penq_head(struct pktq *pq, int prec, void *p)
{
	struct pktq_prec *q;			/**< single precedence packet queue */

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	ASSERT(prec >= 0 && prec < pq->num_prec);
	ASSERT(PKTLINK(p) == NULL);		/* queueing chains not allowed */

	ASSERT(!pktq_full(pq));
	ASSERT(!pktqprec_full(pq, prec));

	q = &pq->q[prec];

	if (q->head == NULL)
		q->tail = p;

	PKTSETLINK(p, q->head);
	q->head = p;
	q->n_pkts++;

	pq->n_pkts_tot++;

	if (pq->hi_prec < prec)
		pq->hi_prec = (uint8)prec;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param spktq : single priority packet queue */
void * BCMFASTPATH
spktq_enq_head(struct spktq *spq, void *p)
{
	struct pktq_prec *q;			/**< single precedence packet queue */

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	ASSERT(!spktq_full(spq));

	PKTSETLINK(p, NULL);

	q = &spq->q;

	if (q->head == NULL)
		q->tail = p;

	PKTSETLINK(p, q->head);
	q->head = p;
	q->n_pkts++;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
void * BCMFASTPATH
pktq_pdeq(struct pktq *pq, int prec)
{
	struct pktq_prec *q;			/**< single precedence packet queue */
	void *p;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	ASSERT(prec >= 0 && prec < pq->num_prec);

	q = &pq->q[prec];

	if ((p = q->head) == NULL)
		goto done;

	if ((q->head = PKTLINK(p)) == NULL)
		q->tail = NULL;

	q->n_pkts--;

	pq->n_pkts_tot--;

	PKTSETLINK(p, NULL);

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param spktq : single priority packet queue */
void * BCMFASTPATH
spktq_deq(struct spktq *spq)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	void *p;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	q = &spq->q;

	if ((p = q->head) == NULL)
		goto done;

	if ((q->head = PKTLINK(p)) == NULL)
		q->tail = NULL;

	q->n_pkts--;

	PKTSETLINK(p, NULL);

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
void * BCMFASTPATH
pktq_pdeq_tail(struct pktq *pq, int prec)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	void *p, *prev;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	ASSERT(prec >= 0 && prec < pq->num_prec);

	q = &pq->q[prec];

	if ((p = q->head) == NULL)
		goto done;

	for (prev = NULL; p != q->tail; p = PKTLINK(p))
		prev = p;

	if (prev)
		PKTSETLINK(prev, NULL);
	else
		q->head = NULL;

	q->tail = prev;
	q->n_pkts--;

	pq->n_pkts_tot--;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param spktq : single priority packet queue */
void * BCMFASTPATH
spktq_deq_tail(struct spktq *spq)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	void *p, *prev;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	q = &spq->q;

	if ((p = q->head) == NULL)
		goto done;

	for (prev = NULL; p != q->tail; p = PKTLINK(p))
		prev = p;

	if (prev)
		PKTSETLINK(prev, NULL);
	else
		q->head = NULL;

	q->tail = prev;
	q->n_pkts--;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
void *
pktq_peek_tail(struct pktq *pq, int *prec_out)
{
	int prec;
	void *p = NULL;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	if (pq->n_pkts_tot == 0)
		goto done;

	for (prec = 0; prec < pq->hi_prec; prec++)
		if (pq->q[prec].head)
			break;

	if (prec_out)
		*prec_out = prec;

	p = pq->q[prec].tail;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/**
 * Append spktq 'list' to the tail of pktq 'pq'
 *
 * @param pq    Multi-priority packet queue
 * @param list  Single priority packet queue
 */
void BCMFASTPATH
pktq_append(struct pktq *pq, int prec, struct spktq *list)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	struct pktq_prec *list_q;			/**< single precedence packet queue */

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return;

	list_q = &list->q;

	/* empty list check */
	if (list_q->head == NULL)
		goto done;

	ASSERT(prec >= 0 && prec < pq->num_prec);
	ASSERT(PKTLINK(list_q->tail) == NULL);         /* terminated list */

	ASSERT(!pktq_full(pq));
	ASSERT(!pktqprec_full(pq, prec));

	q = &pq->q[prec];

	if (q->head)
		PKTSETLINK(q->tail, list_q->head);
	else
		q->head = list_q->head;

	q->tail = list_q->tail;
	q->n_pkts += list_q->n_pkts;
	pq->n_pkts_tot += list_q->n_pkts;

	if (pq->hi_prec < prec)
		pq->hi_prec = (uint8)prec;

	list_q->head = NULL;
	list_q->tail = NULL;
	list_q->n_pkts = 0;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return;
}

/*
 * Append spktq 'list' to the tail of spktq 'spq'
 * @param spq : single priority packet queue
 */
void BCMFASTPATH
spktq_enq_list(struct spktq *spq, struct spktq *list)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	struct pktq_prec *list_q;			/**< single precedence packet queue */

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return;

	list_q = &list->q;

	/* empty list check */
	if (list_q->head == NULL)
		goto done;

	ASSERT(PKTLINK(list_q->tail) == NULL);         /* terminated list */

	ASSERT(!spktq_full(spq));

	q = &spq->q;

	if (q->head)
		PKTSETLINK(q->tail, list_q->head);
	else
		q->head = list_q->head;

	q->tail = list_q->tail;
	q->n_pkts += list_q->n_pkts;

	list_q->head = NULL;
	list_q->tail = NULL;
	list_q->n_pkts = 0;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return;
}

/**
 * Prepend spktq 'list' to the head of pktq 'pq'
 * @param pq     Multi-priority packet queue
 * @param list   Single priority packet queue
 */
void BCMFASTPATH
pktq_prepend(struct pktq *pq, int prec, struct spktq *list)
{
	struct pktq_prec *q;			/**< single precedence packet queue */
	struct pktq_prec *list_q;		/**< single precedence packet queue */

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return;

	list_q = &list->q;

	/* empty list check */
	if (list_q->head == NULL)
		goto done;

	ASSERT(prec >= 0 && prec < pq->num_prec);
	ASSERT(PKTLINK(list_q->tail) == NULL);         /* terminated list */

	ASSERT(!pktq_full(pq));
	ASSERT(!pktqprec_full(pq, prec));

	q = &pq->q[prec];

	/* set the tail packet of list to point at the former pq head */
	PKTSETLINK(list_q->tail, q->head);
	/* the new q head is the head of list */
	q->head = list_q->head;

	/* If the q tail was non-null, then it stays as is.
	 * If the q tail was null, it is now the tail of list
	 */
	if (q->tail == NULL) {
		q->tail = list_q->tail;
	}

	q->n_pkts += list_q->n_pkts;
	pq->n_pkts_tot += list_q->n_pkts;

	if (pq->hi_prec < prec)
		pq->hi_prec = (uint8)prec;

	list_q->head = NULL;
	list_q->tail = NULL;
	list_q->n_pkts = 0;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return;
}

/*
 * Prepend spktq 'list' to the head of spktq 'spq'
 * @param spq   Single priority packet queue
 * @param list  Single priority packet queue
 */
void BCMFASTPATH
spktq_enq_head_list(struct spktq *spq, struct spktq *list)
{
	struct pktq_prec *q;			/**< single precedence packet queue */
	struct pktq_prec *list_q;		/**< single precedence packet queue */

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return;

	list_q = &list->q;

	/* empty list check */
	if (list_q->head == NULL)
		goto done;

	ASSERT(PKTLINK(list_q->tail) == NULL);         /* terminated list */

	ASSERT(!spktq_full(spq));

	q = &spq->q;

	/* set the tail packet of list to point at the former pq head */
	PKTSETLINK(list_q->tail, q->head);
	/* the new q head is the head of list */
	q->head = list_q->head;

	/* If the q tail was non-null, then it stays as is.
	 * If the q tail was null, it is now the tail of list
	 */
	if (q->tail == NULL) {
		q->tail = list_q->tail;
	}

	q->n_pkts += list_q->n_pkts;

	list_q->head = NULL;
	list_q->tail = NULL;
	list_q->n_pkts = 0;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return;
}

/** @param pq   Multi-priority packet queue */
void * BCMFASTPATH
pktq_pdeq_prev(struct pktq *pq, int prec, void *prev_p)
{
	struct pktq_prec *q;			/**< single precedence packet queue */
	void *p = NULL;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	ASSERT(prec >= 0 && prec < pq->num_prec);

	q = &pq->q[prec];

	if (prev_p == NULL)
		goto done;

	if ((p = PKTLINK(prev_p)) == NULL)
		goto done;

	q->n_pkts--;

	pq->n_pkts_tot--;

	PKTSETLINK(prev_p, PKTLINK(p));
	PKTSETLINK(p, NULL);

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
void * BCMFASTPATH
pktq_pdeq_with_fn(struct pktq *pq, int prec, ifpkt_cb_t fn, int arg)
{
	struct pktq_prec *q;			/**< single precedence packet queue */
	void *p, *prev = NULL;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	ASSERT(prec >= 0 && prec < pq->num_prec);

	q = &pq->q[prec];
	p = q->head;

	while (p) {
		if (fn == NULL || (*fn)(p, arg)) {
			break;
		} else {
			prev = p;
			p = PKTLINK(p);
		}
	}
	if (p == NULL)
		goto done;

	if (prev == NULL) {
		if ((q->head = PKTLINK(p)) == NULL) {
			q->tail = NULL;
		}
	} else {
		PKTSETLINK(prev, PKTLINK(p));
		if (q->tail == p) {
			q->tail = prev;
		}
	}

	q->n_pkts--;

	pq->n_pkts_tot--;

	PKTSETLINK(p, NULL);

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
bool BCMFASTPATH
pktq_pdel(struct pktq *pq, void *pktbuf, int prec)
{
	bool ret = FALSE;
	struct pktq_prec *q;			/**< single precedence packet queue */
	void *p = NULL;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return FALSE;

	ASSERT(prec >= 0 && prec < pq->num_prec);

	/* Should this just assert pktbuf? */
	if (!pktbuf)
		goto done;

	q = &pq->q[prec];

	if (q->head == pktbuf) {
		if ((q->head = PKTLINK(pktbuf)) == NULL)
			q->tail = NULL;
	} else {
		for (p = q->head; p && PKTLINK(p) != pktbuf; p = PKTLINK(p))
			;
		if (p == NULL)
			goto done;

		PKTSETLINK(p, PKTLINK(pktbuf));
		if (q->tail == pktbuf)
			q->tail = p;
	}

	q->n_pkts--;
	pq->n_pkts_tot--;

	PKTSETLINK(pktbuf, NULL);
	ret = TRUE;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return FALSE;

	return ret;
}

/** @param pq   Multi-priority packet queue */
bool
pktq_init(struct pktq *pq, int num_prec, int max_pkts)
{
	int prec;

	ASSERT(num_prec > 0 && num_prec <= PKTQ_MAX_PREC);

	/* pq is variable size; only zero out what's requested */
	bzero(pq, OFFSETOF(struct pktq, q) + (sizeof(struct pktq_prec) * num_prec));

	if (HND_PKTQ_MUTEX_CREATE("pktq", &pq->mutex) != OSL_EXT_SUCCESS)
		return FALSE;

	pq->num_prec = (uint16)num_prec;

	pq->max_pkts = (uint16)max_pkts;

	for (prec = 0; prec < num_prec; prec++)
		pq->q[prec].max_pkts = pq->max_pkts;

	return TRUE;
}

/** @param spq : single priority packet queue */
bool
spktq_init(struct spktq *spq, int max_pkts)
{
	bzero(spq, sizeof(struct spktq));

	if (HND_PKTQ_MUTEX_CREATE("spktq", &spq->mutex) != OSL_EXT_SUCCESS)
		return FALSE;

	spq->q.max_pkts = (uint16)max_pkts;

	return TRUE;
}

/** @param spq : single priority packet queue */
bool
spktq_init_list(struct spktq *spq, uint max_pkts, void *head, void *tail, uint16 n_pkts)
{
	if (HND_PKTQ_MUTEX_CREATE("spktq", &spq->mutex) != OSL_EXT_SUCCESS)
		return FALSE;

	ASSERT(PKTLINK(tail) == NULL);
	PKTSETLINK(tail, NULL);
	spq->q.head = head;
	spq->q.tail = tail;
	spq->q.max_pkts = (uint16)max_pkts;
	spq->q.n_pkts = n_pkts;
	spq->q.stall_count = 0;
	spq->q.dequeue_count = 0;

	return TRUE;
}

#ifdef HND_PKTQ_THREAD_SAFE
/** @param pq   Multi-priority packet queue */
void
pktq_deinit(struct pktq *pq)
{
	BCM_REFERENCE(pq);
	HND_PKTQ_MUTEX_DELETE(&pq->mutex);
}

/** @param spq : single priority packet queue */
void
spktq_deinit(struct spktq *spq)
{
	BCM_REFERENCE(spq);
	HND_PKTQ_MUTEX_DELETE(&spq->mutex);
}
#endif /* HND_PKTQ_THREAD_SAFE */

/** @param pq   Multi-priority packet queue */
void
pktq_set_max_plen(struct pktq *pq, int prec, int max_pkts)
{
	ASSERT(prec >= 0 && prec < pq->num_prec);

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return;

	if (prec < pq->num_prec)
		pq->q[prec].max_pkts = (uint16)max_pkts;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return;
}

/** @param pq   Multi-priority packet queue */
void * BCMFASTPATH
pktq_deq(struct pktq *pq, int *prec_out)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	void *p = NULL;
	int prec;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	if (pq->n_pkts_tot == 0)
		goto done;

	while ((prec = pq->hi_prec) > 0 && pq->q[prec].head == NULL)
		pq->hi_prec--;

	q = &pq->q[prec];

	if ((p = q->head) == NULL)
		goto done;

	if ((q->head = PKTLINK(p)) == NULL)
		q->tail = NULL;

	q->n_pkts--;

	pq->n_pkts_tot--;

	if (prec_out)
		*prec_out = prec;

	PKTSETLINK(p, NULL);

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
void * BCMFASTPATH
pktq_deq_tail(struct pktq *pq, int *prec_out)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	void *p = NULL, *prev;
	int prec;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	if (pq->n_pkts_tot == 0)
		goto done;

	for (prec = 0; prec < pq->hi_prec; prec++)
		if (pq->q[prec].head)
			break;

	q = &pq->q[prec];

	if ((p = q->head) == NULL)
		goto done;

	for (prev = NULL; p != q->tail; p = PKTLINK(p))
		prev = p;

	if (prev)
		PKTSETLINK(prev, NULL);
	else
		q->head = NULL;

	q->tail = prev;
	q->n_pkts--;

	pq->n_pkts_tot--;

	if (prec_out)
		*prec_out = prec;

	PKTSETLINK(p, NULL);

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
void *
pktq_peek(struct pktq *pq, int *prec_out)
{
	int prec;
	void *p = NULL;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	if (pq->n_pkts_tot == 0)
		goto done;

	while ((prec = pq->hi_prec) > 0 && pq->q[prec].head == NULL)
		pq->hi_prec--;

	if (prec_out)
		*prec_out = prec;

	p = pq->q[prec].head;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param spq : single priority packet queue */
void *
spktq_peek(struct spktq *spq)
{
	void *p = NULL;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	if (spq->q.n_pkts == 0)
		goto done;

	p = spq->q.head;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/** @param pq   Multi-priority packet queue */
void
pktq_pflush(osl_t *osh, struct pktq *pq, int prec, bool dir)
{
	void *p;

	/* no need for a mutex protection! */

	/* start with the head of the list */
	while ((p = pktq_pdeq(pq, prec)) != NULL) {

		/* delete this packet */
		PKTFREE(osh, p, dir);
	}
}

/** @param spq : single priority packet queue */
void
spktq_flush(osl_t *osh, struct spktq *spq, bool dir)
{
	void *p;

	/* no need for a mutex protection! */

	/* start with the head of the list */
	while ((p = spktq_deq(spq)) != NULL) {

		/* delete this packet */
		PKTFREE(osh, p, dir);
	}
}

/** @param pq   Multi-priority packet queue */
void
pktq_flush(osl_t *osh, struct pktq *pq, bool dir)
{
	bool flush = FALSE;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return;

	/* Optimize flush, if pktq n_pkts_tot = 0, just return.
	 * pktq len of 0 means pktq's prec q's are all empty.
	 */
	if (pq->n_pkts_tot > 0) {
		flush = TRUE;
	}

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return;

	if (flush) {
		int prec;

		PKTQ_PREC_ITER(pq, prec) {
			pktq_pflush(osh, pq, prec, dir);
		}
	}
}

/*
 * For each pktq_prec in a pktq, promote packets to the head of the pktq_prec
 * using the promote_cb.
 * promote_cb, determines whether a packet needs to be promoted (return true).
 * The ordering of all false and true packets within the queue are retained.
 * promote_cb callback may not modify the PKTLINK of the packet passed to it.
 *
 * Caller could have suggested how many packets needed promotion across all
 * precedences. This could be used to quickly break out.
 */
bool
pktq_promote(struct pktq *pq, pktq_promote_cb_t promote_cb)
{
	void *pkt;
	int prec, n_pkts, n_pkts_tot;
	struct pktq_prec q_hi, q_lo, *pq_q;

	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return FALSE;

	n_pkts_tot = (int)pq->n_pkts_tot;
	if (n_pkts_tot == 0)
		return FALSE;

	PKTQ_PREC_ITER(pq, prec) {

		pq_q = &pq->q[prec]; /* precedence queue */
		n_pkts = pq_q->n_pkts;

		if (n_pkts <= 1) {
			if (n_pkts == 1) /* callback may perform a pkt operation */
				promote_cb(pq_q->head);
			continue; /* no promotion when precedence queue is empty or 1 */
		}

		q_hi.head = q_hi.tail = NULL;
		q_lo.head = q_lo.tail = NULL;

		pkt = pq_q->head;

		do {  /* enqueue to tail of hi or lo precedence queue, during walk */
			if (promote_cb(pkt)) { /* enqueue to tail of hi queue */
				if (q_hi.head)
					PKTSETLINK(q_hi.tail, pkt);
				else
					q_hi.head = pkt;
				q_hi.tail = pkt;
			} else {          /* enqueue to tail of lo queue */
				if (q_lo.head)
					PKTSETLINK(q_lo.tail, pkt);
				else
					q_lo.head = pkt;
				q_lo.tail = pkt;
			}
		} while ((pkt = PKTLINK(pkt)) != NULL); /* traverse precedence queue */

		if (q_hi.head == NULL)
			continue; /* lo queue is exactly as original precedence queue */

		/* Create precedence queue, by appending lo queue to tail of hi queue */
		pq_q->head = q_hi.head;
		if (q_lo.head == NULL) {
			pq_q->tail = q_hi.tail;
		} else {
			PKTSETLINK(q_hi.tail, q_lo.head);
			pq_q->tail = q_lo.tail;
		}

		PKTSETLINK(pq_q->tail, NULL);
	}

	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return FALSE;

	return TRUE;
}

/**
 * Return sum of lengths of a specific set of precedences
 *
 * @param pq   Multi-priority packet queue
 */
int
pktq_mlen(struct pktq *pq, uint prec_bmp)
{
	int prec, len;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return 0;

	len = 0;

	for (prec = 0; prec <= pq->hi_prec; prec++)
		if (prec_bmp & (1 << prec))
			len += pq->q[prec].n_pkts;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return 0;

	return len;
}

/**
 * Priority peek from a specific set of precedences
 *
 * @param pq   Multi-priority packet queue
 */
void * BCMFASTPATH
pktq_mpeek(struct pktq *pq, uint prec_bmp, int *prec_out)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	void *p = NULL;
	int prec;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	if (pq->n_pkts_tot == 0)
		goto done;

	while ((prec = pq->hi_prec) > 0 && pq->q[prec].head == NULL)
		pq->hi_prec--;

	while ((prec_bmp & (1 << prec)) == 0 || pq->q[prec].head == NULL)
		if (prec-- == 0)
			goto done;

	q = &pq->q[prec];

	if ((p = q->head) == NULL)
		goto done;

	if (prec_out)
		*prec_out = prec;

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

/**
 * Priority dequeue from a specific set of precedences
 *
 * @param pq   Multi-priority packet queue
 */
void * BCMFASTPATH
pktq_mdeq(struct pktq *pq, uint prec_bmp, int *prec_out)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	void *p = NULL;
	int prec;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return NULL;

	if (pq->n_pkts_tot == 0)
		goto done;

	while ((prec = pq->hi_prec) > 0 && pq->q[prec].head == NULL)
		pq->hi_prec--;

	while ((pq->q[prec].head == NULL) || ((prec_bmp & (1 << prec)) == 0))
		if (prec-- == 0)
			goto done;

	q = &pq->q[prec];

	if ((p = q->head) == NULL)
		goto done;

	if ((q->head = PKTLINK(p)) == NULL)
		q->tail = NULL;

	q->n_pkts--;

	if (prec_out)
		*prec_out = prec;

	pq->n_pkts_tot--;

	PKTSETLINK(p, NULL);

done:
	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return NULL;

	return p;
}

#ifdef HND_PKTQ_THREAD_SAFE
/** @param pq   Multi-priority packet queue */
int
pktqprec_avail_pkts(struct pktq *pq, int prec)
{
	int ret;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return 0;

	ASSERT(prec >= 0 && prec < pq->num_prec);

	ret = pq->q[prec].max_pkts - pq->q[prec].n_pkts;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return 0;

	return ret;
}

/** @param pq   Multi-priority packet queue */
bool
pktqprec_full(struct pktq *pq, int prec)
{
	bool ret;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return FALSE;

	ASSERT(prec >= 0 && prec < pq->num_prec);

	ret = pq->q[prec].n_pkts >= pq->q[prec].max_pkts;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return FALSE;

	return ret;
}

/** @param pq   Multi-priority packet queue */
int
pktq_avail(struct pktq *pq)
{
	int ret;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return 0;

	ret = pq->max_pkts - pq->n_pkts_tot;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return 0;

	return ret;
}

/** @param spq : single priority packet queue */
int
spktq_avail(struct spktq *spq)
{
	int ret;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return 0;

	ret = spq->q.max_pkts - spq->q.n_pkts;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return 0;

	return ret;
}

/** @param pq   Multi-priority packet queue */
bool
pktq_full(struct pktq *pq)
{
	bool ret;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&pq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return FALSE;

	ret = pq->n_pkts_tot >= pq->max_pkts;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&pq->mutex) != OSL_EXT_SUCCESS)
		return FALSE;

	return ret;
}

/** @param spq : single priority packet queue */
bool
spktq_full(struct spktq *spq)
{
	bool ret;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_ACQUIRE(&spq->mutex, OSL_EXT_TIME_FOREVER) != OSL_EXT_SUCCESS)
		return FALSE;

	ret = spq->q.n_pkts >= spq->q.max_pkts;

	/* protect shared resource */
	if (HND_PKTQ_MUTEX_RELEASE(&spq->mutex) != OSL_EXT_SUCCESS)
		return FALSE;

	return ret;
}

#endif	/* HND_PKTQ_THREAD_SAFE */

typedef struct {
	spktq_cb_t cb;
	void *arg;
} spktq_cbinfo_t;
static spktq_cbinfo_t spktq_cbinfo = {NULL, NULL};
static spktq_cbinfo_t *spktq_cbinfo_get(void);

static spktq_cbinfo_t*
BCMRAMFN(spktq_cbinfo_get)(void)
{
	return (&spktq_cbinfo);
}

void
BCMATTACHFN(spktq_free_register)(spktq_cb_t cb, void *arg)
{
	spktq_cbinfo_t *cbinfop = spktq_cbinfo_get();
	cbinfop->cb = cb;
	cbinfop->arg = arg;
}

void
spktq_cb(void *spq)
{
	spktq_cbinfo_t *cbinfop = spktq_cbinfo_get();
	if (cbinfop->cb) {
		cbinfop->cb(cbinfop->arg, spq);
	}
}
#ifdef HNDPQP
/* Total packets in the queue including host and dongle packets */
int BCMFASTPATH
pktq_pqp_pkt_cnt(struct pktq *pq, int prec)
{
	struct pktq_prec *q;

	ASSERT(pq);
	ASSERT(prec >= 0 && prec < pq->num_prec);

	q = &pq->q[prec];
	return pqp_pkt_cnt(q);
}
/* Host resident packet count */
int BCMFASTPATH
pktq_pqp_hbm_cnt(struct pktq *pq, int prec)
{
	struct pktq_prec *q;

	ASSERT(pq);
	ASSERT(prec >= 0 && prec < pq->num_prec);

	q = &pq->q[prec];
	return pqp_hbm_cnt(q);
}
/* Dongle resident packet count */
int BCMFASTPATH
pktq_pqp_dbm_cnt(struct pktq *pq, int prec)
{
	struct pktq_prec *q;

	ASSERT(pq);
	ASSERT(prec >= 0 && prec < pq->num_prec);

	q = &pq->q[prec];
	return pqp_dbm_cnt(q);
}

/**
 * Return sum of lengths of a specific set of precedences
 *
 * @param pq   Multi-priority packet queue
 */
int
pktq_pqp_mlen(struct pktq *pq, uint prec_bmp)
{
	int prec, len;

	len = 0;

	for (prec = 0; prec <= pq->hi_prec; prec++) {
		if (prec_bmp & (1 << prec)) {
			len += pqp_pkt_cnt(&pq->q[prec]);
		}
	}

	return len;
}
/* Returns if queue owned by PQP for a given prec */
bool BCMFASTPATH
pktq_pqp_owns(struct pktq *pq, int prec)
{
	struct pktq_prec *q;

	ASSERT(pq);
	ASSERT(prec >= 0 && prec < pq->num_prec);

	q = &pq->q[prec];
	return pqp_owns(q);
}
/* Check if any of the prec is owned by PQP */
bool BCMFASTPATH
pktq_mpqp_owns(struct pktq *pq, uint prec_bmp)
{
	int prec;

	ASSERT(pq);

	PKTQ_PREC_ITER(pq, prec) {
		if ((prec_bmp & (1 << prec)) == 0)
			continue;

		/* Check if owned by PQP */
		if (pktq_pqp_owns(pq, prec))
			return TRUE;
	}
	return FALSE;
}

/* #### PQP Page in utilities #### */

/**
 * Priority PQP Page IN from a specific set of precedences.
 *
 * Given a multi prio pktq and a prec bitmap, find the highest prec with
 * packets queued either in host or dongle.
 * For the highest prec with avaialble packet, if head packet is in dongle
 * return immediately without PGI.
 * If packets available but head packet not in dongle, initiate a PQP PGI for a single packet.
 */
bool BCMFASTPATH
pktq_mpqp_pgi(struct pktq *pq, uint prec_bmp)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	int prec;
	/* Dont update pq->hi_prec in this function; PQP module doesnt own this state.
	 * Spend extra cycles and always start from from pq->hi_prec.
	 */
	uint16 hi_prec;

	ASSERT(pq);

	hi_prec = pq->hi_prec;

	/* Check if PQP owns any of the prec queues */
	if (!pktq_mpqp_owns(pq, prec_bmp))
		goto done;

	/* Starting from hi_prec, find a prec with available packets */
	while (((prec = hi_prec) > 0) && (pktq_pqp_pkt_cnt(pq, prec) == 0))
		hi_prec--;

	/* Loop through the prec_bit map to find a prec with available packets */
	while ((pktq_pqp_pkt_cnt(pq, prec) == 0) || ((prec_bmp & (1 << prec)) == 0))
		if (prec-- == 0)
			goto done;

	/* Atleast 1 packet avaialble for the given prec */
	ASSERT(pktq_pqp_pkt_cnt(pq, prec));

	q = &pq->q[prec];

	/* Head packet in Dongle. Return without PGI */
	if ((q->head) != NULL)
		goto done;

	/* Packet in the host. Trigger a Page IN for one packet */
	pqp_pgi(q, 1, 1);

	/* PGI will be resumed through callbacks when resource is available. */
	if ((q->head) == NULL)
		return FALSE;
done:
	return TRUE;
}

/* PQP page in for a given prec */
void BCMFASTPATH
pktq_pqp_pgi(struct pktq *pq, int prec, int cont_pkts, int fill_pkts)
{
	int __cont_pkts, __fill_pkts, pqp_pkt_cnt;
	struct pktq_prec *q;				/**< single precedence packet queue */
	ASSERT(pq);

	q = &(pq->q[prec]);

	/* Check for PQP ownership */
	if (!pqp_owns(q))
		return;

	pqp_pkt_cnt = pktq_pqp_pkt_cnt(pq, prec);

	/* pq->hi_prec will be changed in pktq_mdeq().
	 * If last pqp_pgi() didn't page-in all pkts in pktq and
	 * there are still pkts in HBM.
	 * hi_prec should be re-assigned before pktq_mdeq().
	 */
	if ((pqp_pkt_cnt > 0) && (pq->hi_prec < prec))
		pq->hi_prec = (uint8)prec;

	/* Check if we need to drain the whole queue */
	__fill_pkts = (fill_pkts == PKTQ_PKTS_ALL) ? pqp_pkt_cnt : fill_pkts;

	__cont_pkts = (cont_pkts == PKTQ_PKTS_ALL) ? pqp_pkt_cnt : cont_pkts;

	ASSERT(__fill_pkts <= pqp_pkt_cnt);
	ASSERT(__cont_pkts <= pqp_pkt_cnt);

	/* Page in requested count */
	pqp_pgi(q, __cont_pkts, __fill_pkts);
}

/* SPKTQ PQP page in */
void
spktq_pqp_pgi(struct spktq* spq, int cont_pkts, int fill_pkts)
{
	int __cont_pkts, __fill_pkts, pkt_cnt;
	struct pktq_prec *q;				/**< single precedence packet queue */
	ASSERT(spq);

	q = &spq->q;

	/* Check for PQP ownership */
	if (!pqp_owns(q))
		return;

	pkt_cnt = pqp_pkt_cnt(q);

	/* Check if we need to drain the whole queue */
	__fill_pkts = (fill_pkts == PKTQ_PKTS_ALL) ? pkt_cnt : fill_pkts;

	__cont_pkts = (cont_pkts == PKTQ_PKTS_ALL) ? pkt_cnt : cont_pkts;

	ASSERT(__fill_pkts <= pkt_cnt);
	ASSERT(__cont_pkts <= pkt_cnt);

	/* Page in requested count */
	pqp_pgi(q, __cont_pkts, __fill_pkts);
}

/* #### PQP Page out utilities #### */

/* SPKTQ PQP page out */
void
spktq_pqp_pgo(struct spktq* spq, int policy,
	void* cb_ctx)
{
	struct pktq_prec *q;				/**< single precedence packet queue */
	ASSERT(spq);

	q = &spq->q;

	/* Page Out the single prio queue */
	if (q->n_pkts) {
		pqp_pgo(q, policy, cb_ctx);
	}
}

/* PQP page out for a given prec bmp */
void BCMFASTPATH
pktq_pqp_pgo(struct pktq *pq, uint prec_bmp,
	int policy, void* cb_ctx)
{
	int prec;
	struct pktq_prec *q;				/**< single precedence packet queue */

	ASSERT(pq);

	PKTQ_PREC_ITER(pq, prec) {
		if ((prec_bmp & (1 << prec)) == 0)
			continue;

		q = &(pq->q[prec]);

		/* Page Out the single prio queue */
		if (q->n_pkts) {
			pqp_pgo(q, policy, cb_ctx);
		}
	}
}

/* PQP page out for a given specific prec */
void BCMFASTPATH
pktq_prec_pqp_pgo(struct pktq *pq, int prec,
	int policy, void* cb_ctx)
{
	struct pktq_prec *q;				/**< single precedence packet queue */

	ASSERT(pq);

	q = &(pq->q[prec]);

	/* Page Out the single prio queue */
	if (q->n_pkts) {
		pqp_pgo(q, policy, cb_ctx);
	}
}
#endif /* HNDPQP */
