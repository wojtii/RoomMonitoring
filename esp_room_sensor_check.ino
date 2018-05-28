#include <ESP8266WiFi.h>
#include "DHTesp.h"

#define WIFI_SSID "YOUR WIFI SSID"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"
#define LUM_PIN 0
#define PIR_PIN 5
#define DHT_PIN 4

DHTesp dht;
float temp=0, hum=0;
int lum=0, motion_st=0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  dht.setup(DHT_PIN);
  pinMode(PIR_PIN, INPUT);
}

void loop() {
  
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Failed to connect. Reconnecting");
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    delay(5000);
   }

   temp = dht.getTemperature();
   hum = dht.getHumidity();
   lum = analogRead(LUM_PIN);
   if(digitalRead(PIR_PIN) == HIGH){
    Serial.println("MOVE");
   }
   Serial.println(temp);
   Serial.println(hum);
   Serial.println(lum);
   delay(2000);
}
