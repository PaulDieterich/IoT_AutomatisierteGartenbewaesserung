#include "UNIT_LoRaWAN.h"
//#include <sstream>

#include "settings.h"
class Lorawan {
     public:
        void setUpLoRaWAN(String &response);
        void send(String message);
       // void send(int message);
        String receive();
    private:
        UNIT_LoRaWAN LoRaWAN;
        String response;
        String message;
        String message_to_send;
};