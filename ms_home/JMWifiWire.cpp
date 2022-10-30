#include "JMWifiWire.h"
#include "JMGlobal.h"
#include "JMFunctions.h"

int sendId = 0;

JMWifiWire::JMWifiWire()
{
    this->_wire = &Wire;
};

void JMWifiWire::setAsMaster(int sda, int scl, void (*receiveEvent)(int)){
    /*this->isMaster=true;
    //this->_wire->begin(D1,D2);
    this->_wire->begin(sda,scl);
    this->_wire->onReceive(receiveEvent);
    this->masterSda=sda;
    this->masterScl=scl;*/
};
void JMWifiWire::setAsSlave(int address, void (*receiveEvent)(int), void (*requestEvent)())
{
    this->isMaster = false;
    this->_wire->begin(address);
    this->_wire->onReceive(receiveEvent);
    this->_wire->onRequest(requestEvent);
    this->slaveAddress = address;
};
void JMWifiWire::sendMessage(const char *msg, const int slaveAddress)
{
    // Serial.println(msg[0]);
    if (this->isMaster)
        this->_wire->beginTransmission(slaveAddress);
    Serial.println(this->_wire->write(msg, 32));
    if (this->isMaster)
        Serial.println(this->_wire->endTransmission());
};
void JMWifiWire::sendMessage2(const byte *msg, const int slaveAddress)
{
    // Serial.println(msg[0]);
    if (this->isMaster)
        this->_wire->beginTransmission(slaveAddress);
    this->_wire->write(msg, 8);
    if (this->isMaster)
        this->_wire->endTransmission();
};

TwoWire *JMWifiWire::getWire()
{
    return this->_wire;
};