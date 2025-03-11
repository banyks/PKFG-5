#include "oledDisplayControl.hpp"
#include "oledDisplayPresets.hpp"
#include "mqttControl.hpp"

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

const char displayControl::DISPLAY_WIDTH = 128;
const char displayControl::DISPLAY_HEIGHT = 64;
const char displayControl::RESET_PIN = -1;
const int animationTime = 50;

Adafruit_SSD1306 display(displayControl::DISPLAY_WIDTH, displayControl::DISPLAY_HEIGHT, &Wire, displayControl::RESET_PIN);

void displayControl::displayStartup(){
    // Start display
    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
        Serial.println(F("DISPLAYCONTROL: SSD1306 allocation failed"));
        delay(1000);
    }

    else if(display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
        Serial.println(F("DISPLAYCONTROL: SSD1306 allocation successfull"));
        delay(1000);
        displayControl::displayStartupAnimation();

    }

    else{
        Serial.println(F("DISPLAYCONTROL: Unknown startup error"));
        delay(1000);
    }

}
    
void displayControl::displayStartupAnimation() {

    display.clearDisplay();
    display.drawBitmap(0, 0, animationPresets::beanAnimationFrame1, 128, 64, 1);
    display.display();
    delay(5000);
    
    display.clearDisplay();
    display.drawBitmap(0, 0, animationPresets::beanAnimationFrame2, 128, 64, 1);
    display.display();
    delay(animationTime);

    display.clearDisplay();
    display.drawBitmap(0, 0, animationPresets::beanAnimationFrame3, 128, 64, 1);
    display.display();
    delay(animationTime);

    display.clearDisplay();
    display.drawBitmap(0, 0, animationPresets::beanAnimationFrame4, 128, 64, 1);
    display.display();
    delay(animationTime);
    
    
    display.clearDisplay();
    display.drawBitmap(0, 0, animationPresets::beanAnimationFrame5, 128, 64, 1);
    display.display();
    delay(animationTime);
    
    display.clearDisplay();
    display.drawBitmap(0, 0, animationPresets::beanAnimationFrame6, 128, 64, 1);
    display.display();
    delay(animationTime);
    
    display.clearDisplay();
    display.drawBitmap(0, 0, animationPresets::beanAnimationFrame7, 128, 64, 1);
    display.display();
    delay(animationTime);
    
}

void beanAnimationFrame8(){
    display.clearDisplay();    
    display.drawBitmap(0, 0, animationPresets::beanAnimationFrame8, 128, 64, 1);
    display.display();
    delay(animationTime);
}

void displayControl::displayLoadUpConnections(){
    beanAnimationFrame8();
    displayControl::displayText("- GRUPPE 5 -");
    delay(1000);

    displayControl::displayText("WIFI connectieren");
    if (true/*mqttControl::wifiConnect()*/){            //----------------- TO REMOVE (comment and true) -----------------
        displayControl::displayText("WIFI connectiert..");
        delay(1000);
    }
    else if(!mqttControl::wifiConnect()){
        displayControl::displayText("WIFI fehlerhaft..");
        delay(1000);

    }
    
    

    displayControl::displayText("MQTT connectieren");
    if (true/*mqttControl::mqttConnect()*/){            //----------------- TO REMOVE (comment and true) -----------------
        displayControl::displayText("MQTT connectiert..");
        delay(1000);
    }
    else if(!mqttControl::mqttConnect()){
        displayControl::displayText("MQTT fehlerhaft..");
        delay(1000);

    }

}

int displayControl::displayText(const char* text){
    
    // zu ueberartbeiten
    int textlenght = strlen(text);
    int textCenterPosition = (displayControl::DISPLAY_WIDTH - textlenght)/2;
    //Serial.println(textCenterPosition);         //----------------- TO REMOVE (comment) ----------------- 

    beanAnimationFrame8();
    display.setCursor(textCenterPosition,50);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.println(text);
    display.display();

    return textCenterPosition;
}

