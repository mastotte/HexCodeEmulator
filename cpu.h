#ifndef CPU_H //added header guards
#define CPU_H 

#include <cstdint>
#include <iostream>

class CPU {
    private:
        uint16_t programCounter;
        uint16_t registers[32];
        uint16_t *memory;
    public:
        //--------------------- 2.1.1-2.14 (Milan) ---------------------
        void branchOnEqual(int reg_a, int reg_b, int immediate){
            if (registers[reg_a] == registers[reg_b]){
                programCounter += 4+4*immediate;
            }
        }

        void loadWord(int reg_a, int reg_b, int immediate){
            registers[reg_b] = memory[registers[reg_a] + immediate];
        }

        void loadByteUnsigned(int reg_a, int reg_b, int immediate){
            registers[reg_b] = memory[registers[reg_a] + immediate]; // what does (7:0) mean?
        }

        void jump(int immediate){
            programCounter = 4 * immediate; 
        }

        //--------------------- 2.1.5-2.1.8 (Daniel) ---------------------
        void storeWord(int reg_a, int reg_b, int immediate){
            memory[registers[reg_a] + immediate] = registers[reg_b];
        }
        void storeByte(int reg_a, int reg_b, int immediate){
            
        }
        void orImmediate(int reg_a, int reg_b, int immediate){
            (registers[reg_b] = registers[reg_a] | immediate);
        }
        void branchOnNotEqual(int reg_a, int reg_b, int immediate){
            if (registers[reg_a] != registers[reg_b]){
                programCounter += 4+4*immediate;
            }
        }
        

        //--------------------- 2.1.9-2.2.3 (Josh) ---------------------
        void jumpAndLink(int immediate){
        	registers[31] = programCounter + 4;
        	programCounter = 4*immediate;
        }
        void subtract(int reg_a, int reg_b, int reg_c){
        	registers[reg_c] = registers[reg_a] = registers[reg_b];
        }
        void or_Op(int reg_a, int reg_b, int reg_c){
        	registers[reg_c] = registers[reg_a] or registers[reg_b];
        }
        void nor(int reg_a, int reg_b, int reg_c){
        	registers[reg_c] = not (registers[reg_a] or registers[reg_b]);
        }
        //--------------------- 2.2.4-2.2.7 (Max) --------------------
        void add(int reg_a, int reg_b, int reg_c){
            registers[reg_c] = registers[reg_a] + registers[reg_b];
        }
        void shiftRightArithmetic(int reg_b, int reg_c, int shift_value){
            registers[reg_c] = (signed) registers[reg_b] >> shift_value;
        }
        void bitwise_and(int reg_a, int reg_b, int reg_c){      //Can't use 'and' as the function name gives an error
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
        void setLessThan (int reg_a, int reg_b, int reg_c, int shift_value){ 
            registers[reg_c] =  (registers[reg_a] < registers[reg_b]);
        }

};
#endif
