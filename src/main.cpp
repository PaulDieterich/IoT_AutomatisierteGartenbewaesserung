//#include <Arduino.h>
#include <M5Stack.h>
//#include <M5LoRa.h>
#include <WiFi.h>
#include "class/soil.h"
#include "class/lorawan.h"
#include "settings.h"

#define MOISTURE_SENSOR_PIN 36
#define PUMP_PIN 35
double soil_moisture;
String response;
Lorawan* lora = new Lorawan(); // my own LoraWAN class
Soil* soil = new Soil(); // my own Soil class

void connectWiFi(){
  WiFi.begin(SSID,PASSWORD);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.printf("WiFi Connected: %s",WiFi.localIP().toString());
 
}

void setToSleep(){
  Serial.print("goToSleep");
  //time in microsec. 1000000 = 1 second
  //                  10*1000000 = 10 seconds
  esp_sleep_enable_timer_wakeup(10 * 1000000);
  esp_deep_sleep_start();
  //M5.Power.deepSleep(5);
}


void setup() {
 M5.begin();
 M5.Power.begin();
 connectWiFi();
 lora->setUpLoRaWAN(response);
}

void loop() {
  M5.Lcd.printf("Hello World!");
  soil_moisture = analogRead(MOISTURE_SENSOR_PIN);
  soil->setMoisture(soil_moisture);
  Serial.printf("Soil moisture: %f\n", soil_moisture);
  lora->send("soil.getMoisture()");
  response = lora->receive();
  setToSleep();
}
