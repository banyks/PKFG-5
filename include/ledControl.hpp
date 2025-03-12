#pragma once

class ledControl{
    public:
        static const int LED_RED;
        static const int LED_YELLOW;
        static const int LED_GREEN;
        
        static void ledStartup();
        static void ledOn(const char* led, unsigned int  fade);
        static void ledOff(const char* led, unsigned int fade);



};