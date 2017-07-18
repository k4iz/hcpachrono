#include <DHT_U.h>
#include "sensor_DHT22.h"

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


void init_DHT22(void)
{
    Serial.print("Initializing DHT22...\t");
    dht.begin();
    Serial.println("OK!");
}


String read_DHT22(char sep)
{
    float h = dht.readHumidity();
    float t = dht.readTemperature(); //read temperature as Celcius, for Fahrenheit put argument as "true"

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) 
    {
        Serial.println("Failed to read from DHT sensor!");
        return String("<error_dt_read>");
    }

    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);


    String s="";
    s += String(h) + sep;
    s += String(t) + sep;
    s += String(hic);
    return s;
}



DHT22_LOG_t * read_DHT22_s(char sep)
{
    float h = dht.readHumidity();
    float t = dht.readTemperature(); //read temperature as Celcius, for Fahrenheit put argument as "true"

    // Check if any reads failed and exit early (to try again).
    // if (isnan(h) || isnan(t)) 
    // {
    //     Serial.println("Failed to read from DHT sensor!");
    //     return String("<error_dt_read>");
    // }

    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);


    String s="";
    s += String(h) + sep;
    s += String(t) + sep;
    s += String(hic);
    
    DHT22_LOG_t * log = new DHT22_LOG_t;

    log->temp = t;
    log->hum = h;
    log->datalog = s;
    return log;
}
