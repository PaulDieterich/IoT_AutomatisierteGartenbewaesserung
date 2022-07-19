//Aktuell alles Für M5stack ausgelegt

/* In der passwd.h werden alle passcodes für apis gesetzt
*  Lorawan: DEVICE_EUI, APP_EUI, APP_KEY
*  OpenWeatherAPI: API_KEY
*  WLAN: SSID, PASSWORD
*  Diese Datei muss selbst erzeugt werden und api keys eingetragen werden
*  Siehe src/passwd_example.h
*/
#include "passwd.h"
    
//set Pins
#define MOISTURE_SENSOR_PIN 25
#define PUMP_PIN 26
#define INPUT_PIN 36

//set Moisture Sensor Threshold
#define MOISTURE_MINIMUM 1500 //soil is dry af
#define MOISTURE_MAXIMUM 3000 //soil is wet


//debugging
#define DEBUG 0




//api call in c++
//https://stackoverflow.com/questions/5707957/c-libcurl-json-rest/5780603#5780603