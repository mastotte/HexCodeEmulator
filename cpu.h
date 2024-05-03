#include <cstdint>
#include <iostream>

class CPU {
    private:
        uint16_t programCounter;
        uint16_t *registers;
    public:
        //--------------------- 2.1.1-2.14 (Milan) ---------------------
        void branchOnEqual(int reg_a, int reg_b, int immediate){
            if (registers[reg_a] == registers[reg_b]){
                programCounter += 4+4*immediate;
            }
        }

        //--------------------- 2.1.5-2.1.8 (Daniel) ---------------------
        

        //--------------------- 2.1.9-2.2.3 (Josh) ---------------------

        //--------------------- 2.2.4-2.2.7 (Max) ---------------------
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
        //--------------------- 2.2.8-2.2.10 (Omid) ---------------------
        void shiftLeftLogical (int reg_b, int reg_c, int shift_value){
            registers[reg_c] = registers[reg_b] << shift_value;
        }


        void shiftRightLogical (int reg_b, int reg_c, int shift_value){
            registers[reg_c] =  registers[reg_b] >> shift_value; 
        }

        void setLessThan (int reg_b, int reg_c, int shift_value){
            registers[reg_c] =  (R[reg_a] < R[reg_b]);
        }



}
