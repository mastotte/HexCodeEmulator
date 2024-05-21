// Ideally, you should have a class that acts like the OS and runs the reset sequence, as well as a class that is in charge of handling the memory.


// read and write functions
#include "memory.h"

uint16_t MEMORY::read16(uint32_t address){
    return (memory[address] << 8) | memory[address + 1];
}

uint8_t MEMORY::read8(uint32_t address){
    
    char c;
    if (address == 0x7100){
        std::cin >> c; 
        return c;
    }
    else{
        return memory[address];
    }
    
}


void MEMORY::write8(uint32_t address, uint8_t data){
    memory[address] = data;
    if (address == 0x7110) {
        std::cout << data;
    }
    else if (address == 0x7120) {
        std::cerr << data;
    }
    else if (address == 0x7200) {
        exit(EXIT_SUCCESS);
        // std::cout << data;
        
    }
}

void MEMORY::write16(uint32_t address, uint16_t data){
    memory[address] = data >> 8;
    memory[address + 1] = data; 
    if (address == 0x7110) {
        std::cout << data;
    }
    else if (address == 0x7120) {
        std::cerr << data;
    }
    else if (address == 0x7200) {
        exit(EXIT_SUCCESS);
        // std::cout << data;
    }
}


// File analyzer functions changed into cpu versions
void MEMORY::FileAnalyzerFile(const std::string& filename){
    // Open the file
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    // Check if file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
/*
Note the .slug file size is ALWAYS 0x8000 bytes in size per Ben's email. 
We also don't need to seek to the beginning.
*/

    
    // Allocate memory to store the contents of the file
    // std::unique_ptr<char[]> contents;
    memory = std::make_unique<char[]>(0x8000);
    
    // stores value (displays differently based on computer), 1 byte in each index) actually reading in 4 at a time (the actual instruction)
    // Read the contents of the file into the allocated memory
    file.read((memory.get() + 0x8000), 0x8000);
    // Close the file
    file.close();
}

uint32_t MEMORY::ReadBigEndianInt32(const size_t& addr) const {
  uint32_t out = 0;
  for (int i = 0; i < 4; i++) {
    out <<= 8;
    out |= (uint8_t)memory[addr + i];
  }
  return out;
}