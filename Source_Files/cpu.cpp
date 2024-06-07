#include "cpu.h"

#include <any>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "memory.h"

#define STOP_ADDRESS ((volatile uint8_t*)(0x7200))
#define STOP *(STOP_ADDRESS) = 0

// The CPU should only be in charge of running the instruction at the current
// program counter and incrementing the program counter when necessary.
// Instruction Functions
//--------------------- 2.1.1-2.14 (Milan) ---------------------
void CPU::branchOnEqual(const int reg_a, const int reg_b, const int immediate) {
  if (registers[reg_a] == registers[reg_b]) {
    programCounter -= 4;
    programCounter += 4 + (4 * immediate);
  }
  // s//td::cout << "beq" << std::endl;
}

void CPU::loadWord(const int reg_a, const int reg_b, const int immediate) {
  // s//td::cout << "load word during pre reg a " << registers[reg_a] << " reg b
  // " << registers[reg_b] << " immediate " << immediate << std::endl;
  registers[reg_b] = memory.read16(registers[reg_a] + immediate);
  // s//td::cout << "loadword reg_a " << reg_a << " reg_b " << reg_b << "
  // immediate " <<immediate << std::endl; s//td::cout << "load word during reg
  // a " << registers[reg_a] << " reg b " << registers[reg_b] << " immediate "
  // << immediate << std::endl;
}

void CPU::loadByteUnsigned(const int reg_a, const int reg_b,
                           const int immediate) {
  registers[reg_b] = memory.read8(registers[reg_a] + immediate);
  // // Read a byte from memory
  // uint16_t byteFromMemory = memory[registers[reg_a] + immediate];

  // // Extract the lower 8 bits
  // uint8_t lower8Bits = byteFromMemory & 0xFF;

  // // Store the extracted value into registers[reg_b]
  // registers[reg_b] = lower8Bits;
  // std::cout << "load byte during reg a " << registers[reg_a] << " reg b " <<
  // registers[reg_b] << std::endl;
}

void CPU::jump(const int reg_a, const int reg_b, const int immediate) {
  programCounter -= 4;
  programCounter = 4 * immediate;
  // std::cout << "j" << std::endl;
}
//--------------------- 2.1.5-2.1.8 (Daniel) ---------------------
void CPU::storeWord(const int reg_a, const int reg_b, const int immediate) {
  memory.write16(registers[reg_a] + immediate, registers[reg_b]);
  // std::cout << "storew stored data" << reg_b << std::endl;

  // memory[registers[reg_a] + immediate] = registers[reg_b];
}

void CPU::storeByte(const int reg_a, const int reg_b, const int immediate) {
  // // Extract the lower 8 bits from registers[reg_b]
  // uint8_t lower8Bits = registers[reg_b] & 0xFF;

  // // Store the lower 8 bits into memory at the specified address
  // memory[registers[reg_a] + immediate] = lower8Bits;
  memory.write8(registers[reg_a] + immediate, registers[reg_b]);
  // std::cout << "store" << std::endl;
}

void CPU::orImmediate(const int reg_a, const int reg_b, const int immediate) {
  registers[reg_b] = (registers[reg_a] | immediate);
  // std::cout << "orimmediate during reg a " << registers[reg_a] << " reg b "
  // << registers[reg_b] << std::endl;
}

void CPU::branchOnNotEqual(const int reg_a, const int reg_b,
                           const int immediate) {
  if (registers[reg_a] != registers[reg_b]) {
    programCounter -= 4;
    programCounter += 4 + 4 * immediate;
  }
  // std::cout << "branchnotequal during reg a " << registers[reg_a] << " reg b
  // " << registers[reg_b] << std::endl;
}
//--------------------- 2.1.9-2.2.3 (Josh) ---------------------
void CPU::jumpAndLink(const int reg_a, const int reg_b, const int immediate) {
  registers[31] = programCounter + 4;
  programCounter -= 4;
  programCounter = 4 * immediate;

  // std::cout << "jal" << std::endl;
}

void CPU::subtract(const int reg_a, const int reg_b, const int reg_c,
                   const int shift_value) {
  registers[reg_c] = registers[reg_a] - registers[reg_b];
  // std::cout << "sub" << std::endl;
}

void CPU::or_Op(const int reg_a, const int reg_b, const int reg_c,
                const int shift_value) {
  registers[reg_c] = registers[reg_a] | registers[reg_b];
  // std::cout << "or" << std::endl;
}

void CPU::nor(const int reg_a, const int reg_b, const int reg_c,
              const int shift_value) {
  registers[reg_c] = !(registers[reg_a] | registers[reg_b]);
  // std::cout << "nor" << std::endl;
}
//--------------------- 2.2.4-2.2.7 (Max) --------------------
void CPU::add(const int reg_a, const int reg_b, const int reg_c,
              const int shift_value) {
  // std::cout << "add during reg a " << registers[reg_a] << " reg b " <<
  // registers[reg_b] << "reg c " << registers[reg_c] << std::endl;
  registers[reg_c] = registers[reg_a] + registers[reg_b];
}

void CPU::shiftRightArithmetic(const int reg_a, const int reg_b,
                               const int reg_c, const int shift_value) {
  // std::cout << "sra" << std::endl;
  registers[reg_c] = (signed)registers[reg_b] >> shift_value;
}

void CPU::bitwise_and(const int reg_a, const int reg_b, const int reg_c,
                      const int shift_value) {
  registers[reg_c] = registers[reg_a] & registers[reg_b];
  // std::cout << "and" << std::endl;
}

void CPU::jumpRegister(const int reg_a, const int reg_b, const int reg_c,
                       const int shift_value) {
  programCounter -= 4;
  programCounter = registers[reg_a];
  // s//td::cout << "jr regc: " << reg_c  << " reg_a: " << reg_a << " reg_b: "
  // << reg_b << std::endl;
  // std::cout << "jumpreg during reg a " << registers[reg_a] << " reg b " <<
  // registers[reg_b] << "reg c " << registers[reg_c] << std::endl;
}
//--------------------- 2.2.8-2.2.10 (Omid) ---------------------
void CPU::shiftLeftLogical(const int reg_a, const int reg_b, const int reg_c,
                           const int shift_value) {
  // registers[reg_c] = (unsigned)registers[reg_b] << shift_value;
  registers[reg_c] = registers[reg_b] << shift_value;
  // std::cout << "sll during reg a " << registers[reg_a] << " reg b " <<
  // registers[reg_b] << "reg c " << registers[reg_c] << std::endl;
  //  s//td::cout << "sll regc: " << reg_c  << " shift value: " << shift_value
  //  << " reg_b: " << reg_b << std::endl;
}

void CPU::shiftRightLogical(const int reg_a, const int reg_b, const int reg_c,
                            const int shift_value) {
  // registers[reg_c] = (unsigned)registers[reg_b] >> shift_value;
  registers[reg_c] = registers[reg_b] >> shift_value;
  // std::cout << "srl" << std::endl;
}

void CPU::setLessThan(const int reg_a, const int reg_b, const int reg_c,
                      const int shift_value) {
  registers[reg_c] = (registers[reg_a] < registers[reg_b]);
  // std::cout << "slt during reg a " << registers[reg_a] << " reg b " <<
  // registers[reg_b] << "reg c " << registers[reg_c] << std::endl;
  //  s//td::cout << "slt regc: " << reg_c  << " reg_a: " << reg_a << " reg_b: "
  //  << reg_b << std::endl;
}

// seperate things out of CPU class (inheritance)
// memory class
// OS class contains cpu object and memory object
// everything runs through the OS (using the CPU and memory objects)
// cpu class references memory