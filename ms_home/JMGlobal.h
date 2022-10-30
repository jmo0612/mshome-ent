#ifndef JMGlobal_h
#define JMGlobal_h

class JMGlobal
{
private:
public:
    static const unsigned long baudrate = 115200;
    // static const int maxStack = 3;
    // static const unsigned int wireMaxChar = 20;

    static const int PACKET_MSG_DEVICES_DATA = 0;
    static const int PACKET_MSG_DO_CMD = 1;
    static const int PACKET_MSG_SPECIAL = 2;

    static const int CMD_STATUS_IDLE = 0;
    static const int CMD_STATUS_PROCESSING = 1;

    static const int DO_CMD_BOX_TO_LG = 1;
    static const int DO_CMD_INDI_TO_LG = 2;
    static const int DO_CMD_PS_TO_LG = 3;
    static const int DO_CMD_ELSE_TO_LG = 4;
    static const int DO_CMD_BOX_TO_AKARI = 5;
    static const int DO_CMD_INDI_TO_AKARI = 6;
    static const int DO_CMD_PS_TO_AKARI = 7;
    static const int DO_CMD_ELSE_TO_AKARI = 8;
    // static const int DO_CMD_TOGGLE_POWER_SPEAKER = 9;
    // static const int DO_CMD_CALIBRATE_POWER_LG = 10;
    // static const int DO_CMD_CALIBRATE_POWER_AKARI = 11;
    // static const int DO_CMD_CALIBRATE_POWER_SPEAKER = 12;
    // static const int DO_CMD_CALIBRATE_POWER_MATRIX = 13;

    static const int DEV_DISPLAY_LG = 31; // 0
    static const int DEV_DISPLAY_AKARI = 30;
    static const int DEV_HDMI_AMP_LG = 29;
    static const int DEV_HDMI_AMP_AKARI = 28;
    static const int DEV_HDMI_AMP_PS = 27;
    static const int DEV_HDMI_MATRIX = 26;
    static const int DEV_PLAYER_BOX = 25;
    static const int DEV_PLAYER_INDI = 24;
    static const int DEV_PLAYER_PS = 23;
    static const int DEV_SERVER_EVERCOSS_BAT = 22;
    static const int DEV_SERVER_EVERCOSS_CHARGER = 21;
    static const int DEV_SERVER_NAS = 20;
    static const int DEV_HDD_DOCK = 19;
    static const int DEV_SPEAKER = 18;

    static const int DEV_REMOTE_A1 = 7;
    static const int DEV_REMOTE_A2 = 6;
    static const int DEV_REMOTE_A3 = 5;
    static const int DEV_REMOTE_A4 = 4;
    static const int DEV_REMOTE_B1 = 3;
    static const int DEV_REMOTE_B2 = 2;
    static const int DEV_REMOTE_B3 = 1;
    static const int DEV_REMOTE_B4 = 0; // 23
};

#endif
