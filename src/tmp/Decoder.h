#pragma once

#include "Msgs.h"

#include <array>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>

class Decoder {
    std::vector<char> charHexPayload_;
public:
    Decoder(std::vector<char> hexPayload) :
        charHexPayload_(hexPayload) {
        for(char ch : hexPayload) {
            std::cout << ch;
        }
    }
};

