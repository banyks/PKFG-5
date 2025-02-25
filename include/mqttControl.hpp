#pragma once

class   mqttControl{
    public:
        char* displayMessage;

        static bool wifiConnect();
        static bool mqttConnect();
        static void mqttMessageReceave();
        static void mqttMessageSend();

};