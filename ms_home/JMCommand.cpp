#include "JMCommand.h"
#include "JMRelay8.h"
#include "JMIr.h"
#include "JMDevice.h"

JMCommand::JMCommand(){

};
void JMCommand::setup()
{
    this->initSetup();
};
void JMCommand::doCommand(int cmd)
{
    if (cmd == CMD_BOX_TO_LG)
        this->cmdBoxToLg();
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
    this->displayLG = new JMDevice("Home Cinema",
                                   *this->relay8[0]->getRelay(0),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   5000,
                                   3000);
};
void JMCommand::setDisplayAkari()
{
    this->displayAkari = new JMDevice("Bedroom",
                                      *this->relay8[0]->getRelay(1),
                                      *this->ir,
                                      0x0,
                                      0x0,
                                      3000,
                                      2000,
                                      5000,
                                      3000);
};

void JMCommand::setHdmiAmpLG()
{
    this->hdmiAmpLG = new JMDevice("Splitter Home Cinema",
                                   *this->relay8[0]->getRelay(2),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   0,
                                   0);
};
void JMCommand::setHdmiAmpAkari()
{
    this->hdmiAmpAkari = new JMDevice("Splitter Bedroom",
                                      *this->relay8[0]->getRelay(3),
                                      *this->ir,
                                      0x0,
                                      0x0,
                                      3000,
                                      2000,
                                      0,
                                      0);
};
void JMCommand::setHdmiAmpPS()
{
    this->hdmiAmpPS = new JMDevice("Splitter PS",
                                   *this->relay8[0]->getRelay(4),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   0,
                                   0);
};

void JMCommand::setHdmiMatrix()
{
    this->hdmiMatrix = new JMDevice("Matrix",
                                    *this->relay8[0]->getRelay(5),
                                    *this->ir,
                                    0x0,
                                    0x0,
                                    3000,
                                    2000,
                                    5000,
                                    3000);
};

void JMCommand::setPlayerBox()
{
    this->playerBox = new JMDevice("Box",
                                   *this->relay8[0]->getRelay(6),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   5000,
                                   3000);
};
void JMCommand::setPlayerIndi()
{
    this->playerIndi = new JMDevice("IndiHome",
                                    *this->relay8[0]->getRelay(7),
                                    *this->ir,
                                    0x0,
                                    0x0,
                                    3000,
                                    2000,
                                    5000,
                                    3000);
};
void JMCommand::setPlayerPS()
{
    return;
    this->playerPS = new JMDevice("PS3",
                                  *this->relay8[1]->getRelay(7),
                                  *this->ir,
                                  0x0,
                                  0x0,
                                  3000,
                                  2000,
                                  5000,
                                  3000);
};

void JMCommand::setServerEvercossBat()
{
    return;
    this->serverEvercossBat = new JMDevice("Evercoss Power",
                                           *this->relay8[1]->getRelay(0),
                                           *this->ir,
                                           0x0,
                                           0x0,
                                           3000,
                                           2000,
                                           5000,
                                           3000);
};
void JMCommand::setServerEvercossCharger()
{
    return;
    this->serverEvercossCharger = new JMDevice("Evercoss Charger",
                                               *this->relay8[1]->getRelay(1),
                                               *this->ir,
                                               0x0,
                                               0x0,
                                               3000,
                                               2000,
                                               5000,
                                               3000);
};
void JMCommand::setServerNAS()
{
    return;
    this->serverNAS = new JMDevice("NAS",
                                   *this->relay8[1]->getRelay(2),
                                   *this->ir,
                                   0x0,
                                   0x0,
                                   3000,
                                   2000,
                                   5000,
                                   3000);
};
void JMCommand::setHddDock()
{
    return;
    this->hddDock = new JMDevice("HDD Dock",
                                 *this->relay8[1]->getRelay(3),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 3000,
                                 2000,
                                 5000,
                                 3000);
};
void JMCommand::setSpeaker()
{
    return;
    this->speaker = new JMDevice("Speaker",
                                 *this->relay8[1]->getRelay(4),
                                 *this->ir,
                                 0x0,
                                 0x0,
                                 3000,
                                 2000,
                                 5000,
                                 3000);
};