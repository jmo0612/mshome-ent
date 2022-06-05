#include "JMCommand.h"
//#include "JMWifi.h"
#include "JMGlobal.h"
#include "JMFunctions.h"
#include "JMMessenger.h"
#include "JMWifiWire.h"
#include <ArduinoJson.h>

// JMWifi *wifi = new JMWifi();
JMCommand *cmd = new JMCommand();

JMWifiWire *wifiWire = new JMWifiWire();
bool networkConnected = false;
bool goodToGo = false;
void setup()
{
  cmd->setup();
  wifiWire->setAsSlave(8, receiveEvent, requestEvent);
  Serial.begin(JMGlobal::baudrate);
  delay(1000);
  Serial.println(F("RESET"));

  // wifi->setup();

  // cmd->doCommand(JMCommand::CMD_BOX_TO_LG);
  /*List<List<char> *> *kkk = new List<List<char> *>();
  List<char> *ddd = new List<char>();
  char ccc = 'a';
  ddd->add(ccc);
  ccc = 'b';
  ddd->add(ccc);

  kkk->add(ddd);
  delete ddd;
  Serial.println(kkk->getValue(0)->toArray());*/
}
bool go = true;
void loop()
{
  if (goodToGo)
  {
    // loop
    if (go)
    {
      go = false;
      cmd->doCommand(JMCommand::CMD_BOX_TO_LG);
    }
    // Serial.println("Looping");
    // delay(1000);
  }
  else
  {
    if (cmd->isLoaded() && networkConnected)
      goodToGo = true;
  }
  // char *data = "/mshome-ent/index.php";
  //  JMMessenger::add("jimi", data, tes);
  // delay(100);

  // bridge->checkSerial();
  /*
    if (ardSerial.available())
    {
      // Serial.println(ardSerial.readString());
      //  char tmp = ardSerial.read();
      //  Serial.print(tmp);
    }*/
  // Serial.println("\n");

  // delay(3000);
  //  wifi->sendHttp("/mshome-ent/post_tes.php", "aaa");
  //   wifiTest();
  //   doit();
}

void doit()
{

  // cmd
  // delay(5000);
}

void tes(String a)
{
  Serial.println(a);
}

void processCall(String command)
{
  DynamicJsonDocument doc(256);
  deserializeJson(doc, command);
  // JsonObject& root= jsonBuffer.parseObject(command);

  int id = doc["id"];
  Serial.println(id);
  const char *nama = doc["nama"];
  Serial.println(nama);
  // tes();
}

void receiveEvent(int howMany)
{
  // Serial.println(F("received"));
  char data[32] = {};
  int i = 0;
  while (wifiWire->getWire()->available())
  {
    char c = wifiWire->getWire()->read();
    // Serial.println(int(c));
    data[i++] = c;
  }
  // Serial.println(data);
  cmd->processTask(data);
  // delete data;
}

void requestEvent()
{
  networkConnected = true;
  if (!cmd->isLoaded())
  {
    wifiWire->sendMessage("|INIT0|");
  }
  else
  {
    String msg = "|UPD";
    msg += cmd->getStats();
    msg += "|";
    char m[msg.length()];
    for (int i = 0; i < msg.length(); i++)
    {
      m[i] = char(msg[i]);
    }
    // Serial.println(m);
    wifiWire->sendMessage(m);
  }
  // Serial.println("requested");
  // wifiWire->sendMessage("D200000000000000000000000000002D");
}
