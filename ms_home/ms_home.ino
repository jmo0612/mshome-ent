//#include "JMCommand.h"
//#include "JMWifi.h"
#include "JMSerialSlave.h"
#include "JMGlobal.h"
#include "JMMessenger.h"
#include <Wire.h>
#include <ArduinoJson.h>

// JMWifi *wifi = new JMWifi();
//  JMCommand *cmd = new JMCommand();
JMSerialSlave *bridge = new JMSerialSlave();

void setup()
{
  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Serial.begin(JMGlobal::baudrate);
  delay(1000);
  Serial.println("RESET");

  bridge->setup();

  // wifi->setup();
  //  cmd->setup();

  // cmd->doCommand(JMCommand::CMD_BOX_TO_LG);
}
bool go = true;
void loop()
{
  char *data = "/mshome-ent/index.php";
  JMMessenger::add("jimi", bridge, tes)->send(data);
  delay(10000);

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
void receiveEvent(int howMany)
{
  String data = "";
  while (0 < Wire.available())
  {
    char c = Wire.read(); /* receive byte as a character */
    data += c;
  }
  Serial.println(data); /* print the request data */

  // processCall(data);         /* to newline */

  DynamicJsonDocument doc(2048);
  deserializeJson(doc, data);
  // JsonObject& root= jsonBuffer.parseObject(command);

  char *id = doc["JMMsgrId"];
  char *msg = doc["data"];
  Serial.println(id);
  JMMessenger *tmp = JMMessenger::find(id);
  if (tmp != NULL)
    tmp->doAction(msg);
}