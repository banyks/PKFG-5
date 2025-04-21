#pragma once

class   mqttControl{
    public:
        static bool emergencyStop;

        static bool manualMode;
        static bool motor3run;
        static bool motor4run;


        static bool wifiConnect();
        static bool mqttConnect();
        static void mqttMessageReceave();
        static void mqttMessageSend();
        static void mqttLoop();


};