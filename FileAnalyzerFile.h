// Copyright (c) 2024 Ethan Sifferman.
// All rights reserved. Distribution Prohibited.

#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <vector>

class FileAnalyzerFile {
 protected:
  std::unique_ptr<char[]> contents_;

 private:
  std::string filename_;
  size_t file_size_;
 public:
  std::string filename() const { return filename_; }
  size_t file_size() const { return file_size_; }
  FileAnalyzerFile(const std::string& filename);
  uint32_t ReadBigEndianInt32(const size_t& addr) const;
};
