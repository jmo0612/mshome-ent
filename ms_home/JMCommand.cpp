#include "JMCommand.h"
#include "JMRelay8.h"
#include "JMIr.h"
#include "JMDevice.h"
#include "JMFunctions.h"
#include "JMGlobal.h"
#include "JMData.h"

char *statTmp;
JMCommand::JMCommand()
{
    this->devs = new List<JMDevice *>();
};
void JMCommand::setup(JMIr *ir, JMData *devData)
{
    this->ir = ir;
    this->devData = devData;
    this->ir->setCommander(*this);
    this->initSetup();
};
void JMCommand::updateStats(JMDevice &dev)
{
    int mode = dev.getMode();
    this->devData->updateDevice(dev.getId(), mode);
};
/*void JMCommand::updateStats(char *stats)
{
    this->stats = stats;
};*/
/*char *JMCommand::getStats()
{
    return this->stats;
};*/
/*char *JMCommand::extractTaskType(char *msg)
{
    if (msg[1] == 'S' && msg[2] == 'T' && msg[3] == 'A' && msg[4] == 'T' && msg[5] == 'S')
    {
        return "STATS";
    }
    else if (msg[1] == 'C' && msg[2] == 'M' && msg[3] == 'D')
    {
        return "CMD";
    }
    return "NONE";
};*/
/*char *JMCommand::extractTaskMsg(char *msg, char *taskType)
{
    // Serial.println(taskType);
    if (taskType == "NONE")
        return "";
    int ind = 32;
    if (taskType == "STATS")
    {
        // Serial.println("stats");
        ind = 6;
    }
    else if (taskType == "CMD")
    {
        // Serial.println("cmd");
        ind = 4;
    }
    int j = 0;
    for (int i = ind; i < 32; i++)
    {
        if (msg[i] == '|')
            break;
        j++;
    }
    char ret[j];
    for (int i = 0; i < j; i++)
    {
        int tmp = int(msg[ind++]);
        ret[i] = tmp;
    }
    Serial.println(ret);
    //  char *r = (char *)JMFunctions::strToCharP(ret);
    //  delete ret;
    //  delete &ret;
    return ret;
};*/
/*void JMCommand::processTask(char *msg)
{
    char *taskType = this->extractTaskType(msg);
    char *taskData = this->extractTaskMsg(msg, taskType);
    if (taskType == "STATS")
    {
        statTmp = (char *)JMFunctions::strToCharP(taskData);
        this->specialInit();
        this->loaded = true;
    }
    else if (taskType == "CMD")
    {
        Serial.println(taskData);
    }

    //  delete msg;
};*/
/*void JMCommand::specialInit()
{
    // LG TV
    if (statTmp[this->displayLG->getId()] == '2')
    {
        this->stats[this->displayLG->getId()] = '2';
        this->displayLG->setShutDownFailed(true);
    }
};*/
/*char *JMCommand::getStatsPacked()
{
    if (this->stats == "")
        return "";

    String ret = "|UPD";
    ret += this->stats;
    ret += "|";
    return (char *)ret.c_str();
};*/
/*bool JMCommand::isLoaded()
{
    return this->loaded;
};*/
void JMCommand::doInetCommand(char *cmd){

};
void JMCommand::doCommand(int cmd)
{
    if (this->cmdStats[cmd] == JMGlobal::CMD_STATUS_PROCESSING)
        return;
    this->cmdStats[cmd] = JMGlobal::CMD_STATUS_PROCESSING;
    if (cmd == JMGlobal::DO_CMD_BOX_TO_LG)
    {
        this->cmdBoxToLg();
    }
    else if (cmd == JMGlobal::DO_CMD_BOX_TO_AKARI)
    {
        this->cmdBoxToAkari();
    }
    else if (cmd == JMGlobal::DO_CMD_ELSE_TO_LG)
    {
        //
    }
    else if (cmd == JMGlobal::DO_CMD_ELSE_TO_AKARI)
    {
        //
    }
    else if (cmd == JMGlobal::DO_CMD_INDI_TO_LG)
    {
        this->cmdIndiToLg();
    }
    else if (cmd == JMGlobal::DO_CMD_INDI_TO_AKARI)
    {
        this->cmdIndiToAkari();
    }
    else if (cmd == JMGlobal::DO_CMD_PS_TO_LG)
    {
        this->cmdPsToLg();
    }
    else if (cmd == JMGlobal::DO_CMD_PS_TO_AKARI)
    {
        this->cmdPsToAkari();
    }

    // Serial.println("this->stats");
    this->cmdStats[cmd] = JMGlobal::CMD_STATUS_IDLE;
};

