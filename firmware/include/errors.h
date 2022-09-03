/*
 * Copyright 2022 Cristóvão Zuppardo Rufino <cristovaozr+hwtotp@gmail.com>
 * This firmware is free-software. See LICENSE file attached.
 */

#ifndef INCLUDE_ERRORS_H_
#define INCLUDE_ERRORS_H_

#include <stdint.h>

/**
 * @brief Error numbers
 */
enum {
    /* General errors */
    E_UNKNOWN_ERROR = INT32_MIN,        /** Unknown error */
    E_INVALID_PARAMETER,                /** Invalid parameter */
    W_IO_WOULD_BLOCK,                   /** IO operation would block */

    /* Mutex errors */
    W_MUTEX_ALREADY_LOCKED,             /** Mutex already locked */

    /* Queue errors */
    W_QUEUE_IS_LOCKED,                  /** Queue is locked for use */
    W_QUEUE_BECAME_FULL,                /** Queue became full during use */
    W_QUEUE_BECAME_EMPTY,               /** Queue became empty during use */

    E_SUCCESS = 0                       /** Success */
};

#endif // INCLUDE_ERRORS_H_