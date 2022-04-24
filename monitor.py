from argparse import ArgumentParser
from serial import Serial
import time

BLOCK_SIZE = 512
N_BLOCKS = 1000
FS_SIZE = BLOCK_SIZE * N_BLOCKS

BOOT_SECTOR_HEADER = bytes([0xEB, 0x3C, 0x90])

def get_fs(ser):
    read = 0
    found = 0
    while True:
        print(f"\rScanning for start of boot sector... have read {read} bytes so far")
        b = ser.read(1)
        for i, bi in enumerate(b):
            read += 1
            if bi == BOOT_SECTOR_HEADER[found]:
                found += 1
                if found == len(BOOT_SECTOR_HEADER):
                    print(f"Found!")
                    out = BOOT_SECTOR_HEADER
                    remaining = FS_SIZE - len(BOOT_SECTOR_HEADER)
                    while remaining > 0:
                        print(f"Reading rest of filesystem, need {remaining} more")
                        chunk = ser.read(remaining)
                        out += chunk
                        remaining -= len(chunk)
                    return out
                else:
                    print(f"Found {found}")
            else:
                found = 0


def main():
    parser = ArgumentParser()
    parser.add_argument("port")
    parser.add_argument("baud")
    parser.add_argument("output")
    args = parser.parse_args()
    ser = Serial(args.port, args.baud, timeout=1)
    fs = get_fs(ser)
    with open(args.output, "wb") as file:
        file.write(fs)


if __name__ == "__main__":
    main()
