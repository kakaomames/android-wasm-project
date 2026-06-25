#include "media.h"
#include <string.h>

uint8_t camera_buffer[CAM_WIDTH * CAM_HEIGHT * 3];
float audio_buffer[AUDIO_BUFFER_SIZE];

void media_init() {
    memset(camera_buffer, 0, sizeof(camera_buffer));
    memset(audio_buffer, 0, sizeof(audio_buffer));
}
