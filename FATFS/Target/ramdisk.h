/*
 * ramdisk.h
 *
 *  Created on: Apr 24, 2022
 *      Author: dt
 */

#ifndef TARGET_RAMDISK_H_
#define TARGET_RAMDISK_H_

#include "stdint.h"

#define RAMDISK_SIZE_BYTES (500U * 1024U)

uint8_t *ramdisk_buffer_get(void);

#endif /* TARGET_RAMDISK_H_ */
