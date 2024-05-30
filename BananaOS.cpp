// Ideally, you should have a class that acts like the OS and runs the reset sequence, as well as a class that is in charge of handling the memory.

/* 
move CPU functions into other classes (OS,memory, CPU)
tenative list:
Memory:
1)loadword
2)loadbyteunsigned
3)store word
4)storebyte
5)read8/16/32
6)write8/16/32

OS:
1) jump
2) Jumpandlink
3) jumpregister

CPU: 
1)shiftleftlogical
2)shiftrightlogical
3)shiftleftarithmetic
4)shiftrightarithmetic
5) various ops like subtract,add, or

note: use dependancy injection instead of inheritance

lecture:
image: image that varies based on individual computer (GPU)

input: tests io (a/b, up/down, left/right, select/start, stdin)
*/
// dataLoad()
#include "BananaOS.h"

/* How can cpu access memory that is defined in the bananaOS class? specifically when using read8 and write8 (which are memory functions)

*/



void BananaOS::dataLoad(){
    // get data size from 0x81f0
    uint32_t dataSize = bananaMEM->readAddress(0x81f0);
    // get where to store data in ram from 0x81ec
    uint32_t ramAddress = bananaMEM->readAddress(0x81ec);
    // read data from address 0x81e4
    uint32_t dataAddress = bananaMEM->readAddress(0x81e8);
    for (uint32_t i = 0; i < dataSize; i++){
        uint8_t data = bananaMEM->read8(dataAddress);
        // std::cout << data << std::endl;
        bananaMEM->write8(ramAddress, data);
        ramAddress++;
        dataAddress++;
    }

}

// setup()

void BananaOS::setup(){
    bananaCPU->programCounter = 0xfffc;
    std::cout << bananaCPU->programCounter << std::endl;
    bananaCPU->jumpAndLink(0, 0, 0x2078, *bananaMEM); //skipping 81e0 bits
    std::cout << bananaCPU->programCounter << std::endl;
    bananaCPU->programCounter = bananaMEM->readAddress(bananaCPU->programCounter);
    std::cout << bananaCPU->programCounter << std::endl;
    while (bananaCPU->programCounter > 0x8000){
        doInstruction();
        if (bananaCPU->programCounter == 0){
            break;
        }
    }
}

// loop()

void BananaOS::loop(){
    // read into loop addres
    
    
    // std::cout << programCounter << std::endl;  
    bananaCPU->programCounter = 0xfffc;
    bananaCPU->jumpAndLink(0, 0, 0x2079, *bananaMEM);
    uint32_t loopAddress = bananaMEM->readAddress(bananaCPU->programCounter);
    while(1){
        bananaCPU->programCounter = loopAddress;
        while (bananaCPU->programCounter != 0){
            doInstruction();
        }
    }
    // infinite loop 
    // go back to the top of the loop when PC == 0
}


void BananaOS::doInstruction(){
    //store instructions in register[12]
    // loadWord(0, 12, programCounter);
    uint32_t instruction = bananaMEM->readAddress(bananaCPU->programCounter);
    bananaCPU->programCounter += 4;

    uint32_t opcode = instruction >> 26;
    // std::cout << "opcode: " << opcode << std::endl;
    //check if the opcode is a value function
    if (bananaCPU->IOptable.find(opcode) != bananaCPU->IOptable.end()){
        uint32_t reg_a = instruction << 6;
        reg_a = reg_a >> 27;
        uint32_t reg_b = instruction << 11;
        reg_b = reg_b >> 27;
        // if (registers[11] == R_TYPE){
        if (opcode == bananaCPU->R_TYPE){
            // check if function code is valid

            uint32_t function = instruction << 26;

            function = function >> 26;
            // std::cout << "function: " << function << std::endl;


            if (bananaCPU->ROptable.find(function) != bananaCPU->ROptable.end()){
            
                uint32_t reg_c = instruction << 16;
                reg_c = reg_c >> 27;

                uint32_t shift_value = instruction << 21;
                shift_value = shift_value >> 27;
                
                (bananaCPU->ROptable[function])(*bananaCPU, reg_a, reg_b, reg_c, shift_value, *bananaMEM);
            }
        }
        else {

            uint32_t immediate = instruction << 16;
            immediate = immediate >> 16;
            (bananaCPU->IOptable[opcode])(*bananaCPU, reg_a, reg_b, immediate, *bananaMEM);
        }
        
    }
}

void BananaOS::registerSet(int regNum, int value){
    bananaCPU->registers[regNum] = value;
}


void BananaOS::openFile(char * name){
    filename = name;
    bananaMEM->fileReader(filename);
}
