This directory stores firmware projects related to bitaxe Gamma.

- `esp-miner/` references the existing ESP-Miner firmware for single-ASIC mining.
- `usb-bridge/` will contain firmware turning the ESP32 into a USB bridge so cgminer can control the ASIC directly.

Each subdirectory should provide its own build instructions using ESP-IDF.
