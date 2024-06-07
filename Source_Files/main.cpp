#include <any>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Banana.h"

int main(int argc, char* argv[]) {
  Banana mainOS = Banana();
  char* filename = argv[1];
  mainOS.startup(filename);
}