#include "lorawan.h"
//https://github.com/m5stack/ATOM_DTU_LoRaWAN/blob/master/examples/LoRaWAN_OTAA/LoRaWAN_OTAA.ino
//https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/docs/datasheet/unit/lorawan/ASR650X%20AT%20Command%20Introduction-20190605.pdf
void Lorawan::setUpLoRaWAN(String &response){
 loRaWAN.Init(&Serial2, 16, 17);
    Serial.println("Module Connect.....");
    while (!loRaWAN.checkDeviceConnect())
        ;
    Serial.println("Module Connected");
    //MAC SetUP Command AT+CRESTORE - Restore to Default Configuration
    loRaWAN.writeCMD("AT+CRESTORE\r\n");
    // AT+ILOGLVL - set Log Level; 0 = Disable Log Information; 1 = Enable Log Information
    loRaWAN.writeCMD("AT+ILOGLVL=0\r\n");
    // AT+CSAVE - Save Configuration
    loRaWAN.writeCMD("AT+CSAVE\r\n");
    // AT+IREBOOT - Reboot
    loRaWAN.writeCMD("AT+IREBOOT=0\r\n");
    delay(1000);
    while (!loRaWAN.checkDeviceConnect())
        ;
    Serial.println("Module Config...");
    loRaWAN.configOTTA(DEVICE_EUI,APP_EUI,APP_KEY,"2");  // APP KEY

    response = loRaWAN.waitMsg(1000);
    Serial.println(response);

    // Set Class Mode
    loRaWAN.setClass("1");
    // AT+CWORKMODE
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
    }
    Serial.println("Join success.....");
    
}

void Lorawan::send(int message,int status,uint8_t battery){
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