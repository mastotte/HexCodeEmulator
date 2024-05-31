#include <SDL2/SDL.h>
#include "gpu.h"

GPU::GPU(){
    GPU::clearFrameBuffer();
}

int getPixelAddress(int width, int height){
    int pixel_index = width + (height * 64);
    int pixel_offset = 1 * pixel_index;
    return 0x6000 + pixel_offset;

};

void setPixel(int address, int value){ //value will be 1 or 0
    //add code here
}

void decodeAndDisplay(){
    //add code here
};

void clearFrameBuffer(){
    //add code here
};


/*
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}
*/