void setupWifi() {
  //WiFi network connection
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Connecting to the WiFi network");
    delay(100;)
    Serial.print(".");
    delay(100);
    Serial.print(".");
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    //Loop until there is a client connection
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "ESP32ClientTest";
    // Attempt to connect
    if (client.connect(clientId.c_str(), MQTT_USER, MQTT_PASSWORD)) {
      Serial.println("Successful MQTT connection");
      //Once connected, publish an announcement...
      client.publish("/smartmeter/ESP32/measurements", "hello world");
      // ... and resubscribe
      client.subscribe(MQTT_SERIAL_RECEIVER);
    } else {
      Serial.print("Failed connection:");
      Serial.print(client.state());
    }
  }
}

void callback(char * topic, byte * payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char) payload[i]);
  }
  Serial.println();
  Serial.println("-----------------------");
}

void publishSerialData(char * serialData) {
  if (!client.connected()) {
    reconnect();
  }
  client.publish(MQTT_SERIAL_PUBLISH, serialData);
}