/*All necessary libraries*/
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "mysensors.h"

// Uncomment to enable printing out nice debug messages.
#define  DHT_DEBUG

// #define  SAMPLING_RATE      10                    // seconds (reading interval)

/*Setting up CAYENNE*/
//#define CAYENNE_DEBUG
// #define CAYENNE_PRINT Serial
// #include <CayenneMQTTESP8266.h>

//network info
// char ssid[] = "GVT-2707";
// char wifiPassword[] = "S1F6542520";

//Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
// char username[] = "444972e0-286d-11e7-a4a6-237007b7399c";
// char password[] = "9c85871452d250e2a28630b16b0f0dbdf5d81e1e";
// char clientID[] = "40096c10-59ed-11e7-9118-bfd202a30a41";

// unsigned long lastMillis = 0;

// bool datalog_timeout=false;

void datalog(void);

String filename = "dados.txt";

void setup() 
{
    /*Open serial communications and wait for port to open:*/
    Serial.begin(9600);
    // while (!Serial) {};

    #ifndef ESP8266
        // while (!Serial); // for Leonardo/Micro/Zero
    #endif

    // Cayenne.begin(username, password, clientID, ssid, wifiPassword);

    initializeSDCard();
    initializeRTC();
    // initializeDHT22();
    initializeTCS34725();
}


void loop() 
{
    datalog();
    delay(5000);
}


void datalog(void)
{
    /*sd card*/
    File myFile;     //defining object 
    char sep='\t';   // CSV datalog line separator

    myFile = SD.open(filename.c_str(), FILE_WRITE);

    if (myFile) 
    {
        String log_line="";

        log_line += getDateTime(sep, '-', ':') + sep;
        // log_line += getTemperatureData(sep) + sep;
        log_line += getLightData(sep);
        log_line += "\r\n";  // NEW LINE windows style
 
        Serial.print("[DEBUG] ");
        Serial.print(log_line);
        myFile.print(log_line);
        myFile.close();
        Serial.println("[INFO] Datalog written at '" + filename + "'");
    } 
    else 
    {
        /*if the file didn't open, print an error:*/
        Serial.println("[ERROR] Could not open file '" + filename + "'");
    }    
}

/*********************************************************************
 * timer callback 
 *********************************************************************/
// void datalog(void)
// {
// 	datalog_timeout = true;
// }

//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
// CAYENNE_IN_DEFUALT()
// {
//     CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
//     //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
// }