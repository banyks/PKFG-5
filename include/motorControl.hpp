#pragma once

class motorControl{
    public:
        static const int MOTOR1_ENA;
        static const int MOTOR1_IN1;
        static const int MOTOR1_IN2;

        static const int MOTOR2_ENB;
        static const int MOTOR2_IN3;
        static const int MOTOR2_IN4;

        static const int POTENTIOMETER1;
        static const int VCC;

        static void motorSetup();
        static bool motorRun(int motor, const char* direction, unsigned int pwmSpeed, unsigned int motorSpeed);
        static bool motorStop(int motor, bool err, unsigned int pwmSpeed, unsigned int motorSpeed);



};