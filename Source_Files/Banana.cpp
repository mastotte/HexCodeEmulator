#include "Banana.h"

void Banana::openFile(const std::string& name) {
  filename = name;
  bananaMEM.fileReader(filename);
}

void Banana::dataLoad() {
  uint16_t dataSize = bananaMEM.readAddress(DATA_SIZE);
  uint16_t ramAddress = bananaMEM.readAddress(PROGRAM_DATA_ADDR_RAM);
  uint16_t dataAddress = bananaMEM.readAddress(LOAD_DATA_ADDR_ROM);

  for (uint16_t i = 0; i < dataSize; i++) {
    uint8_t data = bananaMEM.read8(dataAddress);
    bananaMEM.write8(ramAddress, data);
    ramAddress++;
    dataAddress++;
  }
}

void Banana::setup() {
  bananaGPU.init();
  bananaCPU.programCounter = PC_RESET;
  bananaCPU.jumpAndLink(0, 0, SETUP_ADD);
  bananaCPU.programCounter = bananaMEM.readAddress(bananaCPU.programCounter);
  while (bananaCPU.programCounter > SLUG_ADDRESS_HEADER) {
    doInstruction();
    if (bananaCPU.programCounter == 0) {
      break;
    }
  }
}

void Banana::loop() {
  bananaCPU.programCounter = PC_RESET;
  bananaCPU.jumpAndLink(0, 0, LOOP_ADD);
  uint32_t loopAddress = bananaMEM.readAddress(bananaCPU.programCounter);
  while (true) {
    bananaCPU.programCounter = loopAddress;

    while (bananaCPU.programCounter != 0) {
      doInstruction();
    }
    bananaMEM.write8(CONTROLLER_INPUT_MEMORY, 0x0000);
    bananaGPU.decodeAndDisplay();
    bananaGPU.handleInput();
  }
  bananaGPU.quit();
}

void Banana::doInstruction() {
  uint32_t instruction = bananaMEM.readAddress(bananaCPU.programCounter);
  bananaCPU.programCounter += 4;
  uint32_t opcode = instruction >> 26;

  if (bananaCPU.IOptable.find(opcode) != bananaCPU.IOptable.end()) {
    uint32_t reg_a = instruction << 6;
    reg_a = reg_a >> 27;
    uint32_t reg_b = instruction << 11;
    reg_b = reg_b >> 27;
    if (opcode == bananaCPU.R_TYPE) {
      uint32_t function = instruction << 26;

      function = function >> 26;

      if (bananaCPU.ROptable.find(function) != bananaCPU.ROptable.end()) {
        uint32_t reg_c = instruction << 16;
        reg_c = reg_c >> 27;

        uint32_t shift_value = instruction << 21;
        shift_value = shift_value >> 27;

        (bananaCPU.ROptable[function])(bananaCPU, reg_a, reg_b, reg_c,
                                       shift_value);
      }
    } else {
      uint32_t immediate = instruction << 16;
      immediate = immediate >> 16;
      (bananaCPU.IOptable[opcode])(bananaCPU, reg_a, reg_b, immediate);
    }
  }
}

void Banana::registerSet(int regNum, int value) {
  bananaCPU.registers[regNum] = value;
}

void Banana::startup(std::string filename) {
  openFile(filename);

  dataLoad();

  registerSet(29, 0x6000);

  setup();

  loop();
}
