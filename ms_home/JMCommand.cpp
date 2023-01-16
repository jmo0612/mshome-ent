#include "JMCommand.h"
#include "JMRelay8.h"
#include "JMIr.h"
#include "JMDevice.h"
#include "JMGlobal.h"
#include "JMData.h"
#include "JMWifiWire.h"

JMCommand::JMCommand(){
    // this->devs = new List<JMDevice *>();
};
void JMCommand::setup(JMIr *ir, JMData *devData, JMWifiWire *wifiWire)
{
    this->ir = ir;
    this->devData = devData;
    this->wifiWire = wifiWire;
    this->ir->setCommander(*this);
    this->initSetup();
};
void JMCommand::processPackage(const int64_t package)
{
    // Serial.println(F("prosesing"));
    uint8_t msg = JMData::getMsgFromPacket(package);
    // Serial.println(msg);
    if (msg == JMGlobal::PACKET_MSG_DO_CMD && this->initialized)
    {
        uint8_t inetCmd = JMData::getValueFromPacket(package);
        uint8_t cmd = this->getTranslatedInnetCommand(inetCmd);
        bool on = this->isForceOnInnetCommand(inetCmd);
        uint8_t mode = JMGlobal::CMD_MODE_FORCE_ON;
        if (!on)
            mode = JMGlobal::CMD_MODE_FORCE_OFF;
        if (inetCmd == JMGlobal::DO_INET_ON_CMD_SPEAKER)
        {
            if (this->speaker->getMode() != JMDevice::DEV_MODE_RUNNING)
                this->doInetCommand(cmd, mode);
        }
        else if (inetCmd == JMGlobal::DO_INET_OFF_CMD_SPEAKER)
        {
            if (this->speaker->getMode() != JMDevice::DEV_MODE_DEAD)
                this->doInetCommand(cmd, mode);
        }
        else if (inetCmd == JMGlobal::DO_INET_CMD_SLEEP_LG)
        {
            if (this->displayLG->getMode() == JMDevice::DEV_MODE_RUNNING)
                this->doInetCommand(cmd, mode);
        }
        else if (inetCmd == JMGlobal::DO_INET_CMD_WAKE_LG)
        {
            if (this->displayLG->getMode() != JMDevice::DEV_MODE_RUNNING)
                this->doInetCommand(cmd, mode);
        }
        else if (inetCmd == JMGlobal::DO_INET_CMD_SLEEP_AKARI)
        {
            if (this->displayAkari->getMode() == JMDevice::DEV_MODE_RUNNING)
                this->doInetCommand(cmd, mode);
        }
        else if (inetCmd == JMGlobal::DO_INET_CMD_WAKE_AKARI)
        {
            if (this->displayAkari->getMode() != JMDevice::DEV_MODE_RUNNING)
                this->doInetCommand(cmd, mode);
        }
        else
            this->doInetCommand(cmd, mode);
    }
    else if (msg == JMGlobal::PACKET_MSG_SPECIAL && this->initialized)
    {
        uint8_t val = JMData::getValueFromPacket(package);
        if (val == JMGlobal::MSG_SPECIAL_VALUE_SHUTDOWNALL)
        {
            this->shutDownAll();
            this->serverNAS->acOff();
            this->hddDock->acOff();
            this->serverEvercossCharger->acOff();
            // this->serverEvercossBat->acOff();
        }
    }
    else if (msg == JMGlobal::PACKET_MSG_INIT_DEVICES && !this->initialized)
    {
        // uint8_t val = JMData::getValueFromPacket(package);
        this->firstRun2(package);
    }
};
void JMCommand::shutDownAll()
{
    this->displayLG->acOff();
    this->displayAkari->acOff();
    this->playerBox->acOff();
    this->playerIndi->acOff();
    this->playerPS->acOff();
    this->playerElse->acOff();

    this->speaker->acOff();
    // this->playerBox->acOff();
    // this->playerIndi->acOff();
    // this->playerPS->acOff();
    // this->playerElse->acOff();
    this->hdmiAmpPS->acOff();
    this->hdmiAmpIndi->acOff();
    this->hdmiAmpLG->acOff();
    this->hdmiAmpAkari->acOff();
    this->hdmiMatrix->acOff();

    this->remoteA1->acOff();
    this->remoteA2->acOff();
    this->remoteA3->acOff();
    this->remoteA4->acOff();
    this->remoteB1->acOff();
    this->remoteB2->acOff();
    this->remoteB3->acOff();
    this->remoteB4->acOff();

    this->homeCinemaCurrent = NULL;
    this->bedroomCurrent = NULL;
};
void JMCommand::firstRun2(uint64_t package)
{
    // Serial.println(F("firstrun"));
    if (this->initialized)
        return;
    uint8_t msg = JMData::getMsgFromPacket(package);
    if (msg != JMGlobal::PACKET_MSG_INIT_DEVICES)
        return;
    this->devData->updateDevData(JMData::getValueFromPacket(package));
    for (uint8_t i = 0; i < 32; i++)
    {
        JMDevice *tmp = this->getDeviceById(i);
        if (tmp != NULL)
        {
            if (this->devData->getDeviceStatus(i) == 1)
            {
                tmp->setShutDownFailed(); // MODIFICATION: first run without IR
            }
            else if (this->devData->getDeviceStatus(i) == 2)
            {
                tmp->setAlwaysRunWithoutIrFromACOff(); // MODIFICATION: always run without IR (from acOff)
            }
            else
            {
                if (i != JMGlobal::DEV_SERVER_EVERCOSS_CHARGER && i != JMGlobal::DEV_SERVER_EVERCOSS_BAT && i != JMGlobal::DEV_HDD_DOCK && i != JMGlobal::DEV_SERVER_NAS)
                    tmp->acOff();
            }
        }
    }
    this->serverNAS->run();
    this->hddDock->run();
    this->initialized = true;
};
JMDevice *JMCommand::getDeviceById(uint8_t id)
{
    if (id == JMGlobal::DEV_DISPLAY_AKARI)
    {
        return this->displayAkari;
    }
    else if (id == JMGlobal::DEV_DISPLAY_LG)
    {
        return this->displayLG;
    }
    else if (id == JMGlobal::DEV_HDD_DOCK)
    {
        return this->hddDock;
    }
    else if (id == JMGlobal::DEV_HDMI_AMP_AKARI)
    {
        return this->hdmiAmpAkari;
    }
    else if (id == JMGlobal::DEV_HDMI_AMP_LG)
    {
        return this->hdmiAmpLG;
    }
    else if (id == JMGlobal::DEV_HDMI_AMP_PS)
    {
        return this->hdmiAmpPS;
    }
    else if (id == JMGlobal::DEV_HDMI_MATRIX)
    {
        return this->hdmiMatrix;
    }
    else if (id == JMGlobal::DEV_PLAYER_BOX)
    {
        return this->playerBox;
    }
    else if (id == JMGlobal::DEV_PLAYER_INDI)
    {
        return this->playerIndi;
    }
    else if (id == JMGlobal::DEV_PLAYER_PS)
    {
        return this->playerPS;
    }
    else if (id == JMGlobal::DEV_REMOTE_A1)
    {
        return this->remoteA1;
    }
    else if (id == JMGlobal::DEV_REMOTE_A2)
    {
        return this->remoteA2;
    }
    else if (id == JMGlobal::DEV_REMOTE_A3)
    {
        return this->remoteA3;
    }
    else if (id == JMGlobal::DEV_REMOTE_A4)
    {
        return this->remoteA4;
    }
    else if (id == JMGlobal::DEV_REMOTE_B1)
    {
        return this->remoteB1;
    }
    else if (id == JMGlobal::DEV_REMOTE_B2)
    {
        return this->remoteB2;
    }
    else if (id == JMGlobal::DEV_REMOTE_B3)
    {
        return this->remoteB3;
    }
    else if (id == JMGlobal::DEV_REMOTE_B4)
    {
        return this->remoteB4;
    }
    else if (id == JMGlobal::DEV_SERVER_EVERCOSS_BAT)
    {
        return this->serverEvercossBat;
    }
    else if (id == JMGlobal::DEV_SERVER_EVERCOSS_CHARGER)
    {
        return this->serverEvercossCharger;
    }
    else if (id == JMGlobal::DEV_SERVER_NAS)
    {
        return this->serverNAS;
    }
    else if (id == JMGlobal::DEV_SPEAKER)
    {
        return this->speaker;
    }
    else
    {
        return NULL;
    }
};
void JMCommand::updateStats(JMDevice &dev)
{
    uint8_t mode = dev.getMode();
    this->devData->updateDevice(dev.getId(), mode);
};

