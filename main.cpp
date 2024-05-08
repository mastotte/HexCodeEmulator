#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

#include "FileAnalyzerFile.h"
#include "cpu.h"

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




int main(char* argv[]){
    // r type map
    std::unordered_map<int, std::any> ROptable;
    ROptable[subtract] = &CPU::subtract;
    ROptable[or_Op] = &CPU::or_Op;
    ROptable[nor] = &CPU::nor;
    ROptable[add] = &CPU::add;
    ROptable[shiftRightArithmetic] = &CPU::shiftRightArithmetic;
    ROptable[bitwise_and] = &CPU::bitwise_and;
    ROptable[jumpRegister] = &CPU::jumpRegister;
    ROptable[shiftLeftLogical] = &CPU::shiftLeftLogical;
    ROptable[shiftRightLogical] = &CPU::shiftRightLogical;
    ROptable[setLessThan] = &CPU::setLessThan;

    // i type map
    std::unordered_map<int, std::any> IOptable;
    IOptable[branchOnEqual] = &CPU::branchOnEqual;
    IOptable[loadWord] = &CPU::loadWord;
    IOptable[loadByteUnsigned] = &CPU::loadByteUnsigned;
    IOptable[jump] = &CPU::jump;
    IOptable[storeWord] = &CPU::storeWord;
    IOptable[storeByte] = &CPU::storeByte;
    IOptable[orImmediate] = &CPU::orImmediate;
    IOptable[branchOnNotEqual] = &CPU::branchOnNotEqual;
    IOptable[jumpAndLink] = &CPU::jumpAndLink;
    

    CPU cpu;
    void doInstruction(CPU cpu, uint16_t* programCounter){
        //store instructions in register[12]
        cpu.loadWord(0, 12, file.ReadBigEndianInt32(programCounter));
        //store opcodes in register[11]
        cpu.shiftRightLogical(11, 12, 26);
        // store reg_a in 13
        cpu.shiftLeftLogical(13, 12, 5);
        cpu.shiftRightLogical(13, 13, 20);
        // store reg_b in 14
        cpu.shiftLeftLogical(14, 12, 11);
        cpu.shiftRightLogical(14, 14, 16);
        
        if (cpu.registers[11] == R_TYPE){
            // store function (r-type) in 16
            cpu.shiftLeftLogical(16, 12, 26);
            // store reg_c in 15
            cpu.shiftLeftLogical(15, 12, 16);
            cpu.shiftRightLogical(15, 15, 11);
            ROptable[cpu.registers[16]](13, 14, 15);
        }
        else {
            // store immediate in 17
            cpu.shiftLeftLogical(17, 12, 16);
            IOptable[cpu.registers[11]](13, 14, 17);
        }
    }
     

    // get opcode
    // if opcode == 62
    //  access next value to get function
    // else
    //  optable[opcode]





    cpu.programCounter = 0x0000;




    // setup
    cpu.programCounter = 0xfffc;
    char* filename = argv[1];
    std::cout << argv[1] << std::endl;
    FileAnalyzerFile file = FileAnalyzerFile(filename);

    uint32_t setup_address = file.ReadBigEndianInt32(0x01e0);
    std::cout << setup_address << std::endl;
    //the following math is no longer needed, since we will be using an array of the entire memory. <---
    setup_address -= 0x8000; // subtracting 8000 hex in order to account for slug file starting at 0x8000

    // Use a while loop to iterate through the instructions 
    std::cout << file.ReadBigEndianInt32(setup_address) << std::endl;

    /*

    //jump to setup here <----
    
    
    //actual code draft
    while(validAddress(programCounter)){
        doInstruction(programCounter);
    }
    

    //helper function to check if address is valid
    bool validAddress(uint16_t addr){
        if(0x8000 <= addr <= MAX_ADDRESS){
            return 1;
        }
        return 0;
    }

    //function to execute instruction based on current programCounter.
    void doInstruction(uint16_t* programCounter){
        //add code to compare programCounter reference to our memory array.
        //update programCounter reference with new address.
    }
    
    */

    

}