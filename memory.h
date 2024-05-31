#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <vector>

class MEMORY {
private:
    std::vector<char> memory;

public:
    MEMORY();
    MEMORY(const MEMORY& other);

    void fileReader(const std::string& filename);
    uint32_t readAddress(const size_t& addr) const;

    uint8_t read8(uint32_t address);
    uint16_t read16(uint32_t address);

    void write8(uint32_t address, uint8_t data);
    void write16(uint32_t address, uint16_t data);
};

#endif // MEMORY_H