uint32_t JMCommand::getMatrixCode(int cmd)
{
    if (cmd == JMGlobal::DO_CMD_BOX_TO_LG)
        return 4211376000;
    if (cmd == JMGlobal::DO_CMD_INDI_TO_LG)
        return 4177952640;
    if (cmd == JMGlobal::DO_CMD_PS_TO_LG)
        return 4228087680;
    if (cmd == JMGlobal::DO_CMD_ELSE_TO_LG)
        return 4261511040;
    if (cmd == JMGlobal::DO_CMD_BOX_TO_AKARI)
        return 4111105920;
    if (cmd == JMGlobal::DO_CMD_INDI_TO_AKARI)
        return 3760160640;
    if (cmd == JMGlobal::DO_CMD_PS_TO_AKARI)
        return 4127817600;
    if (cmd == JMGlobal::DO_CMD_ELSE_TO_AKARI)
        return 4161240960;
    return 0x0;
};
//============================================= COMMANDS ====================================
void JMCommand::cmdBoxToLg()
{
    if (this->homeCinemaCurrent == this->playerBox)
    {
        if (this->bedroomCurrent != this->playerBox)
            this->playerBox->shutDown();
        this->hdmiAmpLG->acOff();
        this->displayLG->acOff();
        if (this->bedroomCurrent == NULL)
            this->hdmiMatrix->acOff();
        this->homeCinemaCurrent = NULL;
    }
    else
    {
        this->hdmiMatrix->run();
        this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_BOX_TO_LG));
        this->hdmiAmpLG->run();
        this->displayLG->run();
        this->playerBox->run();
        this->homeCinemaCurrent = this->playerBox;
    }
};
void JMCommand::cmdIndiToLg()
{
    if (this->homeCinemaCurrent == this->playerIndi)
    {
        if (this->bedroomCurrent != this->playerIndi)
            this->playerIndi->shutDown();
        this->hdmiAmpLG->acOff();
        if (this->bedroomCurrent == NULL)
            this->hdmiMatrix->acOff();
        this->homeCinemaCurrent = NULL;
    }
    else
    {
        this->hdmiMatrix->run();
        this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_INDI_TO_LG));
        this->hdmiAmpLG->run();
        this->playerIndi->run();
        this->homeCinemaCurrent = this->playerIndi;
    }
};
void JMCommand::cmdPsToLg()
{
    if (this->homeCinemaCurrent == this->playerPS)
    {
        if (this->bedroomCurrent != this->playerPS)
        {
            this->playerPS->shutDown();
            this->hdmiAmpPS->shutDown();
        }

        this->hdmiAmpLG->acOff();
        if (this->bedroomCurrent == NULL)
            this->hdmiMatrix->acOff();
        this->homeCinemaCurrent = NULL;
    }
    else
    {
        this->hdmiMatrix->run();
        this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_PS_TO_LG));
        this->hdmiAmpLG->run();
        this->hdmiAmpPS->run();
        this->playerPS->run();
        this->homeCinemaCurrent = this->playerPS;
    }
};
void JMCommand::cmdElseToLg(){
    // NOT YET
};

