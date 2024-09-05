#ifndef __TEST_VIDEO_H__
#define __TEST_VIDEO_H__
#include "main.h"
#include "spi.h"
#define TEST_VIDEO_FRAME_COUNT (5010)
void read_frame_data(uint32_t count);
void play_test_video(uint32_t count);
uint8_t first_frame_data(void);
#endif