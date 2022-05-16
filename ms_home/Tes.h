#ifndef MyClass_h
#define MyClass_h
#include "Arduino.h"
class Tes
{
public:
    Tes(int pin);
    int getPin();

private:
    int pin;
};
#endif
