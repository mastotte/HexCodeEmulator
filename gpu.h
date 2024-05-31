
#pragma once
#include <SDL2/SDL.h>
#include "memory.h"
#include <memory>

class GPU{
private:
    MEMORY& memory;
    //framebuffer here?
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int* pixels = new int[64 * 64];
    const int SCREEN_WIDTH = 64;
    const int SCREEN_HEIGHT = 64;
public:
    GPU(MEMORY& memory): memory(memory){}

    void init();

    int getPixelAddress(int width, int height);

    void setPixel(int address, int value); //value will be 1 or 0

    void decodeAndDisplay();

    void clearFrameBuffer();
};
