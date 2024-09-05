#include "q64.h"

HAL_StatusTypeDef W25Q64_Read(SPI_HandleTypeDef * hspi,uint32_t start_addr,uint8_t*data,uint16_t size)
{
	uint8_t cmd[4] = {0x3,start_addr >> 16,start_addr >> 8, start_addr};
	HAL_StatusTypeDef ret;
	HAL_GPIO_WritePin(Q64_NSS_GPIO_Port,Q64_NSS_Pin,GPIO_PIN_RESET);
	
	HAL_SPI_Transmit(hspi,cmd,4,100);
	ret = HAL_SPI_Receive(hspi,data,size,100);
	
	HAL_GPIO_WritePin(Q64_NSS_GPIO_Port,Q64_NSS_Pin,GPIO_PIN_SET);
	
	return ret;
}