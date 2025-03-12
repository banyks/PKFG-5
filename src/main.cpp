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






#include <Arduino.h>  //Framework

#include <Wire.h>     //display
#include <SPI.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include <WiFi.h>     //NodeRed
//#include <PubSubClient.h>

#include "oledDisplayPresets.hpp" //classes
#include "oledDisplayControl.hpp" 


//----------------- TO REMOVE (TESTTESTTEST) -----------------
#define lr 12
#define ly 14
#define lg 27

#define s1 36
#define s2 39
#define s3 34
#define s4 35

#define p1 32


void setup() {
  Serial.begin(115200);

  // Start the display
  //displayControl display;
  pinMode(lr, OUTPUT);
  pinMode(ly, OUTPUT);
  pinMode(lg, OUTPUT);

  pinMode(s1, INPUT);
  pinMode(s2, INPUT);
  pinMode(s3, INPUT);
  pinMode(s4, INPUT);
  pinMode(p1, INPUT);


  //displayControl::displayStartup();
  //displayControl::displayLoadUpConnections();

  

}

void loop() {

  Serial.println("----------------------------------------"); 
  Serial.println("s1"); 
  Serial.println(digitalRead(s1)); 
  digitalWrite(lr, digitalRead(s1));
  Serial.println("s2"); 
  Serial.println(digitalRead(s2)); 
  digitalWrite(ly, digitalRead(s2));
  Serial.println("s3"); 
  Serial.println(digitalRead(s3)); 
  digitalWrite(lg, digitalRead(s3));
  Serial.println("s4"); 
  Serial.println(digitalRead(s4)); 

  Serial.println("p1"); 
  Serial.println(analogRead(p1)); 
  

  

  delay(1000);

}
//----------------- TO REMOVE (TESTTESTTEST) -----------------
