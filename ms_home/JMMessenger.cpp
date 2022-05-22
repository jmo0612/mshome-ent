#include "JMMessenger.h"
#include "JMGlobal.h"
#include "JMSerialSlave.h"
#include "JMFunctions.h"
#include <Wire.h>
#include <ArduinoJson.h>

JMMessenger *added = NULL;
JMMessenger::JMMessenger(const String id, JMSerialSlave *serialSlave, CallbackFunction todo)
{
    this->id = id;
    this->serial = serialSlave;
    this->todo = todo;
    added = this;
};
JMMessenger *JMMessenger::add(const String idTemplate, JMSerialSlave *serialSlave, CallbackFunction todo)
{
    JMMessenger *tmp = added;
    if (tmp == NULL)
    {
        tmp = new JMMessenger(idTemplate, serialSlave, todo);
        tmp->prev = NULL;
        tmp->next = NULL;
        added = tmp;
        return tmp;
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
    tmp = new JMMessenger(id, serialSlave, todo);
    last->next = tmp;
    tmp->prev = last;
    tmp->next = NULL;
    added = tmp;
    return tmp;
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
    added = NULL;
    if (this->next != NULL)
    {
        this->next->prev = this->prev;
        added = this->next->getLast();
    }
    if (this->prev != NULL)
    {
        this->prev->next = this->next;
        added = this->next->getLast();
    }
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

void JMMessenger::send(String msg)
{
    Serial.println(msg);
    Serial.println(this->id);
    String newMsg;
    DynamicJsonDocument doc(256);
    // StaticJsonDocument<256> doc;
    doc["JMMsgrId"] = this->id;
    doc["data"] = msg;
    serializeJson(doc, newMsg);
    Serial.println(newMsg);
    this->serial->send(JMFunctions::strToCharP(newMsg));
    this->deleteMe();
};
void JMMessenger::doAction(String msg)
{
    this->todo(msg);
    this->deleteMe();
};