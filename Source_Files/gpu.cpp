#include "gpu.h"

#include <SDL2/SDL.h>

#include <memory>

#include "memory.h"
#define SIZE 10

const int BOX_SIZE = 64;

void GPU::init() {
  GPU::clearFrameBuffer();
  window = SDL_CreateWindow("SDL Box", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * SIZE,
                            SCREEN_HEIGHT * SIZE, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  SDL_RenderPresent(renderer);
};

void GPU::quit() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
};

int GPU::getPixelAddress(const int width, const int height) {
  const int pixel_index = width + (height * 64);
  const int pixel_offset = 1 * pixel_index;
  return 0x6000 + pixel_offset;
};

void GPU::decodeAndDisplay(){
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
  for (int height = 0; height < SCREEN_HEIGHT; height++){
    for (int width = 0; width < SCREEN_WIDTH; width++){
      int pixAdd = getPixelAddress(width, height);
      int pixVal = memory.read8(pixAdd);
        if (pixVal) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        // }
        } else {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        }
        for (int i = 0; i < SIZE; i++){
          for (int j = 0; j < SIZE;j++){
            SDL_RenderDrawPoint(renderer, (width * SIZE) + j, (height * SIZE) + i);
          }
        }
                  
    }
  }
  SDL_RenderPresent(renderer);
}

void GPU::clearFrameBuffer() {
  memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
};

void GPU::handleInput() {
  SDL_Event event;
  uint8_t controllerInput = 0;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      exit(EXIT_SUCCESS);
    }
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
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
