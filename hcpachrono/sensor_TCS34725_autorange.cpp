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

    // Serial.print(F("Gain:")); 
    // Serial.print(rgb_sensor.againx); 
    // Serial.print(F("x "));
    // Serial.print(F("Time:")); 
    // Serial.print(rgb_sensor.atime_ms); 
    // Serial.print(F("ms (0x")); 
    // Serial.print(rgb_sensor.atime, HEX);   
    // Serial.println(F(")"));
      
    // Serial.print(F("Raw R:")); 
    // Serial.print(rgb_sensor.r); 
    // Serial.print(F(" G:")); 
    // Serial.print(rgb_sensor.g); 
    // Serial.print(F(" B:")); 
    // Serial.print(rgb_sensor.b); 
    // Serial.print(F(" C:")); 
    // Serial.println(rgb_sensor.c); 

    // Serial.print(F("IR:")); 
    // Serial.print(rgb_sensor.ir); 
    // Serial.print(F(" CRATIO:"));
    // Serial.print(rgb_sensor.cratio); 
    // Serial.print(F(" Sat:"));
    // Serial.print(rgb_sensor.saturation); 
    // Serial.print(F(" Sat75:"));
    // Serial.print(rgb_sensor.saturation75); 
    // Serial.print(F(" "));
    // Serial.println(rgb_sensor.isSaturated ? "*SATURATED*" : "");

    // Serial.print(F("CPL:")); 
    // Serial.print(rgb_sensor.cpl);
    // Serial.print(F(" Max lux:")); 
    // Serial.println(rgb_sensor.maxlux);

    // Serial.print(F("Compensated R:")); 
    // Serial.print(rgb_sensor.r_comp); 
    // Serial.print(F(" G:")); 
    // Serial.print(rgb_sensor.g_comp); 
    // Serial.print(F(" B:")); 
    // Serial.print(rgb_sensor.b_comp); 
    // Serial.print(F(" C:")); 
    // Serial.println(rgb_sensor.c_comp); 
      
    // Serial.print(F("Lux:")); 
    // Serial.print(rgb_sensor.lux);
    // Serial.print(F(" CT:")); 
    // Serial.print(rgb_sensor.ct);
    // Serial.println(F("K")); 
      
    // Serial.println();

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
