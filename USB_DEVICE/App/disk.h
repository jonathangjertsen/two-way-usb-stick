/*
 * disk.h
 *
 *  Created on: Apr 24, 2022
 *      Author: dt
 */

#ifndef APP_DISK_H_
#define APP_DISK_H_


#define STORAGE_LUN_NBR                  1
#define STORAGE_BLK_NBR                  512
#define STORAGE_BLK_SIZ                  0x200

#define DISK_SIZE (STORAGE_BLK_NBR * STORAGE_BLK_SIZ)

#endif /* APP_DISK_H_ */
