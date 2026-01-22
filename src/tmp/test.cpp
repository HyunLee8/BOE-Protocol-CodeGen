#define DECODER
#include "Decoder.h"

#include <fstream>
#include <sstream>
#include <iostream>

std::vector<char> readHexFile(const std::string file_name) {
    std::ifstream file(file_name, std::ios::binary);
    if (!file) {
       throw std::runtime_error("Error: cannot open file " + file_name);
    }

    return std::vector<char>((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
}   

std::vector<uint8_t> convertHexToBinary() {

}

int main(int argc, char* arg[]) {
    if(argc < 2) {
        std::cout << "Arguments: program <hexPayload.txt>\n";
        return 1;
    }

    std::vector<char> hexPayload = readHexFile(arg[1]);
    Decoder decoder(hexPayload);
}