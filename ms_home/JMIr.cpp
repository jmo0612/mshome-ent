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
        if (code == JMIr::getIrCode(JMIr::IR_LG1_ID))
        {
            if (ml - this->irLg1Time < max && ml - this->irLg1Time > min)
            {
                if (this->irLg1Count < 255)
                    this->irLg1Count++;
            }
            else
            {
                if (this->irLg1Count == 0)
                    this->irLg1Count = 1;
            }
            this->irLg1Time = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_LG2_ID))
        {
            if (ml - this->irLg2Time < max && ml - this->irLg2Time > min)
            {
                if (this->irLg2Count < 255)
                    this->irLg2Count++;
            }
            else
            {
                if (this->irLg2Count == 0)
                    this->irLg2Count = 1;
            }
            this->irLg2Time = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_LG3_ID))
        {
            if (ml - this->irLg3Time < max && ml - this->irLg3Time > min)
            {
                if (this->irLg3Count < 255)
                    this->irLg3Count++;
            }
            else
            {
                if (this->irLg3Count == 0)
                    this->irLg3Count = 1;
            }
            this->irLg3Time = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_LG4_ID))
        {
            if (ml - this->irLg4Time < max && ml - this->irLg4Time > min)
            {
                if (this->irLg4Count < 255)
                    this->irLg4Count++;
            }
            else
            {
                if (this->irLg4Count == 0)
                    this->irLg4Count = 1;
            }
            this->irLg4Time = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_LGP_ID))
        {
            if (ml - this->irLgPTime < max && ml - this->irLgPTime > min)
            {
                if (this->irLgPCount < 255)
                    this->irLgPCount++;
            }
            else
            {
                if (this->irLgPCount == 0)
                    this->irLgPCount = 1;
            }
            this->irLgPTime = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_AK1_ID))
        {
            if (ml - this->irAk1Time < max && ml - this->irAk1Time > min)
            {
                if (this->irAk1Count < 255)
                    this->irAk1Count++;
            }
            else
            {
                if (this->irAk1Count == 0)
                    this->irAk1Count = 1;
            }
            this->irAk1Time = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_AK2_ID))
        {
            if (ml - this->irAk2Time < max && ml - this->irAk2Time > min)
            {
                if (this->irAk2Count < 255)
                    this->irAk2Count++;
            }
            else
            {
                if (this->irAk2Count == 0)
                    this->irAk2Count = 1;
            }
            this->irAk2Time = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_AK3_ID))
        {
            if (ml - this->irAk3Time < max && ml - this->irAk3Time > min)
            {
                if (this->irAk3Count < 255)
                    this->irAk3Count++;
            }
            else
            {
                if (this->irAk3Count == 0)
                    this->irAk3Count = 1;
            }
            this->irAk3Time = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_AK4_ID))
        {
            if (ml - this->irAk4Time < max && ml - this->irAk4Time > min)
            {
                if (this->irAk4Count < 255)
                    this->irAk4Count++;
            }
            else
            {
                if (this->irAk4Count == 0)
                    this->irAk4Count = 1;
            }
            this->irAk4Time = ml;
        }
        else if (code == JMIr::getIrCode(JMIr::IR_AKP_ID))
        {
            if (ml - this->irAkPTime < max && ml - this->irAkPTime > min)
            {
                if (this->irAkPCount < 255)
                    this->irAkPCount++;
            }
            else
            {
                if (this->irAkPCount == 0)
                    this->irAkPCount = 1;
            }
            this->irAkPTime = ml;
        }
        IrReceiver.resume();
    }
    else
    {
        // proses ir-s
        if (this->irLg1Count > 0)
        {
            if (millis() - this->irLg1Time > max)
            {
                this->processIr(JMIr::IR_LG1_ID, trace);
                this->irLg1Time = 0;
                this->irLg1Count = 0;
            }
        }
        if (this->irLg2Count > 0)
        {
            if (millis() - this->irLg2Time > max)
            {
                this->processIr(JMIr::IR_LG2_ID, trace);
                this->irLg2Time = 0;
                this->irLg2Count = 0;
            }
        }
        if (this->irLg3Count > 0)
        {
            if (millis() - this->irLg3Time > max)
            {
                this->processIr(JMIr::IR_LG3_ID, trace);
                this->irLg3Time = 0;
                this->irLg3Count = 0;
            }
        }
        if (this->irLg4Count > 0)
        {
            if (millis() - this->irLg4Time > max)
            {
                this->processIr(JMIr::IR_LG4_ID, trace);
                this->irLg4Time = 0;
                this->irLg4Count = 0;
            }
        }
        if (this->irLgPCount > 0)
        {
            if (millis() - this->irLgPTime > max)
            {
                this->processIr(JMIr::IR_LGP_ID, trace);
                this->irLgPTime = 0;
                this->irLgPCount = 0;
            }
        }
        if (this->irAk1Count > 0)
        {
            if (millis() - this->irAk1Time > max)
            {
                this->processIr(JMIr::IR_AK1_ID, trace);
                this->irAk1Time = 0;
                this->irAk1Count = 0;
            }
        }
        if (this->irAk2Count > 0)
        {
            if (millis() - this->irAk2Time > max)
            {
                this->processIr(JMIr::IR_AK2_ID, trace);
                this->irAk2Time = 0;
                this->irAk2Count = 0;
            }
        }
        if (this->irAk3Count > 0)
        {
            if (millis() - this->irAk3Time > max)
            {
                this->processIr(JMIr::IR_AK3_ID, trace);
                this->irAk3Time = 0;
                this->irAk3Count = 0;
            }
        }
        if (this->irAk4Count > 0)
        {
            if (millis() - this->irAk4Time > max)
            {
                this->processIr(JMIr::IR_AK4_ID, trace);
                this->irAk4Time = 0;
                this->irAk4Count = 0;
            }
        }
        if (this->irAkPCount > 0)
        {
            if (millis() - this->irAkPTime > max)
            {
                this->processIr(JMIr::IR_AKP_ID, trace);
                this->irAkPTime = 0;
                this->irAkPCount = 0;
            }
        }
    }
};
void JMIr::processIr(uint8_t id, bool trace)
{
    if (id == JMIr::IR_LG1_ID)
    {
        if (this->irLg1Count == 1)
        {
            if (trace)
                Serial.println(F("A1:      1"));
            this->commander->doCommand(1/*DO_CMD_BOX_TO_LG*/, 1/*CMD_MODE_FORCE_ON*/);
        }
        else if (this->irLg1Count == 2)
        {
            if (trace)
                Serial.println(F("A1:      2"));
            this->commander->doCommand(1/*DO_CMD_BOX_TO_LG*/, 2/*CMD_MODE_FORCE_OFF*/);
        }
        else if (this->irLg1Count >= 5)
        {
            if (trace)
                Serial.println(F("A1:      >=5"));
            this->commander->doCommand(12/*DO_CMD_CALIBRATE_POWER_DISPLAY_LG*/, 0);
        }
    }
    else if (id == JMIr::IR_LG2_ID)
    {
        if (this->irLg2Count == 1)
        {
            if (trace)
                Serial.println(F("A2:      1"));
            this->commander->doCommand(2/*DO_CMD_INDI_TO_LG*/, 1/*CMD_MODE_FORCE_ON*/);
        }
        else if (this->irLg2Count == 2)
        {
            if (trace)
                Serial.println(F("A2:      2"));
            this->commander->doCommand(2/*DO_CMD_INDI_TO_LG*/, 2/*CMD_MODE_FORCE_OFF*/);
        }
        else if (this->irLg2Count >= 5)
        {
            if (trace)
                Serial.println(F("A2:      >=5"));
            this->commander->doCommand(16/*DO_CMD_CALIBRATE_POWER_SPEAKER*/, 0);
        }
    }
    else if (id == JMIr::IR_LG3_ID)
    {
        if (this->irLg3Count == 1)
        {
            if (trace)
                Serial.println(F("A3:      1"));
            this->commander->doCommand(3/*DO_CMD_PS_TO_LG*/, 1/*CMD_MODE_FORCE_ON*/);
        }
        else if (this->irLg3Count == 2)
        {
            if (trace)
                Serial.println(F("A3:      2"));
            this->commander->doCommand(3/*DO_CMD_PS_TO_LG*/, 2/*CMD_MODE_FORCE_OFF*/);
        }
        else if (this->irLg3Count >= 5)
        {
            if (trace)
                Serial.println(F("A3:      >=5"));
            this->commander->doCommand(17/*DO_CMD_CALIBRATE_POWER_MATRIX*/, 0);
        }
    }
    else if (id == JMIr::IR_LG4_ID)
    {
        if (this->irLg4Count == 1)
        {
            if (trace)
                Serial.println(F("A4:      1"));
            this->commander->doCommand(4/*DO_CMD_ELSE_TO_LG*/, 1/*CMD_MODE_FORCE_ON*/);
        }
        else if (this->irLg4Count == 2)
        {
            if (trace)
                Serial.println(F("A4:      2"));
            this->commander->doCommand(4/*DO_CMD_ELSE_TO_LG*/, 2/*CMD_MODE_FORCE_OFF*/);
        }
        else if (this->irLg4Count >= 5)
        {
            if (trace)
                Serial.println(F("A4:      >=5"));
            this->commander->doCommand(14/*DO_CMD_CALIBRATE_POWER_PLAYER_LG*/, 0);
        }
    }
    else if (id == JMIr::IR_LGP_ID)
    {
        if (this->irLgPCount == 1)
        {
            if (trace)
                Serial.println(F("AP:      1"));
            this->commander->doCommand(10/*DO_CMD_TOGGLE_SLEEP_LG*/, 0);
        }
        else if (this->irLgPCount == 2)
        {
            if (trace)
                Serial.println(F("AP:      2"));
            this->commander->doCommand(18/*DO_CMD_TURN_LG_OFF*/, 0);
        }
        else if (this->irLgPCount == 3)
        {
            if (trace)
                Serial.println(F("AP:      3"));
            this->commander->doCommand(9/*DO_CMD_TOGGLE_POWER_SPEAKER*/, 0);
        }
    }
    else if (id == JMIr::IR_AK1_ID)
    {
        if (this->irAk1Count == 1)
        {
            if (trace)
                Serial.println(F("B1:      1"));
            this->commander->doCommand(5/*DO_CMD_BOX_TO_AKARI*/, 1/*CMD_MODE_FORCE_ON*/);
        }
        else if (this->irAk1Count == 2)
        {
            if (trace)
                Serial.println(F("B1:      2"));
            this->commander->doCommand(5/*DO_CMD_BOX_TO_AKARI*/, 2/*CMD_MODE_FORCE_OFF*/);
        }
        else if (this->irAk1Count >= 5)
        {
            if (trace)
                Serial.println(F("B1:      >=5"));
            this->commander->doCommand(13/*DO_CMD_CALIBRATE_POWER_DISPLAY_AKARI*/, 0);
        }
    }
    else if (id == JMIr::IR_AK2_ID)
    {
        if (this->irAk2Count == 1)
        {
            if (trace)
                Serial.println(F("B2:      1"));
            this->commander->doCommand(6/*DO_CMD_INDI_TO_AKARI*/, 1/*CMD_MODE_FORCE_ON*/);
        }
        else if (this->irAk2Count == 2)
        {
            if (trace)
                Serial.println(F("B2:      2"));
            this->commander->doCommand(6/*DO_CMD_INDI_TO_AKARI*/, 2/*CMD_MODE_FORCE_OFF*/);
        }
        else if (this->irAk2Count >= 5)
        {
            if (trace)
                Serial.println(F("B2:      >=5"));
            // no command
        }
    }
    else if (id == JMIr::IR_AK3_ID)
    {
        if (this->irAk3Count == 1)
        {
            if (trace)
                Serial.println(F("B3:      1"));
            this->commander->doCommand(7/*DO_CMD_PS_TO_AKARI*/, 1/*CMD_MODE_FORCE_ON*/);
        }
        else if (this->irAk3Count == 2)
        {
            if (trace)
                Serial.println(F("B3:      2"));
            this->commander->doCommand(7/*DO_CMD_PS_TO_AKARI*/, 2/*CMD_MODE_FORCE_OFF*/);
        }
        else if (this->irAk3Count >= 5)
        {
            if (trace)
                Serial.println(F("B3:      >=5"));
            this->commander->doCommand(17/*DO_CMD_CALIBRATE_POWER_MATRIX*/, 0);
        }
    }
    else if (id == JMIr::IR_AK4_ID)
    {
        if (this->irAk4Count == 1)
        {
            if (trace)
                Serial.println(F("B4:      1"));
            this->commander->doCommand(8/*DO_CMD_ELSE_TO_AKARI*/, 1/*CMD_MODE_FORCE_ON*/);
        }
        else if (this->irAk4Count == 2)
        {
            if (trace)
                Serial.println(F("B4:      2"));
            this->commander->doCommand(8/*DO_CMD_ELSE_TO_AKARI*/, 2/*CMD_MODE_FORCE_OFF*/);
        }
        else if (this->irAk4Count >= 5)
        {
            if (trace)
                Serial.println(F("B4:      >=5"));
            this->commander->doCommand(15/*DO_CMD_CALIBRATE_POWER_PLAYER_AKARI*/, 0);
        }
    }
    else if (id == JMIr::IR_AKP_ID)
    {
        if (this->irAkPCount == 1)
        {
            if (trace)
                Serial.println(F("BP:      1"));
            this->commander->doCommand(11/*DO_CMD_TOGGLE_SLEEP_AKARI*/, 0);
        }
        else if (this->irAkPCount == 2)
        {
            if (trace)
                Serial.println(F("BP:      2"));
            this->commander->doCommand(19/*DO_CMD_TURN_AKARI_OFF*/, 0);
        }
    }
};

void JMIr::sendIr(uint32_t code)
{
    IrSender.sendNECRaw(code, 1);
    // irsend.sendNECRaw(code, 1);
};