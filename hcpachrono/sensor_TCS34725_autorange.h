#ifndef SENSOR_TCS34725_AUTORANGE_H
#define SENSOR_TCS34725_AUTORANGE_H


typedef struct 
{	
	float gain;
	float lux;
	float colortemp;
	float red;
	float green;
	float blue;
	float clear;
	String datalog;
} TCS34725_LOG_t;


void init_TCS34725_autorange(void);

String read_TCS34725_autorange(char sep);

TCS34725_LOG_t * read_TCS34725_s(char sep);

#endif