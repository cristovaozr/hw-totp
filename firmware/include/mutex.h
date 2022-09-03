/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#ifndef INCLUDE_MUTEX_H_
#define INCLUDE_MUTEX_H_

#include <stdint.h>

struct mutex {
    int32_t mutex;
};

int32_t mutex_try_lock(struct mutex * const mutex);

int32_t mutex_unlock(struct mutex * const mutex);

#define MUTEX_UNLOCKED  0               /** Mutex locked symbol */
#define MUTEX_LOCKED    !MUTEX_UNLOCKED /** Mutex unlocked symbol */

#endif // INCLUDE_MUTEX_H_