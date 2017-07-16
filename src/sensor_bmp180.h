#ifndef SENSOR_BMP180_H
#define SENSOR_BMP180_H



void initializeBMP180(void);


/* Parameters:
 *     char sep -- CSV separator
 * Return: String -- value of the readings
 */
String getTemperatureBMP180(char sep);

 
#endif