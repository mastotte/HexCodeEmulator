#include "BananaOS.h"






void BananaOS::openFile(const std::string& name) {
    filename = name;
    bananaMEM.fileReader(filename);
}

void BananaOS::dataLoad() {
    uint32_t dataSize = bananaMEM.readAddress(0x81f0);
    uint32_t ramAddress = bananaMEM.readAddress(0x81ec);
    uint32_t dataAddress = bananaMEM.readAddress(0x81e8);

    for (uint32_t i = 0; i < dataSize; i++) {
        uint8_t data = bananaMEM.read8(dataAddress);
        bananaMEM.write8(ramAddress, data);
        ramAddress++;
        dataAddress++;
    }
}

void BananaOS::setup() {
    bananaCPU.programCounter = 0xfffc;
    bananaCPU.jumpAndLink(0, 0, 0x2078);
    bananaCPU.programCounter = bananaMEM.readAddress(bananaCPU.programCounter);
    while (bananaCPU.programCounter > 0x8000) {
        doInstruction();
        if (bananaCPU.programCounter == 0) {
            break;
        }
    }
}

void BananaOS::loop() {
    bananaCPU.programCounter = 0xfffc;
    bananaCPU.jumpAndLink(0, 0, 0x2079);
    // std::cout << bananaCPU.programCounter << std::endl;
    uint32_t loopAddress = bananaMEM.readAddress(bananaCPU.programCounter);
    // std::cout << loopAddress << std::endl;
   
    while (true) {
        bananaCPU.programCounter = loopAddress;
        // std::cout << bananaCPU.programCounter << std::endl;
        while (bananaCPU.programCounter != 0) {
            doInstruction();
            int controllerInput = bananaMEM.read8(CONTROLLER_INPUT_MEMORY);
            bananaMEM.write8(CONTROLLER_INPUT_MEMORY, CharacterMaskMap[controllerInput]);
        }
    }
}

void BananaOS::doInstruction(){
    //store instructions in register[12]
    // loadWord(0, 12, programCounter);
    uint32_t instruction = bananaMEM.readAddress(bananaCPU.programCounter);
    bananaCPU.programCounter += 4;
    uint32_t opcode = instruction >> 26;
    
    // std::cout << "opcode: " << opcode << std::endl;
    //check if the opcode is a value function
    if (bananaCPU.IOptable.find(opcode) != bananaCPU.IOptable.end()){
        uint32_t reg_a = instruction << 6;
        reg_a = reg_a >> 27;
        uint32_t reg_b = instruction << 11;
        reg_b = reg_b >> 27;
        // if (registers[11] == R_TYPE){
        if (opcode == bananaCPU.R_TYPE){
            // check if function code is valid

            uint32_t function = instruction << 26;

            function = function >> 26;
            // std::cout << "function: " << function << std::endl;


            if (bananaCPU.ROptable.find(function) != bananaCPU.ROptable.end()){
            
                uint32_t reg_c = instruction << 16;
                reg_c = reg_c >> 27;
                // std::cout << "before reg a " << bananaCPU.registers[reg_a] << " reg b " << bananaCPU.registers[reg_b] << "reg c " << bananaCPU.registers[reg_c] << std::endl;
                uint32_t shift_value = instruction << 21;
                shift_value = shift_value >> 27;
                
                (bananaCPU.ROptable[function])(bananaCPU, reg_a, reg_b, reg_c, shift_value);
                // std::cout << "after reg a " << bananaCPU.registers[reg_a] << " reg b " << bananaCPU.registers[reg_b] << "reg c " << bananaCPU.registers[reg_c] << std::endl;
            }
        }
        else {
            // std::cout << "before reg a " << bananaCPU.registers[reg_a] << " reg b " << bananaCPU.registers[reg_b] << std::endl;
            uint32_t immediate = instruction << 16;
            immediate = immediate >> 16;
            (bananaCPU.IOptable[opcode])(bananaCPU, reg_a, reg_b, immediate);
            // std::cout << "after reg a " << bananaCPU.registers[reg_a] << " reg b " << bananaCPU.registers[reg_b] << std::endl;
        }
        
    }
}
void BananaOS::registerSet(int regNum, int value) {
    bananaCPU.registers[regNum] = value;
}
