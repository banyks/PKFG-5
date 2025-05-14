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

  displayControl::displayStartup();
  displayControl::displayLoadUpConnections();

}
// if the second sensor detected, motor continues normally
// if fist detected alone, motor stops shortly then proceeds
// if second detects, then shortly after first detects, 
// motor stop at first, then proceeds slowly until second, then stops a litle longer, then proceeds
bool motorStatus = false;
void loop() {
  mqttControl::mqttLoop();

  // Manual control of motor 3 and 4
  if (!motorStatus && mqttControl::manualMode && mqttControl::motor3cw && mqttControl::emergencyStop) {
    if (mqttControl::motor3Speed == 0) {
      motorControl::motorRun(1, "clockwise", 10, mqttControl::motor3Speed);
    } else {
      motorControl::motorRun(1, "clockwise", 10, 220);
    }
    motorStatus = true;
    Serial.println("Motor 3 cw");
  }
  else if (motorStatus && mqttControl::manualMode && !mqttControl::motor4cw && mqttControl::emergencyStop) {
    if (mqttControl::motor4Speed == 0) {
      motorControl::motorRun(2, "clockwise", 10, mqttControl::motor4Speed);
    } else {
      motorControl::motorRun(2, "clockwise", 10, 220);
    }
    motorStatus = true;
    Serial.println("Motor 4 cw");
  }
  else if (!motorStatus && mqttControl::manualMode && mqttControl::motor3ccw && mqttControl::emergencyStop) {
    if (mqttControl::motor3Speed == 0) {
      motorControl::motorRun(1, "counterclockwise", 10, mqttControl::motor3Speed);
    } else {
      motorControl::motorRun(1, "counterclockwise", 10, 220);
    }
    motorStatus = true;
    Serial.println("Motor 3 ccw");
  }
  else if (motorStatus && mqttControl::manualMode && mqttControl::motor4ccw && mqttControl::emergencyStop) {
    if (mqttControl::motor4Speed == 0) {
      motorControl::motorRun(2, "counterclockwise", 10, mqttControl::motor4Speed);
    } else {
      motorControl::motorRun(2, "counterclockwise", 10, 220);
    }

    motorStatus = true;
    Serial.println("Motor 4 ccw");
  } // Motor stop
  else if (motorStatus && mqttControl::manualMode && !mqttControl::motor3ccw && !mqttControl::motor3cw  && mqttControl::emergencyStop) {
    if (mqttControl::motor3Speed == 0) {
      motorControl::motorStop(1, 0, 10, mqttControl::motor3Speed);
    } else {
      motorControl::motorStop(1, 0, 10, 220);
    }
    motorStatus = false;
    Serial.println("Motor 3 stopped");
  }
  else if (motorStatus && mqttControl::manualMode && !mqttControl::motor4ccw && !mqttControl::motor4cw && mqttControl::emergencyStop) {
    if (mqttControl::motor4Speed == 0) {
      motorControl::motorStop(2, 0, 10, mqttControl::motor4Speed);
    } else {
      motorControl::motorStop(2, 0, 10, 220);
    }
    motorStatus = false;
    Serial.println("Motor 3 stopped");
  } // Motor emergency stop
  else if(motorStatus && !mqttControl::emergencyStop){
    motorControl::motorStop(0, 1, 0, 0);
    motorStatus = false;
    Serial.println("Motors stopped");

  }

  // Automatic control of motor 3 and 4
  if (!mqttControl::manualMode && mqttControl::emergencyStop){
    motorControl::motorRun(1, "clockwise", 10, 180);
    delay(1000);
    motorControl::motorRun(2, "clockwise", 10, 180);


  }

}
