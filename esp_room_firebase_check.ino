#include <ESP8266WiFi.h>
#include "DHTesp.h"
#include <FirebaseArduino.h>

#define WIFI_SSID "YOUR WIFI SSID"
#define WIFI_PASSWORD "YOUR WIFI PASSWORD"
//You can find this info in Settings-> Service accounts-> Database secrets:
#define FIREBASE_HOST "<YOUR PROJECT NAME>.firebaseio.com"
#define FIREBASE_AUTH "YOUR PROJECT SECRET KEY"
#define LIGHT_PIN 0
#define PIR_PIN 5
#define DHT_PIN 4

DHTesp dht;
float temp=0, hum=0;
int lum=0, motion_st=0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(250);
  }
  Serial.println();
  Serial.print("Connected, ip: ");
  Serial.println(WiFi.localIP());
  dht.setup(DHT_PIN);
  pinMode(PIR_PIN, INPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  temp = dht.getTemperature();
  hum = dht.getHumidity();
  lum = analogRead(LIGHT_PIN);
  String tempName = Firebase.pushFloat("temp", temp);
  String humName = Firebase.pushFloat("hum", hum);
  String lightName = Firebase.pushInt("light", lum);
  String motionName = Firebase.pushInt("motion", motion_st);
  if(Firebase.failed()){
    Serial.println(Firebase.error());
  }

  if(digitalRead(PIR_PIN)==HIGH){
    motion_st = 1;
  }
  else{
    motion_st = 0;
  }
  
  delay(5000);
}
