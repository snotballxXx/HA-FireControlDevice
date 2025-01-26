/*                                                                    
 _______ _                ______                            _ 
(_______|_)              / _____)           _              | |
 _____   _  ____ ____   | /      ___  ____ | |_   ____ ___ | |
|  ___) | |/ ___) _  )  | |     / _ \|  _ \|  _) / ___) _ \| |
| |     | | |  ( (/ /   | \____| |_| | | | | |__| |  | |_| | |
|_|     |_|_|   \____)   \______)___/|_| |_|\___)_|   \___/|_|
 _  _  _                           _____    __    ______  _       _ 
| || || |                         (____ \  /  |  |  ___ \(_)     (_)
| || || | ____ ____   ___   ___    _   \ \/_/ |  | | _ | |_ ____  _ 
| ||_|| |/ _  )    \ / _ \ /___)  | |   | | | |  | || || | |  _ \| |
| |___| ( (/ /| | | | |_| |___ |  | |__/ /  | |  | || || | | | | | |
 \______|\____)_|_|_|\___/(___/   |_____/   |_|  |_||_||_|_|_| |_|_|
 Created by http://www.network-science.de/ascii/ (stop)
	   
  Pin Out                        _______________	   
                                (               )
                               (       ____      )
                          RST  | o    |    |   o | TX
                          A0   | o    |____|   o | RX
                          D0   | o             o | D1
                          D5   | o             o | D2 ---- IR LED
                          D6   | o             o | D3
                          D7   | o             o | D4
                          D8   | o             o | GND
                          3v3  | o             o | 5v
                               |      _____      |
                               (     |     |     )
                                (____|     |____)
                                     |_____|

This project sends a IR output to an IR LED to control a fire (Real Flame RF XLF50 - 74 - 100)
It connects to MQTT to get commands from HA. Firemware updates are remote via Elegant OTA via http://<HOST IP>/update
*/

#include <Arduino.h>
#include "./control/HomeAssistantMqtt.h"
#include "./control/Wifi.h"
#include "./control/IRSender.h"
#include "./control/Ota.h"
#include "constants.h"

Control::Wifi* wifi = new Control::Wifi();
Control::HomeAssistantMqtt* homeAssistant = new Control::HomeAssistantMqtt();
Control::IRSender* irSender = new Control::IRSender(homeAssistant);
Control::Ota* ota = new Control::Ota();

void setup()
{
    Serial.begin(SERIAL_BAUD_RATE);
    
    wifi->setup();
    homeAssistant->setup();
    irSender->setup();
    ota->setup();
}

void loop()
{
    unsigned long now = millis();

    wifi->loop(now);
    homeAssistant->loop(now);
    irSender->loop(now);
    ota->loop(now);
}