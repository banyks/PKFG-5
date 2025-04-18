#include "mqttControl.hpp"
#include <PubSubClient.h>
#include <WiFi.h>

// wifi connection (test)
WiFiClient ESP_CLIENT;
const char* WIFI_SSID = "FRITZ!Box 7530 DW_EXT";
const char* WIFI_PASSWORD = "76089546061926253871";   
const char* WIFI_HOSTNAME = "ESP32_GRUPPE5";
// wifi connection
IPAddress local_IP(192, 168, 8, 192);
IPAddress gateway(192, 168, 8, 1);
IPAddress subnet(255, 255, 0, 0);
// make it so that if swtch 1 pressed, you use pc keyboard to connect to wifi

// mqtt connection
PubSubClient MQTT_CLIENT(ESP_CLIENT);
const char* MQTT_SERVER = "192.168.178.71";
const int MQTT_PORT = 1883;
const char* MQTT_USER = "";
const char* MQTT_PASSWORD = "";

// Topics
const char* TOPIC_SUB = "esp32/commands";       // Subscribed topic (Node-RED → ESP32)
const char* TOPIC_PUB = "esp32/status";         // Published topic (ESP32 → Node-RED)

bool mqttControl::wifiConnect(){
    WiFi.mode(WIFI_STA);
    WiFi.setHostname(WIFI_HOSTNAME);
    
    /* First try with static IP
    if (!WiFi.config(local_IP, gateway, subnet)){
        Serial.println("STA Failed to configure");
        // Continue anyway with DHCP
    }*/

    Serial.println("MQTTCONTROL: Attempting wifi connection..");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    // Wait for connection with timeout
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000) {
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED){
        Serial.println("MQTTCONTROL: Wifi connection -> succeeded");
        Serial.print("MQTTCONTROL: IP -> ");
        Serial.println(WiFi.localIP());
        return 1;
    }
    
    // Handle specific error cases
    switch(WiFi.status()) {
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
    
    delay(1000);
    return 0;
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
    Serial.print("MQTTCONTROL: Message arrived [");
    Serial.print(topic);
    Serial.print("]: ");
    
    // Create a buffer for the payload and null-terminate it
    char message[length + 1];
    memcpy(message, payload, length);
    message[length] = '\0';
    
    Serial.println(message);
    
    // Here you can add logic to handle different commands
    if (strcmp(topic, TOPIC_SUB) == 0) {
        // Process commands for the ESP32
        if (strcmp(message, "ON") == 0) {
            Serial.println("MQTTCONTROL: Received ON command");
            // Add your ON action here
        } 
        else if (strcmp(message, "OFF") == 0) {
            Serial.println("MQTTCONTROL: Received OFF command");
            // Add your OFF action here
        }
        else {
            Serial.println("MQTTCONTROL: Received unknown command");
        }
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
            Serial.println("MQTTCONTROL: Connected to MQTT broker.");
            // Subscribe to your desired topic
            if (MQTT_CLIENT.subscribe(TOPIC_SUB)) {
                Serial.print("MQTTCONTROL: Subscribed to topic -> ");
                Serial.println(TOPIC_SUB);
            } else {
                Serial.println("MQTTCONTROL: Subscription failed!");
            }
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
void mqttControl::mqttMessageReceave(){
    // Keep empty if not implementing yet
}

void mqttControl::mqttMessageSend(){
    // Keep empty if not implementing yet
}

void mqttControl::mqttLoop() {MQTT_CLIENT.loop();}