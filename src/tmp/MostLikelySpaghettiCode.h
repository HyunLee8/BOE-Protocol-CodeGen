#include<iostream>
#include<string>
#include<vector>
#include<cstdint>
#include<iomanip>

//create a method that takes encoded values and put it in unordered map then pass through LoginRequest.

struct ParamGroups {
    uint8_t UnitNumber;
    uint32_t UnitSequence;
};

enum ReturnBitfields: uint8_t {
    RETURNBITFIELDS = 0
};

//table 10
class ReturnBitFieldsParameterGroup {
    uint16_t ParamGroupLength_;
    uint8_t ParaGroupType_ = 129; //0x81 as a hex value
    uint8_t MessageType_;
    uint8_t NumberOfReturnBitfields_;
    std::vector<ReturnBitfields> returnBitfields;
};


class LoginRequest {
public:
    uint16_t startOfMessage;
    uint16_t messageLength;
    uint8_t messageType;
    uint8_t matchingUnit;
    uint32_t sequenceNumber;
    char sessionSubID[4];
    char userName[4];
    char password[10];

    uint8_t numberOfParamGroups;
    std::vector<ParamGroups> paramGroups;

    LoginRequest(uint16_t encodedStartOfMessage, uint16_t encodedMessageLength, uint8_t encodedMessageType, 
        uint8_t encodedMatchingUnit, uint32_t encodedSequenceNumber, char encodedSessionSubID[4], char encodedUserName[4], char encodedPassword[10],
        uint8_t encodedNumberOfParamGroups, std::vector<ParamGroups> encodedParamGroups) : 
        startOfMessage(encodedStartOfMessage),
        messageLength(encodedMessageLength),
        messageType(encodedMessageType),
        matchingUnit(encodedMatchingUnit),
        sequenceNumber(encodedSequenceNumber),
        numberOfParamGroups(encodedNumberOfParamGroups),
        paramGroups(encodedParamGroups) {
            std::memcpy(sessionSubID, encodedSessionSubID, 4);
            std::memcpy(userName, encodedUserName, 4);
            std::memcpy(password, encodedPassword, 10);
    }
};
