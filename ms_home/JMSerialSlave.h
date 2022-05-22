#ifndef JMSerialSlave_h
#define JMSerialSlave_h
#include <SoftwareSerial.h>

class JMSerialSlave
{
private:
    SoftwareSerial *serial;

public:
    JMSerialSlave();
    void setup();
    void send(const char *data);
};
#endif
