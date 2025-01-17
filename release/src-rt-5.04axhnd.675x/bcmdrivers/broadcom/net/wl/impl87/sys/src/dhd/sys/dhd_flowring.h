/**
 * @file Header file describing the flow rings DHD interfaces.
 *
 * Flow rings are transmit traffic (=propagating towards antenna) related entities.
 *
 * Provides type definitions and function prototypes used to create, delete and manage flow rings at
 * high level.
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
 * $Id: dhd_flowrings.h  jaganlv $
 */

/****************
 * Common types *
 */

#ifndef _dhd_flowrings_h_
#define _dhd_flowrings_h_

/* Max pkts held in a flow ring's backup queue */
#define FLOW_RING_QUEUE_THRESHOLD       (2048)

/* Number of H2D common rings */
#define FLOW_RING_COMMON                BCMPCIE_H2D_COMMON_MSGRINGS

#define FLOWID_INVALID                  (ID16_INVALID)
#define FLOWID_RESERVED                 (FLOW_RING_COMMON)

#define FLOW_RING_STATUS_OPEN           0
#define FLOW_RING_STATUS_PENDING        1
#define FLOW_RING_STATUS_CLOSED         2
#define FLOW_RING_STATUS_DELETE_PENDING 3
#define FLOW_RING_STATUS_FLUSH_PENDING  4
#define FLOW_RING_STATUS_STA_FREEING    5

#define DHD_FLOW_PRIO_AC_MAP		0
#define DHD_FLOW_PRIO_TID_MAP		1

/* Pkttag not compatible with PROP_TXSTATUS or WLFC */
typedef struct dhd_pkttag_fr {
	uint16  flowid;
	uint16  ifid;
	int     dataoff;
	dmaaddr_t physaddr;
	uint32 pa_len;

} dhd_pkttag_fr_t;

#define DHD_PKTTAG_SET_FLOWID(tag, flow)    ((tag)->flowid = (uint16)(flow))
#define DHD_PKTTAG_SET_IFID(tag, idx)       ((tag)->ifid = (uint16)(idx))
#define DHD_PKTTAG_SET_DATAOFF(tag, offset) ((tag)->dataoff = (int)(offset))
#define DHD_PKTTAG_SET_PA(tag, pa)          ((tag)->physaddr = (pa))
#define DHD_PKTTAG_SET_PA_LEN(tag, palen)   ((tag)->pa_len = (palen))

#define DHD_PKTTAG_FLOWID(tag)              ((tag)->flowid)
#define DHD_PKTTAG_IFID(tag)                ((tag)->ifid)
#define DHD_PKTTAG_DATAOFF(tag)             ((tag)->dataoff)
#define DHD_PKTTAG_PA(tag)                  ((tag)->physaddr)
#define DHD_PKTTAG_PA_LEN(tag)              ((tag)->pa_len)

/* Hashing a MacAddress for lkup into a per interface flow hash table */
#define DHD_FLOWRING_HASH_SIZE    256
#define	DHD_FLOWRING_HASHINDEX(ea, prio) \
	       ((((uint8 *)(ea))[3] ^ ((uint8 *)(ea))[4] ^ ((uint8 *)(ea))[5] ^ ((uint8)(prio))) \
		% DHD_FLOWRING_HASH_SIZE)

#define DHD_IF_ROLE(pub, idx)		(((if_flow_lkup_t *)(pub)->if_flow_lkup)[idx].role)
#define DHD_IF_ROLE_AP(pub, idx)	(DHD_IF_ROLE(pub, idx) == WLC_E_IF_ROLE_AP)
#define DHD_IF_ROLE_STA(pub, idx)	(DHD_IF_ROLE(pub, idx) == WLC_E_IF_ROLE_STA)
#define DHD_IF_ROLE_P2PGO(pub, idx)	(DHD_IF_ROLE(pub, idx) == WLC_E_IF_ROLE_P2P_GO)
#define DHD_IF_ROLE_WDS(pub, idx)	(DHD_IF_ROLE(pub, idx) == WLC_E_IF_ROLE_WDS)
#define DHD_FLOW_RING(dhdp, flowid) \
	(flow_ring_node_t *)&(((flow_ring_node_t *)((dhdp)->flow_ring_table))[flowid])

struct flow_queue;

/* Flow Ring Queue Enqueue overflow callback */
typedef int (*flow_queue_cb_t)(struct flow_queue * queue, void * pkt);

/**
 * Each flow ring has an associated (tx flow controlled) queue. 802.3 packets are transferred
 * between queue and ring. A packet from the host stack is first added to the queue, and in a later
 * stage transferred to the flow ring. Packets in the queue are dhd owned, whereas packets in the
 * flow ring are device owned.
 */
