#ifndef SENSOR_DHT22_H
#define SENSOR_DHT22_H
#include "nodemcu_pinout.h"

/* TEMPERATURE AND HUMIDTY SENSOR */

typedef struct 
{
	float temp;
	float hum;
	String datalog;
} DHT22_LOG_t;


/*DHT22 parameters*/
#ifdef __AVR
    #define DHTPIN A1 // Pin 2 on Arduino Uno
#elif defined(ESP8266)
    #define DHTPIN D4 // GPIO 2 | D4 on Nodemcu
#endif


void init_DHT22(void);


/* Parameters:
 *     char sep -- CSV separator
 * Return: String -- value of the readings
 */
String read_DHT22(char sep);



DHT22_LOG_t * read_DHT22_s(char sep);


#endif