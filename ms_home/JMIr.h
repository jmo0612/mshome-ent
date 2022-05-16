#ifndef JMIr_h
#define JMIr_h
#include "Arduino.h"

class JMIr
{
public:
    JMIr();
    void setup();
    uint32_t decode();
    void sendIr(uint32_t code);
};
#endif
