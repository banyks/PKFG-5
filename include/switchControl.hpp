#pragma once

class switchControl{
    public:
        static const int SWITCH1;
        static const int SWITCH2;
        static const int SWITCH3;
        static const int SWITCH4;

        static void switchSetup();
        static bool switchValue(int switchToRead);

};
