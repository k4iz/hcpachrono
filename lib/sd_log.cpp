#include <SD.h>
#include <SPI.h>
#include "sd_log.h"


bool initSDCard(int pinCS)
{
    Serial.print("Initializing SD card...\t");
    if (!SD.begin(pinCS)) 
    {
        Serial.println("Card failed, or not present");
        return false;
    }
    Serial.println("SD Card initialized.");
    return true;
}


bool writeDatalogSDCard(String filename, String datalogLine)
{
	File sdFile = SD.open(filename.c_str(), FILE_WRITE);
    if (sdFile) 
    {
		sdFile.print(datalogLine);
    	sdFile.close();
		Serial.println("[INFO] Datalog line written at '" + filename + "'"); 	
		return true;
    } 
    else 
    {
        Serial.println("[ERROR] Unable to write at file '" + filename + "'");
        return false;
    }    
}
