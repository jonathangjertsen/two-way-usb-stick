/*
 * flashdisk.c
 *
 *  Created on: Apr 24, 2022
 *      Author: dt
 */
#include "stm32h7xx_hal.h"

#include "flashdisk.h"

#include <string.h>

#define FLASH_DISK_ADDR 0x08100000UL

#define FLASH_DISK_N_SECTORS (DISK_SIZE / FLASH_SECTOR_SIZE)

static_assert((DISK_SIZE % FLASH_SECTOR_SIZE) == 0, "Disk size must be aligned to flash sector");

uint32_t *_flash_disk = (uint32_t*)FLASH_DISK_ADDR;

static const uint8_t FAT_HEAD[] = { 0xEB, 0x3C, 0x90 };
bool flashdisk_init(void)
{
	return memcmp((uint8_t*)_flash_disk, FAT_HEAD, sizeof(FAT_HEAD)) == 0;
}

flashdisk_store_result_t flashdisk_store(uint8_t *buffer, size_t size)
{
	if (((uintptr_t)buffer & 0x3) != 0)
	{
		return FLASHDISK_STORE_UNALIGNED;
	}

	if ((size & 0x3) != 0)
	{
		return FLASHDISK_STORE_UNALIGNED;
	}

	HAL_FLASH_Unlock();
    uint32_t error = 0;
    FLASH_EraseInitTypeDef FLASH_EraseInitStruct =
    {
    	.TypeErase = FLASH_TYPEERASE_SECTORS,
		.Sector = 1,
		.NbSectors = 1,
		.VoltageRange = FLASH_VOLTAGE_RANGE_3
    };

    HAL_StatusTypeDef status = HAL_FLASHEx_Erase(&FLASH_EraseInitStruct, &error);
	if (status == HAL_OK)
	{
		for (uint32_t offset = 0; offset < size; offset += 32)
		{
			status = HAL_FLASH_Program(
				FLASH_TYPEPROGRAM_FLASHWORD,
				FLASH_DISK_ADDR + offset,
				(uint32_t)(uintptr_t)(&buffer[offset])
			);

			if (status != HAL_OK)
			{
				break;
			}
		}
	}

    HAL_FLASH_Lock();

    return (flashdisk_store_result_t)status;
}

void flashdisk_load(uint8_t *buffer, size_t size)
{
	memcpy(buffer, (uint8_t*)_flash_disk, size);
}
