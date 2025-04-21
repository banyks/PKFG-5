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

const int pwmChannel1 = 0; // motor 1
const int pwmChannel2 = 1; // motor 2
const int pwmFrequency = 10000;
const int pwmResolution = 8;

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

    ledcSetup(pwmChannel1, pwmFrequency, pwmResolution);
    ledcSetup(pwmChannel2, pwmFrequency, pwmResolution);
    ledcAttachPin(motorControl::MOTOR1_ENA, pwmChannel1);
    ledcAttachPin(motorControl::MOTOR2_ENB, pwmChannel2);
}

void motorControl::motorRun(int motor, const char* direction, unsigned int pwmSpeed, unsigned int motorSpeed){
    switch(motor){
        case 1:
            if (strcmp(direction, "clockwise") == 0 && pwmSpeed == 0){
                digitalWrite(motorControl::MOTOR1_IN1, 1);
                digitalWrite(motorControl::MOTOR1_IN2, 0);
                ledcWrite(pwmChannel1, motorSpeed);
            }
            if (strcmp(direction, "clockwise") && pwmSpeed != 0){
                digitalWrite(motorControl::MOTOR1_IN1, 1);
                digitalWrite(motorControl::MOTOR1_IN2, 0);

                for(int i=0; i<=motorSpeed; i++){
                    ledcWrite(pwmChannel1, i);
                    delay(pwmSpeed);
                }
                ledcWrite(pwmChannel1, motorSpeed);

            }
            if (strcmp(direction, "counterclockwise") && pwmSpeed == 0){
                digitalWrite(motorControl::MOTOR1_IN1, 0);
                digitalWrite(motorControl::MOTOR1_IN2, 1);
                ledcWrite(pwmChannel1, motorSpeed);
            }
            if (strcmp(direction, "counterclockwise") && pwmSpeed != 0){
                digitalWrite(motorControl::MOTOR1_IN1, 0);
                digitalWrite(motorControl::MOTOR1_IN2, 1);

                for(int i=0; i<=motorSpeed; i++){
                    ledcWrite(pwmChannel1, i);
                    delay(pwmSpeed);
                }
                ledcWrite(pwmChannel1, motorSpeed);

            }
            break;
            
        case 2:
            if (strcmp(direction, "clockwise") && pwmSpeed == 0){
                digitalWrite(motorControl::MOTOR2_IN3, 1);
                digitalWrite(motorControl::MOTOR2_IN4, 0);
                ledcWrite(pwmChannel2, motorSpeed);
            }
            if (strcmp(direction, "clockwise") && pwmSpeed != 0){
                digitalWrite(motorControl::MOTOR2_IN3, 1);
                digitalWrite(motorControl::MOTOR2_IN4, 0);

                for(int i=0; i<=motorSpeed; i++){
                    ledcWrite(pwmChannel2, i);
                    delay(pwmSpeed);
                }
                ledcWrite(pwmChannel2, motorSpeed);

            }
            if (strcmp(direction, "counterclockwise") && pwmSpeed == 0){
                digitalWrite(motorControl::MOTOR2_IN3, 0);
                digitalWrite(motorControl::MOTOR2_IN4, 1);
                ledcWrite(pwmChannel2, motorSpeed);
            }
            if (strcmp(direction, "counterclockwise") && pwmSpeed != 0){
                digitalWrite(motorControl::MOTOR2_IN3, 0);
                digitalWrite(motorControl::MOTOR2_IN4, 1);

                for(int i=0; i<=motorSpeed; i++){
                    ledcWrite(pwmChannel2, i);
                    delay(pwmSpeed);
                }
                ledcWrite(pwmChannel2, motorSpeed);

            }
            break;
        default:
            Serial.println("MOTORCONTROL: Unknown motor");
            break;
    }
}

bool motorControl::motorStop(int motor, bool err, unsigned int pwmSpeed, unsigned int motorSpeed){
    if (err && motor == 0){
        digitalWrite(motorControl::MOTOR1_IN1, 0);
        digitalWrite(motorControl::MOTOR1_IN2, 0);
        digitalWrite(motorControl::MOTOR2_IN3, 0);
        digitalWrite(motorControl::MOTOR2_IN4, 0);
        ledcWrite(pwmChannel1, 0);
        ledcWrite(pwmChannel2, 0);
        return true;

    }

    switch (motor){
        case 1:
            for(int i=motorSpeed; i>=1; i--){
                ledcWrite(pwmChannel1, i);
                delay(pwmSpeed);
            }
            digitalWrite(motorControl::MOTOR1_ENA, 0);
            return true;
            break;
        case 2:
            for(int i=motorSpeed; i>=1; i--){
                ledcWrite(pwmChannel2, i);
                delay(pwmSpeed);
            }
            digitalWrite(motorControl::MOTOR2_ENB, 0);
            return true;
            break;
        default:
            Serial.println("MOTORCONTROL: Unknown motor");
            return false;
            break;

    }

}