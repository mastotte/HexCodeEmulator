
#pragma once
#include <SDL2/SDL.h>

#include <memory>
#include <unordered_map>

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
  SDL_Texture* tex;
  int box_X = 0;
  int box_Y = 0;
  int box_Size = 10;
  int color = 0;

  std::unordered_map<SDL_Keycode, bool> keyStates = {
      {SDLK_UP, false},     {SDLK_DOWN, false}, {SDLK_LEFT, false},
      {SDLK_RIGHT, false},  {SDLK_a, false},    {SDLK_b, false},
      {SDLK_RETURN, false}, {SDLK_SPACE, false}};

  std::unordered_map<SDL_Keycode, uint8_t> keyMasks = {
      {SDLK_UP, CONTROLLER_UP_MASK},
      {SDLK_DOWN, CONTROLLER_DOWN_MASK},
      {SDLK_LEFT, CONTROLLER_LEFT_MASK},
      {SDLK_RIGHT, CONTROLLER_RIGHT_MASK},
      {SDLK_a, CONTROLLER_A_MASK},
      {SDLK_b, CONTROLLER_B_MASK},
      {SDLK_RETURN, CONTROLLER_START_MASK},
      {SDLK_SPACE, CONTROLLER_SELECT_MASK}};

  uint8_t controllerInput = 0;

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

  void decodeAndDisplay();

  void clearFrameBuffer();

  void updateControllerInput();
};