typedef struct flow_queue {
	dll_t  list;                /* manage a flowring queue in a double linked list */
	void * head;                /* first packet in the queue */
	void * tail;                /* last packet in the queue */
	uint16 len;                 /* number of packets in the queue */
	uint16 max;                 /* maximum or min budget (used in cumm) */
	uint32 threshold;           /* parent's cummulative length threshold */
	void * clen_ptr;            /* parent's cummulative length counter */
	uint32 failures;            /* enqueue failures due to queue overflow */
	flow_queue_cb_t cb;         /* callback invoked on threshold crossing */
	uint32 l2threshold;         /* grandparent's (level 2) cummulative length threshold */
	void * l2clen_ptr;          /* grandparent's (level 2) cummulative length counter */
} flow_queue_t;

#define DHD_FLOW_QUEUE_LEN(queue)       ((int)(queue)->len)
#define DHD_FLOW_QUEUE_MAX(queue)       ((int)(queue)->max)
#define DHD_FLOW_QUEUE_THRESHOLD(queue) ((int)(queue)->threshold)
#define DHD_FLOW_QUEUE_L2THRESHOLD(queue) ((int)(queue)->l2threshold)
#define DHD_FLOW_QUEUE_EMPTY(queue)     ((queue)->len == 0)
#define DHD_FLOW_QUEUE_FAILURES(queue)  ((queue)->failures)

#define DHD_FLOW_QUEUE_AVAIL(queue)     ((int)((queue)->max - (queue)->len))
#define DHD_FLOW_QUEUE_FULL(queue)      ((queue)->len >= (queue)->max)

#define DHD_FLOW_QUEUE_OVFL(queue, budget)  \
	(((queue)->len) > budget)

#define DHD_FLOW_QUEUE_SET_MAX(queue, budget) \
	((queue)->max) = ((budget) - 1)

/* Queue's cummulative threshold. */
#define DHD_FLOW_QUEUE_SET_THRESHOLD(queue, cumm_threshold) \
	((queue)->threshold) = ((cumm_threshold) - 1)

/* Queue's cummulative length object accessor. */
#define DHD_FLOW_QUEUE_CLEN_PTR(queue)  ((queue)->clen_ptr)

/* Set a queue's cumm_len point to a parent's cumm_ctr_t cummulative length */
#define DHD_FLOW_QUEUE_SET_CLEN(queue, parent_clen_ptr)  \
	((queue)->clen_ptr) = (void *)(parent_clen_ptr)

/* Queue's level 2 cummulative threshold. */
#define DHD_FLOW_QUEUE_SET_L2THRESHOLD(queue, l2cumm_threshold) \
	((queue)->l2threshold) = ((l2cumm_threshold) - 1)

/* Queue's level 2 cummulative length object accessor. */
#define DHD_FLOW_QUEUE_L2CLEN_PTR(queue)  ((queue)->l2clen_ptr)

/* Set a queue's level 2 cumm_len point to a grandparent's cumm_ctr_t cummulative length */
#define DHD_FLOW_QUEUE_SET_L2CLEN(queue, grandparent_clen_ptr)  \
	((queue)->l2clen_ptr) = (void *)(grandparent_clen_ptr)

/*  see wlfc_proto.h for tx status details */
#define DHD_FLOWRING_MAXSTATUS_MSGS	5
#if defined(BCMDBG)
#define DHD_FLOWRING_TXSTATUS_CNT_UPDATE(bus, flowid, txstatus) \
		dhd_bus_flow_ring_cnt_update(bus, flowid, txstatus)
#else
#define DHD_FLOWRING_TXSTATUS_CNT_UPDATE(bus, flowid, txstatus)
#endif /* BCMDBG */
/** each flow ring is dedicated to a tid/sa/da combination */
typedef struct flow_info {
	uint8		tid;
	uint8		ifindex;
	char		sa[ETHER_ADDR_LEN];
	char		da[ETHER_ADDR_LEN];
#if defined(BCMDBG)
	uint32		tx_status[DHD_FLOWRING_MAXSTATUS_MSGS];
#endif
} flow_info_t;

#if defined(BCM_DHD_RUNNER)
#define DHD_FLOWRING_SET_RNR_OFFL(flow_ring, offl) ((flow_ring)->rnr_offl = offl)
#define DHD_FLOWRING_RNR_OFFL(flow_ring)           ((flow_ring)->rnr_offl)
#endif /* BCM_DHD_RUNNER */

/** a flow ring is used for outbound (towards antenna) 802.3 packets */
typedef struct flow_ring_node {
	dll_t		list;  /* manage a constructed flowring in a dll, must be at first place */
	flow_queue_t	queue; /* queues packets before they enter the flow ring, flow control */
	bool		active;
	uint8		status;
#if defined(BCM_DHD_RUNNER)
	bool		rnr_offl; /* tx post ring managed by hw accelerator */
#endif /* BCM_DHD_RUNNER */
	/*
	 * flowid: unique ID of a flow ring, which can either be unicast or broadcast/multicast. For
	 * unicast flow rings, the flow id accelerates ARM 802.3->802.11 header translation.
	 */
	uint16		flowid;
	flow_info_t	flow_info;
	void		*prot_info;
	void		*lock; /* lock for flowring access protection */
#ifdef DHD_IFE
	uint16          evict_wr_idx;
	bool            evict_inprogress;
#endif /* DHD_IFE */
} flow_ring_node_t;

