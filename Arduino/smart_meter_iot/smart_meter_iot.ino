#include <WiFi.h>
#include <PubSubClient.h>
#include <connections.h>
#include <measuring.h>
#include <driver/adc.h>

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
  Serial.setTimeout(500); // Set time out for Serial communication

  //Pin OUTPUT/INPUT declaration
  pinMode(4, INPUT); // voltage_1 pin ADC1_3
  pinMode(5, INPUT); // voltage_2 pin ADC1_4
  pinMode(6, INPUT); // voltage_3 pin ADC1_5
  pinMode(11, INPUT); // current_1 pin ADC2_0
  pinMode(12, INPUT); // current_2 pin ADC2_1
  pinMode(13, INPUT); // current_3 pin ADC2_2


  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);
  reconnect();

  //ADCs configuration (Bits, attenuation and calibration)
  adc1_config_width(ADC_WIDTH_BIT_12); // 12 bits measurements in ADC1
  adc1_config_channel_atten(ADC1_CHANNEL_0,ADC_ATTEN_DB_0); // Attenuation in channel 0 of ADC1 set to 0dB
  adc1_config_channel_atten(ADC1_CHANNEL_1,ADC_ATTEN_DB_0); // Attenuation in channel 1 of ADC1 set to 0dB
  adc1_config_channel_atten(ADC1_CHANNEL_2,ADC_ATTEN_DB_0); // Attenuation in channel 2 of ADC1 set to 0dB
  
  adc2_config_width(ADC_WIDTH_BIT_12); // 12 bits measurements in ADC2
  adc2_config_channel_atten(ADC2_CHANNEL_0,ADC_ATTEN_DB_0); // Attenuation in channel 0 of ADC2 set to 0dB
  adc2_config_channel_atten(ADC2_CHANNEL_1,ADC_ATTEN_DB_0); // Attenuation in channel 1 of ADC2 set to 0dB
  adc2_config_channel_atten(ADC2_CHANNEL_2,ADC_ATTEN_DB_0); // Attenuation in channel 2 of ADC2 set to 0dB

  //ADC calibration
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

  esp_err_t r = adc2_get_raw( ADC2_CHANNEL_7, ADC_WIDTH_12Bit, &read_raw);
  if ( r == ESP_OK ) {
      printf("%d\n", read_raw );
  } else if ( r == ESP_ERR_TIMEOUT ) {
      printf("ADC2 used by Wi-Fi.\n");
  }
  
}
