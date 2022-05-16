#include "Arduino.h"
#include "Tes.h"

Tes::Tes(int pin)
{
    this->pin = pin;
}
int Tes::getPin()
{
    return this->pin;
}
