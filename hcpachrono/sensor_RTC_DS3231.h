#ifndef SENSOR_RTC_H
#define SENSOR_RTC_H

void init_RTC_DS3231(void);

String getFilenameTimestamp(void);

/* Parameters:
 *     char sep -- CSV separator
 * Return: String -- value of the readings
 */
String read_RTC_DS3231(char sep, char date_sep, char hour_sep);

#endif
