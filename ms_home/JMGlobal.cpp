#include "JMGlobal.h"

unsigned long JMGlobal::baudrate()
{
    return 115200;
};

// uint8_t JMGlobal::getVar(const char *var)
// {
//     if(var==""){}
//     return 0;
// };
/*
uint8_t JMGlobal::PACKET_MSG_DEVICES_DATA()
{
    return 0;
};
uint8_t JMGlobal::PACKET_MSG_DO_CMD()
{
    return 1;
}; // = 1;
uint8_t JMGlobal::PACKET_MSG_SPECIAL()
{
    return 2;
}; // = 2;
uint8_t JMGlobal::PACKET_MSG_QUEUED_DEVICES_DATA()
{
    return 3;
}; // = 3;
uint8_t JMGlobal::PACKET_MSG_INIT_DEVICES()
{
    return 4;
}; // = 4;
uint8_t JMGlobal::CMD_STATUS_IDLE()
{
    return 0;
}; // = 0;
uint8_t JMGlobal::CMD_STATUS_PROCESSING()
{
    return 1;
}; // = 1;
uint8_t JMGlobal::CMD_MODE_TOGGLE()
{
    return 0;
}; // = 0;
uint8_t JMGlobal::CMD_MODE_FORCE_ON()
{
    return 1;
}; // = 1;
uint8_t JMGlobal::CMD_MODE_FORCE_OFF()
{
    return 2;
}; // = 2;
uint8_t JMGlobal::DO_CMD_BOX_TO_LG()
{
    return 1;
}; // = 1;
uint8_t JMGlobal::DO_CMD_INDI_TO_LG()
{
    return 2;
}; // = 2;
uint8_t JMGlobal::DO_CMD_PS_TO_LG()
{
    return 3;
}; // = 3;
uint8_t JMGlobal::DO_CMD_ELSE_TO_LG()
{
    return 4;
}; // = 4;
uint8_t JMGlobal::DO_CMD_BOX_TO_AKARI()
{
    return 5;
}; // = 5;
uint8_t JMGlobal::DO_CMD_INDI_TO_AKARI()
{
    return 6;
}; // = 6;
uint8_t JMGlobal::DO_CMD_PS_TO_AKARI()
{
    return 7;
}; // = 7;
uint8_t JMGlobal::DO_CMD_ELSE_TO_AKARI()
{
    return 8;
}; // = 8;
uint8_t JMGlobal::DO_CMD_TOGGLE_POWER_SPEAKER()
{
    return 9;
}; // = 9;
uint8_t JMGlobal::DO_CMD_TOGGLE_SLEEP_LG()
{
    return 10;
}; // = 10;
uint8_t JMGlobal::DO_CMD_TOGGLE_SLEEP_AKARI()
{
    return 11;
}; // = 11;
uint8_t JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_LG()
{
    return 12;
}; // = 12;
uint8_t JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_AKARI()
{
    return 13;
}; // = 13;
uint8_t JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_LG()
{
    return 14;
}; // = 14;
uint8_t JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_AKARI()
{
    return 15;
}; // = 15;
uint8_t JMGlobal::DO_CMD_CALIBRATE_POWER_SPEAKER()
{
    return 16;
}; // = 16;
uint8_t JMGlobal::DO_CMD_CALIBRATE_POWER_MATRIX()
{
    return 17;
}; // = 17;
uint8_t JMGlobal::DO_CMD_TURN_LG_OFF()
{
    return 18;
}; // = 18;
uint8_t JMGlobal::DO_CMD_TURN_AKARI_OFF()
{
    return 19;
}; // = 19;
uint8_t JMGlobal::DO_INET_ON_CMD_BOX_TO_LG()
{
    return 1;
}; // = 1;
uint8_t JMGlobal::DO_INET_ON_CMD_INDI_TO_LG()
{
    return 2;
}; // = 2;
uint8_t JMGlobal::DO_INET_ON_CMD_PS_TO_LG()
{
    return 3;
}; // = 3;
uint8_t JMGlobal::DO_INET_ON_CMD_ELSE_TO_LG()
{
    return 4;
}; // = 4;
uint8_t JMGlobal::DO_INET_ON_CMD_BOX_TO_AKARI()
{
    return 5;
}; // = 5;
uint8_t JMGlobal::DO_INET_ON_CMD_INDI_TO_AKARI()
{
    return 6;
}; // = 6;
uint8_t JMGlobal::DO_INET_ON_CMD_PS_TO_AKARI()
{
    return 7;
}; // = 7;
uint8_t JMGlobal::DO_INET_ON_CMD_ELSE_TO_AKARI()
{
    return 8;
}; // = 8;
uint8_t JMGlobal::DO_INET_ON_CMD_SPEAKER()
{
    return 9;
}; // = 9;
uint8_t JMGlobal::DO_INET_CMD_SLEEP_LG()
{
    return 10;
}; // = 10;
uint8_t JMGlobal::DO_INET_CMD_SLEEP_AKARI()
{
    return 11;
}; // = 11;
uint8_t JMGlobal::DO_INET_OFF_CMD_BOX_TO_LG()
{
    return 12;
}; // = 12;
uint8_t JMGlobal::DO_INET_OFF_CMD_INDI_TO_LG()
{
    return 13;
}; // = 13;
uint8_t JMGlobal::DO_INET_OFF_CMD_PS_TO_LG()
{
    return 14;
}; // = 14;
uint8_t JMGlobal::DO_INET_OFF_CMD_ELSE_TO_LG()
{
    return 15;
}; // = 15;
uint8_t JMGlobal::DO_INET_OFF_CMD_BOX_TO_AKARI()
{
    return 16;
}; // = 16;
uint8_t JMGlobal::DO_INET_OFF_CMD_INDI_TO_AKARI()
{
    return 17;
}; // = 17;
uint8_t JMGlobal::DO_INET_OFF_CMD_PS_TO_AKARI()
{
    return 18;
}; // = 18;
uint8_t JMGlobal::DO_INET_OFF_CMD_ELSE_TO_AKARI()
{
    return 19;
}; // = 19;
uint8_t JMGlobal::DO_INET_OFF_CMD_SPEAKER()
{
    return 20;
}; // = 20;
uint8_t JMGlobal::DO_INET_CMD_WAKE_LG()
{
    return 21;
}; // = 21;
uint8_t JMGlobal::DO_INET_CMD_WAKE_AKARI()
{
    return 22;
}; // = 22;
uint8_t JMGlobal::DO_INET_CMD_CALIBRATE_POWER_DISPLAY_LG()
{
    return 23;
}; // = 23;
uint8_t JMGlobal::DO_INET_CMD_CALIBRATE_POWER_DISPLAY_AKARI()
{
    return 24;
}; // = 24;
uint8_t JMGlobal::DO_INET_CMD_CALIBRATE_POWER_PLAYER_LG()
{
    return 25;
}; // = 25;
uint8_t JMGlobal::DO_INET_CMD_CALIBRATE_POWER_PLAYER_AKARI()
{
    return 26;
}; // = 26;
uint8_t JMGlobal::DO_INET_CMD_CALIBRATE_POWER_SPEAKER()
{
    return 27;
}; // = 27;
uint8_t JMGlobal::DO_INET_CMD_CALIBRATE_POWER_MATRIX()
{
    return 28;
}; // = 28;
uint8_t JMGlobal::DO_INET_CMD_TURN_LG_OFF()
{
    return 29;
} // = 29;
uint8_t JMGlobal::DO_INET_CMD_TURN_AKARI_OFF()
{
    return 30;
}; // = 30;
uint8_t JMGlobal::DEV_DISPLAY_LG()
{
    return 31;
}; // = 31; // 0
uint8_t JMGlobal::DEV_DISPLAY_AKARI()
{
    return 30;
}; // = 30;
uint8_t JMGlobal::DEV_HDMI_AMP_LG()
{
    return 29;
}; // = 29;
uint8_t JMGlobal::DEV_HDMI_AMP_AKARI()
{
    return 28;
}; // = 28;
uint8_t JMGlobal::DEV_HDMI_AMP_PS()
{
    return 27;
}; // = 27;
uint8_t JMGlobal::DEV_HDMI_MATRIX()
{
    return 26;
}; // = 26;
uint8_t JMGlobal::DEV_PLAYER_BOX()
{
    return 25;
}; // = 25;
uint8_t JMGlobal::DEV_PLAYER_INDI()
{
    return 24;
}; // = 24;
uint8_t JMGlobal::DEV_PLAYER_PS()
{
    return 23;
}; // = 23;
uint8_t JMGlobal::DEV_PLAYER_ELSE()
{
    return 22;
}; // = 22;
uint8_t JMGlobal::DEV_SERVER_EVERCOSS_BAT()
{
    return 21;
}; // = 21;
uint8_t JMGlobal::DEV_SERVER_EVERCOSS_CHARGER()
{
    return 20;
}; // = 20;
uint8_t JMGlobal::DEV_SERVER_NAS()
{
    return 19;
}; // = 19;
uint8_t JMGlobal::DEV_HDD_DOCK()
{
    return 18;
}; // = 18;
uint8_t JMGlobal::DEV_SPEAKER()
{
    return 17;
}; // = 17;
uint8_t JMGlobal::DEV_HDMI_AMP_INDI()
{
    return 16;
}; // = 16;
uint8_t JMGlobal::DEV_REMOTE_A1()
{
    return 7;
}; // = 7;
uint8_t JMGlobal::DEV_REMOTE_A2()
{
    return 6;
}; // = 6;
uint8_t JMGlobal::DEV_REMOTE_A3()
{
    return 5;
}; // = 5;
uint8_t JMGlobal::DEV_REMOTE_A4()
{
    return 4;
}; // = 4;
uint8_t JMGlobal::DEV_REMOTE_B1()
{
    return 3;
}; // = 3;
uint8_t JMGlobal::DEV_REMOTE_B2()
{
    return 2;
}; // = 2;
uint8_t JMGlobal::DEV_REMOTE_B3()
{
    return 1;
}; // = 1;
uint8_t JMGlobal::DEV_REMOTE_B4()
{
    return 0;
}; // = 0; // 23
uint8_t JMGlobal::MSG_SPECIAL_VALUE_SHUTDOWNALL()
{
    return 1;
}; // = 1;
*/