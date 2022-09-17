/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#ifndef FIRMWARE_INCLUDE_SYSTICK_H_
#define FIRMWARE_INCLUDE_SYSTICK_H_

#include <stdint.h>

struct systick {
    uint32_t secs;
    uint32_t msecs;
};

int32_t systick_get(struct systick * const systick);

#endif // FIRMWARE_INCLUDE_SYSTICK_H_