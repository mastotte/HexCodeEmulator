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

    //temp comment 
    // FileAnalyzerFile file = FileAnalyzerFile(filename);
    
    //     // get opcode
    //     // if opcode == 62
    //     //  access next value to get function
    //     // else
    //     //  optable[opcode]
    // cpu.programCounter = 0x0000;
    // // Clear all of RAM with zeros

    // // 2. Copy data section to RAM

    // // 3. Initialize stack pointer register to the end of the stack (0x6000)
    // cpu.registers[29] = 0x6000;

    
    // // pre setup or loop
    // cpu.programCounter = 0xfffc;

    // // setup
    // // calling JAL to setup address (jumping by number of instructions not number of bytes)
    // cpu.jumpAndLink(0, 0, 120); // 0x01e0/4 = 120
    // uint32_t setup_address = file.ReadBigEndianInt32(cpu.programCounter);

    // // ask ta/professor - the following math is no longer needed, since we will be using an array of the entire memory. <---
    // setup_address -= 0x8000; // subtracting 8000 hex in order to account for slug file starting at 0x8000

    

    // while (validAddress(file.ReadBigEndianInt32(setup_address))){
    //     doInstruction(programCounter);
    // }

    
    // // Use a while loop to iterate through the instructions 
    // std::cout << file.ReadBigEndianInt32(setup_address) << std::endl;

    /*

    //jump to setup here <----
    
    
    //actual code draft
    while(validAddress(programCounter)){
        doInstruction(programCounter);
    }
    

    //helper function to check if address is valid


    //function to execute instruction based on current programCounter.
    void doInstruction(uint16_t* programCounter){
        //add code to compare programCounter reference to our memory array.
        //update programCounter reference with new address.
    }
    
    */


// setup
// check to see if the program counter reaches 0, if it reaches 0 breakout
// loop
// different after pc reaches 0 go back to the top of the loop 

}
