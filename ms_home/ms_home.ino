#include "JMCommand.h"
//#include "JMWifi.h"
#include "JMGlobal.h"
#include "JMWifiWire.h"
#include "JMData.h"
//#include "JMMsgs.h"
#include "JMIr.h"

// JMWifi *wifi = new JMWifi();
JMIr *ir = new JMIr();
JMCommand *cmd = new JMCommand();
JMData *devData = new JMData();
// JMMsgs *msgs = new JMMsgs();
// long long jimi = 1;

JMWifiWire *wifiWire = new JMWifiWire();
bool networkConnected = false;
bool goodToGo = false;
uint64_t package = 0;
void setup()
{
  Serial.begin(JMGlobal::baudrate);

  wifiWire->setAsSlave(8, receiveEvent, requestEvent);
  ir->setup();
  cmd->setup(ir, devData, wifiWire);
  Serial.println(F("RESET"));
  // JMData::msgToBytes(devData->devDataToInt64());

  //  const char *tmp = devData->cek();
  //  Serial.println(tmp);

  // wifi->setup();

  // cmd->doCommand(JMGlobal::DO_CMD_BOX_TO_LG);
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

  // Serial.println("tes");
  if (package != 0)
  {
    cmd->processPackage(package);
    package = 0;
  }
  ir->receiveIr();
  // delay(1000);
  /*uint32_t ir = irRec->decode();
  if (ir != 0)
    Serial.println(ir);*/
  /*
    if (goodToGo)
    {
      // loop
      if (go)
      {
        go = false;
        cmd->doCommand(JMGlobal::DO_CMD_BOX_TO_LG);
        processMsg();
      }
    }
    else
    {
      if (cmd->isLoaded() && networkConnected)
        goodToGo = true;
    }
    */
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
  // Serial.println(F("receiving"));
  byte data[howMany];
  int i = 0;
  while (wifiWire->getWire()->available())
  {
    byte c = wifiWire->getWire()->read();
    data[i++] = c;
  }
  package = msgInt64(data);
  // cmd->processPackage(package);
}

void requestEvent()
{
  Serial.println(F("requested"));
  networkConnected = true;
  uint64_t data = devData->devDataToInt64();
  byte *msg = JMData::msgToBytes(data);
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.println(*(msg + i));
  }
  wifiWire->sendMessage2(msg);
}

uint64_t msgInt64(byte *msg)
{
  uint64_t d0 = msg[0];
  d0 = d0 << 56;
  uint64_t d1 = msg[1];
  d1 = d1 << 48;
  uint64_t d2 = msg[2];
  d2 = d2 << 40;
  uint64_t d3 = msg[3];
  d3 = d3 << 32;
  uint64_t d4 = msg[4];
  d4 = d4 << 24;
  uint64_t d5 = msg[5];
  d5 = d5 << 16;
  uint64_t d6 = msg[6];
  d6 = d6 << 8;
  uint64_t d7 = msg[7];
  return d0 + d1 + d2 + d3 + d4 + d5 + d6 + d7;
}

/*void processMsg()
{
  uint64_t msg = msgs->dequeueMsg();
  if (msg == 0)
    return;
  uint64_t msgType = msg >> 56;
  uint64_t tmp = msg << 8;
  uint64_t data = tmp >> 8;
  if (msgType == JMGlobal::PACKET_MSG_UPDATE_DEVICES_DATA)
  {
    devData->updateDevData(data);
  }
  else if (msgType == JMGlobal::PACKET_MSG_REQUEST_DEVICES_DATA)
  {
    uint64_t data = devData->devDataToInt64(JMGlobal::PACKET_MSG_UPDATE_DEVICES_DATA);
    // wifiWire->sendMessage(msgStr(data));
  }
  else
  {
    cmd->doCommand(data);
  }
}*/
