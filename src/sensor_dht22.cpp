#include <DHT_U.h>
#include "sensor_DHT22.h"

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


void initializeDHT22(void)
{
    /*initializing DHT22*/
    Serial.println("DHT22 initialized");
    dht.begin();
}


String getTemperatureData(char sep)
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
