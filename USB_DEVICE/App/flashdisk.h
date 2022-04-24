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

bool flashdisk_init(void);

void flashdisk_store(uint8_t *buffer, size_t size);

void flashdisk_load(uint8_t *buffer, size_t size);

#endif /* APP_FLASHDISK_H_ */
