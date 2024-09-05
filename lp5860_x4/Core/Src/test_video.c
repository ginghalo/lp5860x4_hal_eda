#include "test_video.h"
#include "lp5860_x4.h"
#include "q64.h"

uint8_t frame[792] = {0};
void read_frame_data(uint32_t count)
{
	W25Q64_Read(&hspi1,count*792,frame,792);
}

uint8_t first_frame_data(void)
{
	return frame[0];
}

void play_test_video(uint32_t count)
{
	for(uint8_t i = 0;i < 4;i++)
	{
		Lp5860_Writes(&hspi2,i,LP5860_x4_REG_PWM_BRI(0),&frame[i*198],198);
	}
}
