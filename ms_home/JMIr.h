#ifndef JMIr_h
#define JMIr_h
#include "Arduino.h"

class JMCommand;

class JMIr
{
private:
    JMCommand *commander;

    void processIr2(uint32_t code);
    void processIr(uint8_t id);

public:
    /*static const uint32_t IR_A1_CODE = 2733166887;
    static const uint32_t IR_A2_CODE = 1663147656;
    static const uint32_t IR_A3_CODE = 1494494661;
    static const uint32_t IR_A4_CODE = 3967086620;
    static const uint32_t IR_B1_CODE = 4257650505;
    static const uint32_t IR_B2_CODE = 271251858;
    static const uint32_t IR_B3_CODE = 2952684369;
    static const uint32_t IR_B4_CODE = 2508896912;*/

    static const uint8_t IR_LG1_ID = 0;
    static const uint8_t IR_LG2_ID = 1;
    static const uint8_t IR_LG3_ID = 2;
    static const uint8_t IR_LG4_ID = 3;
    static const uint8_t IR_AK1_ID = 4;
    static const uint8_t IR_AK2_ID = 5;
    static const uint8_t IR_AK3_ID = 6;
    static const uint8_t IR_AK4_ID = 7;

    uint8_t irLg1Count = 0;
    uint8_t irLg2Count = 0;
    uint8_t irLg3Count = 0;
    uint8_t irLg4Count = 0;
    uint8_t irAk1Count = 0;
    uint8_t irAk2Count = 0;
    uint8_t irAk3Count = 0;
    uint8_t irAk4Count = 0;

    unsigned long irLg1Time = 0;
    unsigned long irLg2Time = 0;
    unsigned long irLg3Time = 0;
    unsigned long irLg4Time = 0;
    unsigned long irAk1Time = 0;
    unsigned long irAk2Time = 0;
    unsigned long irAk3Time = 0;
    unsigned long irAk4Time = 0;

    static const uint32_t getIrCode(uint8_t id);

    JMIr();
    void setup();
    void receiveIr2();
    void receiveIr();
    void sendIr(uint32_t code);
    void setCommander(JMCommand &commander);
};
#endif
