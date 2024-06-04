#include "BananaOS.h"


void BananaOS::openFile(const std::string& name) {
    filename = name;
    bananaMEM.fileReader(filename);
}

void BananaOS::dataLoad() {
    uint32_t dataSize = bananaMEM.readAddress(DATA_SIZE);
    uint32_t ramAddress = bananaMEM.readAddress(PROGRAM_DATA_ADDR_RAM);
    uint32_t dataAddress = bananaMEM.readAddress(LOAD_DATA_ADDR_ROM);

    for (uint32_t i = 0; i < dataSize; i++) {
        uint8_t data = bananaMEM.read8(dataAddress);
        bananaMEM.write8(ramAddress, data);
        ramAddress++;
        dataAddress++;
    }
}

void BananaOS::setup() {
    bananaGPU.init();
    bananaCPU.programCounter = PC_RESET;
    bananaCPU.jumpAndLink(0, 0, 0x2078);
    bananaCPU.programCounter = bananaMEM.readAddress(bananaCPU.programCounter);
    while (bananaCPU.programCounter > SLUG_ADDRESS_HEADER) {
        doInstruction();
        if (bananaCPU.programCounter == 0) {
            break;
        }
    }
}

void BananaOS::loop() {
    bananaCPU.programCounter = PC_RESET;
    bananaCPU.jumpAndLink(0, 0, 0x2079);
    // std::cout << bananaCPU.programCounter << std::endl;
    uint32_t loopAddress = bananaMEM.readAddress(bananaCPU.programCounter);
    // std::cout << loopAddress << std::endl;
    while (true) {
        bananaCPU.programCounter = loopAddress;
        // std::cout << bananaCPU.programCounter << std::endl;
        while (bananaCPU.programCounter != 0) {
            
            doInstruction(); //segfaulting
            bananaGPU.handleInput();
            bananaGPU.decodeAndDisplay();

            // int controllerInput = bananaMEM.read8(CONTROLLER_INPUT_MEMORY);
            // bananaMEM.write8(CONTROLLER_INPUT_MEMORY, CharacterMaskMap[controllerInput]);
        }
    }
}

void BananaOS::doInstruction(){
    
    //store instructions in register[12]
    // loadWord(0, 12, programCounter);
    uint32_t instruction = bananaMEM.readAddress(bananaCPU.programCounter);
    bananaCPU.programCounter += 4;
    uint32_t opcode = instruction >> 26;
    /*std::cout<<"instruction: "<<instruction<<std::endl;
    std::cout<<"program counter: "<<bananaCPU.programCounter<<std::endl;
    std::cout<<"opcode: "<<opcode<<std::endl;*/
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

void BananaOS::startup(char* filename){
    openFile(filename);
    // get data size from 0x81f0
    // get where to store data in ram from 0x81ec
    // read data from address 0x81e4
    dataLoad();

    registerSet(29, 0x6000);

    setup();
    
    loop();
}
