#include <Adafruit_TCS34725.h>

#include "autorange.h"
#include "sensor_TCS34725_autorange.h"

tcs34725 tcs_autorange; 

void init_TCS34725_autorange(void)
{
    Serial.print("Initializing TCS34725..\t");    
    if (tcs_autorange.begin()) 
    {
        Serial.println("OK!");
    } 
    else 
    {
        Serial.println("No TCS34725 found ... check your connections");
    }
}


String read_TCS34725_autorange(char sep)
{ 
    tcs_autorange.getData();

    String s="";
    s += String(tcs_autorange.againx) + sep;    
    s += String(tcs_autorange.lux) + sep;
    s += String(tcs_autorange.ct) + sep;
    s += String(tcs_autorange.r_comp) + sep;
    s += String(tcs_autorange.g_comp) + sep;
    s += String(tcs_autorange.b_comp) + sep;
    s += String(tcs_autorange.c_comp);

    return s;
}

TCS34725_LOG_t * read_TCS34725_s(char sep)
{ 
    tcs_autorange.getData();

    String s="";
    s += String(tcs_autorange.againx) + sep;    
    s += String(tcs_autorange.lux) + sep;
    s += String(tcs_autorange.ct) + sep;
    s += String(tcs_autorange.r_comp) + sep;
    s += String(tcs_autorange.g_comp) + sep;
    s += String(tcs_autorange.b_comp) + sep;
    s += String(tcs_autorange.c_comp);

    TCS34725_LOG_t * log = new TCS34725_LOG_t;

    log->gain = tcs_autorange.againx;
    log->lux = tcs_autorange.lux;
    log->colortemp = tcs_autorange.ct;
    log->red = tcs_autorange.r_comp;
    log->green = tcs_autorange.g_comp;
    log->blue = tcs_autorange.b_comp;
    log->clear = tcs_autorange.c_comp;
    log->datalog = s;
    return log;
}

