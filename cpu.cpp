#include "cpu.h"
#include <unordered_map>
#include <any>
#include <memory>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>


// File analyzer functions changed into cpu versions
void CPU::FileAnalyzerFile(const std::string& filename){
    // Open the file
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    // Check if file is opened successfully
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Get the size of the file
    size_t file_size = file.tellg();

    // Reset file pointer to the beginning
    file.seekg(0, std::ios::beg);
    
    // Allocate memory to store the contents of the file
    // std::unique_ptr<char[]> contents;
    memory = std::make_unique<char[]>(0x8000+file_size);
    
    // stores value (displays differently based on computer), 1 byte in each index) actually reading in 4 at a time (the actual instruction)
    // Read the contents of the file into the allocated memory
    file.read((memory.get() + 0x8000), file_size);
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


// enums and unordered maps for tables

enum Opcode {
    branchOnEqualCode = 0,
    loadWordCode = 2,
    loadByteUnsignedCode = 16,
    jumpCode = 36,
    storeWordCode = 48,
    storeByteCode = 50,
    orImmediateCode = 53,
    branchOnNotEqualCode = 59,
    jumpAndLinkCode = 61,
    R_TYPE = 62 // note that all R-type instructions have same opcode, but diff function #s 
};

enum function_codes { //R-type instructions function codes
    subtractCode = 0,
    or_OpCode = 4,
    norCode = 7,
    addCode = 9,
    shiftRightArithmeticCode = 11,
    bitwise_andCode = 24,
    jumpRegisterCode = 28,
    shiftLeftLogicalCode = 32,
    shiftRightLogicalCode = 35,
    setLessThanCode = 36
};



// }





// Instruction Functions
//--------------------- 2.1.1-2.14 (Milan) ---------------------
void CPU::branchOnEqual(int reg_a, int reg_b, int immediate) {
    if (registers[reg_a] == registers[reg_b]) {
        programCounter += 4 + 4 * immediate;
    }
}

void CPU::loadWord(int reg_a, int reg_b, int immediate) {
    registers[reg_b] = memory[registers[reg_a] + immediate];
}

void CPU::loadByteUnsigned(int reg_a, int reg_b, int immediate) {
    // Read a byte from memory
    uint16_t byteFromMemory = memory[registers[reg_a] + immediate];

    // Extract the lower 8 bits
    uint8_t lower8Bits = byteFromMemory & 0xFF;

    // Store the extracted value into registers[reg_b]
    registers[reg_b] = lower8Bits;
}

void CPU::jump(int reg_a, int reg_b, int immediate) {
    programCounter = 4 * immediate;
}
//--------------------- 2.1.5-2.1.8 (Daniel) ---------------------
void CPU::storeWord(int reg_a, int reg_b, int immediate) {
    memory[registers[reg_a] + immediate] = registers[reg_b];
}

void CPU::storeByte(int reg_a, int reg_b, int immediate) {
    // Extract the lower 8 bits from registers[reg_b]
    uint8_t lower8Bits = registers[reg_b] & 0xFF;

    // Store the lower 8 bits into memory at the specified address
    memory[registers[reg_a] + immediate] = lower8Bits;
}

void CPU::orImmediate(int reg_a, int reg_b, int immediate) {
    registers[reg_b] = registers[reg_a] | immediate;
}

void CPU::branchOnNotEqual(int reg_a, int reg_b, int immediate) {
    if (registers[reg_a] != registers[reg_b]) {
        programCounter += 4 + 4 * immediate;
    }
}
//--------------------- 2.1.9-2.2.3 (Josh) ---------------------
void CPU::jumpAndLink(int reg_a, int reg_b, int immediate) {
    registers[31] = programCounter + 4;
    programCounter = 4 * immediate;
}

void CPU::subtract(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_a] = registers[reg_b];
}

void CPU::or_Op(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_a] | registers[reg_b];
}

void CPU::nor(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = ~(registers[reg_a] | registers[reg_b]);
}
//--------------------- 2.2.4-2.2.7 (Max) --------------------
void CPU::add(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_a] + registers[reg_b];
}

void CPU::shiftRightArithmetic(int reg_a,int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = (signed)registers[reg_b] >> shift_value;
}

void CPU::bitwise_and(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_a] & registers[reg_b];
}

void CPU::jumpRegister(int reg_a, int reg_b, int reg_c, int shift_value) {
    programCounter = registers[reg_a];
}
//--------------------- 2.2.8-2.2.10 (Omid) ---------------------
void CPU::shiftLeftLogical(int reg_a,int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_b] << shift_value;
}

void CPU::shiftRightLogical(int reg_a,int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = registers[reg_b] >> shift_value;
}

void CPU::setLessThan(int reg_a, int reg_b, int reg_c, int shift_value) {
    registers[reg_c] = (registers[reg_a] < registers[reg_b]);
}




CPU::CPU() {
    // Initialize ROptable
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

    // Initialize IOptable
    IOptable[branchOnEqualCode] = &CPU::branchOnEqual;
    IOptable[loadWordCode] = &CPU::loadWord;
    IOptable[loadByteUnsignedCode] = &CPU::loadByteUnsigned;
    IOptable[jumpCode] = &CPU::jump;
    IOptable[storeWordCode] = &CPU::storeWord;
    IOptable[storeByteCode] = &CPU::storeByte;
    IOptable[orImmediateCode] = &CPU::orImmediate;
    IOptable[branchOnNotEqualCode] = &CPU::branchOnNotEqual;
    IOptable[jumpAndLinkCode] = &CPU::jumpAndLink;
}

// // r type map
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

// IOptable[branchOnEqual] = &CPU::branchOnEqual;
// IOptable[loadWord] = &CPU::loadWord;
// IOptable[loadByteUnsigned] = &CPU::loadByteUnsigned;
// IOptable[jump] = &CPU::jump;
// IOptable[storeWord] = &CPU::storeWord;
// IOptable[storeByte] = &CPU::storeByte;
// IOptable[orImmediate] = &CPU::orImmediate;
// IOptable[branchOnNotEqual] = &CPU::branchOnNotEqual;
// IOptable[jumpAndLink] = &CPU::jumpAndLink;



// Setup Functions 



void CPU::doInstruction(){
    //store instructions in register[12]
    loadWord(0, 12, ReadBigEndianInt32(programCounter));
    //store opcodes in register[11]
    shiftRightLogical(0, 11, 12, 26);
    // store reg_a in 13
    shiftLeftLogical(0, 13, 12, 5);
    shiftRightLogical(0, 13, 13, 20);
    // store reg_b in 14
    shiftLeftLogical(0, 14, 12, 11);
    shiftRightLogical(0, 14, 14, 16);
    
    if (registers[11] == R_TYPE){
        // store function (r-type) in 16
        shiftLeftLogical(0, 16, 12, 26);
        // store reg_c in 15
        shiftLeftLogical(0, 15, 12, 16);
        shiftRightLogical(0, 15, 15, 11);
        //shift value
        (ROptable[registers[16]])(*this, 13, 14, 15, 0);
    }
    else {
        // store immediate in 17
        shiftLeftLogical(0, 17, 12, 16);
        (IOptable[registers[11]])(*this, 13, 14, 17);
    }
    
}