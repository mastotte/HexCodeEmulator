#include "gpu.h"

#include <SDL2/SDL.h>

#include <memory>

#include "memory.h"
const int BOX_SIZE = 64;
void GPU::init() {
  GPU::clearFrameBuffer();
  window = SDL_CreateWindow("SDL Box", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * 10,
                            SCREEN_HEIGHT * 10, SDL_WINDOW_SHOWN);
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  SDL_Init(SDL_INIT_VIDEO);
  drawBox(box_Size);

  // Present the renderer
  SDL_RenderPresent(renderer);
};

void GPU::quit() {
  // Clean up
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
};

int GPU::getPixelAddress(const int width, const int height) {
  const int pixel_index = width + (height * 64);
  const int pixel_offset = 1 * pixel_index;
  return 0x6000 + pixel_offset;
};

void GPU::drawBox(const int size) {
  // Set the color of the box based on the value of 'color'
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

  // Define the dimensions of the box
  SDL_Rect boxRect = {box_X, box_Y, size, size};

  // Draw the box on the renderer
  SDL_RenderFillRect(renderer, &boxRect);
}

void GPU::eraseBox(const int size) {
  // Set the color of the box based on the value of 'color'
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  // Define the dimensions of the box
  SDL_Rect boxRect = {box_X, box_Y, size, size};

  // Draw the box on the renderer
  SDL_RenderFillRect(renderer, &boxRect);
}

void GPU::resizeBox(bool larger) {
  eraseBox(box_Size);
  if (larger) {
    box_Size += 5;
    drawBox(box_Size);
  } else {
    box_Size -= 5;
    drawBox(box_Size);
  }
}

void GPU::moveBox(uint8_t const direction) {
  eraseBox(box_Size);
  if (direction == CONTROLLER_RIGHT_MASK) {
    if (box_Size + box_X < SCREEN_WIDTH) {
      box_X += 1;
    }
    drawBox(box_Size);
  } else if (direction == CONTROLLER_LEFT_MASK) {
    if (box_X > 0) {
      box_X -= 1;
    }
    drawBox(box_Size);
  } else if (direction == CONTROLLER_UP_MASK) {
    if (box_Y > 0) {
      box_Y -= 1;
    }
    drawBox(box_Size);
  } else if (direction == CONTROLLER_DOWN_MASK) {
    if (box_Y + box_Size < SCREEN_HEIGHT) {
      box_Y += 1;
    }
    drawBox(box_Size);
  }
}

void GPU::setPixel(const int x, const int y, const int color) {
  if (color == 0) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black
  } else {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);  // White
  }
  SDL_RenderDrawPoint(renderer, x, y);

  // Render present
  SDL_RenderPresent(renderer);
};

void GPU::decodeAndDisplay() {
  SDL_RenderPresent(renderer);
  for (int h = 0; h < SCREEN_HEIGHT; h++) {
    // std::cout<<h<<std::endl;
    for (int w = 0; w < SCREEN_WIDTH; w++) {
      int pixel_address = getPixelAddress(w, h);
      int value = memory.read8(pixel_address);
      if (value != 0) setPixel(w, h, value);
    }
  }
};

void GPU::clearFrameBuffer() {
  // add code here
  memset(pixels, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
};

void GPU::handleInput() {
  SDL_Event event;
  int16_t controllerInput = 0;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      exit(EXIT_SUCCESS);
    }
    if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      controllerInput = 0;
      switch (event.key.keysym.sym) {
        case SDLK_UP:
          controllerInput = CONTROLLER_UP_MASK;
          moveBox(controllerInput);
          break;
        case SDLK_DOWN:
          controllerInput = CONTROLLER_DOWN_MASK;
          moveBox(controllerInput);
          break;
        case SDLK_LEFT:
          controllerInput = CONTROLLER_LEFT_MASK;
          moveBox(controllerInput);
          break;
        case SDLK_RIGHT:
          controllerInput = CONTROLLER_RIGHT_MASK;
          moveBox(controllerInput);
          break;
        case SDLK_a:
          resizeBox(true);
          controllerInput = CONTROLLER_A_MASK;
          break;
        case SDLK_b:
          resizeBox(false);
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
