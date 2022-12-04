#ifndef JMCommand_h
#define JMCommand_h
#include "Arduino.h"

class JMRelay8;
class JMDevice;
class JMIr;
class JMData;
class JMWifiWire;

class JMCommand
{
private:
    uint8_t cmdStats[20] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // COMMAND STATUS
    JMData *devData;
    JMWifiWire *wifiWire;
    bool initialized = false;
    JMDevice *homeCinemaCurrent = NULL;
    JMDevice *bedroomCurrent = NULL;
    bool speakerTurnedOff = false;

    JMRelay8 *relay8[3];
    JMIr *ir;

    JMDevice *displayLG;
    JMDevice *displayAkari;

    JMDevice *hdmiAmpLG;
    JMDevice *hdmiAmpAkari;
    JMDevice *hdmiAmpPS;
    JMDevice *hdmiAmpIndi;

    JMDevice *hdmiMatrix;

    JMDevice *playerBox;
    JMDevice *playerIndi;
    JMDevice *playerPS;
    JMDevice *playerElse;

    JMDevice *serverEvercossBat;
    JMDevice *serverEvercossCharger;
    JMDevice *serverNAS;
    JMDevice *hddDock;
    JMDevice *speaker;
    JMDevice *remoteA1;
    JMDevice *remoteA2;
    JMDevice *remoteA3;
    JMDevice *remoteA4;
    JMDevice *remoteB1;
    JMDevice *remoteB2;
    JMDevice *remoteB3;
    JMDevice *remoteB4;

    // void updateStats(char *stats);
    // char *extractTaskType(char *msg);
    // char *extractTaskMsg(char *msg, char *taskType);
    // void specialInit();

    uint32_t getMatrixCode(uint8_t cmd);

    // SETUP
    void initSetup();

    void setRelay8();
    void setIr();

    void setDisplayLG();
    void setDisplayAkari();

    void setHdmiAmpLG();
    void setHdmiAmpAkari();
    void setHdmiAmpPS();
    void setHdmiAmpIndi();

    void setHdmiMatrix();

    void setPlayerBox();
    void setPlayerIndi();
    void setPlayerPS();
    void setPlayerElse();

    void setServerEvercossBat();
    void setServerEvercossCharger();
    void setServerNAS();
    void setHddDock();
    void setSpeaker();
    void setRemoteA1();
    void setRemoteA2();
    void setRemoteA3();
    void setRemoteA4();
    void setRemoteB1();
    void setRemoteB2();
    void setRemoteB3();
    void setRemoteB4();

    // COMMAND
    void cmdBoxToLg(uint8_t cmdMode);
    void cmdIndiToLg(uint8_t cmdMode);
    void cmdPsToLg(uint8_t cmdMode);
    void cmdElseToLg(uint8_t cmdMode);

    void cmdBoxToAkari(uint8_t cmdMode);
    void cmdIndiToAkari(uint8_t cmdMode);
    void cmdPsToAkari(uint8_t cmdMode);
    void cmdElseToAkari(uint8_t cmdMode);

    void cmdTogglePowerSpeaker();
    void cmdToggleSleepLg();
    void cmdToggleSleepAkari();

    void cmdCalibratePowerDisplayLG();
    void cmdCalibratePowerDisplayAkari();
    void cmdCalibratePowerPlayerLG();
    void cmdCalibratePowerPlayerAkari();
    void cmdCalibratePowerSpeaker();
    void cmdCalibratePowerMatrix();

    void cmdTurnLgOff();
    void cmdTurnAkariOff();

    void setRemote(uint8_t remote, uint8_t display);
    void shutDownAll();
    bool isForceOnInnetCommand(uint8_t innetCmd);

public:
    JMCommand();
    void setup(JMIr *ir, JMData *devData, JMWifiWire *wifiWire);
    void doCommand(uint8_t cmd, uint8_t cmdMode);
    void doInetCommand(uint8_t cmd, uint8_t cmdMode);
    // void processTask(char *msg);
    // char *getStats();
    void updateStats(JMDevice &dev);
    // bool isLoaded();
    // char *getStatsPacked();

    JMDevice *getDeviceById(uint8_t id);
    void processPackage(const int64_t package);
    uint8_t getCmdStatus(uint8_t cmd);
    void firstRun2(uint64_t package);
    bool isInitialized();
    uint8_t getTranslatedInnetCommand(uint8_t innetCmd);
};
#endif
