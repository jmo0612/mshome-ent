#include "JMCommand.h"
//#include "JMWifi.h"

// JMWifi *wifi = new JMWifi();
JMCommand *cmd = new JMCommand();

void setup()
{
  Serial.begin(115200);
  delay(1000);

  // wifi->setup();
  cmd->setup();

  // cmd->doCommand(JMCommand::CMD_BOX_TO_LG);
}

void loop()
{
  delay(3000);
  // wifi->sendHttp("/mshome-ent/post_tes.php", "aaa");
  //  wifiTest();
  //  doit();
}

void doit()
{

  // cmd
  delay(5000);
}