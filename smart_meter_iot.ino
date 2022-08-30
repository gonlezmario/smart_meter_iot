#include <WiFi.h>
#include <PubSubClient.h>
#include <connections.h>
#include <measuring.h>

//WiFi constants
const char * ssid = "SSIDtest";
const char * password = "Passwordtest";
WiFiClient wifiClient;

//MQTT Broker constants
const char* ssid = "MQTTSSID";
const char* password = "MQTTPass";
const char* mqtt_server = "www.mqtt.com";
#define mqtt_port 12595
#define MQTT_USER "gn23kaGQds"
#define MQTT_PASSWORD "2feASF3qzVn"
#define MQTT_SERIAL_PUBLISH "/smartmeter/ESP32/tx"
#define MQTT_SERIAL_RECEIVER "/smartmeter/ESP32/rx"
PubSubClient client(wifiClient);

void setup() {
  //Serial baud declaration
  Serial.begin(115200);
  Serial.setTimeout(500); // Set time out for Seial communication

  //Pin OUTPUT/INPUT declaration
  pinMode(4, INPUT); // voltage_1 pin
  pinMode(5, INPUT); // voltage_2 pin
  pinMode(6, INPUT); // voltage_3 pin
  pinMode(11, INPUT); // current_1 pin
  pinMode(12, INPUT); // current_2 pin
  pinMode(13, INPUT); // current_3 pin


  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();
}

void loop() {
  ADC_measurements();
  client.loop();
  if (Serial.available() > 0){
  char mun[501];
  memset(mun,0, 501);
  Serial.readBytesUntil( '\n',mun,500);
  publishSerialData(mun);
  }
}
