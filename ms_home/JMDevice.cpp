#include "JMDevice.h"
#include "JMRelay.h"
#include "JMIr.h"
#include "JMCommand.h"
#include "JMGlobal.h"

const uint32_t JMDevice::getIrPower(uint8_t id, bool on = true)
{
    if (on)
    {
        if (id == JMGlobal::DEV_DISPLAY_LG)
        {
            return 4144560900;
        }
        else if (id == JMGlobal::DEV_DISPLAY_AKARI)
        {
            return 4111105792;
        }
        else if (id == JMGlobal::DEV_HDMI_MATRIX)
        {
            return 3977412480;
        }
        else if (id == JMGlobal::DEV_PLAYER_BOX)
        {
            return 2122416000;
        }
        else if (id == JMGlobal::DEV_PLAYER_INDI)
        {
            return 3208707840;
        }
        else if (id == JMGlobal::DEV_SPEAKER)
        {
            return 4278190467;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return getIrPower(id, true);
    }
};

JMDevice::JMDevice(uint8_t id, JMCommand &commander, JMRelay &relay, JMIr &ir, uint16_t acOnDelay, uint16_t acOffDelay, uint16_t runDelay, uint16_t shutDownDelay)
{
    this->id = id;
    this->commander = &commander;
    this->relay = &relay;
    this->ir = &ir;
    this->acOnDelay = acOnDelay;
    this->acOffDelay = acOffDelay;
    this->runDelay = runDelay;
    this->shutDownDelay = shutDownDelay;
    this->mode = DEV_MODE_DEAD;
};
bool JMDevice::acOn()
{
    if (this->mode != DEV_MODE_DEAD)
        return false;
    // do it
    if (this->relay == NULL)
        return false;
    this->relay->turnOn();
    delay(this->acOnDelay);
    this->mode = DEV_MODE_STANDBY;
    if (this->shutDownFailed)
    {
        delay(this->runDelay);
        this->mode = DEV_MODE_RUNNING;
    }
    this->commander->updateStats(*this);
    return true;
};
bool JMDevice::acOff()
{
    if (this->mode == DEV_MODE_DEAD)
        return false;
    if (this->mode == DEV_MODE_RUNNING)
    {
        if (this->shutDown())
        {
            return this->acOff();
        }
        else
        {
            return false;
        }
    }
    else
    {
        // do it
        if (this->relay == NULL)
            return false;
        this->relay->turnOff();
        delay(this->acOffDelay);
        this->mode = DEV_MODE_DEAD;
        this->commander->updateStats(*this);
        return true;
    }
};
bool JMDevice::run()
{
    if (this->mode == DEV_MODE_RUNNING)
        return false;
    if (this->mode == DEV_MODE_DEAD)
    {
        // ac on
        if (this->acOn())
        {
            if (this->mode = DEV_MODE_STANDBY)
            {
                return this->run();
            }
            else
            {
                this->commander->updateStats(*this);
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        // do it
        if (JMDevice::getIrPower(this->id, true) != 0)
        {
            this->ir->sendIr(JMDevice::getIrPower(this->id, true));
            delay(this->runDelay);
        }
        this->mode = DEV_MODE_RUNNING;
        this->commander->updateStats(*this);
        return true;
    }
};
bool JMDevice::shutDown()
{
    if (this->mode == DEV_MODE_STANDBY || this->mode == DEV_MODE_DEAD)
        return false;
    // do it
    if (JMDevice::getIrPower(this->id, false) != 0x0)
    {
        this->ir->sendIr(JMDevice::getIrPower(this->id, false));
        delay(this->shutDownDelay);
    }
    this->mode = DEV_MODE_STANDBY;
    this->commander->updateStats(*this);
    return true;
};
uint8_t JMDevice::getId()
{
    return this->id;
};
uint8_t JMDevice::getMode()
{
    return this->mode;
};
void JMDevice::setShutDownFailed(bool failed)
{
    this->shutDownFailed = failed;
};
void JMDevice::calibrate()
{
    if (this->mode == DEV_MODE_RUNNING)
        this->ir->sendIr(JMDevice::getIrPower(this->id, true));
    else
        this->ir->sendIr(JMDevice::getIrPower(this->id, false));
};