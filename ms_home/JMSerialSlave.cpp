#include "JMSerialSlave.h"
#include "JMFunctions.h"
#include "JMGlobal.h"

JMSerialSlave::JMSerialSlave(){

};
void JMSerialSlave::setup()
{
    this->serial = new SoftwareSerial(5, 6);
    this->serial->begin(JMGlobal::baudrate);
    // this->serial->setTimeout(JMGlobal::serialTimeOut);
};
void JMSerialSlave::send(const char *data)
{
    this->serial->write(data);
};