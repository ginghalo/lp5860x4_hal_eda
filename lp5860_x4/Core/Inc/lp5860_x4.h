#ifndef __LP5860_X4_H__
#define __LP5860_X4_H__
#include "main.h"
#include "spi.h"

#define LP5860_x4_REG_CFG_CHIP_EN (0x0)
#define LP5860_x4_REG_CFG_DEV_INITIAL (0x1)
#define LP5860_x4_REG_CFG_DEV_CONFIG1 (0x2)
#define LP5860_x4_REG_CFG_DEV_CONFIG2 (0x3)
#define LP5860_x4_REG_CFG_DEV_CONFIG3 (0x4)
#define LP5860_x4_REG_CFG_R_CUR_SET (0x9)
#define LP5860_x4_REG_CFG_G_CUR_SET (0xA)
#define LP5860_x4_REG_CFG_B_CUR_SET (0xB)
#define LP5860_x4_REG_CFG_DOT_GRP_SEL0 (0xC)
#define LP5860_x4_REG_CFG_DOT_GRP_SEL1 (0xD)
#define LP5860_x4_REG_CFG_DOT_GRP_SEL2 (0xE)
#define LP5860_x4_REG_CFG_DOT_GRP_SEL3 (0xF)
#define LP5860_x4_REG_CFG_DOT_GRP_SEL4 (0x10)
#define LP5860_x4_REG_CFG_FAULT_STATE (0x64)
#define LP5860_x4_REG_CFG_LOD_CLEAR (0xA7)
#define LP5860_x4_REG_CFG_LSD_CLEAR (0xA7)
#define LP5860_x4_REG_CFG_RESET (0xA9)

#define LP5860_x4_REG_DC(x) ((0x100) | (x))
#define LP5860_x4_REG_PWM_BRI(x) ((0x200) | (x))

#define LP5860_x4_DEV_DISABLE (0x0)
#define LP5860_x4_DEV_ENABLE (0x1)

#define LP5860_x4_DEV_RESET (0xFF)

#define LP5860_x4_DEV_LINEAR_CURVE (0x0)
#define LP5860_x4_DEV_EXP_CURVE (0x4)

#define LP5860_x4_DEV_11L_MODE1_125K (0x58)
#define LP5860_x4_DEV_11L_MODE2_125K (0x5A)
#define LP5860_x4_DEV_11L_MODE3_125K (0x5C)

#define LP5860_x4_DEV_CURR_20mA (0x59)
#define LP5860_x4_DEV_CURR_3mA (0x51)


HAL_StatusTypeDef Lp5860_Write(SPI_HandleTypeDef *hspi,uint8_t pos,uint16_t reg,uint8_t data);
HAL_StatusTypeDef Lp5860_Writes(SPI_HandleTypeDef *hspi,uint8_t pos,uint16_t reg,uint8_t* data,uint16_t size);
uint8_t Lp5860_Read(SPI_HandleTypeDef *hspi,uint8_t pos,uint16_t reg);
HAL_StatusTypeDef LP5860_x4_Init(SPI_HandleTypeDef *hspi);

#endif