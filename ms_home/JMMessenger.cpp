#include "JMMessenger.h"
#include "JMGlobal.h"
#include "JMFunctions.h"
#include <Wire.h>
#include <ArduinoJson.h>

JMMessenger *added = NULL;

JMMessenger::JMMessenger(const String id, const String msg, CallbackFunction todo)
{
    this->id = id;

    // Serial.println(msg);
    // Serial.println(this->id);

    StaticJsonDocument<256> doc;
    // DynamicJsonDocument doc(256);
    String newJsonMsg;
    doc["JMMsgrId"] = this->id;
    doc["data"] = msg;
    serializeJson(doc, newJsonMsg);
    // Serial.println(newMsg);
    doc.clear();

    this->msg = JMFunctions::strToCharP(newJsonMsg);

    this->todo = todo;
    added = this;
};
JMMessenger *JMMessenger::add(const String idTemplate, const String msg, CallbackFunction todo)
{
    if (added == NULL)
    {
        JMMessenger *tmp = new JMMessenger(idTemplate, msg, todo);
        tmp->prev = NULL;
        tmp->next = NULL;
        added = tmp;
        return tmp;
    }
    else
    {
        if (count() >= JMGlobal::maxStack)
        {
            added->getFirst()->deleteMe();
        }
        JMMessenger *dup = added->find(idTemplate);
        String id = idTemplate;
        while (dup != NULL)
        {
            id += "0";
            dup = added->find(id);
        }
        delete dup;
        JMMessenger *last = added->getLast();
        JMMessenger *tmp = new JMMessenger(id, msg, todo);
        last->next = tmp;
        tmp->prev = last;
        tmp->next = NULL;
        added = tmp;
        return tmp;
    }
}
JMMessenger *JMMessenger::getFirst()
{
    if (this->prev == NULL)
        return this;
    return this->prev->getFirst();
};
JMMessenger *JMMessenger::getLast()
{
    if (this->next == NULL)
        return this;
    return this->next->getLast();
};
void JMMessenger::deleteMe()
{
    // added = NULL;
    JMMessenger *last = this->getLast();
    if (this->next != NULL)
    {
        this->next->prev = this->prev;
        // added = this->next->getLast();
    }
    if (this->prev != NULL)
    {
        this->prev->next = this->next;
        // added = this->next->getLast();
    }

    if (this != last)
        added = last;
    else
        added = NULL;
    delete this;
};
JMMessenger *JMMessenger::find(const String id)
{
    JMMessenger *tmp = added;
    JMMessenger *wlk = tmp->getFirst();
    do
    {
        if (wlk->id.compareTo(id) == 0)
            return wlk;
        wlk = wlk->next;
    } while (wlk != NULL);
    return NULL;
};

void JMMessenger::doAction(String msg)
{
    this->todo(msg);
    this->deleteMe();
};
int JMMessenger::count()
{
    if (added == NULL)
        return 0;
    JMMessenger *wlk = added->getFirst();
    int c = 0;
    while (wlk != NULL)
    {
        c++;
        wlk = wlk->next;
    }

    return c;
};
String JMMessenger::getMessage()
{
    if (added == NULL)
        return "NONE";
    JMMessenger *first = added->getFirst();
    String ret = JMFunctions::strToCharP(first->msg);
    // first->deleteMe();
    return ret;
};
JMMessenger::~JMMessenger()
{
    // delete &this->id;
    // delete &this->msg;
    //  delete &this->next;
    //  delete &this->prev;
}