void JMCommand::doInetCommand(uint8_t cmd, uint8_t cmdMode)
{
    if (!this->initialized)
        return;
    // uint8_t cmdMode = JMGlobal::CMD_MODE_TOGGLE;
    // uint8_t cmdMode = JMGlobal::CMD_MODE_FORCE_ON;
    if (this->cmdStats[cmd] == JMGlobal::CMD_STATUS_PROCESSING)
        return;
    this->cmdStats[cmd] = JMGlobal::CMD_STATUS_PROCESSING;
    if (cmd == JMGlobal::DO_CMD_BOX_TO_LG)
    {
        this->cmdBoxToLg(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_BOX_TO_AKARI)
    {
        this->cmdBoxToAkari(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_ELSE_TO_LG)
    {
        this->cmdElseToLg(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_ELSE_TO_AKARI)
    {
        this->cmdElseToAkari(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_INDI_TO_LG)
    {
        this->cmdIndiToLg(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_INDI_TO_AKARI)
    {
        this->cmdIndiToAkari(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_PS_TO_LG)
    {
        this->cmdPsToLg(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_PS_TO_AKARI)
    {
        this->cmdPsToAkari(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_TOGGLE_POWER_SPEAKER)
    {
        this->cmdTogglePowerSpeaker();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_LG)
    {
        this->cmdCalibratePowerDisplayLG();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_AKARI)
    {
        this->cmdCalibratePowerDisplayAkari();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_LG)
    {
        this->cmdCalibratePowerPlayerLG();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_AKARI)
    {
        this->cmdCalibratePowerPlayerAkari();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_MATRIX)
    {
        this->cmdCalibratePowerMatrix();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_SPEAKER)
    {
        this->cmdCalibratePowerSpeaker();
    }
    else if (cmd == JMGlobal::DO_CMD_TURN_LG_OFF)
    {
        this->cmdTurnLgOff();
    }
    else if (cmd == JMGlobal::DO_CMD_TURN_AKARI_OFF)
    {
        this->cmdTurnAkariOff();
    }
    // this->wifiWire->setPackage(this->devData->devDataToInt64());

    // Serial.println(this->devData->cek());
    this->cmdStats[cmd] = JMGlobal::CMD_STATUS_IDLE;
};
uint8_t JMCommand::getCmdStatus(uint8_t cmd)
{
    if (cmd < 0 || cmd > 13)
        return 0;
    return this->cmdStats[cmd];
};
bool JMCommand::isInitialized()
{
    return this->initialized;
};
void JMCommand::doCommand(uint8_t cmd, uint8_t cmdMode)
{
    if (!this->initialized)
        return;
    // uint8_t cmdMode = JMGlobal::CMD_MODE_TOGGLE;
    // uint8_t cmdMode = JMGlobal::CMD_MODE_FORCE_ON;
    if (this->cmdStats[cmd] == JMGlobal::CMD_STATUS_PROCESSING)
        return;
    this->cmdStats[cmd] = JMGlobal::CMD_STATUS_PROCESSING;
    if (cmd == JMGlobal::DO_CMD_BOX_TO_LG)
    {
        this->cmdBoxToLg(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_BOX_TO_AKARI)
    {
        this->cmdBoxToAkari(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_ELSE_TO_LG)
    {
        this->cmdElseToLg(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_ELSE_TO_AKARI)
    {
        this->cmdElseToAkari(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_INDI_TO_LG)
    {
        this->cmdIndiToLg(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_INDI_TO_AKARI)
    {
        this->cmdIndiToAkari(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_PS_TO_LG)
    {
        this->cmdPsToLg(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_PS_TO_AKARI)
    {
        this->cmdPsToAkari(cmdMode);
    }
    else if (cmd == JMGlobal::DO_CMD_TOGGLE_POWER_SPEAKER)
    {
        this->cmdTogglePowerSpeaker();
    }
    else if (cmd == JMGlobal::DO_CMD_TOGGLE_SLEEP_LG)
    {
        this->cmdToggleSleepLg();
    }
    else if (cmd == JMGlobal::DO_CMD_TOGGLE_SLEEP_AKARI)
    {
        this->cmdToggleSleepAkari();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_LG)
    {
        this->cmdCalibratePowerDisplayLG();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_AKARI)
    {
        this->cmdCalibratePowerDisplayAkari();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_LG)
    {
        this->cmdCalibratePowerPlayerLG();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_AKARI)
    {
        this->cmdCalibratePowerPlayerAkari();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_MATRIX)
    {
        this->cmdCalibratePowerMatrix();
    }
    else if (cmd == JMGlobal::DO_CMD_CALIBRATE_POWER_SPEAKER)
    {
        this->cmdCalibratePowerSpeaker();
    }
    else if (cmd == JMGlobal::DO_CMD_TURN_LG_OFF)
    {
        this->cmdTurnLgOff();
    }
    else if (cmd == JMGlobal::DO_CMD_TURN_AKARI_OFF)
    {
        this->cmdTurnAkariOff();
    }
    // this->wifiWire->setPackage(this->devData->devDataToInt64());

    // Serial.println(this->devData->cek());
    this->cmdStats[cmd] = JMGlobal::CMD_STATUS_IDLE;
};

uint32_t JMCommand::getMatrixCode(uint8_t cmd)
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

void JMCommand::setRemote(uint8_t remote, uint8_t display)
{
    if (display == JMGlobal::DEV_DISPLAY_LG)
    {
        if (remote == JMGlobal::DEV_PLAYER_INDI)
        {
            this->remoteA1->run();
            this->remoteA2->run();
            this->remoteA3->run();
            this->remoteA4->run();
        }
        else
        {
            this->remoteA1->acOff();
            this->remoteA2->acOff();
            this->remoteA3->acOff();
            this->remoteA4->acOff();
        }
    }
    else
    {
        if (remote == JMGlobal::DEV_PLAYER_INDI)
        {
            this->remoteB1->run();
            this->remoteB2->run();
            this->remoteB3->run();
            this->remoteB4->run();
        }
        else
        {
            this->remoteB1->acOff();
            this->remoteB2->acOff();
            this->remoteB3->acOff();
            this->remoteB4->acOff();
        }
    }
};
//============================================= COMMANDS ====================================
void JMCommand::cmdBoxToLg(uint8_t cmdMode)
{
    if (this->homeCinemaCurrent == this->playerBox) // turn of lg
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_ON)
        {
            this->displayLG->acOff();
            if (this->bedroomCurrent != this->playerBox)
            {
                this->playerBox->acOff();
            }
            else
            {
                this->setRemote(JMGlobal::DEV_PLAYER_BOX, JMGlobal::DEV_DISPLAY_AKARI);
            }

            this->hdmiAmpLG->acOff();
            this->speaker->acOff();
            if (this->bedroomCurrent == NULL)
                this->hdmiMatrix->acOff();
            this->homeCinemaCurrent = NULL;
        }
    }
    else
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_OFF)
        {
            this->displayLG->run();
            this->hdmiMatrix->run();
            this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_BOX_TO_LG));
            this->setRemote(JMGlobal::DEV_PLAYER_BOX, JMGlobal::DEV_DISPLAY_LG);
            this->hdmiAmpLG->run();
            this->playerBox->run();
            if (!this->speakerTurnedOff)
                this->speaker->run();
            this->homeCinemaCurrent = this->playerBox;
        }
    }
};
void JMCommand::cmdIndiToLg(uint8_t cmdMode)
{
    if (this->homeCinemaCurrent == this->playerIndi) // turn of lg
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_ON)
        {
            this->displayLG->acOff();
            if (this->bedroomCurrent != this->playerIndi)
            {
                this->playerIndi->acOff();
                this->hdmiAmpIndi->acOff();
            }
            else
            {
                this->setRemote(JMGlobal::DEV_PLAYER_INDI, JMGlobal::DEV_DISPLAY_AKARI);
            }

            this->hdmiAmpLG->acOff();
            this->speaker->acOff();
            if (this->bedroomCurrent == NULL)
                this->hdmiMatrix->acOff();
            this->homeCinemaCurrent = NULL;
        }
    }
    else
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_OFF)
        {
            this->displayLG->run();
            this->hdmiMatrix->run();
            this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_INDI_TO_LG));
            this->setRemote(JMGlobal::DEV_PLAYER_INDI, JMGlobal::DEV_DISPLAY_LG);
            this->hdmiAmpLG->run();
            this->hdmiAmpIndi->run();
            this->playerIndi->run();
            if (!this->speakerTurnedOff)
                this->speaker->run();
            this->homeCinemaCurrent = this->playerIndi;
        }
    }
};
void JMCommand::cmdPsToLg(uint8_t cmdMode)
{
    if (this->homeCinemaCurrent == this->playerPS) // turn of lg
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_ON)
        {
            this->displayLG->acOff();
            if (this->bedroomCurrent != this->playerPS)
            {
                this->playerPS->acOff();
                this->hdmiAmpPS->acOff();
            }

            this->hdmiAmpLG->acOff();
            this->speaker->acOff();
            if (this->bedroomCurrent == NULL)
                this->hdmiMatrix->acOff();
            this->homeCinemaCurrent = NULL;
        }
    }
    else
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_OFF)
        {
            this->displayLG->run();
            this->hdmiMatrix->run();
            this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_PS_TO_LG));
            this->playerPS->run();
            this->hdmiAmpPS->run();
            this->hdmiAmpLG->run();

            if (!this->speakerTurnedOff)
                this->speaker->shutDown();
            this->homeCinemaCurrent = this->playerPS;
        }
    }
};
void JMCommand::cmdElseToLg(uint8_t cmdMode)
{
    if (this->homeCinemaCurrent == this->playerElse) // turn of lg
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_ON)
        {
            this->displayLG->acOff();
            if (this->bedroomCurrent != this->playerBox)
            {
                this->playerElse->acOff();
            }
            this->hdmiAmpLG->acOff();
            this->speaker->acOff();
            if (this->bedroomCurrent == NULL)
                this->hdmiMatrix->acOff();
            this->homeCinemaCurrent = NULL;
        }
    }
    else
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_OFF)
        {
            this->displayLG->run();
            this->hdmiMatrix->run();
            this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_ELSE_TO_LG));
            this->hdmiAmpLG->run();
            this->playerElse->run();
            if (!this->speakerTurnedOff)
                this->speaker->run();
            this->homeCinemaCurrent = this->playerElse;
        }
    }
};

