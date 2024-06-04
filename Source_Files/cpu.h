#ifndef CPU_H
#define CPU_H

#include <cstdint>
#include "memory.h"
#include <fstream>
#include <iostream>
#include <functional>
#include <memory>
#include <unordered_map>

class CPU {
private:
    MEMORY& memory;

public:

    uint16_t programCounter;
    int32_t registers[32];
    CPU(MEMORY& memory): memory(memory){
        ROptable = { 
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
    }


    std::unordered_map<int, std::function<void(CPU&, int, int, int, int)>> ROptable;
    std::unordered_map<int, std::function<void(CPU&, int, int, int)>> IOptable;



void branchOnEqual(const int reg_a, const int reg_b, const int immediate);
void loadWord(const int reg_a, const int reg_b, const int immediate);
void loadByteUnsigned(const int reg_a, const int reg_b, const int immediate);
void jump(const int reg_a, const int reg_b, const int immediate);

void storeWord(const int reg_a, const int reg_b, const int immediate);
void storeByte(const int reg_a, const int reg_b, const int immediate);
void orImmediate(const int reg_a, const int reg_b, const int immediate);
void branchOnNotEqual(const int reg_a, const int reg_b, const int immediate);

void jumpAndLink(const int reg_a, const int reg_b, const int immediate);
void subtract(const int reg_a, const int reg_b, const int reg_c, const int shift_value);
void or_Op(const int reg_a, const int reg_b, const int reg_c, const int shift_value);
void nor(const int reg_a, const int reg_b, const int reg_c, const int shift_value);

void add(const int reg_a, const int reg_b, const int reg_c, const int shift_value);
void shiftRightArithmetic(const int reg_a, const int reg_b, const int reg_c, const int shift_value);
void bitwise_and(const int reg_a, const int reg_b, const int reg_c, const int shift_value);
void jumpRegister(const int reg_a, const int reg_b, const int reg_c, const int shift_value);

void shiftLeftLogical(const int reg_a, const int reg_b, const int reg_c, const int shift_value);
void shiftRightLogical(const int reg_a, const int reg_b, const int reg_c, const int shift_value);
void setLessThan(const int reg_a, const int reg_b, const int reg_c, const int shift_value);

  
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
        R_TYPE = 62, // note that all R-type instructions have same opcode, but diff function #s 
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

};


#endif

