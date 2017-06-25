/*All necessary libraries*/
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <Ticker.h>
//#include <ESP8266WiFi.h>
#include "mysensors.h"


#define  FILENAME           "logfile.txt"        // datafile name 
#define  SAMPLING_RATE      10                    // seconds (reading interval)

/*sd card*/
File myFile; //defining object

Ticker datalogTimer;

/*Setting up CAYENNE*/
//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

//network info
char ssid[] = "GVT-2707";
char wifiPassword[] = "S1F6542520";

//Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "444972e0-286d-11e7-a4a6-237007b7399c";
char password[] = "9c85871452d250e2a28630b16b0f0dbdf5d81e1e";
char clientID[] = "40096c10-59ed-11e7-9118-bfd202a30a41";

unsigned long lastMillis = 0;

bool datalog_timeout=false;

void datalog(void);

void setup() 
{
    /*Open serial communications and wait for port to open:*/
    Serial.begin(9600);
    while (!Serial) {};

    #ifndef ESP8266
        while (!Serial); // for Leonardo/Micro/Zero
    #endif

    Cayenne.begin(username, password, clientID, ssid, wifiPassword);

    initializeSDCard();
    initializeRTC();
    initializeDHT22();
    initializeTCS34725();

    datalogTimer.attach(SAMPLING_RATE, datalog);
}


void loop() 
{
    Cayenne.loop();

    //Publish data every 10 seconds (10000 milliseconds). Change this value to publish at a different interval.
    if (millis() - lastMillis > 10000) {
        lastMillis = millis();
        //Write data to Cayenne here. This example just sends the current uptime in milliseconds.
        Cayenne.virtualWrite(0, lastMillis);
        //Some examples of other functions you can use to send data.
        //Cayenne.celsiusWrite(1, 22.0);
        //Cayenne.luxWrite(2, 700);
        //Cayenne.virtualWrite(3, 50, TYPE_PROXIMITY, UNIT_CENTIMETER);
    }

    if (datalog_timeout)
    {
		myFile = SD.open(FILENAME, FILE_WRITE);
	    if (myFile) 
	    {
	        printDateTime(myFile);
	        myFile.print(",");

	        printLightData(myFile);
	        myFile.print(",");

	        printTemperetureData(myFile);
	       
	        myFile.close();
	        Serial.println("[OK] Datalog written\n");
	    } 
	    else 
	    {
	      /*if the file didn't open, print an error:*/
	      Serial.println("error opening the log file");
	    } 
	    datalog_timeout = false; 	
    }
    
}

/*********************************************************************
 * timer callback 
 *********************************************************************/
void datalog(void)
{
	datalog_timeout = true;
}

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
// CAYENNE_IN_DEFUALT()
// {
//     CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
//     //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
// }