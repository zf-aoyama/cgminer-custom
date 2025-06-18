/*
 * Minimal stub driver for bitaxe Gamma ASIC.
 * Placeholder implementation for future development.
 */

#include "config.h"
#include "miner.h"

static void bitaxe_detect(bool __maybe_unused hotplug)
{
        /* Detection logic will be implemented later */
        (void)hotplug;
}

struct device_drv bitaxe_drv = {
        .drv_id = DRIVER_bitaxe,
        .dname = "bitaxe",
        .name = "BAXG",
        .drv_detect = bitaxe_detect,
};
