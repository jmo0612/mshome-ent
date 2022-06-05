#ifndef JMMessenger_h
#define JMMessenger_h

#include "CallbackFunction.h"

class JMMessenger
{
private:
    String id;
    String msg;
    CallbackFunction todo;
    JMMessenger *next = NULL;
    JMMessenger *prev = NULL;

    JMMessenger *getFirst();
    JMMessenger *getLast();
    void deleteMe();
    static int count();

public:
    JMMessenger(const String id, const String msg, CallbackFunction todo);
    ~JMMessenger();
    void doAction(String msg);

    static JMMessenger *add(const String idTemplate, const String msg, CallbackFunction todo);
    static JMMessenger *find(const String id);
    static String getMessage();
};
#endif
