/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#include "include/usart2.h"

#include "include/queue.h"
#include "include/errors.h"

#include "stm32f1xx.h"
#include "stm32f1xx_ll_usart.h"

#include <stdint.h>

static struct queue tx_queue = {
    .t = 0,
    .h = 0
};

static struct queue rx_queue = {
    .t = 0,
    .h = 0
};

int32_t usart2_write(const void * const data, uint32_t * const size)
{
    int32_t ret = queue_enqueue(&tx_queue, data, size);
    if (ret == W_QUEUE_BECAME_FULL) {
        ret = W_IO_WOULD_BLOCK;
    }
    if (*size > 0) {
        LL_USART_EnableIT_TXE(USART2);
    }

    return ret;
}

int32_t usart2_read(void * const data, uint32_t * const size)
{

    int32_t ret = queue_dequeue(&rx_queue, data, size);
    if (ret == W_QUEUE_BECAME_EMPTY) {
        ret = W_IO_WOULD_BLOCK;
    }

    return ret;
}

int32_t usart2_available(uint32_t * const size)
{
    return queue_size(&rx_queue, size);
}

void USART2_IRQHandler(void)
{
    uint8_t byte;
    uint32_t size;

    if (LL_USART_IsActiveFlag_RXNE(USART2)) {
        while (LL_USART_IsActiveFlag_RXNE(USART2)) {
            uint8_t byte = LL_USART_ReceiveData8(USART2);
            uint32_t size = sizeof(byte);
            queue_enqueue(&rx_queue, &byte, &size);
            // There is nothing that can be done if reading causes an error
            // or rx_queue is full
            LL_USART_ClearFlag_RXNE(USART2);
        }
    }

    if (LL_USART_IsActiveFlag_TXE(USART2)) {
        while (LL_USART_IsActiveFlag_TXE(USART2)) {
            
            size = sizeof(byte);
            int32_t ret = queue_dequeue(&tx_queue, &byte, &size);
            if (size == 0 || ret != E_SUCCESS) {
                // When size == 0 means that the queue is empty
                // When ret < 0, it means that some error hapened
                LL_USART_DisableIT_TXE(USART2);
                break;
            }

            LL_USART_TransmitData8(USART2, byte);
        }
    }
}