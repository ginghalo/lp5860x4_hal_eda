#include "main.h"
#include "spi.h"

HAL_StatusTypeDef Lp5861_Func(void)
{
	return HAL_OK;
}


uint8_t Lp5860_x4_Read_CFG(I2C_HandleTypeDef *hspi,uint8_t sub_addr,uint8_t reg_cfg)
{
	uint8_t data = 0xFF;
	HAL_SPI_Mem_Read(hspi,LP5860_x4_ADDR(sub_addr,LP5860_x4_ADDR_CFG),reg_cfg,I2C_MEMADD_SIZE_8BIT,&data,1,100);
	return data;
}

uint8_t Lp5860_x4_Read_DC(I2C_HandleTypeDef *hspi,uint8_t sub_addr,uint8_t reg_cfg)
{
	uint8_t data = 0xFF;
	HAL_I2C_Mem_Read(hspi,LP5860_x4_ADDR(sub_addr,LP5860_x4_ADDR_DC),reg_cfg,I2C_MEMADD_SIZE_8BIT,&data,1,100);
	return data;
}

HAL_StatusTypeDef Lp5860_x4_Read_PWM(I2C_HandleTypeDef *hspi,uint8_t sub_addr,uint8_t reg_dc)
{
	uint8_t data = 0xFF;
	HAL_I2C_Mem_Write(hspi,LP5860_x4_ADDR(sub_addr,LP5860_x4_ADDR_PWM),reg_dc,I2C_MEMADD_SIZE_8BIT,&data,1,100);
	return data;
}

HAL_StatusTypeDef Lp5860_x4_Write_CFG(I2C_HandleTypeDef *hspi,uint8_t sub_addr,uint8_t reg_cfg,uint8_t data)
{
	return HAL_I2C_Mem_Write(hspi,LP5860_x4_ADDR(sub_addr,LP5860_x4_ADDR_CFG),reg_cfg,I2C_MEMADD_SIZE_8BIT,&data,1,100);
}

HAL_StatusTypeDef Lp5860_x4_Write_DC(I2C_HandleTypeDef *hspi,uint8_t sub_addr,uint8_t reg_dc,uint8_t data)
{
	return HAL_I2C_Mem_Write(hspi,LP5860_x4_ADDR(sub_addr,LP5860_x4_ADDR_DC),reg_dc,I2C_MEMADD_SIZE_8BIT,&data,1,100);
}

HAL_StatusTypeDef Lp5860_x4_Write_PWM(I2C_HandleTypeDef *hspi,uint8_t sub_addr,uint8_t reg_dc,uint8_t data)
{
	return HAL_I2C_Mem_Write(hspi,LP5860_x4_ADDR(sub_addr,LP5860_x4_ADDR_PWM),reg_dc,I2C_MEMADD_SIZE_8BIT,&data,1,100);
}

HAL_StatusTypeDef LP5860_x4_Init(void)
{
	HAL_GPIO_WritePin(VIO_EN_GPIO_Port,VIO_EN_Pin,0);
	HAL_Delay(1);
	HAL_GPIO_WritePin(VIO_EN_GPIO_Port,VIO_EN_Pin,1);
	HAL_Delay(1);
	
	return HAL_OK;
}
