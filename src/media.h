#ifndef MEDIA_H
#define MEDIA_H

#include <stdint.h>

// カメラ用 (簡易的に64x64ピクセルのRGB)
#define CAM_WIDTH 64
#define CAM_HEIGHT 64
extern uint8_t camera_buffer[CAM_WIDTH * CAM_HEIGHT * 3];

// マイク用 (オーディオバッファ)
#define AUDIO_BUFFER_SIZE 1024
extern float audio_buffer[AUDIO_BUFFER_SIZE];

void media_init();
#endif
