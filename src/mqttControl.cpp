#include "mqttControl.hpp"
#include <PubSubClient.h>
#include <WiFi.h>

// wifi connection (test)
WiFiClient ESP_CLIENT;
const char* WIFI_SSID = /*"FRITZ!Box 7530 DW_EXT"*/"Alt_F4";
const char* WIFI_PASSWORD = /*"76089546061926253871"*/"cplusplus";   
const char* WIFI_HOSTNAME = "ESP32_GRUPPE5";
// wifi connection
IPAddress local_IP(192, 168, 8, 192);
IPAddress gateway(192, 168, 8, 1);
IPAddress subnet(255, 255, 0, 0);
// make it so that if swtch 1 pressed, you use pc keyboard to connect to wifi

// mqtt connection
PubSubClient MQTT_CLIENT(ESP_CLIENT);
const char* MQTT_SERVER = "192.168.178.107";
const int MQTT_PORT = 1883;
const char* MQTT_USER = "";
const char* MQTT_PASSWORD = "";

// Topics
const char* TOPIC_SUB_MOTOR = "esp32/motorCommand";
const char* TOPIC_SUB_MOTOR_SPEED1 = "esp32/motor3Speed";
const char* TOPIC_SUB_MOTOR_SPEED2 = "esp32/motor4Speed";
const char* TOPIC_SUB_MOTORMODE = "esp32/motorMode";
const char* TOPIC_SUB_NOTAUS = "esp32/notaus";
const char* TOPIC_SUB_SENSORSTATUS = "esp32/sensorStatus";
const char* TOPIC_SUB_GENERAL = "esp32/generalCommand";

const char* TOPIC_PUB_MOTOR = "esp32/status";

// Variables
bool mqttControl::emergencyStop = false;
bool mqttControl::manualMode = false;
bool mqttControl::motor3ccw = false;
bool mqttControl::motor3cw = false;
int mqttControl::motor3Speed = 0;
bool mqttControl::motor4ccw = false;
bool mqttControl::motor4cw = false;
int mqttControl::motor4Speed = 0;
bool mqttControl::goodQuality = false;
bool mqttControl::badQuality = false;


bool mqttControl::wifiConnect() {
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(WIFI_HOSTNAME);

    bool connected = false;

    do {
        Serial.println("MQTTCONTROL: Attempting wifi connection..");
        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

        unsigned long startTime = millis();
        while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
            delay(500);
            Serial.print(".");
        }
        Serial.println();

        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("MQTTCONTROL: Wifi connection -> succeeded");
            Serial.print("MQTTCONTROL: IP -> ");
            Serial.println(WiFi.localIP());
            connected = true;
        } else {
            switch (WiFi.status()) {
                case WL_CONNECT_FAILED:
                    Serial.println("MQTTCONTROL: Wifi connection -> failed");
                    break;
                case WL_NO_SSID_AVAIL:
                    Serial.println("MQTTCONTROL: Wifi connection -> SSID not available");
                    break;
                case WL_CONNECTION_LOST:
                    Serial.println("MQTTCONTROL: Wifi connection -> connection lost");
                    break;
                case WL_DISCONNECTED:
                    Serial.println("MQTTCONTROL: Wifi connection -> disconnected");
                    break;
                default:
                    Serial.print("MQTTCONTROL: Unknown wifi connection error: ");
                    Serial.println(WiFi.status());
            }

            Serial.println("MQTTCONTROL: Retrying in 60 seconds...");
            delay(60000);
        }

    } while (!connected);

    return true;
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("MQTTCONTROL: Message arrived (from: ");
    Serial.print(topic);
    Serial.print("): ");
    
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    
    Serial.println(message);
    
    // Emergency stop
    if (strcmp(topic, TOPIC_SUB_NOTAUS) == 0 || strcmp(topic, TOPIC_SUB_GENERAL) == 0) {

        if (strcmp(message, "1") == 0 || strcmp(message, "NA") == 0) {
            Serial.println("MQTTCONTROL: EMERGENCY STOP activated");
            mqttControl::emergencyStop = 0;
            mqttControl::motor3ccw = 0;
            mqttControl::motor3cw = 0;
            mqttControl::motor4ccw = 0;
            mqttControl::motor4cw = 0;
        }
        else if (strcmp(message, "0") == 0 || strcmp(message, "NA-") == 0) {
            Serial.println("MQTTCONTROL: EMERGENCY STOP deactivated");
            mqttControl::emergencyStop = 1;
        }
        else {
            Serial.println("MQTTCONTROL: Received unknown command");
        }
    } // Running mode
    else if (strcmp(topic, TOPIC_SUB_MOTORMODE) == 0 || strcmp(topic, TOPIC_SUB_GENERAL) == 0 && strcmp(message, "MODE") == 0) {

        if (strcmp(message, "HAND") == 0 || strcmp(message, "HND") == 0) {
            Serial.println("MQTTCONTROL: Motors running mode: MANUAL");
            mqttControl::manualMode = true;
        }
        else if (strcmp(message, "AUTO") == 0 || strcmp(message, "ATO") == 0) {
            Serial.println("MQTTCONTROL: Motors running mode: AUTOMATIC");
            mqttControl::manualMode = false;
        }
        else {
            Serial.println("MQTTCONTROL: Received unknown command");
        }
    } // Motor control
    else if (strcmp(topic, TOPIC_SUB_MOTOR) == 0) {

        // Motor in 'Handbetrieb' ccw
        if (strcmp(message, "M3-LL") == 0) {
            Serial.println("MQTTCONTROL: Motor 3 ccw");
            mqttControl::motor3ccw = 1;

        }
        else if (strcmp(message, "M4-LL") == 0) {
            Serial.println("MQTTCONTROL: Motor 4 ccw");
            mqttControl::motor4ccw = 1;

        }
        // Motor in 'Handbetrieb' cw
        else if (strcmp(message, "M3-RL") == 0) {
            Serial.println("MQTTCONTROL: Motor 3 cw");
            mqttControl::motor3cw = 0;

        }
        else if (strcmp(message, "M4-RL") == 0) {
            Serial.println("MQTTCONTROL: Motor 4 cw");
            mqttControl::motor4cw = 0;

        }
        else {
            Serial.println("MQTTCONTROL: Received unknown command");
        }
    }
    else if(strcmp(topic, TOPIC_SUB_MOTOR_SPEED1) == 0){
        mqttControl::motor3Speed = atoi(message);
        Serial.print("MQTTCONTROL: Motor 3 speed: ");
        Serial.println(mqttControl::motor3Speed);

    }
    else if(strcmp(topic, TOPIC_SUB_MOTOR_SPEED2) == 0){
        mqttControl::motor4Speed = atoi(message);
        Serial.print("MQTTCONTROL: Motor 4 speed: ");
        Serial.println(mqttControl::motor4Speed);
    
    }
    else if(strcmp(topic, TOPIC_SUB_SENSORSTATUS) == 0){
        if(strcmp(message, "Q-GUT") == 0){
            mqttControl::goodQuality = true;
            Serial.println("MQTTCONTROL: Sensor status: good quality");
        }
        else if(strcmp(message, "Q-SCHT") == 0){
            mqttControl::badQuality = true;
            Serial.println("MQTTCONTROL: Sensor status: bad quality");
        }
        else{
            Serial.println("MQTTCONTROL: Received unknown command");
        }
    
    }
    else if(strcmp(topic, TOPIC_SUB_GENERAL) == 0){


    }
    else {

        Serial.println("MQTTCONTROL: ?");


    }
}

