#ifndef SENSOR_DHT22_H
#define SENSOR_DHT22_H


/*DHT22 parameters*/
#ifdef __AVR
    #define DHTPIN A1 // Pin 2 on Arduino Uno
#elif defined(ESP8266)
    #define DHTPIN 2 // GPIO 2 | D4 on Nodemcu
#endif


void initializeDHT22(void);


/* Parameters:
 *     char sep -- CSV separator
 * Return: String -- value of the readings
 */
String getTemperatureData(char sep);


#endif