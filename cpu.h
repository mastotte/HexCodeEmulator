#include <cstdint>
#include <iostream>

class CPU {
    private:
        uint16_t programCounter;
        uint16_t *registers;
    public:
        void branchOnEqual(int reg_a, int reg_b, int immediate){
            if (registers[reg_a] == registers[reg_b]){
                programCounter += 4+4*immediate;
            }
        }
        void add(int reg_a, int reg_b, int reg_c){
            registers[reg_c] = registers[reg_a] + registers[reg_b];
        }
        void shiftRightArithmetic(int reg_b, int reg_c, int shift_value){
            registers[reg_c] = (signed) registers[reg_b] >> shift_value;
        }
        void and(int reg_a, int reg_b, int reg_c){
            registers[reg_c] = registers[reg_a] & registers[reg_b];
        }
        void jumpRegister(int reg_a){
            programCounter = registers[reg_a];
        }
}