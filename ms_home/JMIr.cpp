#include "JMIr.h"
#include "JMCommand.h"
#include "JMGlobal.h"
// #include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

const uint32_t JMIr::getIrCode(uint8_t id)
{
    if (id == JMIr::IR_LG1_ID)
    {
        return 2733166887;
    }
    else if (id == JMIr::IR_LG2_ID)
    {
        return 1663147656;
    }
    else if (id == JMIr::IR_LG3_ID)
    {
        return 1494494661;
    }
    else if (id == JMIr::IR_LG4_ID)
    {
        return 3967086620;
    }
    else if (id == JMIr::IR_AK1_ID)
    {
        return 4257650505;
    }
    else if (id == JMIr::IR_AK2_ID)
    {
        return 271251858;
    }
    else if (id == JMIr::IR_AK3_ID)
    {
        return 2952684369;
    }
    else if (id == JMIr::IR_AK4_ID)
    {
        return 2508896912;
    }
    else if (id == JMIr::IR_LGP_ID)
    {
        return 3909119151;
    }
    else if (id == JMIr::IR_AKP_ID)
    {
        return 1937930936;
    }
    else
        return 0;
};
JMIr::JMIr(){
    // this->setup();
};
void JMIr::setCommander(JMCommand &commander)
{
    this->commander = &commander;
};
void JMIr::setup()
{

    // IR sender
    // IrSender.begin();

    // IR Receiver
    // IrReceiver.begin(IR_RECEIVE_PIN, false);

    // Serial.println("IR");
    IrSender.begin(3, false);
    IrReceiver.begin(2, false);
};

