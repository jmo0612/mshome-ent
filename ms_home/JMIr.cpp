#include "JMIr.h"
#include "JMCommand.h"
#include "JMGlobal.h"
//#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

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
        this->processIr(code);
        IrReceiver.resume();
    }
};
void JMIr::processIr(uint32_t code)
{
    if (code == JMIr::IR_A1_CODE)
    {
        this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_LG);
        Serial.println(F("LG_BOX"));
    }
    else if (code == JMIr::IR_A2_CODE)
    {
        this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_LG);
        Serial.println(F("LG_PS"));
    }
    else if (code == JMIr::IR_A3_CODE)
    {
        this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_LG);
        Serial.println(F("LG_INDI"));
    }
    else if (code == JMIr::IR_A4_CODE)
    {
        this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_LG);
        Serial.println(F("LG_ELSE"));
    }
    else if (code == JMIr::IR_B1_CODE)
    {
        this->commander->doCommand(JMGlobal::DO_CMD_BOX_TO_AKARI);
        Serial.println(F("AK_BOX"));
    }
    else if (code == JMIr::IR_B2_CODE)
    {
        this->commander->doCommand(JMGlobal::DO_CMD_PS_TO_AKARI);
        Serial.println(F("AK_PS"));
    }
    else if (code == JMIr::IR_B3_CODE)
    {
        this->commander->doCommand(JMGlobal::DO_CMD_INDI_TO_AKARI);
        Serial.println(F("AK_INDI"));
    }
    else if (code == JMIr::IR_B4_CODE)
    {
        this->commander->doCommand(JMGlobal::DO_CMD_ELSE_TO_AKARI);
        Serial.println(F("AK_ELSE"));
    }
};

void JMIr::sendIr(uint32_t code)
{
    IrSender.sendNECRaw(code, 1);
    // irsend.sendNECRaw(code, 1);
};