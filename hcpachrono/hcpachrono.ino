/* Standard libraries -- relative PATH */
#include <Arduino.h>
// #include <Wire.h>
#include <SD.h>
#include <SPI.h>


/* Project libraries -- absolute PATH */
#include "sensor_RTC_DS3231.h"
#include "sensor_DHT22.h"
#include "sensor_BMP180.h"
#include "sensor_TCS34725_autorange.h" 

#include "sd_log.h"

/**************************************************************************/
/* GLOBAL CONFIGURATIONS */

// #define  BAUDRATE  			 	9600
#define  BAUDRATE  			 	115200
#define  DATALOG_FILENAME    	"DADOS.txt"    // max 8 char (beside extension)
#define  DATALOG_CSV_SEP     	'\t'           // char (ex: ',' or ';' or '\t')
#define  DATALOG_DELAY          5000           // milliseconds
#define  DATALOG_CSV_HEADER     "yyyy-mm-dd HH:MM:ss\tagainx\tlux\tct\tr\tg\tb\tc\thum\ttemp\thi\tpress\talt\ttemp"

// uncoment this to get a simple serial protocol for reading data
// #define  __REPL

/*SD card parameters*/
#ifdef __AVR
	#define  SD_CS_PIN  4 	    // uno
#elif defined(ESP8266)
    #define  SD_CS_PIN  15  	// GPIO 15 | D8 on Nodemcu
#endif

/**************************************************************************/
/* CAYENNE SETUP */

/*Setting up CAYENNE*/
#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// network info
char ssid[] = "GVT-2707";
char wifiPassword[] = "S1F6542520";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "444972e0-286d-11e7-a4a6-237007b7399c";
char password[] = "9c85871452d250e2a28630b16b0f0dbdf5d81e1e";
char clientID[] = "40096c10-59ed-11e7-9118-bfd202a30a41";

/**************************************************************************/

String getDatalogLine(char sep);

char sep=DATALOG_CSV_SEP;
String datalogLine;
String datalogHeader = DATALOG_CSV_HEADER;

DHT22_LOG_t * dht22_log;

void setup() 
{
    Serial.begin(BAUDRATE);
    Serial.println();

    init_RTC_DS3231();             // Real Time Clock
    init_DHT22();                  // Humidity + Temperature
    init_BMP180();                 // Pressure + Temperature + Altitude
    init_TCS34725_autorange();     // Lux + RGB

    initSDCard(SD_CS_PIN);

    if (SD.exists(DATALOG_FILENAME))
    {
        datalogHeader += "\t#";     
    }
    writeDatalogSDCard(String(DATALOG_FILENAME), datalogHeader + "\r\n");

	Serial.println(F(DATALOG_CSV_HEADER));

    Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}


void loop() 
{
#ifdef __REPL
	if (Serial.available())
	{
		char c = Serial.read();
		if (c == 'r')
		{ 
			Serial.print("[READING]\n[DEBUG] ");
			// Serial.print(getDatalogLine(DATALOG_CSV_SEP));

		    Serial.print(read_RTC_DS3231(sep, '-', ':') + sep);
		    Serial.print(read_TCS34725_autorange(sep) + sep);
		    Serial.print(read_DHT22(sep) + sep);
		    Serial.print(read_BMP180(sep) + sep);

			Serial.println("[DONE]");
		}
	}
#else
  	datalogLine = getDatalogLine(DATALOG_CSV_SEP);
    Serial.println("[DEBUG] " + String(DATALOG_CSV_HEADER));
    Serial.print("[DEBUG] " + datalogLine);

    writeDatalogSDCard(String(DATALOG_FILENAME), datalogLine);

    delay(DATALOG_DELAY);
#endif
    Cayenne.virtualWrite(0, dht22_log->temp);
    Cayenne.virtualWrite(1, dht22_log->hum);

    free(dht22_log);
    Cayenne.loop();
}

/* sep (char) -- CSV datalog line separator
 * Example: sep = ',' gives datalog line "a,b,c,...,z"
 */
String getDatalogLine(char sep)
{    
    String s="";
    s += read_RTC_DS3231(sep, '-', ':') + sep;
    s += read_TCS34725_autorange(sep) + sep;
    // s += read_DHT22(sep) + sep;

    dht22_log = read_DHT22_s(sep);
    s += dht22_log->datalog;

    s += read_BMP180(sep) + sep;
    s += "\r\n";  // NEW LINE windows style
    return s;
}

// /*********************************************************************/


//Default function for processing actuator commands from the Cayenne Dashboard.
// You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
// CAYENNE_IN_DEFUALT()
// {
//     CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, 
//                 getValue.getId(), getValue.asString());
//     //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
// }