bool mqttControl::mqttConnect() {
    // Configure the MQTT broker
    MQTT_CLIENT.setServer(MQTT_SERVER, MQTT_PORT);
    MQTT_CLIENT.setBufferSize(516);
    MQTT_CLIENT.setCallback(mqttCallback);  

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("MQTTCONTROL: WiFi not connected. Cannot connect to MQTT broker.");
        return false;
    }

    Serial.println("MQTTCONTROL: Connecting to MQTT broker...");

    while (!MQTT_CLIENT.connected()) {
        // Create a unique client ID for this session
        String clientId = "ESP32-" + String(random(0xFFFF), HEX);

        if (MQTT_CLIENT.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
            Serial.println("MQTTCONTROL: Connected to broker");
            
            // Subscribe to BOTH topics
            bool sub1 = MQTT_CLIENT.subscribe(TOPIC_SUB_MOTOR);
            bool sub2 = MQTT_CLIENT.subscribe(TOPIC_SUB_MOTORMODE);
            bool sub3 = MQTT_CLIENT.subscribe(TOPIC_SUB_NOTAUS);
            bool sub4 = MQTT_CLIENT.subscribe(TOPIC_SUB_SENSORSTATUS);
            bool sub5 = MQTT_CLIENT.subscribe(TOPIC_SUB_GENERAL); 
            bool sub6 = MQTT_CLIENT.subscribe(TOPIC_SUB_MOTOR_SPEED1); 
            bool sub7 = MQTT_CLIENT.subscribe(TOPIC_SUB_MOTOR_SPEED2); 
            
            Serial.print("MQTTCONTROL: Subscriptions - motorCommand: ");
            Serial.print(sub1 ? "OK" : "FAIL");
            Serial.print(", motorMode: ");
            Serial.print(sub2 ? "OK" : "FAIL");
            Serial.print(", notaus: ");
            Serial.print(sub3 ? "OK" : "FAIL");
            Serial.print(", sensorStatus: ");
            Serial.print(sub4 ? "OK" : "FAIL");
            Serial.print(", general: ");
            Serial.print(sub5 ? "OK" : "FAIL");
            Serial.print(", motor3Speed: ");
            Serial.println(sub6 ? "OK" : "FAIL");
            Serial.print(", motor4Speed: ");
            Serial.println(sub7 ? "OK" : "FAIL");

            return true;
        } else {
            Serial.print("MQTTCONTROL: Connection failed, MQTT state: ");
            Serial.println(MQTT_CLIENT.state());
            Serial.println("MQTTCONTROL: Retrying in 5 seconds...");

            // If WiFi drops during retries, exit early
            for (int i = 5; i > 0; i--) {
                if (WiFi.status() != WL_CONNECTED) {
                    Serial.println("MQTTCONTROL: WiFi disconnected during retry.");
                    return false;
                }
                delay(1000);
            }
        }
    }

    return false;  // fallback if loop is somehow skipped
}

void mqttControl::mqttLoop() {MQTT_CLIENT.loop();}