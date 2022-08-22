#include "UNIT_LoRaWAN.h"
//#include <sstream>
#include "settings.h"

class Lorawan {
     public:
        void setUpLoRaWAN(String &response);
        void send(int message, int pumpOn,uint8_t battery);
        String receive();
        UNIT_LoRaWAN getUNIT(){
            return loRaWAN;
        }
    private:
        UNIT_LoRaWAN loRaWAN;
        String response;
        String message;
        String payload;
};
