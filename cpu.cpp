#include "cpu.h"
#include "memory.h"
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
// Instruction Functions
//--------------------- 2.1.1-2.14 (Milan) ---------------------
void CPU::branchOnEqual(int reg_a, int reg_b, int immediate, MEMORY memory) {
    printf("entering branchonequal\n");
    if (registers[reg_a] == registers[reg_b]) {
        programCounter -= 4;
        programCounter += 4 + (4 * immediate);
    }
    std::cout << "beq" << std::endl;
        printf("exiting branchonequal\n");

}

void CPU::loadWord(int reg_a, int reg_b, int immediate, MEMORY memory) {
    std::cout << "load word during pre reg a " << registers[reg_a] << " reg b " << registers[reg_b] << " immediate " << immediate << std::endl;
                printf("entering loadword\n");

    registers[reg_b] = memory.read16(registers[reg_a] + immediate);
    // std::cout << "loadword reg_a " << reg_a << " reg_b " << reg_b << " immediate " <<immediate << std::endl;
    std::cout << "load word during reg a " << registers[reg_a] << " reg b " << registers[reg_b] << " immediate " << immediate << std::endl;
            printf("exiting loadword\n");

}

void CPU::loadByteUnsigned(int reg_a, int reg_b, int immediate, MEMORY memory) {
        printf("entering loadByteUnsigned\n");

    registers[reg_b] = memory.read8(registers[reg_a] + immediate);
    // // Read a byte from memory
    // uint16_t byteFromMemory = memory[registers[reg_a] + immediate];

    // // Extract the lower 8 bits
    // uint8_t lower8Bits = byteFromMemory & 0xFF;

    // // Store the extracted value into registers[reg_b]
    // registers[reg_b] = lower8Bits;
    std::cout << "load byte during reg a " << registers[reg_a] << " reg b " << registers[reg_b] << std::endl;

                printf("exiting loadByteUnsigned\n");

}

void CPU::jump(int reg_a, int reg_b, int immediate, MEMORY memory) {
                    printf("entering jump\n");
    programCounter -= 4;
    programCounter = 4 * immediate;
    std::cout << "j" << std::endl;

                printf("exiting jump\n");

    // std::cout << "j" << std::endl;
}
//--------------------- 2.1.5-2.1.8 (Daniel) ---------------------
void CPU::storeWord(int reg_a, int reg_b, int immediate, MEMORY memory) {
                        printf("entering writ16\n");

    memory.write16(registers[reg_a] + immediate, registers[reg_b]);
    std::cout << "storew stored data" << reg_b << std::endl;
    
    // std::cout << "storew" << std::endl;
                            printf("exiting writ16\n");

    //memory[registers[reg_a] + immediate] = registers[reg_b];
}

void CPU::storeByte(int reg_a, int reg_b, int immediate, MEMORY memory) {
    // // Extract the lower 8 bits from registers[reg_b]
    // uint8_t lower8Bits = registers[reg_b] & 0xFF;
                        printf("entering storebyte\n");

    // // Store the lower 8 bits into memory at the specified address
    // memory[registers[reg_a] + immediate] = lower8Bits;
    memory.write8(registers[reg_a] + immediate, registers[reg_b]);
    std::cout << "store" << std::endl;
                            printf("exiting storebyte\n");

    // std::cout << "store" << std::endl;
}

void CPU::orImmediate(int reg_a, int reg_b, int immediate, MEMORY memory) {
                            printf("entering ori\n");

    registers[reg_b] = (registers[reg_a] | immediate);
    std::cout << "orimmediate during reg a " << registers[reg_a] << " reg b " << registers[reg_b] << std::endl;
                            printf("exiting ori\n");

    // std::cout << "ori" << std::endl;
}

void CPU::branchOnNotEqual(int reg_a, int reg_b, int immediate, MEMORY memory) {
                                printf("entering bne\n");

    if (registers[reg_a] != registers[reg_b]) {
        programCounter -= 4;
        programCounter += 4 + 4 * immediate;
    }
    std::cout << "branchnotequal during reg a " << registers[reg_a] << " reg b " << registers[reg_b] << std::endl;
                                    printf("exiting bne\n");

    // std::cout << "benq" << std::endl;
}
//--------------------- 2.1.9-2.2.3 (Josh) ---------------------
void CPU::jumpAndLink(int reg_a, int reg_b, int immediate, MEMORY memory) {
                                    printf("entering jal\n");

    registers[31] = programCounter + 4;
    programCounter -= 4;
    programCounter = 4 * immediate;
    
    std::cout << "jal" << std::endl;
                                        printf("exiting jal\n");

    // std::cout << "jal" << std::endl;
}