void JMCommand::cmdBoxToAkari(uint8_t cmdMode)
{
    if (this->bedroomCurrent == this->playerBox) // turn of akari
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_ON)
        {
            this->displayAkari->acOff();
            if (this->homeCinemaCurrent != this->playerBox)
            {
                this->playerBox->acOff();
            }
            else
            {
                this->setRemote(JMGlobal::DEV_PLAYER_BOX, JMGlobal::DEV_DISPLAY_LG);
            }

            this->hdmiAmpAkari->acOff();
            if (this->homeCinemaCurrent == NULL)
                this->hdmiMatrix->acOff();
            this->bedroomCurrent = NULL;
        }
    }
    else
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_OFF)
        {
            this->displayAkari->run();
            this->hdmiMatrix->run();
            this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_BOX_TO_AKARI));
            this->setRemote(JMGlobal::DEV_PLAYER_BOX, JMGlobal::DEV_DISPLAY_AKARI);
            this->hdmiAmpAkari->run();
            this->playerBox->run();
            this->bedroomCurrent = this->playerBox;
        }
    }
};
void JMCommand::cmdIndiToAkari(uint8_t cmdMode)
{
    if (this->bedroomCurrent == this->playerIndi) // turn of akari
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_ON)
        {
            this->displayAkari->acOff();
            if (this->homeCinemaCurrent != this->playerIndi)
            {
                this->playerIndi->acOff();
                this->hdmiAmpIndi->acOff();
            }
            else
            {
                this->setRemote(JMGlobal::DEV_PLAYER_INDI, JMGlobal::DEV_DISPLAY_LG);
            }

            this->hdmiAmpAkari->acOff();
            if (this->homeCinemaCurrent == NULL)
                this->hdmiMatrix->acOff();
            this->bedroomCurrent = NULL;
        }
    }
    else
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_OFF)
        {
            this->displayAkari->run();
            this->hdmiMatrix->run();
            this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_INDI_TO_AKARI));
            this->setRemote(JMGlobal::DEV_PLAYER_INDI, JMGlobal::DEV_DISPLAY_AKARI);
            this->hdmiAmpAkari->run();
            this->hdmiAmpIndi->run();
            this->playerIndi->run();
            this->bedroomCurrent = this->playerIndi;
        }
    }
};
void JMCommand::cmdPsToAkari(uint8_t cmdMode)
{
    if (this->bedroomCurrent == this->playerPS) // turn of akari
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_ON)
        {
            this->displayAkari->acOff();
            if (this->homeCinemaCurrent != this->playerPS)
            {
                this->playerPS->acOff();
                this->hdmiAmpPS->acOff();
            }

            this->hdmiAmpAkari->acOff();
            if (this->homeCinemaCurrent == NULL)
                this->hdmiMatrix->acOff();
            this->bedroomCurrent = NULL;
        }
    }
    else
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_OFF)
        {
            this->displayAkari->run();
            this->hdmiMatrix->run();
            this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_PS_TO_AKARI));
            this->playerPS->run();
            this->hdmiAmpPS->run();
            this->hdmiAmpAkari->run();

            this->bedroomCurrent = this->playerPS;
        }
    }
};
void JMCommand::cmdElseToAkari(uint8_t cmdMode)
{
    if (this->bedroomCurrent == this->playerElse) // turn off akari
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_ON)
        {
            this->displayAkari->acOff();
            if (this->homeCinemaCurrent != this->playerElse)
            {
                this->playerElse->acOff();
            }

            this->hdmiAmpAkari->acOff();
            if (this->homeCinemaCurrent == NULL)
                this->hdmiMatrix->acOff();
            this->bedroomCurrent = NULL;
        }
    }
    else
    {
        if (cmdMode != JMGlobal::CMD_MODE_FORCE_OFF)
        {
            this->displayAkari->run();
            this->hdmiMatrix->run();
            this->ir->sendIr(this->getMatrixCode(JMGlobal::DO_CMD_ELSE_TO_AKARI));
            this->hdmiAmpAkari->run();
            this->playerElse->run();
            this->bedroomCurrent = this->playerElse;
        }
    }
};
void JMCommand::cmdTogglePowerSpeaker()
{
    if (this->speaker->getMode() == JMDevice::DEV_MODE_RUNNING || this->speaker->getMode() == JMDevice::DEV_MODE_STANDBY)
    {
        this->speaker->acOff();
        this->speakerTurnedOff = true;
    }
    else
    {
        this->speaker->run();
        this->speakerTurnedOff = false;
    }
};
void JMCommand::cmdToggleSleepLg()
{
    if (this->homeCinemaCurrent == NULL)
    {
        if (this->bedroomCurrent != NULL)
        {
            // copy from bedroom
            if (this->bedroomCurrent == this->playerBox)
                this->cmdBoxToLg(JMGlobal::CMD_MODE_FORCE_ON);
            else if (this->bedroomCurrent == this->playerIndi)
                this->cmdIndiToLg(JMGlobal::CMD_MODE_FORCE_ON);
            else if (this->bedroomCurrent == this->playerPS)
                this->cmdPsToLg(JMGlobal::CMD_MODE_FORCE_ON);
            else
                this->cmdElseToLg(JMGlobal::CMD_MODE_FORCE_ON);
        }
        else
        {
            this->cmdBoxToLg(JMGlobal::CMD_MODE_FORCE_ON);
        }
    }
    else
    {
        if (this->displayLG->getMode() == JMDevice::DEV_MODE_RUNNING)
            this->displayLG->shutDown();
        else
            this->displayLG->run();
        if (this->speaker->getMode() == JMDevice::DEV_MODE_RUNNING || this->speaker->getMode() == JMDevice::DEV_MODE_STANDBY)
            this->speaker->acOff();
        else if (!this->speakerTurnedOff)
            this->speaker->run();
    }
};
void JMCommand::cmdToggleSleepAkari()
{
    if (this->bedroomCurrent == NULL)
    {
        if (this->homeCinemaCurrent != NULL)
        {
            // copy from bedroom
            if (this->homeCinemaCurrent == this->playerBox)
                this->cmdBoxToAkari(JMGlobal::CMD_MODE_FORCE_ON);
            else if (this->homeCinemaCurrent == this->playerIndi)
                this->cmdIndiToAkari(JMGlobal::CMD_MODE_FORCE_ON);
            else if (this->homeCinemaCurrent == this->playerPS)
                this->cmdPsToAkari(JMGlobal::CMD_MODE_FORCE_ON);
            else
                this->cmdElseToAkari(JMGlobal::CMD_MODE_FORCE_ON);
        }
        else
        {
            this->cmdBoxToAkari(JMGlobal::CMD_MODE_FORCE_ON);
        }
    }
    else
    {
        if (this->displayAkari->getMode() == JMDevice::DEV_MODE_RUNNING)
            this->displayAkari->shutDown();
        else
            this->displayAkari->run();
    }
};
void JMCommand::cmdCalibratePowerDisplayLG()
{
    this->displayLG->calibrate();
};
void JMCommand::cmdCalibratePowerDisplayAkari()
{
    this->displayAkari->calibrate();
};
void JMCommand::cmdCalibratePowerPlayerLG()
{
    if (this->homeCinemaCurrent == this->playerBox)
    {
        boolean isOn = false;
        if (this->playerBox->getMode() == JMDevice::DEV_MODE_RUNNING)
            isOn = true;
        if (JMDevice::getIrPower(this->playerBox->getId(), isOn) != 0x0)
        {
            this->playerBox->acOn();
            this->ir->sendIr(JMDevice::getIrPower(this->playerBox->getId(), isOn));
        }
    }
    else if (this->homeCinemaCurrent == this->playerIndi)
    {
        boolean isOn = false;
        if (this->playerIndi->getMode() == JMDevice::DEV_MODE_RUNNING)
            isOn = true;
        if (JMDevice::getIrPower(this->playerIndi->getId(), isOn) != 0x0)
        {
            this->playerIndi->acOn();
            this->ir->sendIr(JMDevice::getIrPower(this->playerIndi->getId(), isOn));
        }
    }
    else if (this->homeCinemaCurrent == this->playerPS)
    {
        boolean isOn = false;
        if (this->playerPS->getMode() == JMDevice::DEV_MODE_RUNNING)
            isOn = true;
        if (JMDevice::getIrPower(this->playerPS->getId(), isOn) != 0x0)
        {
            this->playerPS->acOn();
            this->ir->sendIr(JMDevice::getIrPower(this->playerPS->getId(), isOn));
        }
    }
    else if (this->homeCinemaCurrent == this->playerElse)
    {
        boolean isOn = false;
        if (this->playerElse->getMode() == JMDevice::DEV_MODE_RUNNING)
            isOn = true;
        if (JMDevice::getIrPower(this->playerElse->getId(), isOn) != 0x0)
        {
            this->playerElse->acOn();
            this->ir->sendIr(JMDevice::getIrPower(this->playerElse->getId(), isOn));
        }
    }
};
void JMCommand::cmdCalibratePowerPlayerAkari()
{
    if (this->bedroomCurrent == this->playerBox)
    {
        boolean isOn = false;
        if (this->playerBox->getMode() == JMDevice::DEV_MODE_RUNNING)
            isOn = true;
        if (JMDevice::getIrPower(this->playerBox->getId(), isOn) != 0x0)
        {
            this->playerBox->acOn();
            this->ir->sendIr(JMDevice::getIrPower(this->playerBox->getId(), isOn));
        }
    }
    else if (this->bedroomCurrent == this->playerIndi)
    {
        boolean isOn = false;
        if (this->playerIndi->getMode() == JMDevice::DEV_MODE_RUNNING)
            isOn = true;
        if (JMDevice::getIrPower(this->playerIndi->getId(), isOn) != 0x0)
        {
            this->playerIndi->acOn();
            this->ir->sendIr(JMDevice::getIrPower(this->playerIndi->getId(), isOn));
        }
    }
    else if (this->bedroomCurrent == this->playerPS)
    {
        boolean isOn = false;
        if (this->playerPS->getMode() == JMDevice::DEV_MODE_RUNNING)
            isOn = true;
        if (JMDevice::getIrPower(this->playerPS->getId(), isOn) != 0x0)
        {
            this->playerPS->acOn();
            this->ir->sendIr(JMDevice::getIrPower(this->playerPS->getId(), isOn));
        }
    }
    else if (this->bedroomCurrent == this->playerElse)
    {
        boolean isOn = false;
        if (this->playerElse->getMode() == JMDevice::DEV_MODE_RUNNING)
            isOn = true;
        if (JMDevice::getIrPower(this->playerElse->getId(), isOn) != 0x0)
        {
            this->playerElse->acOn();
            this->ir->sendIr(JMDevice::getIrPower(this->playerElse->getId(), isOn));
        }
    }
};
void JMCommand::cmdCalibratePowerSpeaker()
{
    this->speaker->calibrate();
};
void JMCommand::cmdCalibratePowerMatrix()
{
    this->hdmiMatrix->calibrate();
};
void JMCommand::cmdTurnLgOff()
{
    if (this->homeCinemaCurrent == NULL)
        return;
    if (this->bedroomCurrent == NULL) // shutdown all
    {
        this->shutDownAll();
    }
    else
    {
        this->displayLG->acOff();
        this->speaker->acOff();
        this->hdmiAmpLG->acOff();
        this->homeCinemaCurrent = NULL;
    }
};
void JMCommand::cmdTurnAkariOff()
{
    if (this->bedroomCurrent == NULL)
        return;
    if (this->homeCinemaCurrent == NULL) // shutdown all
    {
        this->shutDownAll();
    }
    else
    {
        this->displayAkari->acOff();
        this->hdmiAmpAkari->acOff();
        this->bedroomCurrent = NULL;
    }
};

