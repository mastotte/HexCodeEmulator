// Ideally, you should have a class that acts like the OS and runs the reset sequence, as well as a class that is in charge of handling the memory.
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

public:
    void dataLoad();

    void setup();

    void loop();

    void doInstruction();

};


#endif
