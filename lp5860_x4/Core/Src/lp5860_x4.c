#include "lp5860_x4.h"

#include "oled.h"
uint8_t Lp5860_x4_Read(SPI_HandleTypeDef *hspi,uint16_t reg)
{
	reg <<= 6;
	// read
	
	uint8_t data[2] = { reg>>8,reg&0xFF };
	HAL_SPI_Transmit(hspi,data,2,100);
	HAL_SPI_Receive(hspi,data,1,100); 
	return data[0];
}


HAL_StatusTypeDef Lp5860_x4_Write(SPI_HandleTypeDef *hspi,uint16_t reg,uint8_t data)
{
	reg <<= 6;
	reg |= 1 << 5;// write
	
	uint8_t tx[3] = { reg>>8,reg&0xFF,data};
	return HAL_SPI_Transmit(hspi,tx,3,100);
}
HAL_StatusTypeDef Lp5860_x4_Writes(SPI_HandleTypeDef *hspi,uint16_t reg,uint8_t* data,uint16_t size)
{
	reg <<= 6;
	reg |= 1 << 5;// write
	
	uint8_t tx[3] = { reg>>8,reg&0xFF};
	HAL_SPI_Transmit(hspi,tx,2,100);
	return HAL_SPI_Transmit(hspi,data,size,100);
}



uint8_t Lp5860_Read(SPI_HandleTypeDef *hspi,uint8_t pos,uint16_t reg)
{
	HAL_GPIO_WritePin(SS1_GPIO_Port,SS1_Pin,(pos & 0x1)?1:0);
	HAL_GPIO_WritePin(SS1_GPIO_Port,SS2_Pin,(pos & 0x2)?1:0);
	HAL_GPIO_WritePin(SS1_GPIO_Port,SS_EN_Pin,0);
	
	pos = Lp5860_x4_Read(hspi,reg);

	HAL_GPIO_WritePin(SS1_GPIO_Port,SS_EN_Pin,1);

	return pos;
}

HAL_StatusTypeDef Lp5860_Write(SPI_HandleTypeDef *hspi,uint8_t pos,uint16_t reg,uint8_t data)
{
	HAL_GPIO_WritePin(SS1_GPIO_Port,SS1_Pin,(pos & 0x1)?1:0);
	HAL_GPIO_WritePin(SS2_GPIO_Port,SS2_Pin,(pos & 0x2)?1:0);
	HAL_GPIO_WritePin(SS_EN_GPIO_Port,SS_EN_Pin,0);
	
	
	HAL_StatusTypeDef ret = Lp5860_x4_Write(hspi,reg,data);

	HAL_GPIO_WritePin(SS_EN_GPIO_Port,SS_EN_Pin,1);

	return ret;
}

HAL_StatusTypeDef Lp5860_Writes(SPI_HandleTypeDef *hspi,uint8_t pos,uint16_t reg,uint8_t* data,uint16_t size)
{
	HAL_GPIO_WritePin(SS1_GPIO_Port,SS1_Pin,(pos & 0x1)?1:0);
	HAL_GPIO_WritePin(SS2_GPIO_Port,SS2_Pin,(pos & 0x2)?1:0);
	HAL_GPIO_WritePin(SS_EN_GPIO_Port,SS_EN_Pin,0);
	
	
	HAL_StatusTypeDef ret = Lp5860_x4_Writes(hspi,reg,data,size);

	HAL_GPIO_WritePin(SS_EN_GPIO_Port,SS_EN_Pin,1);

	return ret;
}


HAL_StatusTypeDef LP5860_x4_Init(SPI_HandleTypeDef *hspi)
{
	HAL_GPIO_WritePin(VIO_EN_GPIO_Port,VIO_EN_Pin,0);
	HAL_Delay(1);
	HAL_GPIO_WritePin(VIO_EN_GPIO_Port,VIO_EN_Pin,1);
	HAL_Delay(1);
	for(uint8_t i = 0;i < 4;i++){
		// disable
		Lp5860_Write(hspi,i,LP5860_x4_REG_CFG_CHIP_EN,LP5860_x4_DEV_DISABLE);
		// reset
		Lp5860_Write(hspi,i,LP5860_x4_REG_CFG_RESET,LP5860_x4_DEV_RESET);
		HAL_Delay(1);
		// enable
		Lp5860_Write(hspi,i,LP5860_x4_REG_CFG_CHIP_EN,LP5860_x4_DEV_ENABLE);
		HAL_Delay(1);
		// mode 1 125kHz
		Lp5860_Write(hspi,i,LP5860_x4_REG_CFG_DEV_INITIAL,LP5860_x4_DEV_11L_MODE2_125K);
		// config1
		Lp5860_Write(hspi,i,LP5860_x4_REG_CFG_DEV_CONFIG1,LP5860_x4_DEV_LINEAR_CURVE);
		// config2
		// config3
		Lp5860_Write(hspi,i,LP5860_x4_REG_CFG_DEV_CONFIG3,LP5860_x4_DEV_CURR_3mA);
	}
	
	return HAL_OK;
}
