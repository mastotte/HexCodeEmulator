#include "FileAnalyzerFile.h"

#include <fstream>
#include <iostream>

FileAnalyzerFile::FileAnalyzerFile(
    const std::string& filename)
    : filename_(filename) {


  // Open the file
  std::ifstream file(filename, std::ios::binary | std::ios::ate);

  // Check if file is opened successfully
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }

  // Get the size of the file
  file_size_ = file.tellg();

  // Reset file pointer to the beginning
  file.seekg(0, std::ios::beg);

  // Allocate memory to store the contents of the file
  contents_ = std::make_unique<char[]>(file_size_);
        
  // stores value (displays differently based on computer), 1 byte in each index) actually reading in 4 at a time (the actual instruction)

    
  // Read the contents of the file into the allocated memory
  file.read(contents_.get(), file_size_);

  // Close the file
  file.close();
}

uint32_t FileAnalyzerFile::ReadBigEndianInt32(const size_t& addr) const {
  uint32_t out = 0;
  for (int i = 0; i < 4; i++) {
    out <<= 8;
    out |= (uint8_t)contents_[addr + i];
  }
  return out;
}
