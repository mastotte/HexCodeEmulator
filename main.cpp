#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

#include "FileAnalyzerFile.h"
#include "cpu.h"

int main(int argc, char* argv[]){

    // get file from argument 
    CPU cpu;
    char* filename = argv[1];
    cpu.FileAnalyzerFile(filename);


    // get data size from 0x81f0
    // get where to store data in ram from 0x81ec
    // read data from address 0x81e4
    cpu.dataLoad();

    // initialize stack pointer to 0x6000
    cpu.registers[29] = 0x6000;
    
    cpu.setup();

    cpu.loop();
// setup
// check to see if the program counter reaches 0, if it reaches 0 breakout
// loop
// different after pc reaches 0 go back to the top of the loop 

}
