#include <iostream>
#include <string>
#include <vector>
#include <cstdint>
#include <iomanip>

struct Messsage{
    uint16_t start;
    uint16_t length;
    uint8_t type;
    uint8_t unit;
    uint32_t sequenceNumber;
    char ClOrdID[20];
    char side;
    uint32_t OrderQty;
    uint8_t NumberOfNewOrderBitfields;
    
}
int main() {
    
    return 0;
}

void encode(std::string input) {

}