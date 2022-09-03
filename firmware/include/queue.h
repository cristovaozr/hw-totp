/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#ifndef INCLUDE_QUEUE_H_
#define INCLUDE_QUEUE_H_

#include <stdint.h>

#define DEFAULT_QUEUE_SIZE  32

struct queue {
    uint32_t h, t;
    uint8_t data[DEFAULT_QUEUE_SIZE];
};

int32_t queue_enqueue(struct queue * const queue, const void * const data, uint32_t * const size);

int32_t queue_dequeue(struct queue * const queue, void * const data, uint32_t * const size);

int32_t queue_size(struct queue * const queue, uint32_t * const size);

#endif // INCLUDE_QUEUE_H_