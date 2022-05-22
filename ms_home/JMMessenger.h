#ifndef JMMessenger_h
#define JMMessenger_h

#include "CallbackFunction.h"

class JMSerialSlave;
class JMMessenger
{
private:
    String id;
    JMSerialSlave *serial;
    CallbackFunction todo;
    JMMessenger *next = NULL;
    JMMessenger *prev = NULL;

    JMMessenger *getFirst();
    JMMessenger *getLast();
    void deleteMe();

public:
    JMMessenger(const String id, JMSerialSlave *serialSlave, CallbackFunction todo);
    void send(String msg);
    void doAction(String msg);

    static JMMessenger *add(const String idTemplate, JMSerialSlave *serialSlave, CallbackFunction todo);
    static JMMessenger *find(const String id);
};
#endif
