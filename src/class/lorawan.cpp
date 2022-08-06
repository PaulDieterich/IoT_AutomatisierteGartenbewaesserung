#include "lorawan.h"
//https://github.com/m5stack/ATOM_DTU_LoRaWAN/blob/master/examples/LoRaWAN_OTAA/LoRaWAN_OTAA.ino
void Lorawan::setUpLoRaWAN(String &response){
 loRaWAN.Init(&Serial2, 16, 17);
    Serial.println("Module Connect.....");
    while (!loRaWAN.checkDeviceConnect())
        ;
    Serial.println("Module Connected");
    loRaWAN.writeCMD("AT+CRESTORE\r\n");
    // Disable Log Information
    loRaWAN.writeCMD("AT+ILOGLVL=0\r\n");
    // Enable  Log Information
    // LoRaWAN.writeCMD("AT+ILOGLVL=5\r\n");
    loRaWAN.writeCMD("AT+CSAVE\r\n");
    loRaWAN.writeCMD("AT+IREBOOT=0\r\n");
    delay(1000);
    while (!loRaWAN.checkDeviceConnect())
        ;
    Serial.println("Module Config...");
    loRaWAN.configOTTA(DEVICE_EUI,APP_EUI,APP_KEY,"2");  // APP KEY

    response = loRaWAN.waitMsg(1000);
    Serial.println(response);

    // Set Class Mode
    loRaWAN.setClass("2");

    loRaWAN.writeCMD("AT+CWORKMODE=2\r\n");

    // LoRaWAN868
    loRaWAN.setRxWindow("869525000");

    loRaWAN.setFreqMask("0001");

    delay(100);
    response = loRaWAN.waitMsg(1000);
    Serial.println(response);
    loRaWAN.startJoin();
    Serial.println("Start Join.....");
    while (!loRaWAN.checkJoinStatus()) {
        delay(100);
    };
    Serial.println("Join success.....");
}

void Lorawan::send(String message){
    //String encoded = base64::encode(message)
    //uint8_t confirm, uint8_t nbtrials, size_t length,String data
    Serial.printf("Sending Message: %s\n", message.c_str());
    loRaWAN.sendMsg(1, 7,message.length(),message.c_str());
}

void Lorawan::send(int message,int status,int battery){
    String hex_message = String(message, HEX);
    String hex_status = String(status, HEX); 
    String hex_battery = String(battery, HEX);
    payload = hex_message + "0"+ hex_status + hex_battery;
    loRaWAN.sendMsg(1, 7,8,payload);
    Serial.printf("Sending Message: %s\n",payload);
}

String Lorawan::receive(){
    response = loRaWAN.receiveMsg();
    if (response != "") {
        Serial.println("Received: ");
        Serial.println(response);
        return response;
    }
    return "";
}