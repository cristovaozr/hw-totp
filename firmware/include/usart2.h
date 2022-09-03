/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#ifndef INCLUDE_USART2_H_
#define INCLUDE_USART2_H_

#include <stdint.h>

int32_t usart2_write(const void * const data, uint32_t * const size);

int32_t usart2_read(void * const data, uint32_t * const size);

int32_t usart2_available(uint32_t * const size);

#endif // INCLUDE_USART2_H_