void JMCommand::cmdBoxToAkari()
{
    if (this->bedroomCurrent == this->playerBox)
    {
        if (this->homeCinemaCurrent != this->playerBox)
            this->playerBox->shutDown();
        this->hdmiAmpAkari->acOff();
        if (this->homeCinemaCurrent == NULL)
            this->hdmiMatrix->acOff();
        this->bedroomCurrent = NULL;
    }
    else
    {
        this->hdmiMatrix->run();
        this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_BOX_TO_AKARI));
        this->hdmiAmpAkari->run();
        this->playerBox->run();
        this->bedroomCurrent = this->playerBox;
    }
};
void JMCommand::cmdIndiToAkari()
{
    if (this->bedroomCurrent == this->playerIndi)
    {
        if (this->homeCinemaCurrent != this->playerIndi)
            this->playerIndi->shutDown();
        this->hdmiAmpAkari->acOff();
        if (this->homeCinemaCurrent == NULL)
            this->hdmiMatrix->acOff();
        this->bedroomCurrent = NULL;
    }
    else
    {
        this->hdmiMatrix->run();
        this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_INDI_TO_AKARI));
        this->hdmiAmpAkari->run();
        this->playerIndi->run();
        this->bedroomCurrent = this->playerIndi;
    }
};
void JMCommand::cmdPsToAkari()
{
    if (this->bedroomCurrent == this->playerPS)
    {
        if (this->homeCinemaCurrent != this->playerPS)
            this->playerPS->shutDown();
        this->hdmiAmpAkari->acOff();
        if (this->homeCinemaCurrent == NULL)
            this->hdmiMatrix->acOff();
        this->bedroomCurrent = NULL;
    }
    else
    {
        this->hdmiMatrix->run();
        this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_PS_TO_AKARI));
        this->hdmiAmpAkari->run();
        this->playerPS->run();
        this->bedroomCurrent = this->playerPS;
    }
};
void JMCommand::cmdElseToAkari(){
    // NOT YET
};
void JMCommand::cmdTogglePowerSpeaker()
{
    if (this->speaker->getMode() == JMDevice::DEV_MODE_RUNNING)
        this->speaker->shutDown();
    else
        this->speaker->run();
};
void JMCommand::cmdCalibratePowerLg()
{
    this->displayLG->calibrate();
};
void JMCommand::cmdCalibratePowerAkari()
{
    this->displayAkari->calibrate();
};
void JMCommand::cmdCalibratePowerSpeaker()
{
    this->speaker->calibrate();
};
void JMCommand::cmdCalibratePowerMatrix()
{
    this->hdmiMatrix->calibrate();
};

//============================================= CONFIG ======================================
void JMCommand::initSetup()
{
    // = {new JMRelay8(0x21), new JMRelay8(0x22), new JMRelay8(0x23)}

    //*this->relay8 = {new JMRelay8(0x21), new JMRelay8(0x22), new JMRelay8(0x23)};

    this->relay8[0] = new JMRelay8(0x20);
    this->relay8[1] = new JMRelay8(0x22);
    this->relay8[2] = new JMRelay8(0x23);

    // this->relay8[0] = new JMRelay8(0x22);

    // init
    this->setRelay8();

    this->setDisplayLG();
    this->setDisplayAkari();

    this->setHdmiAmpLG();
    this->setHdmiAmpAkari();
    this->setHdmiAmpPS();

    this->setHdmiMatrix();

    this->setPlayerBox();
    this->setPlayerIndi();
    this->setPlayerPS();

    this->setServerEvercossBat();
    this->setServerEvercossCharger();
    this->setServerNAS();
    this->setHddDock();
    this->setSpeaker();
};

void JMCommand::setRelay8()
{
    for (int i = 0; i < 3; i++)
    {
        this->relay8[i]->setup();
    }
};

