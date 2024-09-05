#include "oled.h"
#include "font.h"

static HAL_StatusTypeDef st;

HAL_StatusTypeDef OLED_Write_Cmds(uint8_t cmd)
{
	return HAL_I2C_Mem_Write(&hi2c2,0x78,0,I2C_MEMADD_SIZE_8BIT,&cmd,1,1000);
}

HAL_StatusTypeDef OLED_Write_Cmd(uint8_t* cmd,uint16_t size)
{
	return HAL_I2C_Mem_Write(&hi2c2,0x78,0x0,I2C_MEMADD_SIZE_8BIT,cmd,size,100);
}

HAL_StatusTypeDef OLED_Write_Datas(uint8_t data)
{
	return HAL_I2C_Mem_Write(&hi2c2,0x78,0x40,I2C_MEMADD_SIZE_8BIT,&data,1,1000);
}

HAL_StatusTypeDef OLED_Write_Data(uint8_t* data,uint16_t size)
{
	return HAL_I2C_Mem_Write(&hi2c2,0x78,0x40,I2C_MEMADD_SIZE_8BIT,data,size,100);
}

HAL_StatusTypeDef OLED_Display_Off(void)
{
	uint8_t Off_Cmd[] = {0X8D,0X10,0xAE};
	st = OLED_Write_Cmd(Off_Cmd,sizeof(Off_Cmd));
  return st;
}

HAL_StatusTypeDef OLED_Display_On(void)
{
	uint8_t On_Cmd[] = {0X8D,0X14,0XAF};
  return OLED_Write_Cmd(On_Cmd,sizeof(On_Cmd));
}

HAL_StatusTypeDef OLED_Raw_SetPos(uint8_t p,uint8_t c)
{
	uint8_t SP_Cmd[] = {c & 0xF,0x10 | ((c & 0xF0) >> 4),0xB0 + p};
  return OLED_Write_Cmd(SP_Cmd,sizeof(SP_Cmd));
}

HAL_StatusTypeDef OLED_Raw_Fill(uint8_t z)
{
	for(uint8_t i = 0;i < 4;i++)
	{
		if((st = OLED_Raw_SetPos(i,0)) != HAL_OK) return st;
		for(uint8_t j = 0;j<128;j++) if((st = OLED_Write_Datas(z)) != HAL_OK) return st;
	}
	return HAL_OK;
}

HAL_StatusTypeDef OLED_Raw_Clear(void)
{
	return OLED_Raw_Fill(0);
}

HAL_StatusTypeDef OLED_Fill(uint8_t map[4][128])
{
	for(uint8_t i = 0;i < 4;i++)
	{
		if((st = OLED_Raw_SetPos(i,0)) != HAL_OK) return st;
		if((st = OLED_Write_Data(map[i],sizeof(map[i]))) != HAL_OK) return st;
	}
	return HAL_OK;
}


HAL_StatusTypeDef OLED_Init(void)
{
	uint8_t gmap[4][128] = {0};
	
	HAL_GPIO_WritePin(GPIOB,GPIO_PIN_5,GPIO_PIN_RESET);// enable
	
	OLED_Display_Off();
	HAL_Delay(10);
	
	uint8_t cmd[] = 
	{
		0x00,0x10,0x00,0xB0,0x81,0x8F,0xA1,0xA8,
		0x1F,0xC8,0xD3,0x00,0xD5,0x80,0xD9,
		0x1F,0xDA,0x00,0xDB,0x40
	};
	OLED_Write_Cmd(cmd,sizeof(cmd));
	
	HAL_Delay(10);
	OLED_Fill(gmap);
	
	HAL_Delay(10);
	OLED_Display_On();
	return HAL_OK;
}


HAL_StatusTypeDef OLED_Raw_Draw(uint8_t p,uint8_t c,uint8_t d)
{
	if((st = OLED_Raw_SetPos(p,c)) != HAL_OK) return st;
	if((st = OLED_Write_Datas(d)) != HAL_OK) return st;
	return HAL_OK;
}

HAL_StatusTypeDef OLED_Raw_Draw_F(uint8_t p,uint8_t c,uint8_t i)
{
	if((st = OLED_Raw_SetPos(p,c)) != HAL_OK) return st;
	if((st = OLED_Write_Data(F6x8[i],6)) != HAL_OK) return st;
	return HAL_OK;
}

HAL_StatusTypeDef OLED_Raw_Draw_Char(uint8_t p,uint8_t c,uint8_t ch)
{
	if(ch < ' ' || ch > 'z'){
		ch = 0;
	}else if(ch < 'A'){
		ch = ch - ' ';
	}else if(ch < 'a'){
		ch = ch - 'A' + 33;
	}else ch = ch - 'a' + 65;
	
	return OLED_Raw_Draw_F(p,c,ch);
}

// ascii only
HAL_StatusTypeDef OLED_Raw_Draw_String(uint8_t p,uint8_t c,const char *str,uint8_t s)
{
	for(uint8_t i = 0;i < s;i++,c+=6) {
		if(c > 128 - 6) {
			c = 0;
			p++;
		}
		
		if((st = OLED_Raw_Draw_Char(p,c,str[i])) != HAL_OK) return st;
	}
	
	return HAL_OK;
}


