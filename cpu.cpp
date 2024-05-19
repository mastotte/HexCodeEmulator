#include "cpu.h"
#include <unordered_map>
#include <any>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


#define STOP_ADDRESS ((volatile uint8_t*)(0x7200))
#define STOP *(STOP_ADDRESS) = 0


// The CPU should only be in charge of running the instruction at the current program counter and incrementing the program counter when necessary. 
// File analyzer functions changed into cpu versions
void CPU::FileAnalyzerFile(const std::string& filename){
    // Open the file
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    // Check if file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }


/*
Note the .slug file size is ALWAYS 0x8000 bytes in size per Ben's email. 
We also don't need to seek to the beginning.
*/

    
    // Allocate memory to store the contents of the file
    // std::unique_ptr<char[]> contents;
    memory = std::make_unique<char[]>(0x8000);
    
    // stores value (displays differently based on computer), 1 byte in each index) actually reading in 4 at a time (the actual instruction)
    // Read the contents of the file into the allocated memory
    file.read((memory.get() + 0x8000), 0x8000);
    // Close the file
    file.close();
}

uint32_t CPU::ReadBigEndianInt32(const size_t& addr) const {
  uint32_t out = 0;
  for (int i = 0; i < 4; i++) {
    out <<= 8;
    out |= (uint8_t)memory[addr + i];
  }
  return out;
}




// }





// Instruction Functions
//--------------------- 2.1.1-2.14 (Milan) ---------------------
void CPU::branchOnEqual(int reg_a, int reg_b, int immediate) {
    if (registers[reg_a] == registers[reg_b]) {
        programCounter -= 4;
        programCounter += 4 + (4 * immediate);
    }
}

void CPU::loadWord(int reg_a, int reg_b, int immediate) {
    registers[reg_b] = read16(registers[reg_a] + immediate);
}

void CPU::loadByteUnsigned(int reg_a, int reg_b, int immediate) {
    registers[reg_b] = read8(registers[reg_a] + immediate);
    // // Read a byte from memory
    // uint16_t byteFromMemory = memory[registers[reg_a] + immediate];

    // // Extract the lower 8 bits
    // uint8_t lower8Bits = byteFromMemory & 0xFF;

    // // Store the extracted value into registers[reg_b]
    // registers[reg_b] = lower8Bits;
}

void CPU::jump(int reg_a, int reg_b, int immediate) {
    programCounter -= 4;
    programCounter = 4 * immediate;
    // std::cout << "j" << std::endl;
}
//--------------------- 2.1.5-2.1.8 (Daniel) ---------------------
void CPU::storeWord(int reg_a, int reg_b, int immediate) {
    write16(registers[reg_a] + immediate, registers[reg_b]);
    // std::cout << "storew" << std::endl;
    
    //memory[registers[reg_a] + immediate] = registers[reg_b];
}

void CPU::storeByte(int reg_a, int reg_b, int immediate) {
    // // Extract the lower 8 bits from registers[reg_b]
    // uint8_t lower8Bits = registers[reg_b] & 0xFF;

    // // Store the lower 8 bits into memory at the specified address
    // memory[registers[reg_a] + immediate] = lower8Bits;

    write8(registers[reg_a] + immediate, registers[reg_b]);
    // std::cout << "store" << std::endl;
}

void CPU::orImmediate(int reg_a, int reg_b, int immediate) {
    registers[reg_b] = (registers[reg_a] | immediate);
    // std::cout << "ori" << std::endl;
}

void CPU::branchOnNotEqual(int reg_a, int reg_b, int immediate) {
    if (registers[reg_a] != registers[reg_b]) {
        programCounter -= 4;
        programCounter += 4 + 4 * immediate;
    }
    // std::cout << "benq" << std::endl;
}
//--------------------- 2.1.9-2.2.3 (Josh) ---------------------
void CPU::jumpAndLink(int reg_a, int reg_b, int immediate) {
    registers[31] = programCounter + 4;
    programCounter -= 4;
    programCounter = 4 * immediate;
    
    // std::cout << "jal" << std::endl;
}

void CPU::subtract(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_a] - registers[reg_b];
    // std::cout << "sub" << std::endl;
}