void JMCommand::setDisplayLG()
{
    this->displayLG = new JMDevice(JMGlobal::DEV_DISPLAY_LG, "Home Cinema",
                                   *this,
                                   *this->relay8[0]->getRelay(0),
                                   *this->ir,
                                   4144560900,
                                   4144560900,
                                   5000,
                                   2000,
                                   5000,
                                   5000);
    this->devs->add(this->displayLG);
};
void JMCommand::setDisplayAkari()
{
    this->displayAkari = new JMDevice(JMGlobal::DEV_DISPLAY_AKARI, "Bedroom",
                                      *this,
                                      *this->relay8[0]->getRelay(1),
                                      *this->ir,
                                      4111105792,
                                      4111105792,
                                      5000,
                                      2000,
                                      5000,
                                      5000);
    this->devs->add(this->displayAkari);
};

void JMCommand::setHdmiAmpLG()
{
    this->hdmiAmpLG = new JMDevice(JMGlobal::DEV_HDMI_AMP_LG, "Splitter Home Cinema",
                                   *this,
                                   *this->relay8[0]->getRelay(2),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   5000,
                                   2000,
                                   0,
                                   0);
    this->devs->add(this->hdmiAmpLG);
};
void JMCommand::setHdmiAmpAkari()
{
    this->hdmiAmpAkari = new JMDevice(JMGlobal::DEV_HDMI_AMP_AKARI, "Splitter Bedroom",
                                      *this,
                                      *this->relay8[0]->getRelay(3),
                                      *this->ir,
                                      0x0,
                                      0x0,
                                      5000,
                                      2000,
                                      0,
                                      0);
    this->devs->add(this->hdmiAmpAkari);
};
void JMCommand::setHdmiAmpPS()
{
    this->hdmiAmpPS = new JMDevice(JMGlobal::DEV_HDMI_AMP_PS, "Splitter PS",
                                   *this,
                                   *this->relay8[0]->getRelay(4),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   5000,
                                   2000,
                                   0,
                                   0);
    this->devs->add(this->hdmiAmpPS);
};

void JMCommand::setHdmiMatrix()
{
    this->hdmiMatrix = new JMDevice(JMGlobal::DEV_HDMI_MATRIX, "Matrix",
                                    *this,
                                    *this->relay8[0]->getRelay(5),
                                    *this->ir,
                                    3977412480,
                                    3977412480,
                                    5000,
                                    2000,
                                    5000,
                                    5000);
    this->devs->add(this->hdmiMatrix);
};

void JMCommand::setPlayerBox()
{
    this->playerBox = new JMDevice(JMGlobal::DEV_PLAYER_BOX, "Box",
                                   *this,
                                   *this->relay8[0]->getRelay(6),
                                   *this->ir,
                                   2122416000,
                                   2122416000,
                                   5000,
                                   2000,
                                   5000,
                                   5000);
    this->devs->add(this->playerBox);
};
void JMCommand::setPlayerIndi()
{
    this->playerIndi = new JMDevice(JMGlobal::DEV_PLAYER_INDI, "IndiHome",
                                    *this,
                                    *this->relay8[0]->getRelay(7),
                                    *this->ir,
                                    3208707840,
                                    3208707840,
                                    5000,
                                    2000,
                                    5000,
                                    5000);
    this->devs->add(this->playerIndi);
};
void JMCommand::setPlayerPS()
{
    return;
    this->playerPS = new JMDevice(JMGlobal::DEV_PLAYER_PS, "PS3",
                                  *this,
                                  *this->relay8[1]->getRelay(0),
                                  *this->ir,
                                  0x0,
                                  0x0,
                                  5000,
                                  2000,
                                  30000,
                                  120000);
    this->devs->add(this->playerPS);
};

