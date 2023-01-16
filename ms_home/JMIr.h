#ifndef JMIr_h
#define JMIr_h
#include "Arduino.h"

class JMCommand;

class JMIr
{
private:
    JMCommand *commander;

    void processIr(uint8_t id, bool trace);

public:
    static const uint8_t IR_LG1_ID = 0;
    static const uint8_t IR_LG2_ID = 1;
    static const uint8_t IR_LG3_ID = 2;
    static const uint8_t IR_LG4_ID = 3;
    static const uint8_t IR_AK1_ID = 4;
    static const uint8_t IR_AK2_ID = 5;
    static const uint8_t IR_AK3_ID = 6;
    static const uint8_t IR_AK4_ID = 7;
    static const uint8_t IR_LGP_ID = 8;
    static const uint8_t IR_AKP_ID = 9;

    uint8_t irLgCount = 0;
    uint8_t irAkCount = 0;

    uint8_t lastLgId = 250;
    uint8_t lastAkId = 250;

    unsigned long irLgTime = 0;
    unsigned long irAkTime = 0;

    static const uint32_t getIrCode(uint8_t id);

    JMIr();
    void setup();
    void receiveIr(bool trace = false);
    void sendIr(uint32_t code);
    void setCommander(JMCommand &commander);
};
#endif
