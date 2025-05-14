#pragma once

class   mqttControl{
    public:
        static bool emergencyStop;

        static bool manualMode;
        static bool motor3ccw;
        static bool motor3cw;
        static int motor3Speed;
        static bool motor4ccw;
        static bool motor4cw;
        static int motor4Speed;
        static bool goodQuality;
        static bool badQuality;



        static bool wifiConnect();
        static bool mqttConnect();
        static void mqttMessageReceave();
        static void mqttMessageSend();
        static void mqttLoop();


};