#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "FileAnalyzerFile.h"

int main(int argc, char* argv[]){
    char* filename = argv[1];
    std::cout << argv[1] << std::endl;
    FileAnalyzerFile file = FileAnalyzerFile(filename);


    // std::ifstream file(filename, std::ios::binary | std::ios::ate);

    // // Check if file is opened successfully
    // if (!file.is_open()) {
    // std::cerr << "Error opening file: " << filename << std::endl;
    //     return 0;
    // }

    // // Get the size of the file
    // int file_size_ = file.tellg();

    // // Reset file pointer to the beginning
    // file.seekg(0, std::ios::beg);

    // // Allocate memory to store the contents of the file
    // std::unique_ptr<char[]> contents_ = std::make_unique<char[]>(file_size_);

    // // Read the contents of the file into the allocated memory
    // file.read(contents_.get(), file_size_);

    // // Close the file
    // file.close();

    std::cout <<file.ReadBigEndianInt32(0x01e0) << std::endl;
    
    // std::cout << (int) contents_[480] << std::endl;
    // std::cout << (int) contents_[481] << std::endl;
    // std::cout << int((uint8_t) (contents_[482])) << std::endl;
    // std::cout << (int) contents_[483] << std::endl;
    // return 0;
}
