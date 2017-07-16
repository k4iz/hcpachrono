#ifndef SENSOR_TCS_H
#define SENSOR_TCS_H


void initializeTCS34725(void);

/* Parameters:
 *     char sep -- CSV separator for internal fields
 * Return: String -- value of the readings
 *                   Format: "colorTemp<sep>lux<sep>r<sep>g<sep>b<sep>c<sep>"
 *                        where: colortemp -- int -- temperature color approx                      
 */
String getLightData(char sep);

#endif