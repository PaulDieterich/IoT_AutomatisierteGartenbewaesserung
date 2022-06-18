//Aktuell alles Für M5stack ausgelegt

/* In der passwd.h werden alle passcodes für apis gesetzt
*  Lorawan: DEVICE_EUI, APP_EUI, APP_KEY
*  OpenWeatherAPI: API_KEY
*  WLAN: SSID, PASSWORD
*  Diese Datei muss selbst erzeugt werden und api keys eingetragen werden
*  Siehe src/passwd_example.h
*/
#include "passwd.h"


#define DEBUG 1


//api call in c++
//https://stackoverflow.com/questions/5707957/c-libcurl-json-rest/5780603#5780603