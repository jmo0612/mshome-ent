#include "JMData.h"
#include "JMGlobal.h"
#include <math.h>

const uint64_t msgMultiplier = 72057594037927936; // byte-8
JMData::JMData(){

};
uint64_t JMData::getPow3s(int ind)
{
    if (ind == 0)
    {
        return 617673396283947;
    }
    else if (ind == 1)
    {
        return 205891132094649;
    }
    else if (ind == 2)
    {
        return 68630377364883;
    }
    else if (ind == 3)
    {
        return 22876792454961;
    }
    else if (ind == 4)
    {
        return 7625597484987;
    }
    else if (ind == 5)
    {
        return 2541865828329;
    }
    else if (ind == 6)
    {
        return 847288609443;
    }
    else if (ind == 7)
    {
        return 282429536481;
    }
    else if (ind == 8)
    {
        return 94143178827;
    }
    else if (ind == 9)
    {
        return 31381059609;
    }
    else if (ind == 10)
    {
        return 10460353203;
    }
    else if (ind == 11)
    {
        return 3486784401;
    }
    else if (ind == 12)
    {
        return 1162261467;
    }
    else if (ind == 13)
    {
        return 387420489;
    }
    else if (ind == 14)
    {
        return 129140163;
    }
    else if (ind == 15)
    {
        return 43046721;
    }
    else if (ind == 16)
    {
        return 14348907;
    }
    else if (ind == 17)
    {
        return 4782969;
    }
    else if (ind == 18)
    {
        return 1594323;
    }
    else if (ind == 19)
    {
        return 531441;
    }
    else if (ind == 20)
    {
        return 177147;
    }
    else if (ind == 21)
    {
        return 59049;
    }
    else if (ind == 22)
    {
        return 19683;
    }
    else if (ind == 23)
    {
        return 6561;
    }
    else if (ind == 24)
    {
        return 2187;
    }
    else if (ind == 25)
    {
        return 729;
    }
    else if (ind == 26)
    {
        return 243;
    }
    else if (ind == 27)
    {
        return 81;
    }
    else if (ind == 28)
    {
        return 27;
    }
    else if (ind == 29)
    {
        return 9;
    }
    else if (ind == 30)
    {
        return 3;
    }
    else
    {
        return 1;
    }
};
uint64_t JMData::devDataToInt64()
{
    uint64_t msgInt64 = JMGlobal::PACKET_MSG_DEVICES_DATA * msgMultiplier;
    uint64_t dataVal = 0;
    int devSize = 32;

    for (int i = 0; i < devSize; i++)
    {
        dataVal += (this->dev[i] * this->getPow3s(i));
    }
    dataVal += msgInt64;
    return dataVal;
};
/*long long JMData::devDataToInt64b(int msg)
{
    long long msgInt64 = msg * msgMultiplier;
    long long dataVal = 0;
    int devSize = 32;
    for (int i = 0; i < devSize; i++)
    {
        dataVal += (this->dev[i] * (pow(3, (devSize - i - 1))));
    }
    dataVal += msgInt64;
    return dataVal;
};*/
uint64_t JMData::dataToInt64(int msg, uint64_t val)
{
    return (msg * msgMultiplier) + val;
};
int JMData::getMsgFromPacket(uint64_t packet)
{
    return packet >> 56;
};
uint64_t JMData::getValueFromPacket(uint64_t packet)
{
    uint64_t tmp = packet << 8;
    return tmp >> 8;
};
void JMData::updateDevData(uint64_t val)
{
    int ind = 0;
    uint64_t quotient = val;
    int remain;
    do
    {
        remain = quotient % 3;
        this->dev[ind++] = remain;
        quotient = quotient / 3;
    } while (quotient > 0);
};
void JMData::updateDevice(int id, int val)
{
    if (id > 31 || id < 0)
        return;
    this->dev[id] = val;
};
/*void JMData::processPacket(uint64_t packet)
{
    int msg = this->getMsgFromPacket(packet);
    uint64_t val = this->getValueFromPacket(packet);
    if (msg == JMGlobal::PACKET_MSG_UPDATE_DEVICES_DATA)
    {
        this->updateDevData(val);
    }
};*/
const char *JMData::cek()
{
    char ret[96];
    int a = 0;
    for (int i = 0; i < 32; i++)
    {
        if (this->dev[i] == 1)
        {
            ret[a++] = '1';
        }
        else if (this->dev[i] == 2)
        {
            ret[a++] = '2';
        }
        else
        {
            ret[a++] = '0';
        }
        ret[a++] = ',';
        ret[a++] = ' ';
    }
    return ret;
};