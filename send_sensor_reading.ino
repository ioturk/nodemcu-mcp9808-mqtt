#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Wire.h>
#include "Adafruit_MCP9808.h"

const char* ssid = "your wifi SSID";
const char* password =  "your wifi password";
const char* mqttServer = "mqtt server address";
const int mqttPort = port number;
const char* mqttUser = "your mqtt username";
const char* mqttPassword = "your mqtt server password";
 
WiFiClient espClient;
PubSubClient client(espClient);
// Create the MCP9808 temperature sensor object
Adafruit_MCP9808 tempsensor = Adafruit_MCP9808();
 
void setup() {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
 
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
 
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
 
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
 
      Serial.println("connected");  
 
    } else {
 
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
 
    }

  if (!tempsensor.begin(0x18)) {
    Serial.println("Couldn't find MCP9808! Check your connections and verify the address is correct.");
    while (1);
  }

  Serial.println("Found MCP9808!");

  tempsensor.setResolution(1);
  }
 
  client.subscribe("Your Topic Name Here");
 
}
 
void callback(char* topic, byte* payload, unsigned int length) {
   
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
 
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
 
  Serial.println();
  Serial.println("-----------------------");
 
}
 
void loop() {
  client.loop();
  tempsensor.wake();   // wake up, ready to read!
  Serial.print("Resolution in mode: ");
  Serial.println (tempsensor.getResolution());
  float c = tempsensor.readTempC();
  float f = tempsensor.readTempF();
  Serial.print("Temp: "); 
  Serial.print(c, 2); Serial.print("*C\t and "); 
  Serial.print(f, 2); Serial.println("*F.");

// convert float to char to be published
  static char reading[15];
  dtostrf(c, 7, 2, reading);

// publish part
  client.publish("Your Topic Name Here", reading);
  delay(10000);

//  Serial.println("Shutdown MCP9808.... ");
  tempsensor.shutdown_wake(1); // shutdown MSP9808 - power consumption ~0.1 mikro Ampere, stops temperature sampling
//  Serial.println("");

}
