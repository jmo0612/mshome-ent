#ifndef JMFunctions_h
#define JMFunctions_h
#include "Arduino.h"
#include <List.hpp>

class JMFunctions
{
private:
public:
    static const char *strToCharP(const String str);
    static int bytesToInt(List<char> *chars);
    static List<char> *intToBytes(const unsigned int num);
    static const char *listToCharsP(List<char> *listChar);
};
#endif
