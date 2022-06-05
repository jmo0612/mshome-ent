#include "JMCommand.h"
#include "JMRelay8.h"
#include "JMIr.h"
#include "JMDevice.h"
#include "JMFunctions.h"

char *statTmp;
JMCommand::JMCommand()
{
    this->devs = new List<JMDevice *>();
};
void JMCommand::setup()
{
    this->initSetup();
};
void JMCommand::updateStats(JMDevice &dev)
{
    String mode = (String)dev.getMode();
    char c = char(mode[0]);
    this->stats[dev.getId()] = c;
};
void JMCommand::updateStats(char *stats)
{
    this->stats = stats;
};
char *JMCommand::getStats()
{
    return this->stats;
};
const char *JMCommand::extractTaskType(const char *msg)
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
};
char *JMCommand::extractTaskMsg(const char *msg, const char *taskType)
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
    String ret = "";
    for (int i = 0; i < j; i++)
    {
        ret += char(msg[ind++]);
    }
    Serial.println(ret);
    return (char *)JMFunctions::strToCharP(ret);
};
void JMCommand::processTask(const char *msg)
{
    const char *taskType = this->extractTaskType(msg);
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
    // delete msg;
};
void JMCommand::specialInit()
{
    // LG TV
    if (statTmp[this->displayLG->getId()] == '2')
    {
        this->stats[this->displayLG->getId()] = '2';
        this->displayLG->setShutDownFailed(true);
    }
};
const char *JMCommand::getStatsPacked()
{
    if (this->stats == "")
        return "";

    String ret = "|UPD";
    ret += this->stats;
    ret += "|";
    return ret.c_str();
};
bool JMCommand::isLoaded()
{
    return this->loaded;
};
void JMCommand::doInetCommand(const char *cmd){

};
void JMCommand::doCommand(int cmd)
{
    if (cmd == CMD_BOX_TO_LG)
        this->cmdBoxToLg();

    Serial.println(this->stats);
};

