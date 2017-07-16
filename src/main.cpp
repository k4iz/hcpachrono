/*All necessary libraries*/
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "sensor_rtc.h"

#define  __USEAUTORANGE

#ifdef __USEAUTORANGE
    #include "sensor_tcs_autorange.h"
#else
    #include "sensor_tcs.h"
    #include "sensor_dht22.h"
#endif

// Uncomment to enable printing out nice debug messages.
// #define  DHT_DEBUG

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


/*SD card parameters*/
#ifdef __AVR
    const int pinCS = 4; // Pin 4 on Arduino Uno
#elif defined(ESP8266)
    const int pinCS = 15; // GPIO 15 | D8 on Nodemcu
#endif


void datalog(void);
void initializeSDCard(void);

String filename = "dados.txt";

void setup() 
{
    /*Open serial communications and wait for port to open:*/
    Serial.begin(115200);
    // while (!Serial) {};

    #ifndef ESP8266
        // while (!Serial); // for Leonardo/Micro/Zero
    #endif

    // Cayenne.begin(username, password, clientID, ssid, wifiPassword);

    initializeSDCard();
    initializeRTC(); 
#ifdef __USEAUTORANGE
    initializeTCS34725_autorange();
#else
    initializeDHT22();    
    initializeTCS34725();
#endif
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
#ifdef __USEAUTORANGE
        log_line += getLightData_autorange(sep);
#else
        log_line += getTemperatureData(sep) + sep;
        log_line += getLightData(sep);        
#endif
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


void initializeSDCard(void)
{

    /*initializing SD card*/
    Serial.print("Initializing SD card...");
    if (!SD.begin(pinCS)) 
    {
        Serial.println("Card failed, or not present");
        while (1) { delay(0); }; //if there is no SD card present, the program does nothing
    }
    Serial.println("SD Card initialized.");

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