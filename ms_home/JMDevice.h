#ifndef JMDevice_h
#define JMDevice_h
#include "Arduino.h"
class JMRelay;
class JMIr;
class JMCommand;
class JMDevice
{
private:
    uint8_t id;
    uint8_t mode;
    JMCommand *commander;
    JMRelay *relay;
    JMIr *ir;
    bool shutDownFailed = false;

    uint16_t acOnDelay;
    uint16_t acOffDelay;
    uint16_t runDelay;
    uint16_t shutDownDelay;

public:
    static const uint8_t DEV_MODE_DEAD = 0;
    static const uint8_t DEV_MODE_STANDBY = 1;
    static const uint8_t DEV_MODE_RUNNING = 2;
    static const uint32_t getIrPower(uint8_t id, bool on = true);

    JMDevice(uint8_t id, JMCommand &commander, JMRelay &relay, JMIr &ir, uint16_t acOnDelay, uint16_t acOffDelay, uint16_t runDelay, uint16_t shutDownDelay);
    bool acOn();
    bool acOff();
    bool run();
    bool shutDown();
    uint8_t getId();
    uint8_t getMode();
    void calibrate();
    void setShutDownFailed(bool failed);
};
#endif
