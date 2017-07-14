#ifndef MYSENSORS_H
#define MYSENSORS_H

/*Declaring necessary functions - C/C++ syntax*/
void initializeSDCard(void);
void initializeRTC(void);
void initializeDHT22(void);
// void initializeTCS34725(void);

String getFilenameTimestamp(void);

/* Parameters:
 *     char sep -- CSV separator
 * Return: String -- value of the readings
 */
String getDateTime(char sep, char date_sep, char hour_sep);

/* Parameters:
 *     char sep -- CSV separator
 * Return: String -- value of the readings
 */
String getTemperatureData(char sep);

/* Parameters:
 *     char sep -- CSV separator for internal fields
 * Return: String -- value of the readings
 *                   Format: "colorTemp<sep>lux<sep>r<sep>g<sep>b<sep>c<sep>"
 *                        where: colortemp -- int -- temperature color approx                      
 */
// String getLightData(char sep);

#endif
