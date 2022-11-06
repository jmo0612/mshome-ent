#ifndef JMWifiWire_h
#define JMWifiWire_h
#include "Arduino.h"
#include <Wire.h>

class JMWifiWire
{
private:
    TwoWire *_wire;
    bool isMaster;
    uint8_t masterSda;
    uint8_t masterScl;
    uint8_t slaveAddress;

public:
    JMWifiWire();
    void setAsMaster(uint8_t sda, uint8_t scl, void (*receiveEvent)(int));
    void setAsSlave(uint8_t address, void (*receiveEvent)(int), void (*requestEvent)());
    void sendMessage2(const byte *msg, const uint8_t slaveAddress = 0);
    TwoWire *getWire();
    // void sendPackage();
    // void setPackage(uint64_t package);
};
#endif
