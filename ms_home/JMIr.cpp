#include "JMIr.h"
#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

JMIr::JMIr(){

};
void JMIr::setup()
{
    // IR sender
    IrSender.begin();

    // IR Receiver
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
};
uint32_t JMIr::decode()
{
    if (IrReceiver.decode())
    {

        if (IrReceiver.decodedIRData.decodedRawData != 0x0)
            return IrReceiver.decodedIRData.decodedRawData;
        IrReceiver.resume(); // Enable receiving of the next value
    }
};
void JMIr::sendIr(uint32_t code)
{
    IrSender.sendNECRaw(code, 1);
};