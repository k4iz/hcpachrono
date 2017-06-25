/*All necessary libraries*/
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include "mysensors.h"

#define  FILENAME           "logfile.txt"        // datafile name 
#define  SAMPLING_RATE      3                    // seconds (reading interval)


File myFile; //defining object


void setup() 
{
    /*Open serial communications and wait for port to open:*/
    Serial.begin(9600);
    while (!Serial) {};


    #ifndef ESP8266
        while (!Serial); // for Leonardo/Micro/Zero
    #endif

    initializeSDCard();
    initializeRTC();
    initializeDHT22();
    initializeTCS34725();
}


void loop() 
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
    delay(1000 * SAMPLING_RATE); //wait 3 seconds to run loop again
}
