#ifndef BananaOS_H
#define BananaOS_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>
#include "cpu.h"
#include "memory.h"

class BananaOS {
private:
    CPU bananaCPU;
    MEMORY bananaMEM;
    std::string filename;

public:
    BananaOS() 
    : bananaMEM(), bananaCPU(bananaMEM){}

    void openFile(const std::string& name);

    void dataLoad();

    void setup();

    void loop();

    void doInstruction();

    void registerSet(int regNum, int value);
};

#endif // BananaOS_H
