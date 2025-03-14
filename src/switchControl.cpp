#include "switchControl.hpp"
#include <Arduino.h>

const int switchControl::SWITCH1 = 36;
const int switchControl::SWITCH2 = 39;
const int switchControl::SWITCH3 = 34;
const int switchControl::SWITCH4 = 35;

void switchControl::switchSetup(){
    pinMode(switchControl::SWITCH1, INPUT);
    pinMode(switchControl::SWITCH2, INPUT);
    pinMode(switchControl::SWITCH3, INPUT);
    pinMode(switchControl::SWITCH4, INPUT);

}

bool switchControl::switchValue(int switchToRead){
    switch (switchToRead){
        case 1:
            return digitalRead(switchControl::SWITCH1);
            break;
        case 2:
            return digitalRead(switchControl::SWITCH2);
            break;
        case 3:
            return digitalRead(switchControl::SWITCH3);
            break;
        case 4:
            return digitalRead(switchControl::SWITCH4);
            break;
        default:
            Serial.println("SWITCHCONTROL: Unknown switch");
            return false;
            break;
    }
}