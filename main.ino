#include <Wire.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "SSD1306Wire.h"
#include "./triggerCollection.h"

const char* WIFI_SSID = "pessima_ideia";
const char* WIFI_PASSWORD = "sucodelaranja";

const char* MQTT_BROKER_USERNAME = "admin";
const char* MQTT_BROKER_PASSWORD = "admin";
const char* MQTT_BROKER_HOST = "192.168.15.16";
const int MQTT_BROKER_PORT = 1883;  

SSD1306Wire display(0x3c, D1, D2);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

vector<Trigger> triggerVector{
  Trigger("charlao", "charlao/state", "OFF")
};

TriggerCollection triggers(triggerVector);



void splash(std::string message) {
  display.clear();
  display.setTextAlignment(TEXT_ALIGN_CENTER);
  display.setFont(ArialMT_Plain_16);

  display.drawString(63, 20, String(message.c_str()));
  display.display();
}

void mqttCallback(char* topic, byte* payload, unsigned int length) {
  char message[length];
  for (int i = 0; i < length; i++) {
    char c = (char)payload[i];
    message[i] = c;
  }

  std::string value(message, length);

  
  Serial.println(topic);
  Serial.println(value.c_str());
  splash(value);
}

void wifiConnectAndWait() {
  Serial.println("Iniciando conexão wifi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }

  Serial.println("ok");
}

void mqttConnectAndWait() {
  Serial.println("Conectando MQTT");
  mqttClient.connect("ESP8266-ESP12-E-Client", MQTT_BROKER_USERNAME, MQTT_BROKER_PASSWORD);
  mqttClient.subscribe("charlao"); 
  while (!mqttClient.connected()) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("ok");
}

void setupWifi() {
  splash("Conectando Wifi");

  wifiConnectAndWait();

  splash("Wifi Conectado");
}
  
void setupMQTT() {
  splash("Conectando MQTT");

  mqttClient.setServer(MQTT_BROKER_HOST, MQTT_BROKER_PORT);
  mqttClient.setCallback(mqttCallback);
  mqttConnectAndWait();

  splash("MQTT conectado");
}

void enforceConnections() {
  if (WiFi.status() != WL_CONNECTED) {
    wifiConnectAndWait();
  }

  if (!mqttClient.connected()) {
    mqttConnectAndWait();
  }
}

void setup() {
  Serial.begin(115200);
  display.init();
  // display.flipScreenVertically();
  splash("Inicializando");

  setupWifi();
  setupMQTT();

  Serial.println("Done!");
}

void loop() {
  enforceConnections();
  mqttClient.loop();
  delay(100);
}
