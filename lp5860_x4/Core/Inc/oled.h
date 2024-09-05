#ifndef __OLED_H
#define __OLED_H
#include "main.h"
#include "i2c.h"

HAL_StatusTypeDef OLED_Write_Cmds(uint8_t cmd);
HAL_StatusTypeDef OLED_Write_Cmd(uint8_t* cmd,uint16_t size);
HAL_StatusTypeDef OLED_Write_Datas(uint8_t data);
HAL_StatusTypeDef OLED_Write_Data(uint8_t* data,uint16_t size);
HAL_StatusTypeDef OLED_Init(void);
HAL_StatusTypeDef OLED_Display_On(void);
HAL_StatusTypeDef OLED_Display_Off(void);
HAL_StatusTypeDef OLED_Raw_SetPos(uint8_t p,uint8_t c);
HAL_StatusTypeDef OLED_Raw_Fill(uint8_t z);
HAL_StatusTypeDef OLED_Raw_Draw(uint8_t p,uint8_t c,uint8_t d);
HAL_StatusTypeDef OLED_Clear(void);
HAL_StatusTypeDef OLED_Raw_Draw_F(uint8_t p,uint8_t c,uint8_t i);
HAL_StatusTypeDef OLED_Raw_Draw_Char(uint8_t p,uint8_t c,uint8_t ch);
HAL_StatusTypeDef OLED_Raw_Draw_String(uint8_t p,uint8_t c,const char *str,uint8_t s);

#include "stdio.h"
#include "string.h"

#define OLED_PRINT(p,c,str,s,fmt,...) \
do{\
		memset(str,0,s);\
		sprintf(str,fmt,##__VA_ARGS__);\
		OLED_Raw_Draw_String(p,c,str,s);\
}while(0);

#endif
