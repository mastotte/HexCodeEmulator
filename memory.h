// Ideally, you should have a class that acts like the OS and runs the reset sequence, as well as a class that is in charge of handling the memory.



// Ideally, you should have a class that acts like the OS and runs the reset sequence, as well as a class that is in charge of handling the memory.
#ifndef MEMORY_H
#define MEMORY_H
#include <cstdint>
#include <fstream>
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>

class MEMORY {
private:
    char* memory = new char[0x16000];

public:
    MEMORY() {
    }
    MEMORY(const MEMORY& other) {
        memory = other.memory;
    }

    void fileReader(const std::string& filename);
    uint32_t readAddress(const size_t& addr) const;

    uint8_t read8(uint32_t address);
    uint16_t read16(uint32_t address);

    void write8(uint32_t address, uint8_t data);
    void write16(uint32_t address, uint16_t data);

};


#endif
