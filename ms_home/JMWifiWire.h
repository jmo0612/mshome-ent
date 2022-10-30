#ifndef JMWifiWire_h
#define JMWifiWire_h
#include "Arduino.h"
#include <Wire.h>

class JMWifiWire
{
private:
    TwoWire *_wire;
    bool isMaster;
    int masterSda;
    int masterScl;
    int slaveAddress;

public:
    JMWifiWire();
    void setAsMaster(int sda, int scl, void (*receiveEvent)(int));
    void setAsSlave(int address, void (*receiveEvent)(int), void (*requestEvent)());
    void sendMessage(const char *msg, const int slaveAddress = 0);
    void sendMessage2(const byte *msg, const int slaveAddress = 0);
    TwoWire *getWire();
};
#endif
