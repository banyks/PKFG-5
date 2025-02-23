#pragma once

class displayControl{
    public:
        static const char DISPLAY_WIDTH;
        static const char DISPLAY_HEIGHT;
        static const char RESET_PIN;

        static void displayStartup();
        static void displayStartupAnimation();
        static void displayLoadUpConnections();
        static int centerDisplayText(int width, const char text[]);

};