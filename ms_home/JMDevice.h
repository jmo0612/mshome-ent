#ifndef JMDevice_h
#define JMDevice_h
#include "Arduino.h"
class JMRelay;
class JMIr;
class JMCommand;
class JMDevice
{
private:
    int id;
    char *devName;
    int mode;
    JMCommand *commander;
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

    JMDevice(int id, char *devName, JMCommand &commander, JMRelay &relay, JMIr &ir, uint32_t irRun, uint32_t irShutDown, int acOnDelay, int acOffDelay, int runDelay, int shutDownDelay);
    bool acOn();
    bool acOff();
    bool run();
    bool shutDown();
    int getId();
    int getMode();
    void calibrate();
    void setShutDownFailed(bool failed);
};
#endif
