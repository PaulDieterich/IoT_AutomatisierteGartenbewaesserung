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

//time between measurements in seconds
#define SLEEP_TIME 60 //1 minutes

//set Moisture Sensor Threshold
#define MOISTURE_MINIMUM 1900//soil is dry
#define MOISTURE_MEDIUM  1700//soil is wet but not too wet
#define MOISTURE_MAXIMUM 1600 //soil is wet
//#define DURATION  15 //pump duration in seconds

//debugging
#define DEBUG 0