void CPU::subtract(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory) {
                                        printf("entering sub\n");

    registers[reg_c] = registers[reg_a] - registers[reg_b];
    std::cout << "sub" << std::endl;
                                            printf("exiting sub\n");

    // std::cout << "sub" << std::endl;
}

void CPU::or_Op(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory) {
                                            printf("entering orop\n");

    registers[reg_c] = registers[reg_a] | registers[reg_b];
    std::cout << "or" << std::endl;
    // std::cout << "or" << std::endl;
                                                printf("exiting orop\n");

}

void CPU::nor(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory) {
                                                printf("entering nor\n");

    registers[reg_c] = !(registers[reg_a] | registers[reg_b]);
    std::cout << "nor" << std::endl;
                                                    printf("exiting nor\n");

    // std::cout << "nor" << std::endl;
}
//--------------------- 2.2.4-2.2.7 (Max) --------------------
void CPU::add(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory) {
    std::cout << "add during reg a " << registers[reg_a] << " reg b " << registers[reg_b] << "reg c " << registers[reg_c] << std::endl;
     std::cout << "entering add" << std::endl;
    // std::cout << "add" << std::endl;
    registers[reg_c] = registers[reg_a] + registers[reg_b];
     std::cout << "exiting add" << std::endl;
}

void CPU::shiftRightArithmetic(int reg_a,int reg_b, int reg_c, int shift_value, MEMORY memory) {
    std::cout << "sra" << std::endl;
     std::cout << "entering shiftRightArithmetic" << std::endl;
    // std::cout << "sra" << std::endl;
    registers[reg_c] = (signed)registers[reg_b] >> shift_value;
     std::cout << "exiting shiftRightArithmetic" << std::endl;
}

void CPU::bitwise_and(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory) {
     std::cout << "entering bitwise_and" << std::endl;
    registers[reg_c] = registers[reg_a] & registers[reg_b];
    std::cout << "and" << std::endl;
    // std::cout << "and" << std::endl;
     std::cout << "exiting bitwise_and" << std::endl;
}

void CPU::jumpRegister(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory) {
     std::cout << "entering jumpRegister" << std::endl;
    programCounter -= 4;
    programCounter = registers[reg_a];
    // std::cout << "jr regc: " << reg_c  << " reg_a: " << reg_a << " reg_b: " << reg_b << std::endl;
    std::cout << "jumpreg during reg a " << registers[reg_a] << " reg b " << registers[reg_b] << "reg c " << registers[reg_c] << std::endl;
    // std::cout << "jr" << std::endl;
     std::cout << "exiting jumpRegister" << std::endl;
}
//--------------------- 2.2.8-2.2.10 (Omid) ---------------------
void CPU::shiftLeftLogical(int reg_a,int reg_b, int reg_c, int shift_value, MEMORY memory) {
     std::cout << "entering shiftLeftLogical" << std::endl;
    registers[reg_c] = (unsigned)registers[reg_b] << shift_value;
    std::cout << "sll during reg a " << registers[reg_a] << " reg b " << registers[reg_b] << "reg c " << registers[reg_c] << std::endl;
    // std::cout << "sll regc: " << reg_c  << " shift value: " << shift_value << " reg_b: " << reg_b << std::endl;
    // std::cout << "sll" << std::endl;
     std::cout << "exiting shiftLeftLogical" << std::endl;
}

void CPU::shiftRightLogical(int reg_a,int reg_b, int reg_c, int shift_value, MEMORY memory) {
     std::cout << "entering shiftRightLogical" << std::endl;
    registers[reg_c] = (unsigned)registers[reg_b] >> shift_value;
    std::cout << "srl" << std::endl;
    // std::cout << "srl" << std::endl;
     std::cout << "exiting shiftRightLogical" << std::endl;
}

void CPU::setLessThan(int reg_a, int reg_b, int reg_c, int shift_value, MEMORY memory) {
    std::cout << "entering setLessThan" << std::endl;
    registers[reg_c] = (registers[reg_a] < registers[reg_b]);
    std::cout << "slt during reg a " << registers[reg_a] << " reg b " << registers[reg_b] << "reg c " << registers[reg_c] << std::endl;
    // std::cout << "slt regc: " << reg_c  << " reg_a: " << reg_a << " reg_b: " << reg_b << std::endl;
    // std::cout << "slt" << std::endl;
     std::cout << "exiting setLessThan" << std::endl;
}

// read and write functions

CPU::CPU() {
    // Initialize ROptable
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
// seperate things out of CPU class (inheritance)
// memory class 
// OS class contains cpu object and memory object
// everything runs through the OS (using the CPU and memory objects)
// cpu class references memory