void JMIr::receiveIr(bool trace = false)
{
    uint16_t max = 2000;
    uint16_t min = 200;
    if (IrReceiver.decode())
    {
        uint32_t code = IrReceiver.decodedIRData.decodedRawData;

        if (trace && code != 0)
            Serial.println(code);
        const unsigned long ml = millis();
        if (code == JMIr::getIrCode(JMIr::IR_LG1_ID) || code == JMIr::getIrCode(JMIr::IR_LG2_ID) || code == JMIr::getIrCode(JMIr::IR_LG3_ID) || code == JMIr::getIrCode(JMIr::IR_LG4_ID) || code == JMIr::getIrCode(JMIr::IR_LGP_ID))
        {
            uint8_t id = 250;
            if (code == JMIr::getIrCode(JMIr::IR_LG1_ID))
            {
                id = JMIr::IR_LG1_ID;
            }
            else if (code == JMIr::getIrCode(JMIr::IR_LG2_ID))
            {
                id = JMIr::IR_LG2_ID;
            }
            else if (code == JMIr::getIrCode(JMIr::IR_LG3_ID))
            {
                id = JMIr::IR_LG3_ID;
            }
            else if (code == JMIr::getIrCode(JMIr::IR_LG4_ID))
            {
                id = JMIr::IR_LG4_ID;
            }
            else if (code == JMIr::getIrCode(JMIr::IR_LGP_ID))
            {
                id = JMIr::IR_LGP_ID;
            }
            else
            {
                IrReceiver.resume();
                return;
            }
            if (this->lastLgId != id)
            {
                this->lastLgId = id;
                this->irLgCount = 0;
                this->irLgTime = 0;
            }
            if (ml - this->irLgTime < max && ml - this->irLgTime > min)
            {
                if (this->irLgCount < 255)
                    this->irLgCount++;
            }
            else
            {
                if (this->irLgCount == 0)
                    this->irLgCount = 1;
            }
            this->irLgTime = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_AK1_ID) || code == JMIr::getIrCode(JMIr::IR_AK2_ID) || code == JMIr::getIrCode(JMIr::IR_AK3_ID) || code == JMIr::getIrCode(JMIr::IR_AK4_ID) || code == JMIr::getIrCode(JMIr::IR_AKP_ID))
        {
            uint8_t id = 250;
            if (code == JMIr::getIrCode(JMIr::IR_AK1_ID))
            {
                id = JMIr::IR_AK1_ID;
            }
            else if (code == JMIr::getIrCode(JMIr::IR_AK2_ID))
            {
                id = JMIr::IR_AK2_ID;
            }
            else if (code == JMIr::getIrCode(JMIr::IR_AK3_ID))
            {
                id = JMIr::IR_AK3_ID;
            }
            else if (code == JMIr::getIrCode(JMIr::IR_AK4_ID))
            {
                id = JMIr::IR_AK4_ID;
            }
            else if (code == JMIr::getIrCode(JMIr::IR_AKP_ID))
            {
                id = JMIr::IR_AKP_ID;
            }
            else
            {
                IrReceiver.resume();
                return;
            }
            if (this->lastAkId != id)
            {
                this->lastAkId = id;
                this->irAkCount = 0;
                this->irAkTime = 0;
            }
            if (ml - this->irAkTime < max && ml - this->irAkTime > min)
            {
                if (this->irAkCount < 255)
                    this->irAkCount++;
            }
            else
            {
                if (this->irAkCount == 0)
                    this->irAkCount = 1;
            }
            this->irAkTime = ml;
        }
        IrReceiver.resume();
    }
    else
    {
        // proses ir-s
        if (this->irLgCount > 0)
        {
            if (millis() - this->irLgTime > max)
            {
                this->processIr(this->lastLgId, trace);
                this->irLgTime = 0;
                this->irLgCount = 0;
                this->lastLgId = 250;
            }
        }
        if (this->irAkCount > 0)
        {
            if (millis() - this->irAkTime > max)
            {
                this->processIr(this->lastAkId, trace);
                this->irAkTime = 0;
                this->irAkCount = 0;
                this->lastAkId = 250;
            }
        }
    }
};
void JMIr::processIr(uint8_t id, bool trace)
{
    if (id == JMIr::IR_LG1_ID)
    {
        if (this->irLgCount == 1)
        {
            if (trace)
                Serial.println(F("A1:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_LG, JMGlobal::CMD_MODE_FORCE_ON);
        }
        else if (this->irLgCount == 2)
        {
            if (trace)
                Serial.println(F("A1:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_LG, JMGlobal::CMD_MODE_FORCE_OFF);
        }
        else if (this->irLgCount >= 5)
        {
            if (trace)
                Serial.println(F("A1:      >=5"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_LG, 0);
        }
    }
    else if (id == JMIr::IR_LG2_ID)
    {
        if (this->irLgCount == 1)
        {
            if (trace)
                Serial.println(F("A2:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_LG, JMGlobal::CMD_MODE_FORCE_ON);
        }
        else if (this->irLgCount == 2)
        {
            if (trace)
                Serial.println(F("A2:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_LG, JMGlobal::CMD_MODE_FORCE_OFF);
        }
        else if (this->irLgCount >= 5)
        {
            if (trace)
                Serial.println(F("A2:      >=5"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_SPEAKER, 0);
        }
    }
    else if (id == JMIr::IR_LG3_ID)
    {
        if (this->irLgCount == 1)
        {
            if (trace)
                Serial.println(F("A3:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_LG, JMGlobal::CMD_MODE_FORCE_ON);
        }
        else if (this->irLgCount == 2)
        {
            if (trace)
                Serial.println(F("A3:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_LG, JMGlobal::CMD_MODE_FORCE_OFF);
        }
        else if (this->irLgCount >= 5)
        {
            if (trace)
                Serial.println(F("A3:      >=5"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_MATRIX, 0);
        }
    }
    else if (id == JMIr::IR_LG4_ID)
    {
        if (this->irLgCount == 1)
        {
            if (trace)
                Serial.println(F("A4:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_LG, JMGlobal::CMD_MODE_FORCE_ON);
        }
        else if (this->irLgCount == 2)
        {
            if (trace)
                Serial.println(F("A4:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_LG, JMGlobal::CMD_MODE_FORCE_OFF);
        }
        else if (this->irLgCount >= 5)
        {
            if (trace)
                Serial.println(F("A4:      >=5"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_LG, 0);
        }
    }
    else if (id == JMIr::IR_LGP_ID)
    {
        if (this->irLgCount == 1)
        {
            if (trace)
                Serial.println(F("AP:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_TOGGLE_SLEEP_LG, 0);
        }
        else if (this->irLgCount == 2)
        {
            if (trace)
                Serial.println(F("AP:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_TURN_LG_OFF, 0);
        }
        else if (this->irLgCount == 3)
        {
            if (trace)
                Serial.println(F("AP:      3"));
            this->commander->doCommand(JMGlobal::DO_CMD_TOGGLE_POWER_SPEAKER, 0);
        }
    }
    else if (id == JMIr::IR_AK1_ID)
    {
        if (this->irAkCount == 1)
        {
            if (trace)
                Serial.println(F("B1:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_AKARI, JMGlobal::CMD_MODE_FORCE_ON);
        }
        else if (this->irAkCount == 2)
        {
            if (trace)
                Serial.println(F("B1:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_AKARI, JMGlobal::CMD_MODE_FORCE_OFF);
        }
        else if (this->irAkCount >= 5)
        {
            if (trace)
                Serial.println(F("B1:      >=5"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_DISPLAY_AKARI, 0);
        }
    }
    else if (id == JMIr::IR_AK2_ID)
    {
        if (this->irAkCount == 1)
        {
            if (trace)
                Serial.println(F("B2:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_AKARI, JMGlobal::CMD_MODE_FORCE_ON);
        }
        else if (this->irAkCount == 2)
        {
            if (trace)
                Serial.println(F("B2:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_AKARI, JMGlobal::CMD_MODE_FORCE_OFF);
        }
        else if (this->irAkCount >= 5)
        {
            if (trace)
                Serial.println(F("B2:      >=5"));
            // no command
        }
    }
    else if (id == JMIr::IR_AK3_ID)
    {
        if (this->irAkCount == 1)
        {
            if (trace)
                Serial.println(F("B3:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_AKARI, JMGlobal::CMD_MODE_FORCE_ON);
        }
        else if (this->irAkCount == 2)
        {
            if (trace)
                Serial.println(F("B3:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_AKARI, JMGlobal::CMD_MODE_FORCE_OFF);
        }
        else if (this->irAkCount >= 5)
        {
            if (trace)
                Serial.println(F("B3:      >=5"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_MATRIX, 0);
        }
    }
    else if (id == JMIr::IR_AK4_ID)
    {
        if (this->irAkCount == 1)
        {
            if (trace)
                Serial.println(F("B4:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_AKARI, JMGlobal::CMD_MODE_FORCE_ON);
        }
        else if (this->irAkCount == 2)
        {
            if (trace)
                Serial.println(F("B4:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_AKARI, JMGlobal::CMD_MODE_FORCE_OFF);
        }
        else if (this->irAkCount >= 5)
        {
            if (trace)
                Serial.println(F("B4:      >=5"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_PLAYER_AKARI, 0);
        }
    }
    else if (id == JMIr::IR_AKP_ID)
    {
        if (this->irAkCount == 1)
        {
            if (trace)
                Serial.println(F("BP:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_TOGGLE_SLEEP_AKARI, 0);
        }
        else if (this->irAkCount == 2)
        {
            if (trace)
                Serial.println(F("BP:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_TURN_AKARI_OFF, 0);
        }
    }
};

void JMIr::sendIr(uint32_t code)
{
    IrSender.sendNECRaw(code, 1);
    // irsend.sendNECRaw(code, 1);
};