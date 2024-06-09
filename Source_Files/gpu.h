
#pragma once
#include <SDL2/SDL.h>

#include <memory>

#include "memory.h"

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

class GPU {
 private:
  MEMORY& memory;
  // framebuffer here?
  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_Texture* texture;
  int* pixels = new int[64 * 64];
  const int SCREEN_WIDTH = 64;
  const int SCREEN_HEIGHT = 64;
  SDL_Texture *tex;
  int box_X = 0;
  int box_Y = 0;
  int box_Size = 10;
  int color = 0;

 public:
  GPU(MEMORY& memory) : memory(memory) {}

  void quit();

  void init();

  void handleInput();

  int getPixelAddress(const int width, const int height);

  void drawBox(const int size);

  void eraseBox(const int size);

  void moveBox(uint8_t const direction);

  void resizeBox(bool larger);

  // void setPixel(const int x, const int y,
  //               const int color);  // value will be 1 or 0
  // void setPixel(SDL_Texture *texture, int x, int y, Uint32 color);

  void decodeAndDisplay();

  void clearFrameBuffer();
};
