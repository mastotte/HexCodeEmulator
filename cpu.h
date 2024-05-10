#ifndef CPU_H
#define CPU_H

#include <cstdint>
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
    std::unique_ptr<char[]> memory;
    CPU();


    std::unordered_map<int, std::function<void(CPU&, int, int, int, int)>> ROptable;
    std::unordered_map<int, std::function<void(CPU&, int, int, int)>> IOptable;

    void FileAnalyzerFile(const std::string& filename);
    uint32_t ReadBigEndianInt32(const size_t& addr) const;

    void branchOnEqual(int reg_a, int reg_b, int immediate);
    void loadWord(int reg_a, int reg_b, int immediate);
    void loadByteUnsigned(int reg_a, int reg_b, int immediate);
    void jump(int reg_a, int reg_b, int immediate);

    void storeWord(int reg_a, int reg_b, int immediate);
    void storeByte(int reg_a, int reg_b, int immediate);
    void orImmediate(int reg_a, int reg_b, int immediate);
    void branchOnNotEqual(int reg_a, int reg_b, int immediate);

    void jumpAndLink(int reg_a, int reg_b, int immediate);
    void subtract(int reg_a, int reg_b, int reg_c, int shift_value);
    void or_Op(int reg_a, int reg_b, int reg_c, int shift_value);
    void nor(int reg_a, int reg_b, int reg_c, int shift_value);

    void add(int reg_a, int reg_b, int reg_c, int shift_value);
    void shiftRightArithmetic(int reg_a, int reg_b, int reg_c, int shift_value);
    void bitwise_and(int reg_a, int reg_b, int reg_c, int shift_value);
    void jumpRegister(int reg_a, int reg_b, int reg_c, int shift_value);

    void shiftLeftLogical(int reg_a, int reg_b, int reg_c, int shift_value);
    void shiftRightLogical(int reg_a, int reg_b, int reg_c, int shift_value);
    void setLessThan(int reg_a, int reg_b, int reg_c, int shift_value);

    uint8_t read8(uint32_t address);
    uint16_t read16(uint32_t address);

    void write8(uint32_t address, uint8_t data);
    void write16(uint32_t address, uint16_t data);

    void dataLoad();

    void setup();

    void loop();

    void doInstruction();


        
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

