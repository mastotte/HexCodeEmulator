#ifndef CPU_H
#define CPU_H

#include <cstdint>

class CPU {
private:
    

public:
    uint16_t programCounter;
    uint16_t registers[32];
    uint16_t *memory;
    void branchOnEqual(int reg_a, int reg_b, int immediate);
    void loadWord(int reg_a, int reg_b, int immediate);
    void loadByteUnsigned(int reg_a, int reg_b, int immediate);
    void jump(int reg_a, int reg_b, int immediate);

    void storeWord(int reg_a, int reg_b, int immediate);
    void storeByte(int reg_a, int reg_b, int immediate);
    void orImmediate(int reg_a, int reg_b, int immediate);
    void branchOnNotEqual(int reg_a, int reg_b, int immediate);

    void jumpAndLink(int reg_a, int reg_b, int immediate);
    void subtract(int reg_a, int reg_b, int reg_c);
    void or_Op(int reg_a, int reg_b, int reg_c);
    void nor(int reg_a, int reg_b, int reg_c);

    void add(int reg_a, int reg_b, int reg_c);
    void shiftRightArithmetic(int reg_b, int reg_c, int shift_value);
    void bitwise_and(int reg_a, int reg_b, int reg_c);
    void jumpRegister(int reg_a, int reg_b, int reg_c);

    void shiftLeftLogical(int reg_b, int reg_c, int shift_value);
    void shiftRightLogical(int reg_b, int reg_c, int shift_value);
    void setLessThan(int reg_a, int reg_b, int reg_c, int shift_value);
};

#endif

