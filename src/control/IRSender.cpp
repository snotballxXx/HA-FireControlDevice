#include <Arduino.h>
#include "./IRSender.h"
#include "../interfaces/IMessenger.h"
#include "../constants.h"
#define IR_SEND_PIN D2
#include <IRremote.hpp>

using namespace Control;

//https://developers.home-assistant.io/docs/core/entity/button
//https://www.home-assistant.io/integrations/button#device-class
/*
                 _____0x81____
                /    POWER    \
               /               \
              /                 \
         0x82 |FLAME        HEAT| 0xD4
              |                 |
         0x94 |TEMP-       TEMP+| 0x95
              |                 |
         0x83 |ECO         BOOST| 0x96
		      |                 |
         0xC0 |COLOR  BRIGHTNESS| 0x97
              |                 |
              |                 |
              \______TIMER______/
                      0x80
*/

IRSender::IRSender(Interfaces::IMessenger* messenger) :
_messenger(messenger)
{
}

void IRSender::setup()
{
    Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));
    Serial.print(F("Send IR signals at pin "));
    Serial.println(IR_SEND_PIN);

    _messenger->subscribe(COMMAND_TOPIC, this);

    IrSender.begin();
    disableLEDFeedback();
}

void IRSender::messageReceived(const String &topic, const String &payload)
{
    Serial.print("Got message: ");
    Serial.println(payload);

    if (payload == "1") 
        IrSender.sendNEC(0x00, 0x81, 0);//POWER

    else if (payload == "2") 
        IrSender.sendNEC(0x00, 0xD4, 0);//HEAT

    else if (payload == "3") 
        IrSender.sendNEC(0x00, 0x82, 0);//FLAME

    else if (payload == "4") 
        IrSender.sendNEC(0x00, 0x95, 0);//TEMP+

    else if (payload == "5") 
        IrSender.sendNEC(0x00, 0x94, 0);//TEMP-

    else if (payload == "6") 
        IrSender.sendNEC(0x00, 0x83, 0);//ECO

    else if (payload == "7") 
        IrSender.sendNEC(0x00, 0x96, 0);//BOOST

    else if (payload == "8") 
        IrSender.sendNEC(0x00, 0xC0, 0);//COLOR

    else if (payload == "9") 
        IrSender.sendNEC(0x00, 0x97, 0);//BRIGHTNESS

    else if (payload == "10") 
        IrSender.sendNEC(0x00, 0x80, 0);//TIMER
}

void IRSender::loop(unsigned long time)
{
}