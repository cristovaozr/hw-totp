/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#include "include/hw_init.h"

#include "include/usart2.h"
#include "include/errors.h"

int main(void)
{
    hw_init();

    // USART loopback
    while(1) {
        uint8_t byte[32];
        uint32_t size;
        int32_t ret = usart2_available(&size);
        if (ret == W_QUEUE_IS_LOCKED) continue;
        if (size > 0) {
            usart2_read(&byte[0], &size);
            usart2_write(&byte[0], &size);
        }
    }

    return 0;
}