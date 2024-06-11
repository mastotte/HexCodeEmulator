#include "memory.h"

MEMORY::MEMORY() : memory(0x16000, 0) {}

// addresses should be 16 bit ints

void MEMORY::fileReader(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  std::streamsize size = file.tellg();
  file.seekg(0, std::ios::beg);

  if (size > SLUG_ADDRESS_HEADER) {
    std::cerr << "File too large to fit in memory." << std::endl;
    file.close();
    return;
  }
  if (!file.read(&memory[SLUG_ADDRESS_HEADER], size)) {
    std::cerr << "Error reading file: " << filename << std::endl;
  }

  file.close();
}

uint32_t MEMORY::readAddress(const size_t& addr) const {
  uint32_t out = 0;
  for (int i = 0; i < 4; i++) {
    out <<= 8;
    // out |= static_cast<uint8_t>(memory[addr + i]);
    out |= (uint8_t)memory[addr + i];
  }
  return out;
}

uint8_t MEMORY::read8(uint16_t address) {
  if (address == DEBUG_STDIN_ADDRESS) {
    char c;
    std::cin >> c;
    memory[address] = static_cast<uint8_t>(c);
    return memory[address];
  } else {
    return static_cast<uint8_t>(memory[address]);
  }
}

uint16_t MEMORY::read16(uint16_t address) {
  return (memory[address] << 8) | memory[address + 1];
}

void MEMORY::write8(uint16_t address, uint8_t data) {
  memory[address] = data;
  if (address == DEBUG_STDOUT_ADDRESS) {
    std::cout << data;
  } else if (address == DEBUG_STDERR_ADDRESS) {
    std::cerr << data;
  } else if (address == EXIT_ADDRESS) {
    exit(EXIT_SUCCESS);
  }
}

void MEMORY::write16(uint16_t address, uint16_t data) {
  memory[address] = data >> 8;
  memory[address + 1] = data;
  if (address == DEBUG_STDOUT_ADDRESS) {
    std::cout << data;
  } else if (address == DEBUG_STDERR_ADDRESS) {
    std::cerr << data;
  } else if (address == EXIT_ADDRESS) {
    exit(EXIT_SUCCESS);
  }
}
