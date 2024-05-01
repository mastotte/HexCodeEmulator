#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "FileAnalyzerFile.h"
#include "cpu.h"

int main(char* argv[]){
    uint16_t programCounter = 0x0000;



    programCounter = 0xfffc;
    char* filename = argv[1];
    std::cout << argv[1] << std::endl;
    FileAnalyzerFile file = FileAnalyzerFile(filename);

    uint32_t setup_address = file.ReadBigEndianInt32(0x01e0);
    std::cout << setup_address << std::endl;
    setup_address -= 32768; // subtracting 8000 hex in order to account for slug file starting at 0x8000

    // Use a while loop to iterate through the instructions 
    std::cout << file.ReadBigEndianInt32(setup_address) << std::endl;

    

}
