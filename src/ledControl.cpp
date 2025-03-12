#include "ledControl.hpp"

#include <Arduino.h>

const int LED_RED =     12;
const int LED_YELLOW =  14;
const int LED_GREEN =   27;

void ledControl::ledStartup(){
    pinMode(ledControl::LED_RED,    OUTPUT);
    pinMode(ledControl::LED_YELLOW, OUTPUT);
    pinMode(ledControl::LED_GREEN,  OUTPUT);

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
    if (led == "red" && !fade == 0){
        for(int i=0; i<=255; i++){
            analogWrite(ledControl::LED_RED, i);
            delay(fade);
        }

    }
    if (led == "yellow" && !fade == 0){
        for(int i=0; i<=255; i++){
            analogWrite(ledControl::LED_YELLOW, i);
            delay(fade);
        }

    }
    if (led == "green" && !fade == 0){
        for(int i=0; i<=255; i++){
            analogWrite(ledControl::LED_GREEN, i);
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
    if (led == "red" && !fade == 0){
        for(int i=255; i>=0; i--){
            analogWrite(ledControl::LED_RED, i);
            delay(fade);
        }

    }
    if (led == "yellow" && !fade == 0){
        for(int i=255; i>=0; i--){
            analogWrite(ledControl::LED_YELLOW, i);
            delay(fade);
        }

    }
    if (led == "green" && !fade == 0){
        for(int i=255; i>=0; i--){
            analogWrite(ledControl::LED_GREEN, i);
            delay(fade);
        }

    }
    else{
        Serial.println("LEDCONTROL: Unknown led colour");
    }
    
}
