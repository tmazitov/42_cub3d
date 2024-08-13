#define MINIAUDIO_IMPLEMENTATION
#include "./miniaudio/miniaudio.h"

#include <stdio.h>

int main(void) {
    ma_result result;
    ma_engine engine;

    // Initialize the engine
    result = ma_engine_init(NULL, &engine);
    if (result != MA_SUCCESS) {
        printf("Failed to initialize audio engine.\n");
        return -1;
    }

    // Play the sound
    result = ma_engine_play_sound(&engine, "cub3d_gun_shot_sound.wav", NULL);
    if (result != MA_SUCCESS) {
        printf("Failed to play sound.\n");
        ma_engine_uninit(&engine);
        return -1;
    }

    // Wait until the sound finishes playing
    ma_sleep(1000);

    // Clean up
    ma_engine_uninit(&engine);
}
