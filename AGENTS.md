# Repository Structure

```
.
└─ cgminer-custom/
   ├─ firmware/
   │   ├─ esp-miner/      – ESP-Miner based firmware
   │   └─ usb-bridge/     – USB bridge firmware
   ├─ reference/
   │   ├─ ESP-Miner/      – software for controlling ASIC chips with an ESP32
   │   └─ bitaxeGamma/    – hardware source for a single-ASIC mining machine
   ├─ docs/               – documentation
   └─ ...                 – main cgminer source tree
```

## Instructions

1. Feel free to consult, copy from, or modify the code in `cgminer-custom/reference/` (including `ESP-Miner/` and `bitaxeGamma/`) whenever it helps your implementation or refactoring work.
2. Apply your functional changes primarily to the files under `cgminer-custom/` itself, keeping the reference code in sync only when necessary.

## Testing method

```
./autogen.sh
./configure --enable-bitaxe
make -j"$(nproc)"
(cd firmware/esp-miner && idf.py build)
(cd firmware/usb-bridge && idf.py build)
```

## Important Notes

1. Always log with stdout and stderr combined into a single stream.
