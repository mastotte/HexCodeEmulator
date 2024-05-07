#include "CPU.h"

//--------------------- 2.1.1-2.14 (Milan) ---------------------
void CPU::branchOnEqual(int reg_a, int reg_b, int immediate)
{
    if (registers[reg_a] == registers[reg_b])
    {
        programCounter += 4 + 4 * immediate;
    }
}

void CPU::loadWord(int reg_a, int reg_b, int immediate)
{
    registers[reg_b] = memory[registers[reg_a] + immediate];
}

void CPU::loadByteUnsigned(int reg_a, int reg_b, int immediate)
{
    registers[reg_b] = memory[registers[reg_a] + immediate];
}

void CPU::jump(int immediate)
{
    programCounter = 4 * immediate;
}
//--------------------- 2.1.5-2.1.8 (Daniel) ---------------------
void CPU::storeWord(int reg_a, int reg_b, int immediate)
{
    memory[registers[reg_a] + immediate] = registers[reg_b];
}

void CPU::storeByte(int reg_a, int reg_b, int immediate)
{
}

void CPU::orImmediate(int reg_a, int reg_b, int immediate)
{
    registers[reg_b] = registers[reg_a] | immediate;
}

void CPU::branchOnNotEqual(int reg_a, int reg_b, int immediate)
{
    if (registers[reg_a] != registers[reg_b])
    {
        programCounter += 4 + 4 * immediate;
    }
}
//--------------------- 2.1.9-2.2.3 (Josh) ---------------------
void CPU::jumpAndLink(int immediate)
{
    registers[31] = programCounter + 4;
    programCounter = 4 * immediate;
}

void CPU::subtract(int reg_a, int reg_b, int reg_c)
{
    registers[reg_c] = registers[reg_a] = registers[reg_b];
}

void CPU::or_Op(int reg_a, int reg_b, int reg_c)
{
    registers[reg_c] = registers[reg_a] | registers[reg_b];
}

void CPU::nor(int reg_a, int reg_b, int reg_c)
{
    registers[reg_c] = ~(registers[reg_a] | registers[reg_b]);
}
//--------------------- 2.2.4-2.2.7 (Max) --------------------
void CPU::add(int reg_a, int reg_b, int reg_c)
{
    registers[reg_c] = registers[reg_a] + registers[reg_b];
}

void CPU::shiftRightArithmetic(int reg_b, int reg_c, int shift_value)
{
    registers[reg_c] = (signed)registers[reg_b] >> shift_value;
}

void CPU::bitwise_and(int reg_a, int reg_b, int reg_c)
{
    registers[reg_c] = registers[reg_a] & registers[reg_b];
}

void CPU::jumpRegister(int reg_a)
{
    programCounter = registers[reg_a];
}
//--------------------- 2.2.8-2.2.10 (Omid) ---------------------
void CPU::shiftLeftLogical(int reg_b, int reg_c, int shift_value)
{
    registers[reg_c] = registers[reg_b] << shift_value;
}

void CPU::shiftRightLogical(int reg_b, int reg_c, int shift_value)
{
    registers[reg_c] = registers[reg_b] >> shift_value;
}

void CPU::setLessThan(int reg_a, int reg_b, int reg_c, int shift_value)
{
    registers[reg_c] = (registers[reg_a] < registers[reg_b]);
}
