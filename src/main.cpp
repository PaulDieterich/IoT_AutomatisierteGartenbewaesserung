#include <Arduino.h>
#include <M5Stack.h>
//#include <M5LoRa.h>
#include <WiFi.h>
#include "class/soil.h"
#include "class/lorawan.h"
#include "class/pump.h"
#include "settings.h"
//#include "UNIT_LoRaWAN.h"
int rawADC;
UNIT_LoRaWAN LoRaWAN;
String massage;
String response;
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
 M5.Lcd.begin();
 M5.Lcd.wakeup();
lora->setUpLoRaWAN(response);
pinMode(INPUT_PIN, INPUT);
pinMode(PUMP_PIN, OUTPUT); 
pinMode(MOISTURE_SENSOR_PIN, OUTPUT);
digitalWrite(MOISTURE_SENSOR_PIN, 0);
}
void PumpIsNeeded(){
  //soil mousture is low
  if(soil->getMoisture() < MOISTURE_MINIMUM){
    //pump is not on
    if(!pump->isPumpOn()){
     // pump->start();
      Serial.println("Pump Start");
    }
  //soil moisture is high
  }if(soil->getMoisture() > MOISTURE_MAXIMUM){
    //pump is on
    if(pump->isPumpOn()){
 //     pump->stop();
   Serial.println("Pump Stop");
    }
  }
}

void loop() {

    rawADC = analogRead(INPUT_PIN);
    soil->setMoisture(rawADC);
    //PumpIsNeeded(); 
    Serial.printf("Massage String: %s\n", soil->getMoistureString().c_str());
    lora->send(soil->getMoistureString());
    response = lora->receive();
    delay(1000);

  //setToSleep();
}
