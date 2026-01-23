#pragma once

#include<string>
#include<vector>
#include<array>
#include<cstdint>
#include<iomanip>
#include<unordered_map>
#include<variant>

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
    FREQUENT_TRADER_ID = 6,
    SYMBOL = 8,
    TARGET_PARTY_ID = 4,
    PREVENT_MATCH = 3,
    ROUTING_FIRM_ID = 4,
    CLIENT_ID_ATTR = 4,
    EQUITY_BUY_CLEARING_FIRM = 4,
    EQUITY_SELL_CLEARING_FIRM = 4
};

enum Offsets : size_t {
    START_OF_MESSAGE = 2,
    MESSAGE_LENGTH = 2,
    MESSAGE_TYPE = 4,
    MATCHING_UNIT = 5,
    SEQUENCE_NUMBER = 6,
    CROSS_ID = 10,
    CROSS_TYPE = 30,
    CROSS_PRIORITZATION = 31,
    PRICE = 32,
    ORDER_QTY = 40,
    NUMBER_OF_NEW_ORDER_CROSS_BITFIELDS = 44,
    NEW_ORDER_CROSS_BITFIELDS = 45
};


//DIFINITIVE VARIABLES
enum StartOfMesageEnumOptions : uint16_t {
    STARTOFMESSAGE = 47802
};

//Indexes
/*

INDEXING may need later

class NewOrderCrossBitfields {
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
        ROUTING_FIRM_ID = 6,
        CLEARING_OPTIONAL_DATA = 7
    };
    
    enum NewOrderCrossBitfieldIndex2 {
        CLINET_ID_ATTR = 0,
        EQUITY_TRADE_PRICE = 1,
        EQUITY_TRADE_SIZE = 2,
        EQUITY_TRADE_VENUE = 3,
        EQUITY_TRANSACT_TIME = 4,
        EQUITY_BUY_CLEARING_FIRM = 5,
        EQUITY_SELL_CLEARING_FIRM = 6,
        SESSION_ELIGIBILITY = 7
    };
    
    enum NewOrderCrossBitfieldIndex3 {
        COMPRESSION = 0,
        ORS = 1,
        FREQUENT_TRADER_ID = 2,
        RESERVED_1 = 3,
        RESERVED_2 = 4,
        RESERVED_3 = 5,
        RESERVED_4 = 6,
        RESERVED_5 = 7
    };
};

*/

class NewOrderCrossBitfield {
public:
    enum SessionEligibility : char {
        REGULAR_TRADING_HOURS = 'R',
        GLOBAL_TRADING_HOURS = 'A',
        CURB_SESSION = 'B'
    };

    enum BitfieldIndex : uint8_t {
        INDEX_0 = 0,
        INDEX_1 = 1,
        INDEX_2 = 2,
        INDEX_3 = 3,
    };

    struct NewOrderCrossBitfieldIndex0 {
        std::array<char, StringLength::SYMBOL> symbol;
        uint32_t maturityDate;
        uint64_t strikePrice;
        char putOrCall;
        char execInst;
        char attributedQuote;
        std::array<char, StringLength::TARGET_PARTY_ID> targetPartyId;
        std::array<char, StringLength::PREVENT_MATCH> preventMatch;
    };
    
    struct NewOrderCrossBitfieldIndex1 {
        char autoMatch;
        uint64_t autoMatchPrice;
        char lastPriority;
        std::array<char, StringLength::ACCOUNT> account;
        uint32_t cmtaNumber;
        std::array<char, StringLength::CLEARING_ACCOUNT> clearingAccount;
        std::array<char, StringLength::ROUTING_FIRM_ID> routingFirmId;
        std::array<char, StringLength::CLEARING_OPTIONAL_DATA> clearingOptionalData;
    };
    
    struct NewOrderCrossBitfieldIndex2 {
        std::array<char, StringLength::CLIENT_ID_ATTR> clientIdAttr;
        uint64_t equityTradePrice;
        uint32_t equityTradeSize;
        char equityTradeVenue;
        std::time_t equityTransactTime;
        std::array<char, StringLength::EQUITY_BUY_CLEARING_FIRM> equityBuyClearingFirm;
        std::array<char, StringLength::EQUITY_SELL_CLEARING_FIRM> equitySellClearingFirm;
        SessionEligibility sessionEligibility;
    };
    
    struct NewOrderCrossBitfieldIndex3 {
        char compression;
        char ors;
        std::array<char, StringLength::FREQUENT_TRADER_ID> frequentTraderId;
    };

    using BitfieldVariant = std::variant <
        NewOrderCrossBitfieldIndex0,
        NewOrderCrossBitfieldIndex1,
        NewOrderCrossBitfieldIndex2,
        NewOrderCrossBitfieldIndex3
    >;

    std::unordered_map<BitfieldIndex, BitfieldVariant> bitfields;
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

private:
    uint16_t startOfMessage_;
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
    std::vector<NewOrderCrossBitfield> newOrderCrossBitfields_;

public:
    void setStartOfMessage(uint16_t input) {
        startOfMessage_ = input;
    }
    void setMessageLength(uint16_t input) {
        messageLength_ = input;
    }
    void setMessageType(uint8_t input) {
        messageType_ = input;
    }
    void setMatchingUnit(uint8_t input) {
        matchingUnit_ = input;
    }
    void setSequenceNumber(uint32_t input) {
        sequenceNumber_ = input;
    }
    void setCrossId(std::array<char, StringLength::CROSSID> &input) {
        crossId_ = input;
    }
    void setCrossType(char &input) {
        crossType_ = input;
    }
    void setCrossPrioritization(char &input) {
        crossPrioritization_ = input;
    }
    void setPrice(uint64_t input) {
        price_ = input;
    }
    void setOrderQty(uint32_t input) {
        orderQty_ = input;
    }
    void setNumberOfNewOrderCrossBitfields(uint8_t input) {
        numberOfNewOrderCrossBitfields_ = input;
    }

public:
    char getStartOfMessageType() {
        return typeid(startOfMessage_).name()[0];
    }
    char getMessageLengthType() {
        return typeid(messageLength_).name()[0];
    }
    char getMatchingUnitType() {
        return typeid(matchingUnit_).name()[0];
    }
    char getMatchingUnitType() {
        return typeid(matchingUnit_).name()[0];
    }
    char getSequenceNumberType() {
        return typeid(sequenceNumber_).name()[0];
    }
    char getCrossIdType() {
        return typeid(crossId_).name()[0];
    }
    char getCrossTypeType() {
        return typeid(crossId_).name()[0];
    }
    char getCrossPrioritizationType() {
        return typeid(crossPrioritization_).name()[0];
    }
    char getPriceType() {
        return typeid(price_).name()[0];
    }
    char getOrderQtyType() {
        return typeid(orderQty_).name()[0];
    }
    char getNumberOfNewOrderCrossBitfieldsType() {
        return typeid(numberOfNewOrderCrossBitfields_).name()[0];
    }
};

class Parser {
    NewOrderCrossMessageFields NOCMF_;

public:
    void setStartOfMessage() {
        if(NOCMF_.getStartOfMessageType() == 't') {
            NOCMF_.setStartOfMessage(StartOfMesageEnumOptions::STARTOFMESSAGE); 
        }
    }
    void setMessageLength(std::string hex) {
        if(NOCMF_.getMessageLengthType() == 't') {
            uint16_t length = (hex.length()/2) - 2;
            NOCMF_.setMessageLength(length);
        }
    }
};