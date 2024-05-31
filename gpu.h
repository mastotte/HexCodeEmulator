
#pragma once
#include <SDL2/SDL.h>   
#include "memory.h"
#include <memory>


#define CONTROLLER_INPUT_MEMORY (0x7000)

class GPU{
private:
    MEMORY& memory;
    //framebuffer here?
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int* pixels = new int[64*64];
    int SCREEN_WIDTH = 64;
    int SCREEN_HEIGHT = 64;
    int color = 0;
public:
    GPU(MEMORY& memory): memory(memory){}

    void quit();
    
    void init();

    //void handleInput();

    int getPixelAddress(int width, int height);

    void setPixel(int x, int y, int color); //value will be 1 or 0

    void decodeAndDisplay();

    void clearFrameBuffer();
};
