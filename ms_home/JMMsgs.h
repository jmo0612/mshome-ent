#ifndef JMMsgs_h
#define JMMsgs_h
#include "Arduino.h"

class JMMsgs
{
private:
    uint64_t msgs[6] = {0, 0, 0, 0, 0, 0};

public:
    JMMsgs();
    void queueMsg(uint64_t msg);
    uint64_t dequeueMsg();
};
#endif
