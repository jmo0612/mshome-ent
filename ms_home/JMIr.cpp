#include "JMIr.h"
#include "JMCommand.h"
#include "JMGlobal.h"
//#include "PinDefinitionsAndMore.h"
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

void JMIr::receiveIr()
{
    if (IrReceiver.decode())
    {
        uint32_t code = IrReceiver.decodedIRData.decodedRawData;
        const unsigned long ml = millis();
        if (code == JMIr::getIrCode(JMIr::IR_LG1_ID))
        {
            if (ml - this->irLg1Time < 1000 && ml - this->irLg1Time > 100)
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
            if (ml - this->irLg2Time < 1000 && ml - this->irLg2Time > 100)
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
            if (ml - this->irLg3Time < 1000 && ml - this->irLg3Time > 100)
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
            if (ml - this->irLg4Time < 1000 && ml - this->irLg4Time > 100)
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
        else if (code == JMIr::getIrCode(JMIr::IR_AK1_ID))
        {
            if (ml - this->irAk1Time < 1000 && ml - this->irAk1Time > 100)
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
            if (ml - this->irAk2Time < 1000 && ml - this->irAk2Time > 100)
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
            if (ml - this->irAk3Time < 1000 && ml - this->irAk3Time > 100)
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
            if (ml - this->irAk4Time < 1000 && ml - this->irAk4Time > 100)
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
        IrReceiver.resume();
    }
    else
    {
        // proses ir-s
        if (this->irLg1Count > 0)
        {
            if (millis() - this->irLg1Time > 1000)
            {
                this->processIr(JMIr::IR_LG1_ID);
                this->irLg1Time = 0;
                this->irLg1Count = 0;
            }
        }
        if (this->irLg2Count > 0)
        {
            if (millis() - this->irLg2Time > 1000)
            {
                this->processIr(JMIr::IR_LG2_ID);
                this->irLg2Time = 0;
                this->irLg2Count = 0;
            }
        }
        if (this->irLg3Count > 0)
        {
            if (millis() - this->irLg3Time > 1000)
            {
                this->processIr(JMIr::IR_LG3_ID);
                this->irLg3Time = 0;
                this->irLg3Count = 0;
            }
        }
        if (this->irLg4Count > 0)
        {
            if (millis() - this->irLg4Time > 1000)
            {
                this->processIr(JMIr::IR_LG4_ID);
                this->irLg4Time = 0;
                this->irLg4Count = 0;
            }
        }
        if (this->irAk1Count > 0)
        {
            if (millis() - this->irAk1Time > 1000)
            {
                this->processIr(JMIr::IR_AK1_ID);
                this->irAk1Time = 0;
                this->irAk1Count = 0;
            }
        }
        if (this->irAk2Count > 0)
        {
            if (millis() - this->irAk2Time > 1000)
            {
                this->processIr(JMIr::IR_AK2_ID);
                this->irAk2Time = 0;
                this->irAk2Count = 0;
            }
        }
        if (this->irAk3Count > 0)
        {
            if (millis() - this->irAk3Time > 1000)
            {
                this->processIr(JMIr::IR_AK3_ID);
                this->irAk3Time = 0;
                this->irAk3Count = 0;
            }
        }
        if (this->irAk4Count > 0)
        {
            if (millis() - this->irAk4Time > 1000)
            {
                this->processIr(JMIr::IR_AK4_ID);
                this->irAk4Time = 0;
                this->irAk4Count = 0;
            }
        }
    }
};
void JMIr::receiveIr2()
{
    if (IrReceiver.decode())
    {
        uint32_t code = IrReceiver.decodedIRData.decodedRawData;
        this->processIr(code);
        IrReceiver.resume();
    }
};
void JMIr::processIr(uint8_t id)
{
    if (id == JMIr::IR_LG1_ID)
    {
        if (this->irLg1Count == 1)
        {
            Serial.println(F("A1:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_LG);
        }
        else if (this->irLg1Count == 2)
        {
            Serial.println(F("A1:      2"));
            this->commander->doCommand(JMGlobal::DO_CMD_TOGGLE_POWER_SPEAKER);
        }
        else if (this->irLg1Count > 2)
        {
            Serial.println(F("A1:      >2"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_SPEAKER);
        }
    }
    else if (id == JMIr::IR_LG2_ID)
    {
        if (this->irLg2Count == 1)
        {
            Serial.println(F("A2:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_LG);
        }
        else if (this->irLg2Count == 2)
        {
            Serial.println(F("A2:      2"));
            // EMPTY COMMAND
        }
        else if (this->irLg2Count > 2)
        {
            Serial.println(F("A2:      >2"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_LG);
        }
    }
    else if (id == JMIr::IR_LG3_ID)
    {
        if (this->irLg3Count == 1)
        {
            Serial.println(F("A3:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_LG);
        }
        else if (this->irLg3Count == 2)
        {
            Serial.println(F("A3:      2"));
            // EMPTY COMMAND
        }
        else if (this->irLg3Count > 2)
        {
            Serial.println(F("A3:      >2"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_MATRIX);
        }
    }
    else if (id == JMIr::IR_LG4_ID)
    {
        if (this->irLg4Count == 1)
        {
            Serial.println(F("A4:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_LG);
        }
        else if (this->irLg4Count == 2)
        {
            Serial.println(F("A4:      2"));
            // EMPTY COMMAND
        }
        else if (this->irLg4Count > 2)
        {
            Serial.println(F("A4:      >2"));
            // EMPTY COMMAND
        }
    }
    else if (id == JMIr::IR_AK1_ID)
    {
        if (this->irAk1Count == 1)
        {
            Serial.println(F("B1:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_AKARI);
        }
        else if (this->irAk1Count == 2)
        {
            Serial.println(F("B1:      2"));
            // EMPTY COMMAND
        }
        else if (this->irAk1Count > 2)
        {
            Serial.println(F("B1:      >2"));
            // EMPTY COMMAND
        }
    }
    else if (id == JMIr::IR_AK2_ID)
    {
        if (this->irAk2Count == 1)
        {
            Serial.println(F("B2:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_AKARI);
        }
        else if (this->irAk2Count == 2)
        {
            Serial.println(F("B2:      2"));
            // EMPTY COMMAND
        }
        else if (this->irAk2Count > 2)
        {
            Serial.println(F("B2:      >2"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_AKARI);
        }
    }
    else if (id == JMIr::IR_AK3_ID)
    {
        if (this->irAk3Count == 1)
        {
            Serial.println(F("B3:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_AKARI);
        }
        else if (this->irAk3Count == 2)
        {
            Serial.println(F("B3:      2"));
            // EMPTY COMMAND
        }
        else if (this->irAk3Count > 2)
        {
            Serial.println(F("B3:      >2"));
            this->commander->doCommand(JMGlobal::DO_CMD_CALIBRATE_POWER_MATRIX);
        }
    }
    else if (id == JMIr::IR_AK4_ID)
    {
        if (this->irAk4Count == 1)
        {
            Serial.println(F("B4:      1"));
            this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_AKARI);
        }
        else if (this->irAk4Count == 2)
        {
            Serial.println(F("B4:      2"));
            // EMPTY COMMAND
        }
        else if (this->irAk4Count > 2)
        {
            Serial.println(F("B4:      >2"));
            // EMPTY COMMAND
        }
    }
};
void JMIr::processIr2(uint32_t code)
{
    if (code == JMIr::getIrCode(JMIr::IR_LG1_ID))
    {
        Serial.println(F("LG_BOX"));
        this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_LG);
    }
    else if (code == JMIr::getIrCode(JMIr::IR_LG2_ID))
    {
        Serial.println(F("LG_PS"));
        this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_LG);
    }
    else if (code == JMIr::getIrCode(JMIr::IR_LG3_ID))
    {
        Serial.println(F("LG_INDI"));
        this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_LG);
    }
    else if (code == JMIr::getIrCode(JMIr::IR_LG4_ID))
    {
        Serial.println(F("LG_ELSE"));
        this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_LG);
    }
    else if (code == JMIr::getIrCode(JMIr::IR_AK1_ID))
    {
        Serial.println(F("AK_BOX"));
        this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_AKARI);
    }
    else if (code == JMIr::getIrCode(JMIr::IR_AK2_ID))
    {
        Serial.println(F("AK_PS"));
        this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_AKARI);
    }
    else if (code == JMIr::getIrCode(JMIr::IR_AK3_ID))
    {
        Serial.println(F("AK_INDI"));
        this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_AKARI);
    }
    else if (code == JMIr::getIrCode(JMIr::IR_AK4_ID))
    {
        Serial.println(F("AK_ELSE"));
        this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_AKARI);
    }
};

void JMIr::sendIr(uint32_t code)
{
    IrSender.sendNECRaw(code, 1);
    // irsend.sendNECRaw(code, 1);
};