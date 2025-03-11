#include "mqttControl.hpp"
#include <PubSubClient.h>
#include <WiFi.h>

// wifi connection
WiFiClient ESP_CLIENT;
const char* WIFI_SSID = "to-be-defined";        //----------------- TO REMOVE (definition) ----------------- 
const char* WIFI_PASSWORD = "to-be-defined";    //----------------- TO REMOVE (definition) -----------------
const char* WIFI_HOSTNAME = "to-be-defined";    // (if no work -> use String) ----------------- TO REMOVE (definition) -----------------

// mqtt connection
PubSubClient MQTT_CLIENT(ESP_CLIENT);
const char* MQTT_CLIENT_NAME = "to-be-defined";    //----------------- TO REMOVE (definition) -----------------
const char* MQTT_USER = "to-be-defined";        //----------------- TO REMOVE (definition) -----------------
const char* MQTT_PASSWORD = "to-be-defined";    //----------------- TO REMOVE (definition) -----------------
const char* MQTT_SERVER = "to-be-defined";      //----------------- TO REMOVE (definition) -----------------

bool mqttControl::wifiConnect(){
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(WIFI_HOSTNAME);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);


    Serial.println("MQTTCONTROL: Attempting wifi connection..");

    if (WiFi.status() == WL_CONNECTED){
        Serial.println("MQTTCONTROL: Wifi connection -> succeeded");
        Serial.print("MQTTCONTROL: IP ->");
        Serial.println(WiFi.localIP());

        return 1;
    }
    else if (!WiFi.status() == WL_CONNECTED){
        Serial.println("MQTTCONTROL: Wifi connection -> failed");
        Serial.println("MQTTCONTROL: Retrying in 1 second");
        delay(1000);

        return 0;
    }
    else {Serial.println("MQTTCONTROL: Unknown wifi connection error"); return 0;}
    Serial.println("");

}

bool mqttControl::mqttConnect(){
    while (!MQTT_CLIENT.connected()){
        Serial.println("MQTTCONTROL: Attempting mqtt connection..");

        if (MQTT_CLIENT.connect("ESP_CLIENT")){
            Serial.println("MQTTCONTROL: Broker connection -> succeeded");

            MQTT_CLIENT.subscribe("to-be-defined");    //----------------- TO REMOVE (definition) -----------------
            Serial.println("MQTTCONTROL: Subscribed to topic -> to-be-defined");    //----------------- TO REMOVE (definition) -----------------

            return 1;
        }
        else if (!MQTT_CLIENT.connect("ESP_CLIENT")){
            Serial.println("MQTTCONTROL: Broker connection -> falied");
            Serial.print("MQTTCONTROL: Error code -> ");
            Serial.println(MQTT_CLIENT.state());
            Serial.println("");

            for (int i=5; i>=0; i--){// counter 
                Serial.print("MQTTCONTROL: Retrying in: ");
                Serial.print(i);
                Serial.println(" seconds");
                delay(1000);

            }

            Serial.println("");

            return 0;
        }
        else {Serial.println("MQTTCONTROL: Unknown mqtt connection error"); return 0;}
        Serial.println("");

    }
    Serial.println("MQTTCONTROL: connection lost"); return 0;
    Serial.println("");

}

void mqttControl::mqttMessageReceave(){

}

void mqttControl::mqttMessageSend(){

}
