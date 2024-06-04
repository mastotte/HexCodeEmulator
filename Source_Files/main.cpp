#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <unordered_map>
#include <any>

#include "BananaOS.h"

int main(int argc, char* argv[]){
    BananaOS mainOS = BananaOS();
    char* filename = argv[1];
    mainOS.startup(filename);
}