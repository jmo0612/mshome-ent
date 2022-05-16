#ifndef JMRelay8_h
#define JMRelay8_h
//#include "Arduino.h"
#include "PCF8574.h"
//#include "JMRelay.h"
class JMRelay;
class JMRelay8
{
private:
    uint8_t address;
    PCF8574 *pcf;
    JMRelay *pins[8];
    bool ready = false;

public:
    JMRelay8(uint8_t address);
    void setup();
    PCF8574 *getPcf();
    void setPinAsOutput(int pinId);
    void setPinAsInput(int pinId);
    void digitalWritePin(int pinId, int value);
    bool isReady();
    JMRelay *getRelay(int pinId);
};

#endif
