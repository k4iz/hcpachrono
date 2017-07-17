#include <RTClib.h>
#include "sensor_rtc.h"

/*DS3231 parameters*/
RTC_DS3231 rtc; //defining object


void initializeRTC(void)
{
    /*initializing DS3231(rtc)*/
    Serial.println("DS3231 initialized");
    rtc.begin();
    
        /*setting time*/
    // following line sets the RTC to the date & time this sketch was compiled
 
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    Serial.println("RTC was set");
}


String getFilenameTimestamp(void)
{
    // OBS: FAT filesystem do not allow more than 8 char for the filename (without extension)
    String filename;
    DateTime now = rtc.now();
    filename = "";
    filename += String(now.month(), DEC);
    filename += String(now.day(), DEC);
    filename += String(now.hour(), DEC);
    filename += String(now.minute(), DEC);
    filename += ".txt";
    return filename;
}


String getDateTime(char sep, char date_sep, char hour_sep)
{
    DateTime now = rtc.now();

    String raw="";
    raw += String(now.year(), DEC) + date_sep;
    raw += String(now.month(), DEC) + date_sep;
    raw += String(now.day(), DEC);
    raw += String(' ');
    raw += String(now.hour(), DEC) + hour_sep;
    raw += String(now.minute(), DEC) + hour_sep;
    raw += String(now.second(), DEC);

    return raw;
}