void JMCommand::setServerEvercossBat()
{
    return;
    this->serverEvercossBat = new JMDevice(JMGlobal::DEV_SERVER_EVERCOSS_BAT, "Evercoss Power",
                                           *this,
                                           *this->relay8[1]->getRelay(1),
                                           *this->ir,
                                           0x0,
                                           0x0,
                                           5000,
                                           2000,
                                           5000,
                                           60000);
    this->devs->add(this->serverEvercossBat);
};
void JMCommand::setServerEvercossCharger()
{
    return;
    this->serverEvercossCharger = new JMDevice(JMGlobal::DEV_SERVER_EVERCOSS_CHARGER, "Evercoss Charger",
                                               *this,
                                               *this->relay8[1]->getRelay(2),
                                               *this->ir,
                                               0x0,
                                               0x0,
                                               5000,
                                               2000,
                                               5000,
                                               5000);
    this->devs->add(this->serverEvercossCharger);
};
void JMCommand::setServerNAS()
{
    return;
    this->serverNAS = new JMDevice(JMGlobal::DEV_SERVER_NAS, "NAS",
                                   *this,
                                   *this->relay8[1]->getRelay(3),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   5000,
                                   2000,
                                   5000,
                                   5000);
    this->devs->add(this->serverNAS);
};
void JMCommand::setHddDock()
{
    return;
    this->hddDock = new JMDevice(JMGlobal::DEV_HDD_DOCK, "HDD Dock",
                                 *this,
                                 *this->relay8[1]->getRelay(4),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 5000,
                                 2000,
                                 5000,
                                 5000);
    this->devs->add(this->hddDock);
};
void JMCommand::setSpeaker()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_SPEAKER, "Speaker",
                                 *this,
                                 *this->relay8[1]->getRelay(5),
                                 *this->ir,
                                 4278190467,
                                 4278190467,
                                 5000,
                                 2000,
                                 5000,
                                 5000);
    this->devs->add(this->speaker);
};
void JMCommand::setRemoteA1()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_REMOTE_A1, "RemoteA1",
                                 *this,
                                 *this->relay8[2]->getRelay(0),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 0,
                                 0,
                                 0,
                                 0);
    this->devs->add(this->remoteA1);
};
void JMCommand::setRemoteA2()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_REMOTE_A2, "RemoteA2",
                                 *this,
                                 *this->relay8[2]->getRelay(1),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 0,
                                 0,
                                 0,
                                 0);
    this->devs->add(this->remoteA2);
};
void JMCommand::setRemoteA3()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_REMOTE_A3, "RemoteA3",
                                 *this,
                                 *this->relay8[2]->getRelay(2),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 0,
                                 0,
                                 0,
                                 0);
    this->devs->add(this->remoteA3);
};
void JMCommand::setRemoteA4()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_REMOTE_A4, "RemoteA4",
                                 *this,
                                 *this->relay8[2]->getRelay(3),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 0,
                                 0,
                                 0,
                                 0);
    this->devs->add(this->remoteA4);
};
void JMCommand::setRemoteB1()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_REMOTE_B1, "RemoteB1",
                                 *this,
                                 *this->relay8[2]->getRelay(4),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 0,
                                 0,
                                 0,
                                 0);
    this->devs->add(this->remoteB1);
};
void JMCommand::setRemoteB2()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_REMOTE_B2, "RemoteB2",
                                 *this,
                                 *this->relay8[2]->getRelay(5),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 0,
                                 0,
                                 0,
                                 0);
    this->devs->add(this->remoteB2);
};
void JMCommand::setRemoteB3()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_REMOTE_B3, "RemoteB3",
                                 *this,
                                 *this->relay8[2]->getRelay(6),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 0,
                                 0,
                                 0,
                                 0);
    this->devs->add(this->remoteB3);
};
void JMCommand::setRemoteB4()
{
    return;
    this->speaker = new JMDevice(JMGlobal::DEV_REMOTE_B4, "RemoteB4",
                                 *this,
                                 *this->relay8[2]->getRelay(7),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 0,
                                 0,
                                 0,
                                 0);
    this->devs->add(this->remoteB4);
};