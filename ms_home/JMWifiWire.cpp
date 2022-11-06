#include "JMWifiWire.h"
#include "JMGlobal.h"
#include "JMData.h"

uint8_t sendId = 0;

JMWifiWire::JMWifiWire()
{
    this->_wire = &Wire;
};

void JMWifiWire::setAsMaster(uint8_t sda, uint8_t scl, void (*receiveEvent)(int)){
    /*this->isMaster=true;
    //this->_wire->begin(D1,D2);
    this->_wire->begin(sda,scl);
    this->_wire->onReceive(receiveEvent);
    this->masterSda=sda;
    this->masterScl=scl;*/
};
void JMWifiWire::setAsSlave(uint8_t address, void (*receiveEvent)(int), void (*requestEvent)())
{
    this->isMaster = false;
    this->_wire->begin(address);
    this->_wire->onReceive(receiveEvent);
    this->_wire->onRequest(requestEvent);
    this->slaveAddress = address;
};
void JMWifiWire::sendMessage2(const byte *msg, const uint8_t slaveAddress)
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
/*void JMWifiWire::sendPackage()
{
    if (this->package != 0)
    {
        this->sendMessage2(JMData::msgToBytes(this->package));
        this->package = 0;
    }
};
void JMWifiWire::setPackage(uint64_t package)
{
    this->package = package;
};*/