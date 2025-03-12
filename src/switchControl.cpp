#include "switchControl.hpp"
#include <Arduino.h>

const int switchControl::SWITCH1 = 36;
const int switchControl::SWITCH2 = 39;
const int switchControl::SWITCH3 = 34;
const int switchControl::SWITCH4 = 35;

void switchSetup(){
    pinMode(switchControl::SWITCH1, INPUT);
    pinMode(switchControl::SWITCH2, INPUT);
    pinMode(switchControl::SWITCH3, INPUT);
    pinMode(switchControl::SWITCH4, INPUT);

}

bool switchControl::switchValue(int switchToRead){
    switch (switchToRead){
        case 36:
            return digitalRead(switchControl::SWITCH1);
            break;
        case 39:
            return digitalRead(switchControl::SWITCH2);
            break;
        case 34:
            return digitalRead(switchControl::SWITCH3);
            break;
        case 35:
            return digitalRead(switchControl::SWITCH4);
            break;
        default:
            return false;
            break;
    }
}