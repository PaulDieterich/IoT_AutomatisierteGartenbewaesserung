#include "pump.h"

Pump::Pump() {
    duration = 30; //default on 30 seconds Pump duration
}
bool Pump::start(){
    if(duration == 0){
        Serial.println("Pump cant Start, duration is 0");
        digitalWrite(PUMP_PIN, LOW);
        return false;
    }
    else{
        is_pump_on = true;
        Serial.printf("Pump Start for %d seconds\n", duration);
        Serial.printf("Pump on Pin %s\n", PUMP_PIN);
        digitalWrite(PUMP_PIN, HIGH);
        return true;
    }
}
bool Pump::stop(){
    Serial.println("Pump Stop");
    digitalWrite(PUMP_PIN, LOW);
    is_pump_on = false;
    return true;
}
void Pump::setPumpDuration(int duration){
    this->duration = duration;
}