//============================================= CONFIG ======================================
void JMCommand::initSetup()
{
    // = {new JMRelay8(0x21), new JMRelay8(0x22), new JMRelay8(0x23)}

    //*this->relay8 = {new JMRelay8(0x21), new JMRelay8(0x22), new JMRelay8(0x23)};

    this->relay8[2] = new JMRelay8(0x20);
    this->relay8[1] = new JMRelay8(0x22);
    this->relay8[0] = new JMRelay8(0x23);

    // this->relay8[0] = new JMRelay8(0x22);

    // init
    this->setRelay8();

    this->setDisplayLG();
    this->setDisplayAkari();

    this->setHdmiAmpLG();
    this->setHdmiAmpAkari();
    this->setHdmiAmpPS();
    this->setHdmiAmpIndi();

    this->setHdmiMatrix();

    // BATAS MEMORI
    this->setPlayerBox();
    this->setPlayerElse();
    this->setPlayerIndi();
    this->setPlayerPS();

    this->setServerEvercossBat();
    this->setServerEvercossCharger();
    this->setServerNAS();
    this->setHddDock();
    this->setSpeaker();

    this->setRemoteA1();
    this->setRemoteA2();
    this->setRemoteA3();
    this->setRemoteA4();
    this->setRemoteB1();
    this->setRemoteB2();
    this->setRemoteB3();
    this->setRemoteB4();

    // for fisrtsrun, run the server
    this->serverEvercossBat->run();
    this->serverEvercossCharger->run();

    /*==============================FOR TEST===================================
    this->remoteA1->acOn();
    this->remoteA2->acOn();
    this->remoteA3->acOn();
    this->remoteA4->acOn();
    this->remoteB1->acOn();
    this->remoteB2->acOn();
    this->remoteB3->acOn();
    this->remoteB4->acOn();

    this->displayLG->acOn();
    this->displayAkari->acOn();

    this->hdmiAmpLG->acOn();
    this->hdmiAmpAkari->acOn();
    this->hdmiAmpPS->acOn();
    this->hdmiAmpIndi->acOn();

    this->hdmiMatrix->acOn();

    this->playerBox->acOn();
    this->playerIndi->acOn();
    this->playerPS->acOn();
    this->playerElse->acOn();

    this->serverEvercossBat->acOn();
    this->serverEvercossCharger->acOn();
    this->serverNAS->acOn();
    this->hddDock->acOn();
    this->speaker->acOn();
    ==============================END FOR TEST===================================*/
};

