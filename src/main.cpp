#include <Arduino.h>
#include <M5Stack.h>
//#include <M5LoRa.h>
#include <WiFi.h>
#include "class/soil.h"
#include "class/lorawan.h"
#include "class/pump.h"
#include "settings.h"
//#include "UNIT_LoRaWAN.h"

int previousMillis = 0;
int interval = 1000;

int rawADC;
String message;
String response;
int pumpStatus;
int batteryStatus;
Lorawan* lora = new Lorawan(); // my own LoraWAN class
Soil* soil = new Soil(); // my own Soil class
Pump *pump = new Pump(); // my own Pump class

void connectWiFi(){
  WiFi.begin(SSID,PASSWORD);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.printf("WiFi Connected: %s/n",WiFi.localIP().toString());
}

void setup() {
  M5.begin();
  M5.Power.begin();
  M5.Lcd.begin();
  M5.Lcd.wakeup();
  lora->setUpLoRaWAN(response);
  pinMode(INPUT_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT); 
  pinMode(MOISTURE_SENSOR_PIN, OUTPUT);
  digitalWrite(MOISTURE_SENSOR_PIN, 0);
}

void pumpIsNeeded(){
  if(soil->getMoisture() > MOISTURE_MINIMUM){
    pump->start();
  }
  if(soil->getMoisture() < MOISTURE_MAXIMUM){
    //pump is on
      pump->stop();
  } 
}
void displayMoisture(){
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0,0);
  M5.Lcd.print("Moisture: ");
  M5.Lcd.print(soil->getMoisture());
  M5.Lcd.print("%");

}

int loops = 0;
void loop() {
  unsigned long currentMillis = millis();
  M5.update();
  if(currentMillis - previousMillis >= interval){
    loops++;
    rawADC = analogRead(INPUT_PIN);
    soil->setMoisture(rawADC);
    displayMoisture();
    pumpIsNeeded();     
    Serial.printf("Massage String: %s\n", soil->getMoistureString().c_str());
    batteryStatus = M5.Power.getBatteryLevel();
    pumpStatus = pump->isPumpOn() ? 1 : 0;
    lora->send(soil->getMoisture() , pumpStatus, batteryStatus);
    response = lora->receive();

    if(response = "ON"){
      pump->start();
    }
  if(loops > 30){
      M5.Power.deepSleep(SLEEP_TIME);
      loops = 0;
   } 
   M5.Lcd.clear();
   }
}
