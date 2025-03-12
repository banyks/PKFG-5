#include "motorControl.hpp"

#include <Arduino.h>

const int motorControl::MOTOR1_ENA = 19;
const int motorControl::MOTOR1_IN1 = 5;
const int motorControl::MOTOR1_IN2 = 17;

const int motorControl::MOTOR2_ENB = 18;
const int motorControl::MOTOR2_IN3 = 16;
const int motorControl::MOTOR2_IN4 = 4;

const int motorControl::POTENTIOMETER1 = 32;
const int motorControl::VCC = 23;

void motorControl::motorSetup(){
    pinMode(motorControl::MOTOR1_ENA, OUTPUT);
    pinMode(motorControl::MOTOR1_IN1, OUTPUT);
    pinMode(motorControl::MOTOR1_IN2, OUTPUT);

    pinMode(motorControl::MOTOR2_ENB, OUTPUT);
    pinMode(motorControl::MOTOR2_IN3, OUTPUT);
    pinMode(motorControl::MOTOR2_IN4, OUTPUT);

    pinMode(motorControl::POTENTIOMETER1, OUTPUT);
    pinMode(motorControl::VCC, OUTPUT);

    digitalWrite(motorControl::VCC, 1);
}

void motorControl::run(int motor, const char* direction, unsigned int speed){


    //----


}

void motorControl::stop(int motor, unsigned int speed){


}