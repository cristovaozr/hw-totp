/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#include "include/mutex.h"
#include "include/errors.h"
#include "include/stm32_critical.h"

#include <stdint.h>
#include <stddef.h>


int32_t mutex_try_lock(struct mutex * const mutex)
{
    int32_t ret = E_SUCCESS;

    if (mutex == NULL) {
        ret = E_INVALID_PARAMETER;
        goto exit;
    }

    ENTER_CRITICAL();

    if (mutex->mutex != MUTEX_UNLOCKED) {
        ret = W_MUTEX_ALREADY_LOCKED;
        goto exit;
    }

    mutex->mutex = MUTEX_LOCKED;

    exit:
    EXIT_CRITICAL();
    return ret;
}

int32_t mutex_unlock(struct mutex * const mutex)
{
    int32_t ret = E_SUCCESS;

    if (mutex == NULL) {
        ret = E_INVALID_PARAMETER;
        goto exit;
    }

    ENTER_CRITICAL();
    mutex->mutex = MUTEX_UNLOCKED;

    exit:
    EXIT_CRITICAL();
    return ret;
}