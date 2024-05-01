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
}