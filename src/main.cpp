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
uint8_t batteryStatus;
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
  //M5.Lcd.wakeup(); 
  lora->setUpLoRaWAN(response);
  pinMode(INPUT_PIN, INPUT);
  pinMode(PUMP_PIN, OUTPUT); 
  pinMode(MOISTURE_SENSOR_PIN, OUTPUT);
  digitalWrite(MOISTURE_SENSOR_PIN, 0);
  //esp_sleep_enable_timer_wakeup(SLEEP_TIME);
}


void pumpIsNeeded(){
  if(soil->getMoisture() > MOISTURE_MEDIUM){
    pump->start();
  }else if(soil->getMoisture() < MOISTURE_MINIMUM){
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

}

int loops = 0;
void loop() {
  unsigned long currentMillis = millis();
  M5.update();
  if(currentMillis - previousMillis >= interval){
    loops++;
    rawADC = analogRead(INPUT_PIN);
    soil->setMoisture(rawADC);
    if(DEBUG) displayMoisture();
    pumpIsNeeded();     
    Serial.printf("Massage String: %s\n", soil->getMoistureString().c_str());
    batteryStatus = M5.Power.getBatteryLevel();
    pumpStatus = pump->isPumpOn() ? 1 : 0;
    lora->send(soil->getMoisture() , pumpStatus, batteryStatus);
    response = lora->receive();
    Serial.printf("loop: %d\n", loops);
    if(loops > 30){
      loops = 0;
      pump->stop();
      M5.Lcd.setBrightness(0); // turn off display  
    //Syntax: esp_deep_sleep_start();
    //void deepSleep(uint64_t time_in_us)
    //This function shifts to deep sleep mode.
    //It starts when the specified time or port status changes. After waking up, the CPU will be restarted instead of running from the next line.
     M5.Power.deepSleep(SLEEP_SEC(SLEEP_TIME));
     }
     if(DEBUG) M5.Lcd.clear();
   }
}
