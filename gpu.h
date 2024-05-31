
#pragma once
#include <SDL2/SDL.h>   
#include "memory.h"
#include <memory>


#define CONTROLLER_A_MASK ((int8_t)0x80)
#define CONTROLLER_B_MASK ((uint8_t)0x40)
#define CONTROLLER_SELECT_MASK ((uint8_t)0x20)
#define CONTROLLER_START_MASK ((uint8_t)0x10)
#define CONTROLLER_UP_MASK ((uint8_t)0x08)
#define CONTROLLER_DOWN_MASK ((uint8_t)0x04)
#define CONTROLLER_LEFT_MASK ((uint8_t)0x02)
#define CONTROLLER_RIGHT_MASK ((uint8_t)0x01)

#define CONTROLLER_INPUT_MEMORY (0x7000)

#define CONTROLLER_A_MASK ((uint8_t)0x80)
#define CONTROLLER_B_MASK ((uint8_t)0x40)
#define CONTROLLER_SELECT_MASK ((uint8_t)0x20)
#define CONTROLLER_START_MASK ((uint8_t)0x10)
#define CONTROLLER_UP_MASK ((uint8_t)0x08)
#define CONTROLLER_DOWN_MASK ((uint8_t)0x04)
#define CONTROLLER_LEFT_MASK ((uint8_t)0x02)
#define CONTROLLER_RIGHT_MASK ((uint8_t)0x01)

#define CONTROLLER_INPUT_MEMORY (0x7000)

class GPU{
private:
    MEMORY& memory;
    //framebuffer here?
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
    int* pixels = new int[2000 * 2000];
    int SCREEN_WIDTH = 64;
    int SCREEN_HEIGHT = 64;
public:
    GPU(MEMORY& memory): memory(memory){}

    void init();

    void handleInput();

    int getPixelAddress(int width, int height);

    void setPixel(int address, int value); //value will be 1 or 0

    void decodeAndDisplay();

    void clearFrameBuffer();

    void handleInput(); 
};