void JMCommand::setRelay8()
{
    for (uint8_t i = 0; i < 3; i++)
    {
        this->relay8[i]->setup();
    }
};

void JMCommand::setDisplayLG()
{
    this->displayLG = new JMDevice(JMGlobal::DEV_DISPLAY_LG,
                                   *this,
                                   *this->relay8[0]->getRelay(4),
                                   *this->ir,
                                   8000,
                                   2000,
                                   5000,
                                   8000);
    // this->devs->add(this->displayLG);
};
void JMCommand::setDisplayAkari()
{
    this->displayAkari = new JMDevice(JMGlobal::DEV_DISPLAY_AKARI,
                                      *this,
                                      *this->relay8[0]->getRelay(1),
                                      *this->ir,
                                      8000,
                                      2000,
                                      5000,
                                      8000);
    // this->devs->add(this->displayAkari);
};

void JMCommand::setHdmiAmpLG()
{
    this->hdmiAmpLG = new JMDevice(JMGlobal::DEV_HDMI_AMP_LG,
                                   *this,
                                   *this->relay8[0]->getRelay(2),
                                   *this->ir,
                                   5000,
                                   2000,
                                   0,
                                   0);
    // this->devs->add(this->hdmiAmpLG);
};
void JMCommand::setHdmiAmpAkari()
{
    this->hdmiAmpAkari = new JMDevice(JMGlobal::DEV_HDMI_AMP_AKARI,
                                      *this,
                                      *this->relay8[0]->getRelay(3),
                                      *this->ir,
                                      5000,
                                      2000,
                                      0,
                                      0);
    // this->devs->add(this->hdmiAmpAkari);
};
void JMCommand::setHdmiAmpPS()
{
    this->hdmiAmpPS = new JMDevice(JMGlobal::DEV_HDMI_AMP_PS,
                                   *this,
                                   *this->relay8[0]->getRelay(0),
                                   *this->ir,
                                   5000,
                                   2000,
                                   0,
                                   0);
    // this->devs->add(this->hdmiAmpPS);
};
void JMCommand::setHdmiAmpIndi()
{
    this->hdmiAmpIndi = new JMDevice(JMGlobal::DEV_HDMI_AMP_INDI,
                                     *this,
                                     *this->relay8[1]->getRelay(5),
                                     *this->ir,
                                     5000,
                                     2000,
                                     0,
                                     0);
    // this->devs->add(this->hdmiAmpPS);
};

