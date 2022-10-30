#ifndef JMData_h
#define JMData_h
#include "Arduino.h"

class JMData
{
private:
    int dev[32] = {0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // static int dev[32];

    uint64_t dataToInt64(int msg, uint64_t val);
    int getMsgFromPacket(uint64_t packet);
    uint64_t getValueFromPacket(uint64_t packet);
    // void processPacket(uint64_t packet);
    uint64_t getPow3s(int ind);

public:
    JMData();
    uint64_t devDataToInt64();
    // long long devDataToInt64b(int msg);
    void updateDevData(uint64_t val);
    const char *cek();
    void updateDevice(int id, int val);
};
#endif
