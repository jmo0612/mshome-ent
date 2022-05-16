//#include "Arduino.h"
//#include "PCF8574.h"
#include "JMRelay.h"
#include "JMRelay8.h"
JMRelay::JMRelay(JMRelay8 &relay8, uint8_t pcfPinNo, uint8_t pcfPinMode = OUTPUT, bool ac = true)
{
  if (this->INVERT_WRITE_LOGIC)
  {
    this->JM_HIGH = LOW;
    this->JM_LOW = HIGH;
  }

  this->relay8 = &relay8;
  if (pcfPinNo < 0 || pcfPinNo > 7)
    pcfPinNo = 0;
  this->pcfPinNo = pcfPinNo;
  if (pcfPinMode != OUTPUT && pcfPinMode != INPUT && pcfPinMode != INPUT_PULLUP)
    pcfPinMode = OUTPUT;

  this->pcfPinMode = pcfPinMode;
  this->ac = ac;
};

void JMRelay::setup()
{
  this->relay8->getPcf()->pinMode(this->pcfPinNo, this->pcfPinMode);
};

JMRelay8 *JMRelay::getRelay8()
{
  return this->relay8;
};

bool JMRelay::isAc()
{
  return this->ac;
};

bool JMRelay::isOutput()
{
  return (this->pcfPinMode == OUTPUT) ? true : false;
};

void JMRelay::turnOn()
{
  if (!this->isOutput())
  {
    this->pcfPinMode = OUTPUT;
    this->relay8->getPcf()->pinMode(this->pcfPinNo, this->pcfPinMode);
  }
  this->relay8->getPcf()->digitalWrite(this->pcfPinNo, this->JM_HIGH);
  this->on = true;
};

void JMRelay::turnOff()
{
  if (!this->isOutput())
  {
    this->pcfPinMode = OUTPUT;
    this->relay8->getPcf()->pinMode(this->pcfPinNo, this->pcfPinMode);
  }
  this->relay8->getPcf()->digitalWrite(this->pcfPinNo, this->JM_LOW);
  this->on = false;
};