void CPU::or_Op(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_a] | registers[reg_b];
    // std::cout << "or" << std::endl;
}

void CPU::nor(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = !(registers[reg_a] | registers[reg_b]);
    // std::cout << "nor" << std::endl;
}
//--------------------- 2.2.4-2.2.7 (Max) --------------------
void CPU::add(int reg_a, int reg_b, int reg_c, int shift_value) {
    // std::cout << "add" << std::endl;
    registers[reg_c] = registers[reg_a] + registers[reg_b];
}

void CPU::shiftRightArithmetic(int reg_a,int reg_b, int reg_c, int shift_value) {
    // std::cout << "sra" << std::endl;
    registers[reg_c] = (signed)registers[reg_b] >> shift_value;
}

void CPU::bitwise_and(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_a] & registers[reg_b];
    // std::cout << "and" << std::endl;
}

void CPU::jumpRegister(int reg_a, int reg_b, int reg_c, int shift_value) {
    programCounter -= 4;
    programCounter = registers[reg_a];
    // std::cout << "jr" << std::endl;
}
//--------------------- 2.2.8-2.2.10 (Omid) ---------------------
void CPU::shiftLeftLogical(int reg_a,int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = (unsigned)registers[reg_b] << shift_value;
    // std::cout << "sll" << std::endl;
}

void CPU::shiftRightLogical(int reg_a,int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = (unsigned)registers[reg_b] >> shift_value;
    // std::cout << "srl" << std::endl;
}

void CPU::setLessThan(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = (registers[reg_a] < registers[reg_b]);
    // std::cout << "slt" << std::endl;
}


// read and write functions


uint16_t CPU::read16(uint32_t address){
    return (memory[address] << 8) | memory[address + 1];
}

uint8_t CPU::read8(uint32_t address){
    
    char c;
    if (address == 0x7100){
        std::cin >> c; 
        return c;
    }
    else{
        return memory[address];
    }
    
}


void CPU::write8(uint32_t address, uint8_t data){
    memory[address] = data;
    if (address == 0x7110) {
        std::cout << data;
    }
    else if (address == 0x7120) {
        std::cerr << data;
    }
    else if (address == 0x7200) {
        exit(EXIT_SUCCESS);
        // std::cout << data;
        
    }
}

void CPU::write16(uint32_t address, uint16_t data){
    memory[address] = data >> 8;
    memory[address + 1] = data; 
    if (address == 0x7110) {
        std::cout << data;
    }
    else if (address == 0x7120) {
        std::cerr << data;
    }
    else if (address == 0x7200) {
        exit(EXIT_SUCCESS);
        // std::cout << data;
    }
}




CPU::CPU() {
    // Initialize ROptable
    ROptable={ 
        {subtractCode, &CPU::subtract},
            {or_OpCode, &CPU::or_Op},
            {norCode, &CPU::nor},
            {addCode, &CPU::add},
            {shiftRightArithmeticCode, &CPU::shiftRightArithmetic},
            {bitwise_andCode, &CPU::bitwise_and},
            {jumpRegisterCode, &CPU::jumpRegister},
            {shiftLeftLogicalCode, &CPU::shiftLeftLogical},
            {shiftRightLogicalCode, &CPU::shiftRightLogical},
            {setLessThanCode, &CPU::setLessThan}
        };

    
    /*
    ROptable[subtractCode] = &CPU::subtract;
    ROptable[or_OpCode] = &CPU::or_Op;
    ROptable[norCode] = &CPU::nor;
    ROptable[addCode] = &CPU::add;
    ROptable[shiftRightArithmeticCode] = &CPU::shiftRightArithmetic;
    ROptable[bitwise_andCode] = &CPU::bitwise_and;
    ROptable[jumpRegisterCode] = &CPU::jumpRegister;
    ROptable[shiftLeftLogicalCode] = &CPU::shiftLeftLogical;
    ROptable[shiftRightLogicalCode] = &CPU::shiftRightLogical;
    ROptable[setLessThanCode] = &CPU::setLessThan;
    */
    // placeholder for function validation
    

    // Initialize IOptable

        IOptable = {
            {branchOnEqualCode, &CPU::branchOnEqual},
            {loadWordCode, &CPU::loadWord},
            {loadByteUnsignedCode, &CPU::loadByteUnsigned},
            {jumpCode, &CPU::jump},
            {storeWordCode, &CPU::storeWord},
            {storeByteCode, &CPU::storeByte},
            {orImmediateCode, &CPU::orImmediate},
            {branchOnNotEqualCode, &CPU::branchOnNotEqual},
            {jumpAndLinkCode, &CPU::jumpAndLink},
            {R_TYPE, &CPU::jumpAndLink} 
        };


    /*
    IOptable[branchOnEqualCode] = &CPU::branchOnEqual;
    IOptable[loadWordCode] = &CPU::loadWord;
    IOptable[loadByteUnsignedCode] = &CPU::loadByteUnsigned;
    IOptable[jumpCode] = &CPU::jump;
    IOptable[storeWordCode] = &CPU::storeWord;
    IOptable[storeByteCode] = &CPU::storeByte;
    IOptable[orImmediateCode] = &CPU::orImmediate;
    IOptable[branchOnNotEqualCode] = &CPU::branchOnNotEqual;
    IOptable[jumpAndLinkCode] = &CPU::jumpAndLink;
    IOptable[R_TYPE] = &CPU::jumpAndLink;
    */
}

