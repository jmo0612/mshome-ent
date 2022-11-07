#ifndef JMGlobal_h
#define JMGlobal_h

class JMGlobal
{
private:
public:
    static const unsigned long baudrate = 115200;
    // static const int maxStack = 3;
    // static const unsigned int wireMaxChar = 20;

    static const uint8_t PACKET_MSG_DEVICES_DATA = 0;
    static const uint8_t PACKET_MSG_DO_CMD = 1;
    static const uint8_t PACKET_MSG_SPECIAL = 2;
    static const uint8_t PACKET_MSG_QUEUED_DEVICES_DATA = 3;
    static const uint8_t PACKET_MSG_INIT_DEVICES = 4;

    static const uint8_t CMD_STATUS_IDLE = 0;
    static const uint8_t CMD_STATUS_PROCESSING = 1;

    static const uint8_t CMD_MODE_TOGGLE = 0;
    static const uint8_t CMD_MODE_FORCE_ON = 1;
    static const uint8_t CMD_MODE_FORCE_OFF = 2;

    static const uint8_t DO_CMD_BOX_TO_LG = 1;
    static const uint8_t DO_CMD_INDI_TO_LG = 2;
    static const uint8_t DO_CMD_PS_TO_LG = 3;
    static const uint8_t DO_CMD_ELSE_TO_LG = 4;
    static const uint8_t DO_CMD_BOX_TO_AKARI = 5;
    static const uint8_t DO_CMD_INDI_TO_AKARI = 6;
    static const uint8_t DO_CMD_PS_TO_AKARI = 7;
    static const uint8_t DO_CMD_ELSE_TO_AKARI = 8;
    static const uint8_t DO_CMD_TOGGLE_POWER_SPEAKER = 9;
    static const uint8_t DO_CMD_CALIBRATE_POWER_LG = 10;
    static const uint8_t DO_CMD_CALIBRATE_POWER_AKARI = 11;
    static const uint8_t DO_CMD_CALIBRATE_POWER_SPEAKER = 12;
    static const uint8_t DO_CMD_CALIBRATE_POWER_MATRIX = 13;

    static const uint8_t DO_INET_ON_CMD_BOX_TO_LG = 1;
    static const uint8_t DO_INET_ON_CMD_INDI_TO_LG = 2;
    static const uint8_t DO_INET_ON_CMD_PS_TO_LG = 3;
    static const uint8_t DO_INET_ON_CMD_ELSE_TO_LG = 4;
    static const uint8_t DO_INET_ON_CMD_BOX_TO_AKARI = 5;
    static const uint8_t DO_INET_ON_CMD_INDI_TO_AKARI = 6;
    static const uint8_t DO_INET_ON_CMD_PS_TO_AKARI = 7;
    static const uint8_t DO_INET_ON_CMD_ELSE_TO_AKARI = 8;

    static const uint8_t DO_INET_OFF_CMD_BOX_TO_LG = 9;
    static const uint8_t DO_INET_OFF_CMD_INDI_TO_LG = 10;
    static const uint8_t DO_INET_OFF_CMD_PS_TO_LG = 11;
    static const uint8_t DO_INET_OFF_CMD_ELSE_TO_LG = 12;
    static const uint8_t DO_INET_OFF_CMD_BOX_TO_AKARI = 13;
    static const uint8_t DO_INET_OFF_CMD_INDI_TO_AKARI = 14;
    static const uint8_t DO_INET_OFF_CMD_PS_TO_AKARI = 15;
    static const uint8_t DO_INET_OFF_CMD_ELSE_TO_AKARI = 16;

    static const uint8_t DEV_DISPLAY_LG = 31; // 0
    static const uint8_t DEV_DISPLAY_AKARI = 30;
    static const uint8_t DEV_HDMI_AMP_LG = 29;
    static const uint8_t DEV_HDMI_AMP_AKARI = 28;
    static const uint8_t DEV_HDMI_AMP_PS = 27;
    static const uint8_t DEV_HDMI_MATRIX = 26;
    static const uint8_t DEV_PLAYER_BOX = 25;
    static const uint8_t DEV_PLAYER_INDI = 24;
    static const uint8_t DEV_PLAYER_PS = 23;
    static const uint8_t DEV_SERVER_EVERCOSS_BAT = 22;
    static const uint8_t DEV_SERVER_EVERCOSS_CHARGER = 21;
    static const uint8_t DEV_SERVER_NAS = 20;
    static const uint8_t DEV_HDD_DOCK = 19;
    static const uint8_t DEV_SPEAKER = 18;

    static const uint8_t DEV_REMOTE_A1 = 7;
    static const uint8_t DEV_REMOTE_A2 = 6;
    static const uint8_t DEV_REMOTE_A3 = 5;
    static const uint8_t DEV_REMOTE_A4 = 4;
    static const uint8_t DEV_REMOTE_B1 = 3;
    static const uint8_t DEV_REMOTE_B2 = 2;
    static const uint8_t DEV_REMOTE_B3 = 1;
    static const uint8_t DEV_REMOTE_B4 = 0; // 23

    static const uint8_t MSG_SPECIAL_VALUE_SHUTDOWNALL = 1;
};

#endif
