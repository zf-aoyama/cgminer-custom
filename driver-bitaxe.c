/*
 * Minimal stub driver for bitaxe Gamma ASIC.
 * Placeholder implementation for future development.
 */

#include "config.h"
#include "miner.h"
#include "usbutils.h"

struct bitaxe_info {
        /* Placeholder for future device specific state */
        int dummy;
};

/*
 * Prepare a mining thread. Currently this simply initialises the
 * per-device data structure and always succeeds.
 */
static bool bitaxe_prepare(struct thr_info *thr)
{
        struct cgpu_info *bitaxe = thr->cgpu;

        if (!bitaxe->device_data)
                bitaxe->device_data = cgcalloc(1, sizeof(struct bitaxe_info));

        return true;
}

/*
 * Main work scanning loop. This stub retrieves work from the core but does
 * not yet communicate with real hardware. It simply sleeps briefly and
 * returns 0 hashes found.
 */
static int64_t bitaxe_scanwork(struct thr_info *thr)
{
        struct work *work;

        work = get_work(thr, thr->id);
        if (!work)
                return 0;

        cgsleep_ms(100);

        return 0;
}

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
        .thread_prepare = bitaxe_prepare,
        .hash_work = hash_driver_work,
        .scanwork = bitaxe_scanwork,
};
