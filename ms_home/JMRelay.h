#ifndef JMRelay_h
#define JMRelay_h
#include "Arduino.h"
//#include "JMRelay8.h"
class JMRelay8;
class JMRelay
{
private:
  const bool INVERT_WRITE_LOGIC = true;
  uint8_t JM_HIGH = HIGH;
  uint8_t JM_LOW = LOW;

  JMRelay8 *relay8;
  uint8_t pcfPinNo;
  uint8_t pcfPinMode;
  bool ac;
  bool on = false;

public:
  JMRelay(JMRelay8 &relay8, uint8_t pcfPinNo, uint8_t pcfPinMode = OUTPUT, bool ac = true);
  void setup();
  JMRelay8 *getRelay8();
  bool isAc();
  bool isOutput();
  void turnOn();
  void turnOff();
};
#endif
