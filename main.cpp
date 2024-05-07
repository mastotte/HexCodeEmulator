#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
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
/*
    subtract = 0;
    or_Op = 4;
    nor = 7
    add = 9;
    shiftRightArithmetic = 11;
    bitwise_and = 24;
    jumpRegister = 28;
    shiftLeftLogical = 32;
    shiftRightLogical = 35;
    setLessThan = 36;
*/
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
    uint16_t programCounter = 0x0000;


    programCounter = 0xfffc;
    char* filename = argv[1];
    std::cout << argv[1] << std::endl;
    FileAnalyzerFile file = FileAnalyzerFile(filename);

    uint32_t setup_address = file.ReadBigEndianInt32(0x01e0);
    std::cout << setup_address << std::endl;
    setup_address -= 32768; // subtracting 8000 hex in order to account for slug file starting at 0x8000

    // Use a while loop to iterate through the instructions 
    std::cout << file.ReadBigEndianInt32(setup_address) << std::endl;

    /*

    //jumpInstruction to setup here <----
    
    
    //actual code draft
    while(validAddress(programCounter)){
        doInstruction(programCounter);
    }
    */

    

}
