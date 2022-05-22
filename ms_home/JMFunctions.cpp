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