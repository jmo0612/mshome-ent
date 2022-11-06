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
    void setPinAsOutput(uint8_t pinId);
    void setPinAsInput(uint8_t pinId);
    void digitalWritePin(uint8_t pinId, uint8_t value);
    bool isReady();
    JMRelay *getRelay(uint8_t pinId);
};

#endif
