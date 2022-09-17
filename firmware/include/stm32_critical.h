/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#ifndef INCLUDE_STM32_CRITICAL_H_
#define INCLUDE_STM32_CRITICAL_H_

#include "stm32f1xx.h"

#define ENTER_CRITICAL() \
    do {                \
        __disable_irq();\
        __DSB();        \
        __ISB();        \
    } while(0)

#define EXIT_CRITICAL() \
    do {                \
        __enable_irq(); \
        __DSB();        \
        __ISB();        \
    } while(0)

#define DISABLE_IRQ()   __disable_irq();

#define ENABLE_IRQ()    __enable_irq();

#endif // INCLUDE_STM32_CRITICAL_H_