void JMCommand::setHdmiMatrix()
{
    this->hdmiMatrix = new JMDevice(JMGlobal::DEV_HDMI_MATRIX,
                                    *this,
                                    *this->relay8[0]->getRelay(5),
                                    *this->ir,
                                    8000,
                                    2000,
                                    5000,
                                    8000);
    // this->devs->add(this->hdmiMatrix);
};

void JMCommand::setPlayerBox()
{
    this->playerBox = new JMDevice(JMGlobal::DEV_PLAYER_BOX,
                                   *this,
                                   *this->relay8[0]->getRelay(6),
                                   *this->ir,
                                   8000,
                                   2000,
                                   5000,
                                   10000);
    // this->devs->add(this->playerBox);
};
void JMCommand::setPlayerIndi()
{
    this->playerIndi = new JMDevice(JMGlobal::DEV_PLAYER_INDI,
                                    *this,
                                    *this->relay8[0]->getRelay(7),
                                    *this->ir,
                                    8000,
                                    2000,
                                    5000,
                                    10000);
    // this->devs->add(this->playerIndi);
};
void JMCommand::setPlayerPS()
{
    this->playerPS = new JMDevice(JMGlobal::DEV_PLAYER_PS,
                                  *this,
                                  *this->relay8[1]->getRelay(7),
                                  *this->ir,
                                  8000,
                                  2000,
                                  5000,
                                  20000);
    // this->devs->add(this->playerPS);
};