uint32_t JMCommand::getMatrixCode(int cmd)
{
    if (cmd == CMD_BOX_TO_LG)
        return 0x0;
    if (cmd == CMD_INDI_TO_LG)
        return 0x0;
    if (cmd == CMD_PS_TO_LG)
        return 0x0;
    if (cmd == CMD_ELSE_TO_LG)
        return 0x0;
    if (cmd == CMD_BOX_TO_AKARI)
        return 0x0;
    if (cmd == CMD_INDI_TO_AKARI)
        return 0x0;
    if (cmd == CMD_PS_TO_AKARI)
        return 0x0;
    if (cmd == CMD_ELSE_TO_AKARI)
        return 0x0;
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
        this->ir->sendIr(this->getMatrixCode(CMD_BOX_TO_LG));
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
        this->ir->sendIr(this->getMatrixCode(CMD_INDI_TO_LG));
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
        this->ir->sendIr(this->getMatrixCode(CMD_PS_TO_LG));
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
        this->ir->sendIr(this->getMatrixCode(CMD_BOX_TO_AKARI));
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
        this->ir->sendIr(this->getMatrixCode(CMD_INDI_TO_AKARI));
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
        this->ir->sendIr(this->getMatrixCode(CMD_PS_TO_AKARI));
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
    this->ir = new JMIr();
    this->relay8[0] = new JMRelay8(0x20);
    this->relay8[1] = new JMRelay8(0x22);
    this->relay8[2] = new JMRelay8(0x23);

    // this->relay8[0] = new JMRelay8(0x22);

    // init
    this->setRelay8();
    this->setIr();

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
void JMCommand::setIr()
{
    this->ir->setup();
};

void JMCommand::setDisplayLG()
{
    this->displayLG = new JMDevice(0, "Home Cinema",
                                   *this,
                                   *this->relay8[0]->getRelay(0),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   5000,
                                   3000);
    this->devs->add(this->displayLG);
};
void JMCommand::setDisplayAkari()
{
    this->displayAkari = new JMDevice(1, "Bedroom",
                                      *this,
                                      *this->relay8[0]->getRelay(1),
                                      *this->ir,
                                      0x0,
                                      0x0,
                                      3000,
                                      2000,
                                      5000,
                                      3000);
    this->devs->add(this->displayAkari);
};

void JMCommand::setHdmiAmpLG()
{
    this->hdmiAmpLG = new JMDevice(2, "Splitter Home Cinema",
                                   *this,
                                   *this->relay8[0]->getRelay(2),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   0,
                                   0);
    this->devs->add(this->hdmiAmpLG);
};
void JMCommand::setHdmiAmpAkari()
{
    this->hdmiAmpAkari = new JMDevice(3, "Splitter Bedroom",
                                      *this,
                                      *this->relay8[0]->getRelay(3),
                                      *this->ir,
                                      0x0,
                                      0x0,
                                      3000,
                                      2000,
                                      0,
                                      0);
    this->devs->add(this->hdmiAmpAkari);
};
void JMCommand::setHdmiAmpPS()
{
    this->hdmiAmpPS = new JMDevice(4, "Splitter PS",
                                   *this,
                                   *this->relay8[0]->getRelay(4),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   0,
                                   0);
    this->devs->add(this->hdmiAmpPS);
};

void JMCommand::setHdmiMatrix()
{
    this->hdmiMatrix = new JMDevice(5, "Matrix",
                                    *this,
                                    *this->relay8[0]->getRelay(5),
                                    *this->ir,
                                    0x0,
                                    0x0,
                                    3000,
                                    2000,
                                    5000,
                                    3000);
    this->devs->add(this->hdmiMatrix);
};

void JMCommand::setPlayerBox()
{
    this->playerBox = new JMDevice(6, "Box",
                                   *this,
                                   *this->relay8[0]->getRelay(6),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   5000,
                                   3000);
    this->devs->add(this->playerBox);
};
void JMCommand::setPlayerIndi()
{
    this->playerIndi = new JMDevice(7, "IndiHome",
                                    *this,
                                    *this->relay8[0]->getRelay(7),
                                    *this->ir,
                                    0x0,
                                    0x0,
                                    3000,
                                    2000,
                                    5000,
                                    3000);
    this->devs->add(this->playerIndi);
};
void JMCommand::setPlayerPS()
{
    return;
    this->playerPS = new JMDevice(8, "PS3",
                                  *this,
                                  *this->relay8[1]->getRelay(7),
                                  *this->ir,
                                  0x0,
                                  0x0,
                                  3000,
                                  2000,
                                  5000,
                                  3000);
    this->devs->add(this->playerPS);
};

void JMCommand::setServerEvercossBat()
{
    return;
    this->serverEvercossBat = new JMDevice(9, "Evercoss Power",
                                           *this,
                                           *this->relay8[1]->getRelay(0),
                                           *this->ir,
                                           0x0,
                                           0x0,
                                           3000,
                                           2000,
                                           5000,
                                           3000);
    this->devs->add(this->serverEvercossBat);
};
void JMCommand::setServerEvercossCharger()
{
    return;
    this->serverEvercossCharger = new JMDevice(10, "Evercoss Charger",
                                               *this,
                                               *this->relay8[1]->getRelay(1),
                                               *this->ir,
                                               0x0,
                                               0x0,
                                               3000,
                                               2000,
                                               5000,
                                               3000);
    this->devs->add(this->serverEvercossCharger);
};
void JMCommand::setServerNAS()
{
    return;
    this->serverNAS = new JMDevice(11, "NAS",
                                   *this,
                                   *this->relay8[1]->getRelay(2),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   5000,
                                   3000);
    this->devs->add(this->serverNAS);
};
void JMCommand::setHddDock()
{
    return;
    this->hddDock = new JMDevice(12, "HDD Dock",
                                 *this,
                                 *this->relay8[1]->getRelay(3),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 3000,
                                 2000,
                                 5000,
                                 3000);
    this->devs->add(this->hddDock);
};
void JMCommand::setSpeaker()
{
    return;
    this->speaker = new JMDevice(13, "Speaker",
                                 *this,
                                 *this->relay8[1]->getRelay(4),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 3000,
                                 2000,
                                 5000,
                                 3000);
    this->devs->add(this->speaker);
};