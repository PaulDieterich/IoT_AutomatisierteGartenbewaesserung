#include "UNIT_LoRaWAN.h"
//#include <sstream>

#include "settings.h"
class Lorawan {
     public:
        void setUpLoRaWAN(String &response);
        void send(String message);
        void send(int message);
        String receive();
        UNIT_LoRaWAN getUNIT(){
            return loRaWAN;
        }
    private:
        UNIT_LoRaWAN loRaWAN;
        String response;
        String message;
        String outgoing;
};
