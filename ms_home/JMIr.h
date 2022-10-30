#ifndef JMIr_h
#define JMIr_h
#include "Arduino.h"

class JMCommand;

class JMIr
{
private:
    JMCommand *commander;

    void processIr(uint32_t code);

public:
    static const uint32_t IR_A1_CODE = 2733166887;
    static const uint32_t IR_A2_CODE = 1663147656;
    static const uint32_t IR_A3_CODE = 1494494661;
    static const uint32_t IR_A4_CODE = 3967086620;
    static const uint32_t IR_B1_CODE = 4257650505;
    static const uint32_t IR_B2_CODE = 271251858;
    static const uint32_t IR_B3_CODE = 2952684369;
    static const uint32_t IR_B4_CODE = 2508896912;

    JMIr();
    void setup();
    void receiveIr();
    void sendIr(uint32_t code);
    void setCommander(JMCommand &commander);
};
#endif
