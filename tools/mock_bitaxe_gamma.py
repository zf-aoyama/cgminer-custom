#!/usr/bin/env python3
"""Simple mock of a bitaxe Gamma USB device for handshake testing."""

import argparse
import serial
import time

HELLO_REQ = b"\xAA\x01\x00\x00\x55"
HELLO_RESP = b"\xAA\x01\x05\x00mock1\x55"


def run(port):
    ser = serial.Serial(port, 115200, timeout=1)
    print(f"Waiting for HELLO on {port}")
    buf = bytearray()
    while True:
        b = ser.read(1)
        if not b:
            continue
        buf += b
        if buf.endswith(HELLO_REQ):
            print("Received HELLO, responding")
            ser.write(HELLO_RESP)
            ser.flush()
            break
    ser.close()


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("port", help="Serial port to emulate")
    args = ap.parse_args()
    run(args.port)


if __name__ == "__main__":
    main()
