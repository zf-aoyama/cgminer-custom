/*
 * Minimal stub driver for bitaxe Gamma ASIC.
 * Placeholder implementation for future development.
 */

#include "config.h"
#include "miner.h"
#include "usbutils.h"

struct bitaxe_info {
        int dummy;
};

static struct cgpu_info *bitaxe_detect_one(struct libusb_device *dev,
                                          struct usb_find_devices *found)
{
        struct cgpu_info *bitaxe = usb_alloc_cgpu(&bitaxe_drv, 1);

        if (!usb_init(bitaxe, dev, found)) {
                bitaxe = usb_free_cgpu(bitaxe);
                return NULL;
        }

        bitaxe->device_data = cgcalloc(1, sizeof(struct bitaxe_info));
        bitaxe->threads = 1;
        add_cgpu(bitaxe);

        applog(LOG_INFO, "%s: Found at %s", bitaxe->drv->dname,
               bitaxe->device_path);

        return bitaxe;
}

static void bitaxe_detect(bool __maybe_unused hotplug)
{
        usb_detect(&bitaxe_drv, bitaxe_detect_one);
}

struct device_drv bitaxe_drv = {
        .drv_id = DRIVER_bitaxe,
        .dname = "bitaxe",
        .name = "BAXG",
        .drv_detect = bitaxe_detect,
};
