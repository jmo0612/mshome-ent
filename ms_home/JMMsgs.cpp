#include "JMMsgs.h"
#include "JMGlobal.h"
#include "JMData.h"

JMMsgs::JMMsgs(){

};
void JMMsgs::queueMsg(uint64_t msg)
{
    for (int i = 0; i < 6; i++)
    {
        if (this->msgs[i] == 0)
        {
            this->msgs[i] = msg;
            break;
        }
    }
};
uint64_t JMMsgs::dequeueMsg()
{
    uint64_t msg = this->msgs[0];
    for (int i = 0; i < 5; i++)
    {
        this->msgs[i] = this->msgs[i + 1];
    }
    this->msgs[5] = 0;
    return msg;
};