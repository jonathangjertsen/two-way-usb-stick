/*
 * ramdisk.c
 *
 *  Created on: Apr 24, 2022
 *      Author: dt
 */
#include "ramdisk.h"

#include "stdint.h"

static uint8_t g_ramdisk[RAMDISK_SIZE_BYTES];

uint8_t *ramdisk_buffer_get(void)
{
	return g_ramdisk;
}
