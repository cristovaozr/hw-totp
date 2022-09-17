#include "include/systick.h"

#include "include/errors.h"
#include "include/stm32_critical.h"

#include <stdint.h>
#include <stddef.h>

static uint64_t msecs = 0;

int32_t systick_get(struct systick * const systick)
{
    int32_t ret = E_SUCCESS;

    if (systick == NULL) {
        ret = E_INVALID_PARAMETER;
        goto exit;
    }

    DISABLE_IRQ();
    uint64_t msecs_copy = msecs;
    ENABLE_IRQ();

    systick->secs = msecs_copy / 1000;
    systick->msecs = msecs_copy % 1000;

    exit:
    return ret;
}

void SysTick_Handler(void)
{
    msecs++;
}