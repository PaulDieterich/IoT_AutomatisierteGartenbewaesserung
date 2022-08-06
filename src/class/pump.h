#include "M5Stack.h"
#include "settings.h"
//#include "class/soil.h"
class Pump{
    public:
        Pump();
        bool start();
        bool stop(); 
        void setPumpDuration(int duration);
        bool isPumpOn(){
            return is_pump_on;
        };
        String getPumpStatus();
    private: 
        bool is_pump_on = 0;
        int duration = 30;//DURATION;
};

