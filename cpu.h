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
    

public:

    uint16_t programCounter;
    uint32_t registers[32];
    CPU();


    std::unordered_map<int, std::function<void(CPU&, int, int, int, int, MEMORY)>> ROptable;
    std::unordered_map<int, std::function<void(CPU&, int, int, int, MEMORY)>> IOptable;



    void branchOnEqual(int reg_a, int reg_b, int immediate, MEMORY memory);
    void loadWord(int reg_a, int reg_b, int immediate, MEMORY memory);
    void loadByteUnsigned(int reg_a, int reg_b, int immediate, MEMORY memory);
    void jump(int reg_a, int reg_b, int immediate, MEMORY memory);

    void storeWord(int reg_a, int reg_b, int immediate, MEMORY memory);
    void storeByte(int reg_a, int reg_b, int immediate, MEMORY memory);
    void orImmediate(int reg_a, int reg_b, int immediate, MEMORY memory);
    void branchOnNotEqual(int reg_a, int reg_b, int immediate, MEMORY memory);

    void jumpAndLink(int reg_a, int reg_b, int immediate, MEMORY memory);
    void subtract(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);
    void or_Op(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);
    void nor(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);

    void add(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);
    void shiftRightArithmetic(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);
    void bitwise_and(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);
    void jumpRegister(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);

    void shiftLeftLogical(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);
    void shiftRightLogical(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);
    void setLessThan(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory);
  
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

