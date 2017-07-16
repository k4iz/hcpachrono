#ifndef SENSOR_RTC_H
#define SENSOR_RTC_H

void initializeRTC(void);

String getFilenameTimestamp(void);

/* Parameters:
 *     char sep -- CSV separator
 * Return: String -- value of the readings
 */
String getDateTime(char sep, char date_sep, char hour_sep);

#endif
