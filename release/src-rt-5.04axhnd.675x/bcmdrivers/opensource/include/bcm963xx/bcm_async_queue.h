/*
<:copyright-BRCM:2018:DUAL/GPL:standard

   Copyright (c) 2018 Broadcom 
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

/*
 *******************************************************************************
 * File Name  : bcm_async_queue.h
 *
 *******************************************************************************
 */

#ifndef __BCM_ASYNC_QUEUE_H_INCLUDED__
#define __BCM_ASYNC_QUEUE_H_INCLUDED__

typedef struct {
    uint32_t writes;
    uint64_t write_bytes;
    uint32_t reads;
    uint32_t discards;
    uint64_t discard_bytes;
} bcm_async_queue_stats_t;

typedef struct {
    volatile uint8_t *alloc_p;
    volatile uint16_t write;
    volatile uint16_t read;
    int depth;
    int entry_size;
    bcm_async_queue_stats_t stats;
} bcm_async_queue_t;

#if 1
#define _STATIC_INLINE_ static inline
#define _STATIC_        static
#else
#define _STATIC_INLINE_
#define _STATIC_
#endif

#define bcm_async_queue_not_full(_queue_p) bcm_async_queue_free_entries(_queue_p)
#define bcm_async_queue_not_empty(_queue_p) !bcm_async_queue_empty(_queue_p)
#define bcm_async_queue_empty(_queue_p) ( (_queue_p)->write == (_queue_p)->read )

_STATIC_INLINE_ uint16_t bcm_async_queue_avail_entries(bcm_async_queue_t *queue_p)
{
    return (queue_p->write - queue_p->read);
}

_STATIC_INLINE_ uint16_t bcm_async_queue_free_entries(bcm_async_queue_t *queue_p)
{
    return queue_p->depth - bcm_async_queue_avail_entries(queue_p);
}

_STATIC_INLINE_ volatile uint8_t *bcm_async_queue_entry_read(bcm_async_queue_t *queue_p)
{
    int read_index = queue_p->read & (queue_p->depth - 1);
    int read_offset = read_index * queue_p->entry_size;
    volatile uint8_t *read_p = &queue_p->alloc_p[read_offset];

    return read_p;
}

_STATIC_INLINE_ void bcm_async_queue_entry_dequeue(bcm_async_queue_t *queue_p)
{
#if !defined(CC_BCM_ASYNC_QUEUE_NO_BARRIER)
    smp_rmb();
#endif
    queue_p->read++;
}

_STATIC_INLINE_ volatile uint8_t *bcm_async_queue_entry_write(bcm_async_queue_t *queue_p)
{
    int write_index = queue_p->write & (queue_p->depth - 1);
    int write_offset = write_index * queue_p->entry_size;
    volatile uint8_t *write_p = &queue_p->alloc_p[write_offset];

    return write_p;
}

_STATIC_INLINE_ void bcm_async_queue_entry_enqueue(bcm_async_queue_t *queue_p)
{
#if !defined(CC_BCM_ASYNC_QUEUE_NO_BARRIER)
    smp_wmb();
#endif
    queue_p->write++;
}

_STATIC_INLINE_ int bcm_async_queue_init(bcm_async_queue_t *queue_p, int queue_size, int entry_size)
{
    int alloc_size = entry_size * queue_size;

    memset((void *)queue_p, 0, sizeof(bcm_async_queue_t));
    queue_p->alloc_p = (uint8_t *)kmalloc(alloc_size, GFP_KERNEL);

    if (queue_p->alloc_p == NULL)
    {
        return -1;
    }

    memset((void *)queue_p->alloc_p, 0, alloc_size);

    queue_p->entry_size = entry_size;
    queue_p->depth = queue_size;

    return 0;
}

_STATIC_INLINE_ void bcm_async_queue_uninit(bcm_async_queue_t *queue_p)
{
    if(!bcm_async_queue_empty(queue_p))
    {
        printk("bcm_async_queue_uninit: Warning, Queue is not empty");
    }

    if(queue_p->alloc_p)
    {
        kfree((void *)queue_p->alloc_p);
    }
}

#endif /*__BCM_ASYNC_QUEUE_H_INCLUDED__ */

