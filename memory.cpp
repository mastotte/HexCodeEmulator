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
