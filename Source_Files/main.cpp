#include <any>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Banana.h" 

//avoid using char*, use std::string
int main(int argc, char* argv[]) {
  Banana mainOS = Banana();
  //char* filename = "../hws/hello_world1.slug";
  char* filename = argv[1];
  //char* filename = argv[1];
  mainOS.startup(filename);
}