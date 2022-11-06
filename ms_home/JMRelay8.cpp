//#include "Arduino.h"
//#include "PCF8574.h"
#include "JMRelay8.h"
#include "JMRelay.h"

JMRelay8::JMRelay8(uint8_t address)
{
    this->address = address;
};

void JMRelay8::setup()
{
    this->pcf = new PCF8574(this->address);
    for (uint8_t i = 0; i < 8; i++)
    {
        this->pins[i] = new JMRelay(*this, i);
        this->pins[i]->setup();
    }

    // Serial.print("Init pcf8574 @");
    // Serial.print(this->address);
    // Serial.print(": ");
    while (!this->pcf->begin())
    {
        // wait
        // Serial.print(".");
        // delay(1000);
    }
    // Serial.print("OK   ");
    // Serial.print("DONE\n");
};

PCF8574 *JMRelay8::getPcf()
{
    return this->pcf;
};

void JMRelay8::setPinAsOutput(uint8_t pinId)
{
    if (pinId < 0 || pinId > 7)
        return;

    this->getPcf()->pinMode(pinId, OUTPUT);
};

void JMRelay8::setPinAsInput(uint8_t pinId)
{
    if (pinId < 0 || pinId > 7)
        return;
    this->pcf->pinMode(pinId, INPUT);
};

void JMRelay8::digitalWritePin(uint8_t pinId, uint8_t value)
{
    if (pinId < 0 || pinId > 7)
        return;
    if (this->pins[pinId]->isOutput())
    {
        if (value == HIGH)
        {
            Serial.println("TURNING ON");

            this->pins[pinId]->turnOn();
        }
        else
        {
            Serial.println("TURNING OFF");
            this->pins[pinId]->turnOff();
        }
    }
};

bool JMRelay8::isReady()
{
    return this->ready;
};
JMRelay *JMRelay8::getRelay(uint8_t pinId)
{
    if (pinId < 0 || pinId > 7)
        return NULL;
    return this->pins[pinId];
};