typedef flow_ring_node_t flow_ring_table_t;

typedef struct flow_hash_info {
	uint16			flowid;
	flow_info_t		flow_info;
	struct flow_hash_info	*next;
} flow_hash_info_t;

typedef struct if_flow_lkup {
	bool		status;
	uint8		role; /* Interface role: STA/AP */
	flow_hash_info_t *fl_hash[DHD_FLOWRING_HASH_SIZE]; /* Lkup Hash table */
} if_flow_lkup_t;

static INLINE flow_ring_node_t *
dhd_constlist_to_flowring(dll_t *item)
{
	return ((flow_ring_node_t *)item);
}

/* Exported API */

/* Flow ring's queue management functions */
extern flow_ring_node_t * dhd_flow_ring_node(dhd_pub_t *dhdp, uint16 flowid);
extern flow_queue_t * dhd_flow_queue(dhd_pub_t *dhdp, uint16 flowid);

extern void dhd_flow_queue_init(dhd_pub_t *dhdp, flow_queue_t *queue, int max);
extern void dhd_flow_queue_reinit(dhd_pub_t *dhdp, flow_queue_t *queue, int max);
extern void dhd_flow_queue_register(flow_queue_t *queue, flow_queue_cb_t cb);
extern int  dhd_flow_queue_enqueue(dhd_pub_t *dhdp, flow_queue_t *queue, void *pkt);
extern void * dhd_flow_queue_dequeue(dhd_pub_t *dhdp, flow_queue_t *queue);
extern void dhd_flow_queue_reinsert(dhd_pub_t *dhdp, flow_queue_t *queue, void *pkt);

extern void dhd_flow_ring_config_thresholds(dhd_pub_t *dhdp, uint16 flowid,
                          int queue_budget, int cumm_threshold, void *cumm_ctr,
                          int l2cumm_threshold, void *l2cumm_ctr);
extern int  dhd_flow_rings_init(dhd_pub_t *dhdp, uint32 num_flow_rings);

extern void dhd_flow_rings_deinit(dhd_pub_t *dhdp);

extern int dhd_flowid_update(dhd_pub_t *dhdp, uint8 ifindex, uint8 prio,
                void *pktbuf);

extern int dhd_flowid_lookup(dhd_pub_t *dhdp, uint8 ifindex,
                uint8 prio, char *sa, char *da, uint16 *flowid);
extern void dhd_flowid_free(dhd_pub_t *dhdp, uint8 ifindex, uint16 flowid);

extern void dhd_flow_rings_delete(dhd_pub_t *dhdp, uint8 ifindex);

extern void dhd_flow_rings_delete_for_peer(dhd_pub_t *dhdp, uint8 ifindex,
                char *addr);

/* Handle Interface ADD, DEL operations */
extern void dhd_update_interface_flow_info(dhd_pub_t *dhdp, uint8 ifindex,
                uint8 op, uint8 role);

/* Handle a STA interface link status update */
extern int dhd_update_interface_link_status(dhd_pub_t *dhdp, uint8 ifindex,
                uint8 status);
extern int dhd_flow_prio_map(dhd_pub_t *dhd, uint8 *map, bool set);
extern int dhd_update_flow_prio_map(dhd_pub_t *dhdp, uint8 map);

/* iDMA flow ring split manager */
extern void *dhd_idma_flowmgr_init(dhd_pub_t *dhdp, int max_h2d_rings);
extern void *dhd_idma_flowmgr_fini(dhd_pub_t *dhdp, void *flowmgr);
extern uint16 dhd_idma_flowmgr_alloc(void *flowmgr, uint8 *mac);
extern void dhd_idma_flowmgr_free(void *flowmgr, uint16 flow_id);
extern uint16 dhd_idma_flowmgr_ringid_2_index(dhd_pub_t *dhdp, uint16 ringid, uint16 flow_id);

extern uint8 dhd_flow_rings_ifindex2role(dhd_pub_t *dhdp, uint8 ifindex);
#ifdef BCM_NBUFF_WLMCAST
int dhd_flowid_get_type(dhd_pub_t *dhdp, void *sta_p, int priority);
#endif  /* BCM_NBUFF_WLMCAST */

#if defined(BCM_PKTFWD)
extern int dhd_pktfwd_pktlist_enqueue(dhd_pub_t *dhdp, uint16 flowid,
	void *pktlist_head, void *pktlist_tail, uint16 pktlist_count);
#endif /* BCM_PKTFWD */

#endif /* _dhd_flowrings_h_ */
