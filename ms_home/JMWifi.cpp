#include "JMWifi.h"

JMWifi::JMWifi()
{
    this->wifi = new SoftwareSerial(10, 11);
};
void JMWifi::setup()
{
    this->wifi->begin(115200);
    this->wifi->setTimeout(10000);
    Serial.println("Checking wifi connection");
    // delay(1000);

    do
    {
        Serial.println(" Connecting... ");
        this->wifi->println("AT+RST");
        // delay(1000);
        if (this->wifi->find("WIFI GOT IP"))
            break;
        // delay(10000);
    } while (!this->wifi->find("WIFI GOT IP"));

    // Serial.println(this->wifi->);
    Serial.println(" Wifi connected ");

    // delay(1000);

    Serial.println("Ready!");
};
bool JMWifi::sendHttp(String url, char *findResult)
{
    String cmd = "AT+CIPSTART=\"TCP\",";
    cmd += "\"192.168.1.3\"";
    cmd += ",8080";
    this->wifi->println(cmd);
    Serial.println(cmd);
    if (this->wifi->find("Error"))
    {
        Serial.println("http Error");
        return false;
    }
    cmd = "GET " + url;
    cmd += "HTTP/1.1";
    cmd += "\r\n";
    this->wifi->print("AT+CIPSEND=");
    this->wifi->println(cmd.length());
    // delay(2000);
    if (this->wifi->find(">"))
    {
        Serial.print(">");
    }
    else
    {
        this->wifi->println("AT+CIPCLOSE");
        Serial.println("Timed out");
        // delay(1000);
        return;
    }
    this->wifi->print(cmd);
    // delay(2000);

    while (this->wifi->available())
    {
        char c = this->wifi->read();
        Serial.write(c);
        if (c == '\r')
            Serial.print('\n');
    }
    Serial.println("—–end");
    // delay(10000);
};