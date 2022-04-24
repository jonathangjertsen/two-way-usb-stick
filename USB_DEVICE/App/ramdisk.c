#include "ramdisk.h"
#include <string.h>

uint8_t ramdisk[STORAGE_BLK_NBR * STORAGE_BLK_SIZ] __attribute__((aligned (4)));

void ramdisk_write(const uint8_t *data, uint32_t block, uint32_t block_size, uint32_t n_blocks)
{
	  memcpy(&ramdisk[block * block_size], data, n_blocks * block_size);
}

void ramdisk_read(uint8_t *data, uint32_t block, uint32_t block_size, uint32_t n_blocks)
{
	  memcpy(data, &ramdisk[block * block_size], n_blocks * block_size);
}

uint8_t *ramdisk_get(void)
{
	return ramdisk;
}


size_t ramdisk_size(void)
{
	return sizeof(ramdisk);
}
