/*
 * flashdisk.h
 *
 *  Created on: Apr 24, 2022
 *      Author: dt
 */

#ifndef APP_FLASHDISK_H_
#define APP_FLASHDISK_H_

#include "disk.h"

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

typedef enum {
	FLASHDISK_STORE_OK        = 0x0000,
	FLASHDISK_STORE_UNALIGNED = 0x1000,
	FLASHDISK_STORE_ERROR     = 0x1001,
} flashdisk_store_result_t;

bool flashdisk_init(void);

flashdisk_store_result_t flashdisk_store(uint8_t *buffer, size_t size);

void flashdisk_load(uint8_t *buffer, size_t size);

#endif /* APP_FLASHDISK_H_ */
