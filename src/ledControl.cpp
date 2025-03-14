#include "ledControl.hpp"

#include <Arduino.h>

const int ledControl::LED_RED =     12;
const int ledControl::LED_YELLOW =  14;
const int ledControl::LED_GREEN =   27;

const int pwmChannel3 = 2;
const int pwmChannel4 = 3;
const int pwmChannel5 = 4;
const int pwmFrequency = 10000;
const int pwmResolution = 8;

void ledControl::ledSetup(){
    pinMode(ledControl::LED_RED,    OUTPUT);
    pinMode(ledControl::LED_YELLOW, OUTPUT);
    pinMode(ledControl::LED_GREEN,  OUTPUT);

    ledcSetup(pwmChannel3, pwmFrequency, pwmResolution);
    ledcSetup(pwmChannel4, pwmFrequency, pwmResolution);
    ledcSetup(pwmChannel5, pwmFrequency, pwmResolution);
    ledcAttachPin(ledControl::LED_RED, pwmChannel3);
    ledcAttachPin(ledControl::LED_YELLOW, pwmChannel4);
    ledcAttachPin(ledControl::LED_GREEN, pwmChannel5);

}

void ledControl::ledOn(const char* led, unsigned int fade){
    fade = fade * 1000; // ms to sec

    // normal state (on)
    if (led == "red" && fade == 0){
        digitalWrite(ledControl::LED_RED, 1);

    }
    if (led == "yellow" && fade == 0){
        digitalWrite(ledControl::LED_YELLOW, 1);

    }
    if (led == "green" && fade == 0){
        digitalWrite(ledControl::LED_GREEN, 1);

    }
    
    // special state (on fade)
    if (led == "red" && fade != 0){
        for(int i=0; i<=255; i++){
            ledcWrite(pwmChannel3, i);
            delay(fade);
        }

    }
    if (led == "yellow" && fade != 0){
        for(int i=0; i<=255; i++){
            ledcWrite(pwmChannel4, i);
            delay(fade);
        }

    }
    if (led == "green" && fade != 0){
        for(int i=0; i<=255; i++){
            ledcWrite(pwmChannel5, i);
            delay(fade);
        }

    }
    else{
        Serial.println("LEDCONTROL: Unknown led colour");
    }

}

void ledControl::ledOff(const char* led, unsigned int fade){
    fade = fade * 1000; // ms to sec

    // normal state (off)
    if (led == "red" && fade == 0){
        digitalWrite(ledControl::LED_RED, 0);

    }
    if (led == "yellow" && fade == 0){
        digitalWrite(ledControl::LED_YELLOW, 0);

    }
    if (led == "green" && fade == 0){
        digitalWrite(ledControl::LED_GREEN, 0);

    }
    
    // special state (off fade)
    if (led == "red" && fade != 0){
        for(int i=255; i>=0; i--){
            ledcWrite(pwmChannel3, i);
            delay(fade);
        }

    }
    if (led == "yellow" && fade != 0){
        for(int i=255; i>=0; i--){
            ledcWrite(pwmChannel4, i);
            delay(fade);
        }

    }
    if (led == "green" && fade != 0){
        for(int i=255; i>=0; i--){
            ledcWrite(pwmChannel5, i);
            delay(fade);
        }

    }
    else{
        Serial.println("LEDCONTROL: Unknown led colour");
    }
    
}
