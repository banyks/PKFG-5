// Copyright © 2025 LPEM.

// Projekt: ESP32 zu © Siemens S7-1500 SPS Kommunikation
// Autor:   Ezechiele Ayena
// Datum:   02.2025

// Beschreibung:
//          Dieses Programm dient dazu, über das NodeRed-Protokoll eine Verbindung 
//          zwischen einem ESP32-Mikrocontroller und einer Siemens S7 1500 SPS 
//          herzustellen. Zusätzlich werden über das Dashboard Aktoren gesteuert.

// Lizenz:  Dieses Programm ist freie Software unter der GNU GPL v3.
//          Details unter: <http://www.gnu.org/licenses/>






#include <Arduino.h>  // Framework

#include <Wire.h>     // Display
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <WiFi.h>     // NodeRed
//#include <PubSubClient.h>

#include "oledDisplayPresets.hpp" // Header files
#include "oledDisplayControl.hpp" 
#include "mqttControl.hpp"
#include "motorControl.hpp"
#include "ledControl.hpp"
#include "switchControl.hpp"  

void setup() {
  Serial.begin(115200);
  motorControl::motorSetup();
  ledControl::ledSetup();
  switchControl::switchSetup();

  delay(100);

  //displayControl::displayStartup();
  //displayControl::displayLoadUpConnections();

}
// if the second sensor detected, motor continues normally
// if fist detected alone, motor stops shortly then proceeds
// if second detects, then shortly after first detects, 
// motor stop at first, then proceeds slowly until second, then stops a litle longer, then proceeds

void loop() {

  if (switchControl::switchValue(1)){
    Serial.println("m1 run");
    motorControl::motorRun(1, "clockwise", 10, 50);
    delay(5000);
    Serial.println("m1 stop");
    motorControl::motorStop(1, 0, 10, 50);
    delay(1000);


    //motorControl::motorRun(2, "counterclockwise", 10, 168);
    /*if (switchControl::switchValue(3))
      motorControl::motorRun(2, "counterclockwise", 0, 168);*/

  }



}
