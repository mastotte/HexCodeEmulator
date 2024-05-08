#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

#include "FileAnalyzerFile.h"
#include "cpu.h"


bool validAddress(uint16_t addr){
    if (0x8000 <= addr && addr <= 0x16000) {
        return 1;
    }
    return 0;
}

enum Opcode {
    branchOnEqual = 0,
    loadWord = 2,
    loadByteUnsigned = 16,
    jump = 36,
    storeWord = 48,
    storeByte = 50,
    orImmediate = 53,
    branchOnNotEqual = 59,
    jumpAndLink = 61,
    R_TYPE = 62 // note that all R-type instructions have same opcode, but diff function #s 
};

enum function_codes { //R-type instructions function codes
    subtract = 0,
    or_Op = 4,
    nor = 7,
    add = 9,
    shiftRightArithmetic = 11,
    bitwise_and = 24,
    jumpRegister = 28,
    shiftLeftLogical = 32,
    shiftRightLogical = 35,
    setLessThan = 36
};

int main(int argc, char* argv[]){

    // std::unordered_map<int, std::any> ROptable;
    // ROptable[subtract] = &CPU::subtract;
    // ROptable[or_Op] = &CPU::or_Op;
    // ROptable[nor] = &CPU::nor;
    // ROptable[add] = &CPU::add;
    // ROptable[shiftRightArithmetic] = &CPU::shiftRightArithmetic;
    // ROptable[bitwise_and] = &CPU::bitwise_and;
    // ROptable[jumpRegister] = &CPU::jumpRegister;
    // ROptable[shiftLeftLogical] = &CPU::shiftLeftLogical;
    // ROptable[shiftRightLogical] = &CPU::shiftRightLogical;
    // ROptable[setLessThan] = &CPU::setLessThan;

    // // i type map
    // std::unordered_map<int, std::any> IOptable;
    // IOptable[branchOnEqual] = &CPU::branchOnEqual;
    // IOptable[loadWord] = &CPU::loadWord;
    // IOptable[loadByteUnsigned] = &CPU::loadByteUnsigned;
    // IOptable[jump] = &CPU::jump;
    // IOptable[storeWord] = &CPU::storeWord;
    // IOptable[storeByte] = &CPU::storeByte;
    // IOptable[orImmediate] = &CPU::orImmediate;
    // IOptable[branchOnNotEqual] = &CPU::branchOnNotEqual;
    // IOptable[jumpAndLink] = &CPU::jumpAndLink;


    // get file from argument 
    CPU cpu;
    char* filename = argv[1];
    cpu.FileAnalyzerFile(filename);
    cpu.programCounter = 0xfffc;
    cpu.jumpAndLink(0, 0, 0x2078); //skipping 81e0 bits

    // setup
    // jumping the first address of the 

    // std::cout << cpu.programCounter << std::endl;
    cpu.programCounter = 0x8280;
    
    while (validAddress(cpu.programCounter)){
        // cpu.loadWord(0, 12, cpu.programCounter);
        
        cpu.doInstruction();
        // std::cout << cpu.ReadBigEndianInt32(cpu.programCounter) << std::endl;
    }

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
