#ifndef BananaOS_H
#define BananaOS_H

#include <cstdint>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <unordered_map>

#include "cpu.h"
#include "gpu.h"
#include "memory.h"

#define SLUG_ADDRESS_HEADER 0x8000
#define DEBUG_STDIN_ADDRESS 0x7100
#define DEBUG_STDOUT_ADDRESS 0x7110
#define DEBUG_STDERR_ADDRESS 0x7120
#define EXIT_ADDRESS 0x7200
#define PC_RESET 0xfffc
#define DATA_SIZE 0x81f0
#define PROGRAM_DATA_ADDR_RAM 0x81ec
#define LOAD_DATA_ADDR_ROM 0x81e8
#define ADDR_TO_LOOP 0x81e4
#define ADDR_TO_SETUP 0x81e0

class BananaOS {
 private:
  CPU bananaCPU;
  MEMORY bananaMEM;
  GPU bananaGPU;
  std::string filename;

 public:
  BananaOS() : bananaMEM(), bananaCPU(bananaMEM), bananaGPU(bananaMEM) {}

  void openFile(const std::string& name);

  void dataLoad();

  void setup();

  void loop();

  void doInstruction();

  void registerSet(int regNum, int value);

  void startup(char* filename);

  std::unordered_map<int, uint8_t> CharacterMaskMap = {
      {7, CONTROLLER_A_MASK},      {6, CONTROLLER_B_MASK},
      {5, CONTROLLER_SELECT_MASK}, {4, CONTROLLER_START_MASK},
      {3, CONTROLLER_UP_MASK},     {2, CONTROLLER_DOWN_MASK},
      {1, CONTROLLER_LEFT_MASK},   {0, CONTROLLER_RIGHT_MASK}};
};

#endif  // BananaOS_H
