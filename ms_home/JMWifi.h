#ifndef JMWifi_h
#define JMWifi_h
#include "Arduino.h"
#include <SoftwareSerial.h>

class JMWifi
{
private:
    SoftwareSerial *wifi;

public:
    JMWifi();
    void setup();
    bool sendHttp(String url, char *findResult);
};
#endif
