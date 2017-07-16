#include <Adafruit_TCS34725.h>
#include "sensor_tcs.h"

/*TCS34725 parameters*/
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);
 

void initializeTCS34725(void)
{
    /*initializing TCS34725*/
    if (tcs.begin()) 
    {
        Serial.println("TCS34725 initialized");
    } 
    else 
    {
        Serial.println("No TCS34725 found ... check your connections");
        // while (1);
    }

}


String getLightData(char sep)
{ 
    tcs.setInterrupt(true);  //turn off LED

    uint16_t r, g, b, c, colorTemp, lux;

    tcs.getRawData(&r, &g, &b, &c);


    colorTemp = tcs.calculateColorTemperature(r, g, b);
    lux = tcs.calculateLux(r, g, b);


    String s="";
    s += String(colorTemp) + sep;
    s += String(lux) + sep;
    s += String(r) + sep;
    s += String(g) + sep;
    s += String(b) + sep;
    s += String(c) + sep;

    return s;
}