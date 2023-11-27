#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define DHTPin 5
#define DHTType DHT11
#define LDR_PIN 17
DHT dht(DHTPin, DHTType);

const char* locationID = "BTL1";
const char* ssid = "Thanh T2";
const char* password = "@9999999";
const char* server = "test.mosquitto.org";
const int port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
const char* topic = "ET";

void setup() {
  Serial.begin(115200);

  //Setup Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting..");
  }
  Serial.println("Connected!");
  
  //Setup MQTT Client
  client.setServer(server, port);
  if (!client.connected()){
    if (client.connect("SensorNode")){
      Serial.println("Connected to broker!");
    }
  }

  //Setup sensor
  dht.begin();
} 

void PublishData(float temp, float humidity, float lux){
  String message = String(locationID) + " " + String(temp) + " " + String(humidity) + " " + String(lux);
  client.publish(topic, message.c_str());
  Serial.println("Sended!");
} 

void ReadData(float &temp, float &humidity, float &lux){
  lux = analogRead(LDR_PIN);
  temp = dht.readTemperature();
  humidity = dht.readHumidity();
}

void loop() {
  float temp, hud, lux;
  ReadData(temp, hud, lux);
  PublishData(temp, hud, lux);
  //PublishData(1.1, 1.2, 1.3);
  delay(5000);
}


