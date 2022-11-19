#include "JMCommand.h"
#include "JMGlobal.h"
#include "JMWifiWire.h"
#include "JMData.h"
#include "JMIr.h"

JMIr *ir = new JMIr();
JMCommand *cmd = new JMCommand();
JMData *devData = new JMData();

JMWifiWire *wifiWire = new JMWifiWire();
bool ongoingPackage = false;
bool packageSent = true;
uint64_t package = 0;

void setup()
{
  Serial.begin(JMGlobal::baudrate);

  wifiWire->setAsSlave(8, receiveEvent, requestEvent);
  ir->setup();
  cmd->setup(ir, devData, wifiWire);
  Serial.println(F("RESET"));
}
bool go = true;
void loop()
{
  if (ongoingPackage)
  {
    uint8_t msg = JMData::getMsgFromPacket(package);
    if (msg == JMGlobal::PACKET_MSG_DO_CMD)
    {
      uint8_t command = JMData::getValueFromPacket(package);
      if (cmd->getCmdStatus(command) == JMGlobal::CMD_STATUS_IDLE)
      {
        // newPackageCompleted = false;
        cmd->processPackage(package);
        ongoingPackage = false;
      }
    }
    else
    {
      cmd->processPackage(package);
      ongoingPackage = false;
      packageSent = true;
    }
  }
  else
  {
    if (packageSent)
      ir->receiveIr();
  }
}

void receiveEvent(int howMany)
{
  Serial.println(F("receive"));
  byte data[howMany];
  int i = 0;
  while (wifiWire->getWire()->available())
  {
    byte c = wifiWire->getWire()->read();
    data[i++] = c;
  }
  package = msgInt64(data);
  ongoingPackage = true;
  packageSent = false;
}

void requestEvent()
{
  // Serial.println(F("xrequested"));
  uint64_t data;

  if (ongoingPackage)
  {
    if (packageSent)
    {
      data = devData->devDataToInt64();
    }
    else
    {
      Serial.println(F("QUE"));
      data = devData->devDataToInt64Queued();
    }
    }
  else
  {
    data = devData->devDataToInt64();
  }

  byte *msg = JMData::msgToBytes(data);
  for (uint8_t i = 0; i < 8; i++)
  {
    // Serial.println(*(msg + i));
  }

  if (cmd->isInitialized())
  {
    Serial.println(F("send"));
    wifiWire->sendMessage2(msg);
  }
  else
  {
    Serial.println(F("uninitialized"));
    byte tmp[8];
    tmp[0] = 255;
    tmp[1] = 0;
    tmp[2] = 0;
    tmp[3] = 0;
    tmp[4] = 0;
    tmp[5] = 0;
    tmp[6] = 0;
    tmp[7] = 0;

    wifiWire->sendMessage2(tmp);
  }

  if (!packageSent)
  {
    packageSent = true;
  }

  /*uint64_t data = devData->devDataToInt64();
  if (!packageSent)
    data = devData->devDataToInt64Queued();
  byte *msg = JMData::msgToBytes(data);
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.println(*(msg + i));
  }
  Serial.println("send");
  wifiWire->sendMessage2(msg);
  if (!packageSent)
    packageSent = true;*/
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