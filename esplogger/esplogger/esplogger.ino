#include <Arduino.h>
#include <SoftwareSerial.h>
#include "nodemcu_pinout.h"


#define     BAUDRATE  115200

#define     ARDUINO_TX        D6    // (soft RX)
#define     ARDUINO_RX        D7    // (soft TX)
#define     ARDUINO_BAUDRATE  115200

#define _SS_MAX_RX_BUFF 256 // RX buffer size

SoftwareSerial arduinoSerial(ARDUINO_TX, ARDUINO_RX);  // RX, TX

void setup()
{
 	Serial.begin(BAUDRATE);
 	Serial.print("Initializing Arduino Software Serial..\t");
    arduinoSerial.begin(ARDUINO_BAUDRATE);
   	Serial.println("done!");
}


void loop()
{
	// Serial.println("Sending byte 'r' to Arduino..");
	// arduinoSerial.write('r');
	// delay(5000);
	// if (arduinoSerial.available())
	// {
	// 	Serial.print(arduinoSerial.readString());
	// }
	// arduinoSerial.flush();

	

	if (arduinoSerial.available()) 
	{
    	Serial.write(arduinoSerial.read());
  	}
  	if (Serial.available()) 
  	{
  		char c = Serial.read();
  		Serial.write(c);
    	arduinoSerial.write(c);
  	}
}
