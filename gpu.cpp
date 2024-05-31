#include <SDL2/SDL.h>
#include "gpu.h"
#include "memory.h"
#include <memory>
const int BOX_SIZE = 64;
void GPU::init(){
    GPU::clearFrameBuffer();
    
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    SDL_Init(SDL_INIT_VIDEO);
    
    
    
}
void GPU::quit(){
    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int GPU::getPixelAddress(int width, int height){

    int pixel_index = width + (height * 64);
    int pixel_offset = 1 * pixel_index;
    return 0x6000 + pixel_offset;
};

void GPU::setPixel(int x, int y, int color) {
    
    if (color == 0){
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
    }else{
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    }
    SDL_RenderDrawPoint(renderer, x, y);

    // Render present
    SDL_RenderPresent(renderer);
};

void GPU::decodeAndDisplay(){
    std::cout<<" "<<std::endl;
    window = SDL_CreateWindow("SDL Box", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //add code here   
    
    // Render present
    SDL_RenderPresent(renderer);
    for(int h = 0; h < SCREEN_HEIGHT; h++){
        for(int w = 0; w < SCREEN_WIDTH; w++){
            int pixel_address = getPixelAddress(w, h);
            int value = memory.read8(pixel_address);
            setPixel(w, h, value);
        } 
    }


};

void GPU::clearFrameBuffer(){
    //add code here
    memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
};

void GPU::handleInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            exit(EXIT_SUCCESS);
        }
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
            int8_t controllerInput = 0;
            switch (event.key.keysym.sym) {
                case SDLK_UP:
                    controllerInput = CONTROLLER_UP_MASK;
                    break;
                case SDLK_DOWN:
                    controllerInput = CONTROLLER_DOWN_MASK;
                    break;
                case SDLK_LEFT:
                    controllerInput = CONTROLLER_LEFT_MASK;
                    break;
                case SDLK_RIGHT:
                    controllerInput = CONTROLLER_RIGHT_MASK;
                    break;
                case SDLK_a:
                    std::cout << CONTROLLER_A_MASK << std::endl; 
                    controllerInput = CONTROLLER_A_MASK;
                    break;
                case SDLK_b:
                    controllerInput = CONTROLLER_B_MASK;
                    break;
                case SDLK_RETURN:
                    controllerInput = CONTROLLER_START_MASK;
                    break;
                case SDLK_SPACE:
                    controllerInput = CONTROLLER_SELECT_MASK;
                    break;
                default:
                    break;
            }
            memory.write8(CONTROLLER_INPUT_MEMORY, controllerInput);
        }
    }
}
/*
int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Quit();
    return 0;
}
void GPU::setPixel(SDL_Renderer *renderer, int x, int y, int color) {
    if (color == 1) {
        std::cout<<"white";
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
    } else {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black
    }
    SDL_RenderDrawPoint(renderer, x, y);
}

void GPU::decodeAndDisplay(){
    //add code here

    /*SDL_GetWindowSize(window, &SCREEN_WIDTH, &SCREEN_HEIGHT);
    SDL_DestroyTexture(texture);
    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);
    //color = (color == 0) ? 1 : 0;
    
    for(int h = 0; h < SCREEN_HEIGHT; h++){
        for(int w = 0; w < SCREEN_WIDTH; w++){
            
            std::cout<<pixel_address<<std::endl;
            setPixel(renderer, w, h, 1);
        } 
    }

    /*SDL_UpdateTexture(texture, nullptr, pixels, SCREEN_WIDTH * sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);

    


};*/
