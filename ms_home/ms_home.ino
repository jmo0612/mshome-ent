#include "JMCommand.h"

JMCommand *cmd = new JMCommand();

void setup()
{

  cmd->setup();
  Serial.begin(9600);
  delay(1000);
  // cmd->doCommand(JMCommand::CMD_BOX_TO_LG);
}

void loop()
{
  // delay(1000);
  // wifiTest();
  // doit();
}

void doit()
{

  // cmd
  delay(5000);
}

void wifiTest()
{
  Serial.println("tes");
  delay(10000);
}
