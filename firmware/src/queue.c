/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#include "include/queue.h"

#include "include/mutex.h"
#include "include/errors.h"
#include "include/stm32_critical.h"

#include <stdint.h>
#include <stddef.h>

#define IS_QUEUE_FULL(q)    ((((q)->t + 1) % DEFAULT_QUEUE_SIZE) == (q)->h)
#define IS_QUEUE_EMPTY(q)   (((q)->t) == ((q)->h))
#define INC_TAIL(q)         ((q)->t = ((q)->t + 1) % DEFAULT_QUEUE_SIZE)
#define INC_HEAD(q)         ((q)->h = ((q)->h + 1) % DEFAULT_QUEUE_SIZE)

int32_t queue_enqueue(struct queue * const queue, const void * const data, uint32_t * const size)
{
    int32_t ret = E_SUCCESS;
    const uint8_t * const udata = (const uint8_t * const)data;

    if (queue == NULL || data == NULL) {
        ret = E_INVALID_PARAMETER;
        goto exit;
    }

    ENTER_CRITICAL();
    uint32_t w;
    for(w = 0; w < *size; w++) {
        if (IS_QUEUE_FULL(queue)){
            ret = W_QUEUE_BECAME_FULL;
            break;
        }
        queue->data[queue->t] = udata[w];
        INC_TAIL(queue);
    }

    *size = w; // Update written size
    EXIT_CRITICAL();

    exit:
    return ret;
}

int32_t queue_dequeue(struct queue * const queue, void * const data, uint32_t * const size)
{
    int32_t ret = E_SUCCESS;
    uint8_t * const udata = (uint8_t * const)data;

    if (queue == NULL || data == NULL) {
        ret = E_INVALID_PARAMETER;
        goto exit;
    }

    ENTER_CRITICAL();
    uint32_t w;
    for(w = 0; w < *size; w++) {
        if (IS_QUEUE_EMPTY(queue)){
            ret = W_QUEUE_BECAME_EMPTY;
            break;
        }
        udata[w] = queue->data[queue->h];
        INC_HEAD(queue);
    }

    *size = w;
    EXIT_CRITICAL();

    exit:
    return ret;
}

int32_t queue_size(struct queue * const queue, uint32_t * const size)
{
    int32_t ret = E_SUCCESS;

    if (queue == NULL || size == NULL) {
        ret = E_INVALID_PARAMETER;
        goto exit;
    }

    if (queue->t > queue->h) *size = queue->t - queue->h;
    else if (queue-> t < queue->h) *size = DEFAULT_QUEUE_SIZE - (queue->h - queue->t);
    else *size = 0;

    exit:
    return ret;
}