// dataLoad()

void CPU::dataLoad(){
    // get data size from 0x81f0
    uint32_t dataSize = ReadBigEndianInt32(0x81f0);
    // get where to store data in ram from 0x81ec
    uint32_t ramAddress = ReadBigEndianInt32(0x81ec);
    // read data from address 0x81e4
    uint32_t dataAddress = ReadBigEndianInt32(0x81e8);
    for (uint32_t i = 0; i < dataSize; i++){
        uint8_t data = read8(dataAddress);
        // std::cout << data << std::endl;
        write8(ramAddress, data);
        ramAddress++;
        dataAddress++;
    }

}

// setup()

void CPU::setup(){
    programCounter = 0xfffc;
    jumpAndLink(0, 0, 0x2078); //skipping 81e0 bits
    programCounter = ReadBigEndianInt32(programCounter);
    while (programCounter > 0x8000){
        doInstruction();
        if (programCounter == 0){
            break;
        }
    }
}

// loop()

void CPU::loop(){
    // read into loop addres
    
    
    // std::cout << programCounter << std::endl;  
    programCounter = 0xfffc;
    jumpAndLink(0, 0, 0x2079);
    uint32_t loopAddress = ReadBigEndianInt32(programCounter);
    while(1){
        programCounter = loopAddress;
        while (programCounter != 0){
            doInstruction();
        }
    }
    // infinite loop 
    // go back to the top of the loop when PC == 0
}


// Setup Functions 

void CPU::doInstruction(){
    //store instructions in register[12]
    // loadWord(0, 12, programCounter);
    uint32_t instruction = ReadBigEndianInt32(programCounter);
    programCounter += 4;

    uint32_t opcode = instruction >> 26;
    // std::cout << "opcode: " << opcode << std::endl;
    //check if the opcode is a value function
    if (IOptable.find(opcode) != IOptable.end()){
        uint32_t reg_a = instruction << 6;
        reg_a = reg_a >> 27;
        uint32_t reg_b = instruction << 11;
        reg_b = reg_b >> 27;
        // if (registers[11] == R_TYPE){
        if (opcode == R_TYPE){
            // check if function code is valid

            uint32_t function = instruction << 26;

            function = function >> 26;
            // std::cout << "function: " << function << std::endl;


            if (ROptable.find(function) != ROptable.end()){
            
                uint32_t reg_c = instruction << 16;
                reg_c = reg_c >> 27;

                uint32_t shift_value = instruction << 21;
                shift_value = shift_value >> 27;
                
                (ROptable[function])(*this, reg_a, reg_b, reg_c, shift_value);
            }
        }
        else {

            uint32_t immediate = instruction << 16;
            immediate = immediate >> 16;
            (IOptable[opcode])(*this, reg_a, reg_b, immediate);
        }
        
    }
    
}

// seperate things out of CPU class (inheritance)
// memory class 
// OS class contains cpu object and memory object
// everything runs through the OS (using the CPU and memory objects)
// cpu class references memory