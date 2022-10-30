#ifndef JMCommand_h
#define JMCommand_h
#include "Arduino.h"
#include "List.hpp"
//#include "JMRelay8.h"
//#include "JMIr.h"
//#include "JMDevice.h"

class JMRelay8;
class JMDevice;
class JMIr;
class JMData;

class JMCommand
{
private:
    int cmdStats[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0}; // COMMAND STATUS
    JMData *devData;
    // bool loaded = false;
    //  char *stats = "00000000000000";
    List<JMDevice *> *devs;
    JMDevice *homeCinemaCurrent = NULL;
    JMDevice *bedroomCurrent = NULL;

    JMRelay8 *relay8[3];
    JMIr *ir;

    JMDevice *displayLG;
    JMDevice *displayAkari;

    JMDevice *hdmiAmpLG;
    JMDevice *hdmiAmpAkari;
    JMDevice *hdmiAmpPS;

    JMDevice *hdmiMatrix;

    JMDevice *playerBox;
    JMDevice *playerIndi;
    JMDevice *playerPS;

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

    uint32_t getMatrixCode(int cmd);

    // SETUP
    void initSetup();

    void setRelay8();
    void setIr();

    void setDisplayLG();
    void setDisplayAkari();

    void setHdmiAmpLG();
    void setHdmiAmpAkari();
    void setHdmiAmpPS();

    void setHdmiMatrix();

    void setPlayerBox();
    void setPlayerIndi();
    void setPlayerPS();

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
    void cmdBoxToLg();
    void cmdIndiToLg();
    void cmdPsToLg();
    void cmdElseToLg();

    void cmdBoxToAkari();
    void cmdIndiToAkari();
    void cmdPsToAkari();
    void cmdElseToAkari();

    void cmdTogglePowerSpeaker();

    void cmdCalibratePowerLg();
    void cmdCalibratePowerAkari();
    void cmdCalibratePowerSpeaker();
    void cmdCalibratePowerMatrix();

public:
    /*static const int CMD_BOX_TO_LG = 0;
    static const int CMD_INDI_TO_LG = 1;
    static const int CMD_PS_TO_LG = 2;
    static const int CMD_ELSE_TO_LG = 3;

    static const int CMD_BOX_TO_AKARI = 4;
    static const int CMD_INDI_TO_AKARI = 5;
    static const int CMD_PS_TO_AKARI = 6;
    static const int CMD_ELSE_TO_AKARI = 7;

    static const int CMD_TOGGLE_POWER_SPEAKER = 8;

    static const int CMD_CALIBRATE_POWER_LG = 9;
    static const int CMD_CALIBRATE_POWER_AKARI = 10;
    static const int CMD_CALIBRATE_POWER_SPEAKER = 11;
    static const int CMD_CALIBRATE_POWER_MATRIX = 12;*/

    JMCommand();
    void setup(JMIr *ir, JMData *devData);
    void doCommand(int cmd);
    void doInetCommand(char *cmd);
    // void processTask(char *msg);
    // char *getStats();
    void updateStats(JMDevice &dev);
    // bool isLoaded();
    // char *getStatsPacked();
};
#endif
