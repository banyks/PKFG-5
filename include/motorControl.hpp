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
        static void run(int motor, const char* direction, unsigned int speed);
        static void stop(int motor, unsigned int speed);



};