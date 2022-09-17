/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#include "include/hw_init.h"

#include "include/usart2.h"
#include "include/errors.h"
#include "include/systick.h"

int main(void)
{
    hw_init();

    // USART loopback
    while(1) {
        struct systick time;
        uint8_t byte[32];
        uint32_t size;
        usart2_available(&size);
        if (size > 0) {
            systick_get(&time);

            usart2_read(&byte[0], &size);
            usart2_write(&byte[0], &size);
        }
    }

    return 0;
}