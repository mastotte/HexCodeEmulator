#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

#include "FileAnalyzerFile.h"
#include "BananaOS.h"

int main(int argc, char* argv[]){
    MEMORY BanMEM = MEMORY();
    CPU BanCPU = CPU();
    BananaOS mainOS = BananaOS(BanCPU, BanMEM);
    char* filename = argv[1];

    mainOS.openFile(filename);
    // get data size from 0x81f0
    // get where to store data in ram from 0x81ec
    // read data from address 0x81e4
    mainOS.dataLoad();

    // initialize stack pointer to 0x6000
    mainOS.registerSet(29, 0x6000);

    mainOS.setup();

    mainOS.loop();
// setup
// check to see if the program counter reaches 0, if it reaches 0 breakout
// loop
// different after pc reaches 0 go back to the top of the loop 

}
