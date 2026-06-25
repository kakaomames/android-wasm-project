#include "gpu.h"

uint8_t vram[SCREEN_WIDTH * SCREEN_HEIGHT * 4];

void gpu_init() {
    // VRAMを真っ黒に初期化
    for(int i = 0; i < sizeof(vram); i++) vram[i] = 0;
}

void gpu_draw_pixel(int x, int y, uint8_t r, uint8_t g, uint8_t b) {
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;
    int offset = (y * SCREEN_WIDTH + x) * 4;
    vram[offset] = r;
    vram[offset+1] = g;
    vram[offset+2] = b;
    vram[offset+3] = 255; // Alpha
}
