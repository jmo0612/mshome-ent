#include "JMFunctions.h"

const char *JMFunctions::strToCharP(const String str)
{
    // Serial.println(str);
    const String *ret = new String(str.c_str());
    const char *tmp = ret->c_str();
    // Serial.println(tmp);
    return tmp;
    // return ret.c_str();
    // return n;
};
List<char> *JMFunctions::intToBytes(const unsigned int num)
{
    List<char> *ret = new List<char>();
    char b1 = (num >> 24) & 0xFF;
    char b2 = (num >> 16) & 0xFF;
    char b3 = (num >> 8) & 0xFF;
    char b4 = num & 0xFF;
    ret->add(b1);
    ret->add(b2);
    ret->add(b3);
    ret->add(b4);
    // Serial.println(bytes[0],HEX);

    return ret;
    // return reinterpret_cast<char*>(bytes);
};
int JMFunctions::bytesToInt(List<char> *chars)
{
    if (chars->getSize() <= 0 || chars->getSize() > 4)
        return -1;
    int ret = 0;
    ret = (ret << 8) + chars->getValue(0);
    ret = (ret << 8) + chars->getValue(1);
    ret = (ret << 8) + chars->getValue(2);
    ret = (ret << 8) + chars->getValue(3);
    // Serial.println(ret);
    return ret;
};
const char *JMFunctions::listToCharsP(List<char> *listChar)
{
    if (listChar->isEmpty())
        return "";
    String bytes;
    int chWalker = 0;
    for (int i = 0; i < listChar->getSize(); i++)
    {
        char ch = listChar->getValue(i);
        // Serial.print(ch);
        // bytes[chWalker++]=ch;
        bytes += ch;
    }
    // Serial.println(bytes);
    return JMFunctions::strToCharP(bytes);
};