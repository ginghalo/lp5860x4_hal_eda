#ifndef __W25Q64_H__
#define __W25Q64_H__
#include "main.h"
#include "spi.h"

HAL_StatusTypeDef W25Q64_Read(SPI_HandleTypeDef * hspi,uint32_t start_addr,uint8_t*data,uint16_t size);

#endif