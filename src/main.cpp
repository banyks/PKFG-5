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

bool placeholder1; // start
bool placeholder2; // sensor 1
bool placeholder3; // sensor 24

void setup() {
  Serial.begin(115200);
  motorControl::motorSetup();
  ledControl::ledSetup();
  switchControl::switchSetup();

  //displayControl::displayStartup();
  //displayControl::displayLoadUpConnections();

}

void loop() {

}
