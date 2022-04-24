#ifndef RAMDISK_H
#define RAMDISK_H

#include <stdint.h>

#include <stddef.h>

#include "disk.h"

void ramdisk_write(const uint8_t *data, uint32_t block, uint32_t block_size, uint32_t n_blocks);

void ramdisk_read(uint8_t *data, uint32_t block, uint32_t block_size, uint32_t n_blocks);

uint8_t *ramdisk_get(void);

size_t ramdisk_size(void);

#endif

