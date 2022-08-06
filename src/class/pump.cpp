#include "pump.h"

Pump::Pump() {
    duration = 30; //default on 30 seconds Pump duration
}
bool Pump::start(){
    Serial.println("Pump started");
    is_pump_on = true;
    digitalWrite(PUMP_PIN, true);
    return true;
}
bool Pump::stop(){
    Serial.println("Pump Stop");
    digitalWrite(PUMP_PIN, false);
    is_pump_on = false;
    return true;
}
void Pump::setPumpDuration(int duration){
    this->duration = duration;
}
String Pump::getPumpStatus(){
    if(is_pump_on){
        return "Pump On";
    }else{
        return "Pump Off";
    }
}
