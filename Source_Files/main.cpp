#include <any>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "BananaOS.h"

int main(int argc, char* argv[]) {
  BananaOS mainOS = BananaOS();
  char* filename = argv[1];
  mainOS.startup(filename);
}