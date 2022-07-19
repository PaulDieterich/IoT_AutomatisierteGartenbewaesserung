#include "soil.h"


// convert moisture int to mousture string
String Soil::getMoistureString() {
    char moisture_string[10];
    sprintf(moisture_string, "%d", moisture);
    return moisture_string;
}