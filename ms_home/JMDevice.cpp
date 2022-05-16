#include "JMDevice.h"
#include "JMRelay.h"
#include "JMIr.h"

JMDevice::JMDevice(char *devName, JMRelay &relay, JMIr &ir, uint32_t irRun, uint32_t irShutDown, int acOnDelay, int acOffDelay, int runDelay, int shutDownDelay)
{
    this->devName = devName;
    this->relay = &relay;
    this->ir = &ir;
    this->irRun = irRun;
    this->irShutDown = irShutDown;
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
        if (this->irRun != 0x0)
        {
            this->ir->sendIr(this->irRun);
            delay(this->runDelay);
        }
        this->mode = DEV_MODE_RUNNING;
        return true;
    }
};
bool JMDevice::shutDown()
{
    if (this->mode == DEV_MODE_STANDBY || this->mode == DEV_MODE_DEAD)
        return false;
    // do it
    if (this->irShutDown != 0x0)
    {
        this->ir->sendIr(this->irShutDown);
        delay(this->shutDownDelay);
    }
    this->mode = DEV_MODE_STANDBY;
    return true;
};
int JMDevice::getMode()
{
    return this->mode;
};
void JMDevice::calibrate()
{
    if (this->mode == DEV_MODE_RUNNING)
        this->ir->sendIr(this->irRun);
    else
        this->ir->sendIr(this->irShutDown);
};