#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

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

class MEMORY {
 private:
  std::vector<char> memory;

 public:
  MEMORY();
  // MEMORY(const MEMORY& other);

  void fileReader(const std::string& filename);
  uint32_t readAddress(const size_t& addr) const;

  uint8_t read8(uint32_t address);
  uint16_t read16(uint32_t address);

  void write8(uint32_t address, uint8_t data);
  void write16(uint32_t address, uint16_t data);
};

#endif  // MEMORY_H