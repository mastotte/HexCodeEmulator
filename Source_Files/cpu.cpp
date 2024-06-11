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

//--------------------- 2.1.1-2.14 (Milan) ---------------------
void CPU::branchOnEqual(const int reg_a, const int reg_b, const int immediate) {
  if (registers[reg_a] == registers[reg_b]) {
    programCounter -= 4;
    programCounter += 4 + (4 * immediate);
  }
}

void CPU::loadWord(const int reg_a, const int reg_b, const int immediate) {
  registers[reg_b] = memory.read16(registers[reg_a] + immediate);
}

void CPU::loadByteUnsigned(const int reg_a, const int reg_b,
                           const int immediate) {
  registers[reg_b] = memory.read8(registers[reg_a] + immediate);
}

void CPU::jump(const int reg_a, const int reg_b, const int immediate) {
  programCounter -= 4;
  programCounter = 4 * immediate;
}
//--------------------- 2.1.5-2.1.8 (Daniel) ---------------------
void CPU::storeWord(const int reg_a, const int reg_b, const int immediate) {
  memory.write16(registers[reg_a] + immediate, registers[reg_b]);
}

//something going wrong here - possibly registers
void CPU::storeByte(const int reg_a, const int reg_b, const int immediate) {
  memory.write8(registers[reg_a] + immediate, registers[reg_b]);
}

void CPU::orImmediate(const int reg_a, const int reg_b, const int immediate) {
  registers[reg_b] = (registers[reg_a] | immediate);
}

void CPU::branchOnNotEqual(const int reg_a, const int reg_b,
                           const int immediate) {
  if (registers[reg_a] != registers[reg_b]) {
    programCounter -= 4;
    programCounter += 4 + 4 * immediate;
  }
}
//--------------------- 2.1.9-2.2.3 (Josh) ---------------------
void CPU::jumpAndLink(const int reg_a, const int reg_b, const int immediate) {
  registers[31] = programCounter + 4;
  programCounter -= 4;
  programCounter = 4 * immediate;
}

void CPU::subtract(const int reg_a, const int reg_b, const int reg_c,
                   const int shift_value) {
  registers[reg_c] = registers[reg_a] - registers[reg_b];
}

void CPU::or_Op(const int reg_a, const int reg_b, const int reg_c,
                const int shift_value) {
  registers[reg_c] = registers[reg_a] | registers[reg_b];
}

void CPU::nor(const int reg_a, const int reg_b, const int reg_c,
              const int shift_value) {
  registers[reg_c] = !(registers[reg_a] | registers[reg_b]);
}
//--------------------- 2.2.4-2.2.7 (Max) --------------------
void CPU::add(const int reg_a, const int reg_b, const int reg_c,
              const int shift_value) {
  registers[reg_c] = registers[reg_a] + registers[reg_b];
}

void CPU::shiftRightArithmetic(const int reg_a, const int reg_b,
                               const int reg_c, const int shift_value) {
  registers[reg_c] = (signed)registers[reg_b] >> shift_value;
}

void CPU::bitwise_and(const int reg_a, const int reg_b, const int reg_c,
                      const int shift_value) {
  registers[reg_c] = registers[reg_a] & registers[reg_b];
}

void CPU::jumpRegister(const int reg_a, const int reg_b, const int reg_c,
                       const int shift_value) {
  programCounter -= 4;
  programCounter = registers[reg_a];
}
//--------------------- 2.2.8-2.2.10 (Omid) ---------------------
void CPU::shiftLeftLogical(const int reg_a, int reg_b, const int reg_c,
                           const int shift_value) {
  registers[reg_c] = (unsigned)registers[reg_b] << shift_value;
}

void CPU::shiftRightLogical(const int reg_a, int reg_b, const int reg_c,
                            const int shift_value) {
  registers[reg_c] = (unsigned)registers[reg_b] >> shift_value;
}

void CPU::setLessThan(const int reg_a, const int reg_b, const int reg_c,
                      const int shift_value) {
  registers[reg_c] = (registers[reg_a] < registers[reg_b]);
}
