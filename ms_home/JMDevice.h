#ifndef JMDevice_h
#define JMDevice_h
#include "Arduino.h"
class JMRelay;
class JMIr;
class JMDevice
{
private:
    char *devName;
    int mode;
    JMRelay *relay;
    JMIr *ir;
    bool shutDownFailed = false;

    uint32_t irRun = 0x0;
    uint32_t irShutDown = 0x0;

    int acOnDelay;
    int acOffDelay;
    int runDelay;
    int shutDownDelay;

public:
    static const int DEV_MODE_DEAD = 0;
    static const int DEV_MODE_STANDBY = 1;
    static const int DEV_MODE_RUNNING = 2;

    JMDevice(char *devName, JMRelay &relay, JMIr &ir, uint32_t irRun, uint32_t irShutDown, int acOnDelay, int acOffDelay, int runDelay, int shutDownDelay);
    bool acOn();
    bool acOff();
    bool run();
    bool shutDown();
    int getMode();
    void calibrate();
};
#endif
