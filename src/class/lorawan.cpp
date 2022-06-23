#include "lorawan.h"

void Lorawan::setUpLoRaWAN(String &response){
  LoRaWAN.Init(&Serial2, 16, 17);
  Serial.println("Module Connect.....");
  while (!LoRaWAN.checkDeviceConnect())
    ;
  Serial.println("Module Connected");
  LoRaWAN.writeCMD("AT+CRESTORE\r\n");
  // Disable Log Information
  LoRaWAN.writeCMD("AT+ILOGLVL=0\r\n");
  // Enable  Log Information
  // LoRaWAN.writeCMD("AT+ILOGLVL=5\r\n");
  LoRaWAN.writeCMD("AT+CSAVE\r\n");
  LoRaWAN.writeCMD("AT+IREBOOT=0\r\n");
  delay(1000);
  while (!LoRaWAN.checkDeviceConnect())
    ;
  Serial.println("Module Config...");
  LoRaWAN.configOTTA(DEVICE_EUI,APP_EUI,APP_KEY,"2");
  response = LoRaWAN.waitMsg(1000);
  Serial.println(response);
  // Set Class Mode
  LoRaWAN.setClass("2");
  LoRaWAN.writeCMD("AT+CWORKMODE=2\r\n");
  //LoRaWAN868
  LoRaWAN.setRxWindow("869525000");
  LoRaWAN.setFreqMask("0001");
  response = LoRaWAN.waitMsg(1000);
  Serial.println(response);
  LoRaWAN.startJoin();
  Serial.println("Join Success");
  while(!LoRaWAN.checkJoinStatus()){
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Join Success");
}

void Lorawan::send(String message){
    //uint8_t confirm, uint8_t nbtrials, size_t length,String data
    LoRaWAN.sendMsg(1, 15,message.length(),message);
}
/*void Lorawan::send(int message){
  std::stringstream ss;
  ss << message;
  String message_to_send = String(ss.str().c_str());
  send(message_to_send);
}*/

String Lorawan::receive(){
    response = LoRaWAN.receiveMsg();
    if (response != "") {
        Serial.println("Received: ");
        Serial.println(response);
        return response;
    }
    return "";
}