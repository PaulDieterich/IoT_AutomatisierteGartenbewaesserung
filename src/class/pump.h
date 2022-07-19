#include "M5Stack.h"
#include "settings.h"

class Pump{
    public:
        Pump();
        bool start();
        bool stop();
        
        void setPumpDuration(int duration);
        bool isPumpOn(){
            return is_pump_on;
        };
    private: 
        bool is_pump_on = false;
        int duration;
};

