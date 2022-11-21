#ifndef JMData_h
#define JMData_h
#include "Arduino.h"

class JMData
{
private:
    uint8_t dev[32] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // static int dev[32];

    uint64_t dataToInt64(uint8_t msg, uint64_t val);
    // void processPacket(uint64_t packet);

public:
    static byte *msgToBytes(uint64_t msg, bool trace = false);
    static const uint8_t getMsgFromPacket(uint64_t packet);
    static const uint64_t getValueFromPacket(uint64_t packet);
    static const uint64_t getMsgMultiplier(uint8_t packetMsg);
    static const uint64_t getPow3s(uint8_t ind);
    static const uint64_t devInitToInt64(const char *str);

    JMData();
    uint64_t devDataToInt64();
    uint64_t devDataToInt64Queued();
    // long long devDataToInt64b(int msg);
    void updateDevData(uint64_t val);
    const char *cek();
    void updateDevice(uint8_t id, uint8_t val);
    uint8_t getDeviceStatus(uint8_t id);
};
#endif
