#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<cstdint>
#include<iomanip>

//**Constants
enum StringLength : size_t {
    SESSIONSUBID = 4,
    USERNAME = 4,
    PASSWORD = 10,
    CROSSID = 20,
    CLORDID = 20,
    GIVEUPFIRMID = 4,
    ACCOUNT = 16,
    CMTA_NUMBER = 4,
    CLEARING_ACCOUNT = 4,
    CLEARING_OPTIONAL_DATA = 16,
    FREQUENT_TRADER_ID = 6
};

enum NewOrderCrossBitfieldIndex0 {
    SYMBOL = 0,
    MATURITY_DATE = 1,
    STRIKE_PRICE  = 2,
    PUT_OR_CALL = 3,
    EXEC_INST = 4,
    ATTRIBUTED_QUOTE = 5,
    TARGET_PARTY_ID = 6,
    PREVENT_MATCH = 7
};

enum NewOrderCrossBitfieldIndex1 {
    AUTO_MATCH = 0,
    AUTO_MATCH_PRICE = 1,
    LAST_PRIORITY = 2,
    ACCOUNT = 3,
    CMTA_NUMBER = 4,
    CLEARING_ACCOUNT = 5,
    ROUTING_FIRM_NUMBER = 6,

};

//-- LOGIN REQUEST --
class LoginRequestMessageFields {
public:
    //LOGIN REQUEST MESSAGE FIELDS GROUP
    enum NoUnspecifiedUnitReplay : uint8_t{
        FALSE = 0,
        TRUE = 1
    };

    struct Unit {
        uint8_t UnitNumber;
        uint32_t UnitSequence;
    };

    class LoginRequestMessageFieldsGroup {
        uint8_t ParamGroupType_ = 128;
        NoUnspecifiedUnitReplay NoUnspecifiedUnitReplay_;
        uint8_t NumberOfUnits_;
        std::vector<Unit> units;
    };

    //RETURN BITFIELDS PARAMTER GROUP
    enum ReturnBitfields: uint8_t {
        RETURNBITFIELDS = 0
    };

    struct ReturnBitFieldsParameterGroup {
        uint16_t ParamGroupLength_;
        uint8_t ParaGroupType_ = 129; //0x81 as a hex value
        uint8_t MessageType_;
        uint8_t NumberOfReturnBitfields_;
        std::vector<ReturnBitfields> returnBitfields;
    };

    //GROUP THE LRMF GROUPS AND RBF GROUPS
    struct ParamGroups {
        std::vector<LoginRequestMessageFieldsGroup> LoginRequestMessageFieldGroups;
        std::vector<ReturnBitFieldsParameterGroup> ReturnBitfieldGroups;
    };

private:
    uint16_t StartOfMessage = 47802;
    uint16_t MessageLength;
    uint8_t MessageType = 55;
    uint8_t MatchingUnit = 0;
    uint32_t SequenceNumber = 0;
    std::array<char, StringLength::SESSIONSUBID> SessionSubID;
    std::array<char, StringLength::USERNAME> Username;
    std::array<char, StringLength::PASSWORD> Password;
    uint8_t NumberOfParamGroups;
    std::vector<ParamGroups> ParamGroups;
};

// -- NEW ORDER CROSS -- 
class NewOrderCrossMessageFields {
public:
    enum NewOrderCrossBitfield : uint8_t{
        NEWORDERCROSSBITFIELD = 0,
    };

    enum Side : char {
        BUY = '1',
        SELL = '0',
    };

    enum Capacity : char {
        CUSTOMER = 'C',
        MARKET_MAKER = 'M',
        FIRM = 'F',
        PROFESSIONAL_CUSTOMER = 'U',
        AWAY_MARKET_MAKER = 'N',
        BROKER_DEALER = 'B',
        JOINT_BACK_OFFICE = 'J'
    };

    enum OpenClose : char {
        OPEN = 'O',
        CLOSE = 'C',
        NONE = 'N',
    };
    
    struct RepeatingGroupOfNewOrderCross {
        Side side;
        uint32_t allocQty;
        std::array<char, StringLength::CLORDID> clOrdId;
        Capacity capacity;
        OpenClose openClose;
        std::array<char, StringLength::GIVEUPFIRMID> giveUpFirmId;
        std::array<char, StringLength::ACCOUNT> account;
        std::array<char, StringLength::CMTA_NUMBER> cmtaNumber;
        std::array<char, StringLength::CLEARING_ACCOUNT> clearingAccount;
        std::array<char, StringLength::CLEARING_OPTIONAL_DATA> clearingOptionalData;
        std::array<char, StringLength::FREQUENT_TRADER_ID> frequentTraderId;
    };

    //not repeating groups
    struct OptionalFields {

    };

private:
    uint16_t startOfMessage_ = 47802;
    uint16_t messageLength_;
    uint8_t messageType_ = 65;
    uint8_t matchingUnit_ = 0;
    uint32_t sequenceNumber_;
    std::array<char, StringLength::CROSSID> crossId_;
    char crossType_;
    char crossPrioritization_;
    uint64_t price_;
    uint32_t orderQty_;
    uint8_t numberOfNewOrderCrossBitfields_;
    std::vector<NewOrderCrossBitfield> newOrderCrossBitfields_;
    uint16_t groupCnt_;
    std::vector<RepeatingGroupOfNewOrderCross> RepeatingGroupsOfNewOrderCross_;
    std::vector<OptionalFields> optionalFields;
};