void JMCommand::setPlayerElse()
{
    this->playerElse = new JMDevice(JMGlobal::DEV_PLAYER_ELSE,
                                    *this,
                                    *this->relay8[1]->getRelay(6),
                                    *this->ir,
                                    8000,
                                    2000,
                                    5000,
                                    8000);
    // this->devs->add(this->playerPS);
};

void JMCommand::setServerEvercossBat()
{
    this->serverEvercossBat = new JMDevice(JMGlobal::DEV_SERVER_EVERCOSS_BAT,
                                           *this,
                                           *this->relay8[1]->getRelay(1),
                                           *this->ir,
                                           8000,
                                           2000,
                                           5000,
                                           8000);
    // this->devs->add(this->serverEvercossBat);
};
void JMCommand::setServerEvercossCharger()
{
    this->serverEvercossCharger = new JMDevice(JMGlobal::DEV_SERVER_EVERCOSS_CHARGER,
                                               *this,
                                               *this->relay8[1]->getRelay(2),
                                               *this->ir,
                                               5000,
                                               8000,
                                               5000,
                                               5000);
    // this->devs->add(this->serverEvercossCharger);
};
void JMCommand::setServerNAS()
{
    this->serverNAS = new JMDevice(JMGlobal::DEV_SERVER_NAS,
                                   *this,
                                   *this->relay8[1]->getRelay(3),
                                   *this->ir,
                                   8000,
                                   2000,
                                   5000,
                                   8000);
    // this->devs->add(this->serverNAS);
};
void JMCommand::setHddDock()
{
    this->hddDock = new JMDevice(JMGlobal::DEV_HDD_DOCK,
                                 *this,
                                 *this->relay8[1]->getRelay(4),
                                 *this->ir,
                                 8000,
                                 2000,
                                 5000,
                                 8000);
    // this->devs->add(this->hddDock);
};
void JMCommand::setSpeaker()
{
    this->speaker = new JMDevice(JMGlobal::DEV_SPEAKER,
                                 *this,
                                 *this->relay8[1]->getRelay(0),
                                 *this->ir,
                                 8000,
                                 2000,
                                 5000,
                                 8000);
    // this->devs->add(this->speaker);
};
void JMCommand::setRemoteA1()
{
    this->remoteA1 = new JMDevice(JMGlobal::DEV_REMOTE_A1,
                                  *this,
                                  *this->relay8[2]->getRelay(0),
                                  *this->ir,
                                  0,
                                  0,
                                  0,
                                  0);
    // this->devs->add(this->remoteA1);
};
void JMCommand::setRemoteA2()
{
    this->remoteA2 = new JMDevice(JMGlobal::DEV_REMOTE_A2,
                                  *this,
                                  *this->relay8[2]->getRelay(1),
                                  *this->ir,
                                  0,
                                  0,
                                  0,
                                  0);
    // this->devs->add(this->remoteA2);
};
void JMCommand::setRemoteA3()
{
    this->remoteA3 = new JMDevice(JMGlobal::DEV_REMOTE_A3,
                                  *this,
                                  *this->relay8[2]->getRelay(2),
                                  *this->ir,
                                  0,
                                  0,
                                  0,
                                  0);
    // this->devs->add(this->remoteA3);
};
void JMCommand::setRemoteA4()
{
    this->remoteA4 = new JMDevice(JMGlobal::DEV_REMOTE_A4,
                                  *this,
                                  *this->relay8[2]->getRelay(3),
                                  *this->ir,
                                  0,
                                  0,
                                  0,
                                  0);
    // this->devs->add(this->remoteA4);
};
void JMCommand::setRemoteB1()
{
    this->remoteB1 = new JMDevice(JMGlobal::DEV_REMOTE_B1,
                                  *this,
                                  *this->relay8[2]->getRelay(4),
                                  *this->ir,
                                  0,
                                  0,
                                  0,
                                  0);
    // this->devs->add(this->remoteB1);
};
void JMCommand::setRemoteB2()
{
    this->remoteB2 = new JMDevice(JMGlobal::DEV_REMOTE_B2,
                                  *this,
                                  *this->relay8[2]->getRelay(5),
                                  *this->ir,
                                  0,
                                  0,
                                  0,
                                  0);
    // this->devs->add(this->remoteB2);
};
void JMCommand::setRemoteB3()
{
    this->remoteB3 = new JMDevice(JMGlobal::DEV_REMOTE_B3,
                                  *this,
                                  *this->relay8[2]->getRelay(6),
                                  *this->ir,
                                  0,
                                  0,
                                  0,
                                  0);
    // this->devs->add(this->remoteB3);
};
void JMCommand::setRemoteB4()
{
    this->remoteB4 = new JMDevice(JMGlobal::DEV_REMOTE_B4,
                                  *this,
                                  *this->relay8[2]->getRelay(7),
                                  *this->ir,
                                  0,
                                  0,
                                  0,
                                  0);
    // this->devs->add(this->remoteB4);
};
uint8_t JMCommand::getTranslatedInnetCommand(uint8_t innetCmd)
{
    if (innetCmd == JMGlobal::DO_INET_ON_CMD_BOX_TO_LG)
    {
        return JMGlobal::DO_CMD_BOX_TO_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_INDI_TO_LG)
    {
        return JMGlobal::DO_CMD_INDI_TO_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_PS_TO_LG)
    {
        return JMGlobal::DO_CMD_PS_TO_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_ELSE_TO_LG)
    {
        return JMGlobal::DO_CMD_ELSE_TO_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_BOX_TO_AKARI)
    {
        return JMGlobal::DO_CMD_BOX_TO_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_INDI_TO_AKARI)
    {
        return JMGlobal::DO_CMD_INDI_TO_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_PS_TO_AKARI)
    {
        return JMGlobal::DO_CMD_PS_TO_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_ELSE_TO_AKARI)
    {
        return JMGlobal::DO_CMD_ELSE_TO_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_SPEAKER)
    {
        return JMGlobal::DO_CMD_TOGGLE_POWER_SPEAKER;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_SLEEP_LG)
    {
        return JMGlobal::DO_CMD_TOGGLE_SLEEP_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_SLEEP_AKARI)
    {
        return JMGlobal::DO_CMD_TOGGLE_SLEEP_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_BOX_TO_LG)
    {
        return JMGlobal::DO_CMD_BOX_TO_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_INDI_TO_LG)
    {
        return JMGlobal::DO_CMD_INDI_TO_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_PS_TO_LG)
    {
        return JMGlobal::DO_CMD_PS_TO_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_ELSE_TO_LG)
    {
        return JMGlobal::DO_CMD_ELSE_TO_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_BOX_TO_AKARI)
    {
        return JMGlobal::DO_CMD_BOX_TO_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_INDI_TO_AKARI)
    {
        return JMGlobal::DO_CMD_INDI_TO_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_PS_TO_AKARI)
    {
        return JMGlobal::DO_CMD_PS_TO_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_ELSE_TO_AKARI)
    {
        return JMGlobal::DO_CMD_ELSE_TO_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_SPEAKER)
    {
        return JMGlobal::DO_CMD_TOGGLE_POWER_SPEAKER;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_WAKE_LG)
    {
        return JMGlobal::DO_CMD_TOGGLE_SLEEP_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_WAKE_AKARI)
    {
        return JMGlobal::DO_CMD_TOGGLE_SLEEP_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_CALIBRATE_POWER_DISPLAY_LG)
    {
        return JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_CALIBRATE_POWER_DISPLAY_AKARI)
    {
        return JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_CALIBRATE_POWER_PLAYER_LG)
    {
        return JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_LG;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_CALIBRATE_POWER_PLAYER_AKARI)
    {
        return JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_AKARI;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_CALIBRATE_POWER_SPEAKER)
    {
        return JMGlobal::DO_CMD_CALIBRATE_POWER_SPEAKER;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_CALIBRATE_POWER_MATRIX)
    {
        return JMGlobal::DO_CMD_CALIBRATE_POWER_MATRIX;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_TURN_LG_OFF)
    {
        return JMGlobal::DO_CMD_TURN_LG_OFF;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_TURN_AKARI_OFF)
    {
        return JMGlobal::DO_CMD_TURN_AKARI_OFF;
    }
    else
    {
        return JMGlobal::DO_CMD_BOX_TO_LG; // ERROR DEFAULT
    }
};
bool JMCommand::isForceOnInnetCommand(uint8_t innetCmd)
{
    if (innetCmd == JMGlobal::DO_INET_ON_CMD_BOX_TO_LG)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_INDI_TO_LG)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_PS_TO_LG)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_ELSE_TO_LG)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_BOX_TO_AKARI)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_INDI_TO_AKARI)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_PS_TO_AKARI)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_ELSE_TO_AKARI)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_ON_CMD_SPEAKER)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_SLEEP_LG)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_SLEEP_AKARI)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_BOX_TO_LG)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_INDI_TO_LG)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_PS_TO_LG)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_ELSE_TO_LG)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_BOX_TO_AKARI)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_INDI_TO_AKARI)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_PS_TO_AKARI)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_ELSE_TO_AKARI)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_OFF_CMD_SPEAKER)
    {
        return false;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_WAKE_LG)
    {
        return true;
    }
    else if (innetCmd == JMGlobal::DO_INET_CMD_WAKE_AKARI)
    {
        return true;
    }
    else
    {
        return true; // ERROR DEFAULT
    }
};