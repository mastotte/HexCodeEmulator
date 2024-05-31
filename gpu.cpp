#include <SDL2/SDL.h>
#include "gpu.h"
#include "memory.h"
#include <memory>

void GPU::init(){
    std::cout<<"check 2"<<std::endl;
    GPU::clearFrameBuffer();
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("SDL Blank Window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH, SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    decodeAndDisplay();
}

int GPU::getPixelAddress(int width, int height){
    //std::cout<<"Width: "<<width<<"  Height: "<<height<<std::endl;
    int pixel_index = width + (height * 64);
    int pixel_offset = 1 * pixel_index;
    return 0x6000 + pixel_offset;

};

void GPU::setPixel(int address, int value){ //value will be 1 or 0
    //add code here
    pixels[address] = value;
}

void GPU::decodeAndDisplay(){
    //add code here

    for(int h = 0; h < SCREEN_HEIGHT; h++){
        for(int w = 0; w < SCREEN_WIDTH; w++){
            int pixel_address = getPixelAddress(w, h);
            int value = memory.read8(pixel_address);
            //std::cout<<pixel_address<<std::endl;
            //std::cout<<value;
            setPixel(w + (h * 64), value);
        }
        
    }
    //std::cout<<"c1"<<std::endl;
    SDL_UpdateTexture(texture, nullptr, pixels, SCREEN_WIDTH * sizeof(Uint32));
    //std::cout<<"c2"<<std::endl;
    SDL_RenderClear(renderer);
    //std::cout<<"c3"<<std::endl;
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    //std::cout<<"c4"<<std::endl;
    SDL_RenderPresent(renderer);
    //std::cout<<"c5"<<std::endl;
};

void GPU::clearFrameBuffer(){
    //add code here
    memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
};


/*
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}
*/