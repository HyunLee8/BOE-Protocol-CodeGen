#pragma once

#include <array>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

class Decoder {
public:
    Decoder(std::vector<char> hexPayload) {
        for(char ch : hexPayload) {
            std::cout << ch;
        }
    }
};

