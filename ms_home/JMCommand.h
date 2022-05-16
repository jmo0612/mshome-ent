#ifndef JMCommand_h
#define JMCommand_h
#include "Arduino.h"
//#include "JMRelay8.h"
//#include "JMIr.h"
//#include "JMDevice.h"

class JMRelay8;
class JMDevice;
class JMIr;

class JMCommand
{
private:
    JMDevice *homeCinemaCurrent = NULL;
    JMDevice *bedroomCurrent = NULL;

    JMRelay8 *relay8[1];
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
    static const int CMD_BOX_TO_LG = 0;
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
    static const int CMD_CALIBRATE_POWER_MATRIX = 12;

    JMCommand();
    void setup();
    void doCommand(int cmd);
};
#endif
