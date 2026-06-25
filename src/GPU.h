#ifndef GPU_H
#define GPU_H

#include <stdint.h>

#define SCREEN_WIDTH 256
#define SCREEN_HEIGHT 256

// VRAM：ここに画素データを書き込む
extern uint8_t vram[SCREEN_WIDTH * SCREEN_HEIGHT * 4];

void gpu_init();
void gpu_draw_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b);

#endif
