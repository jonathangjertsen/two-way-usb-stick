from argparse import ArgumentParser
from serial import Serial
import time

from pathlib import Path
from argparse import ArgumentParser

import fs
import fs.copy
import fs.walk

BLOCK_SIZE = 512
N_BLOCKS = 512
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
    parser.add_argument("--fs", default="fs.iso")
    args = parser.parse_args()
    ser = Serial(args.port, args.baud, timeout=1)

    fs_path = Path(args.fs).absolute()
    out_path = Path(args.output).absolute()
    out_path.mkdir(exist_ok=True, parents=True)

    while True:
        fs_bin = get_fs(ser)
        with open(fs_path, "wb") as file:
            file.write(fs_bin)

        with fs.open_fs(f"fat://{fs_path}") as fat_fs:
            fs.copy.copy_fs(fat_fs, str(out_path), walker=fs.walk.Walker(filter=["*.png", "*.PNG"]))

if __name__ == "__main__":
    main()
