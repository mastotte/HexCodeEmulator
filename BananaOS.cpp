#include "BananaOS.h"

BananaOS::BananaOS() {
    bananaMEM = std::make_unique<MEMORY>();
    bananaCPU = std::make_unique<CPU>();
}

void BananaOS::openFile(const std::string& name) {
    filename = name;
    bananaMEM->fileReader(filename);
}

void BananaOS::dataLoad() {
    uint32_t dataSize = bananaMEM->readAddress(0x81f0);
    uint32_t ramAddress = bananaMEM->readAddress(0x81ec);
    uint32_t dataAddress = bananaMEM->readAddress(0x81e8);

    for (uint32_t i = 0; i < dataSize; i++) {
        uint8_t data = bananaMEM->read8(dataAddress);
        bananaMEM->write8(ramAddress, data);
        ramAddress++;
        dataAddress++;
    }
}

void BananaOS::setup() {
    bananaCPU->programCounter = 0xfffc;
    bananaCPU->jumpAndLink(0, 0, 0x2078, *bananaMEM);
    bananaCPU->programCounter = bananaMEM->readAddress(bananaCPU->programCounter);
    while (bananaCPU->programCounter > 0x8000) {
        doInstruction();
        if (bananaCPU->programCounter == 0) {
            break;
        }
    }
}

void BananaOS::loop() {
    bananaCPU->programCounter = 0xfffc;
    bananaCPU->jumpAndLink(0, 0, 0x2079, *bananaMEM);
    std::cout << bananaCPU->programCounter << std::endl;
    uint32_t loopAddress = bananaMEM->readAddress(bananaCPU->programCounter);
    std::cout << bananaCPU->programCounter << std::endl;
    while (true) {
        bananaCPU->programCounter = loopAddress;
        // std::cout << bananaCPU->programCounter << std::endl;
        while (bananaCPU->programCounter != 0) {
            doInstruction();
        }
    }
}

void BananaOS::doInstruction() {
    uint32_t instruction = bananaMEM->readAddress(bananaCPU->programCounter);
    bananaCPU->programCounter += 4;

    uint32_t opcode = instruction >> 26;
    if (bananaCPU->IOptable.find(opcode) != bananaCPU->IOptable.end()) {
        uint32_t reg_a = (instruction >> 21) & 0x1F;
        uint32_t reg_b = (instruction >> 16) & 0x1F;

        if (opcode == bananaCPU->R_TYPE) {
            uint32_t function = instruction & 0x3F;
            if (bananaCPU->ROptable.find(function) != bananaCPU->ROptable.end()) {
                uint32_t reg_c = (instruction >> 11) & 0x1F;
                uint32_t shift_value = (instruction >> 6) & 0x1F;
                bananaCPU->ROptable[function](*bananaCPU, reg_a, reg_b, reg_c, shift_value, *bananaMEM);
            }
        } else {
            uint32_t immediate = instruction & 0xFFFF;
            bananaCPU->IOptable[opcode](*bananaCPU, reg_a, reg_b, immediate, *bananaMEM);
        }
    }
}

void BananaOS::registerSet(int regNum, int value) {
    bananaCPU->registers[regNum] = value;
}
