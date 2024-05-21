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

void BananaOS::dataLoad(){
    // get data size from 0x81f0
    uint32_t dataSize = ReadBigEndianInt32(0x81f0);
    // get where to store data in ram from 0x81ec
    uint32_t ramAddress = ReadBigEndianInt32(0x81ec);
    // read data from address 0x81e4
    uint32_t dataAddress = ReadBigEndianInt32(0x81e8);
    for (uint32_t i = 0; i < dataSize; i++){
        uint8_t data = read8(dataAddress);
        // std::cout << data << std::endl;
        write8(ramAddress, data);
        ramAddress++;
        dataAddress++;
    }

}

// setup()

void BananaOS::setup(){
    programCounter = 0xfffc;
    jumpAndLink(0, 0, 0x2078); //skipping 81e0 bits
    programCounter = ReadBigEndianInt32(programCounter);
    while (programCounter > 0x8000){
        doInstruction();
        if (programCounter == 0){
            break;
        }
    }
}

// loop()

void BananaOS::loop(){
    // read into loop addres
    
    
    // std::cout << programCounter << std::endl;  
    programCounter = 0xfffc;
    jumpAndLink(0, 0, 0x2079);
    uint32_t loopAddress = ReadBigEndianInt32(programCounter);
    while(1){
        programCounter = loopAddress;
        while (programCounter != 0){
            doInstruction();
        }
    }
    // infinite loop 
    // go back to the top of the loop when PC == 0
}


void BananaOS::doInstruction(){
    //store instructions in register[12]
    // loadWord(0, 12, programCounter);
    uint32_t instruction = ReadBigEndianInt32(programCounter);
    programCounter += 4;

    uint32_t opcode = instruction >> 26;
    // std::cout << "opcode: " << opcode << std::endl;
    //check if the opcode is a value function
    if (IOptable.find(opcode) != IOptable.end()){
        uint32_t reg_a = instruction << 6;
        reg_a = reg_a >> 27;
        uint32_t reg_b = instruction << 11;
        reg_b = reg_b >> 27;
        // if (registers[11] == R_TYPE){
        if (opcode == R_TYPE){
            // check if function code is valid

            uint32_t function = instruction << 26;

            function = function >> 26;
            // std::cout << "function: " << function << std::endl;


            if (ROptable.find(function) != ROptable.end()){
            
                uint32_t reg_c = instruction << 16;
                reg_c = reg_c >> 27;

                uint32_t shift_value = instruction << 21;
                shift_value = shift_value >> 27;
                
                (ROptable[function])(*this, reg_a, reg_b, reg_c, shift_value);
            }
        }
        else {

            uint32_t immediate = instruction << 16;
            immediate = immediate >> 16;
            (IOptable[opcode])(*this, reg_a, reg_b, immediate);
        }
        
    }
    
}
