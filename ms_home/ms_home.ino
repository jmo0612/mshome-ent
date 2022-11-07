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
bool online = false;

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
  if (cmd->isInitialized())
  {
    Serial.println("OK");
  }
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
  }
  else
  {
    if (packageSent && cmd->isInitialized())
      ir->receiveIr();
  }
}

void receiveEvent(int howMany)
{
  Serial.println("receive");
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
  Serial.println("requested");
  uint64_t data;
  if (ongoingPackage)
  {
    data = devData->devDataToInt64();
  }
  else
  {
    if (packageSent)
    {
      data = devData->devDataToInt64();
    }
    else
    {
      data = devData->devDataToInt64Queued();
    }
    byte *msg = JMData::msgToBytes(data);
    for (uint8_t i = 0; i < 8; i++)
    {
      // Serial.println(*(msg + i));
    }

    if (cmd->isInitialized())
    {
      Serial.println("send");
      wifiWire->sendMessage2(msg);
    }

    if (!packageSent)
    {
      packageSent = true;
    }
  }

  /*uint64_t data = devData->devDataToInt64();
  if (!newPackageCompleted)
    data = devData->devDataToInt64Queued();
  byte *msg = JMData::msgToBytes(data);
  for (uint8_t i = 0; i < 8; i++)
  {
    // Serial.println(*(msg + i));
  }
  Serial.println("send");
  wifiWire->sendMessage2(msg);
  if (!newPackageCompleted)
    newPackageCompleted = true;*/
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
