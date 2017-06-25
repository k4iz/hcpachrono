//All necessary libraries
#include <SD.h>
#include <SPI.h>
#include <RTClib.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <DHT.h>

//DS3231 parameters
//DS3231  rtc(SDA, SCL);
RTC_DS3231 rtc;

//TCS34725 parameters
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

//DHT22 parameters
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

//SD card parameters
const int pinCS = 4; // Pin 10 on Arduino Uno


void setup() {

  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  //initializing SD card
  Serial.print("Initializing SD card...");
  if (!SD.begin(pinCS)) {
    Serial.println("Card failed, or not present");
    return; //if there is no SD card present, the program does nothing
  }
  Serial.println("SD Card initialized.");

  //initializing DS3231(rtc)
  Serial.println("DS3231 initialized");
  rtc.begin();

  //initializing TCS34725
  if (tcs.begin()) {
  Serial.println("TCS34725 initialized");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
    }
  //initializing DHT22
  Serial.println("DHT22 initialized");
  dht.begin();

}

void loop(void) {

  //DS3231
  Serial.println("DS3231:");

  DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

  /*problems saving getTimeStr into a variable
  Serial.print("Date: ");
//  Serial.print(rtc.getDateStr());
  Serial.print(", ");

  Serial.print("Time: ");
  Serial.print(rtc.getTimeStr());
  Serial.print(", ");

  float temp_rtc = rtc.getTemp();
  Serial.print("Temperature RTC: ");
  Serial.println(temp_rtc);
  Serial.println(" ");
  */


  //TCS34725
  Serial.println("TCS34725:");

  tcs.setInterrupt(true);  // turn off LED

  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);

  Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  Serial.print("C: "); Serial.print(c, DEC); Serial.println(" ");
  Serial.println(" ");


  //DHT22
  Serial.println("DHT22:");

  float h = dht.readHumidity();
  float t = dht.readTemperature(); //read temperature as Celcius, for Fahrenheit put argument as "true"

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print("Heat index: ");
  Serial.print(hic);
  Serial.println(" *C ");
  Serial.println(" ");


  //just giving some space between all sensors readings
  Serial.println(" ");
  Serial.println(" ");


  //SD
  File myFile = SD.open("logfile.txt", FILE_WRITE);

  //Files will be written in the following order:
  if (myFile) {

    //write rtc data in SD card (time_rtc, temp_rtc)
    
    /*
    myFile.print(rtc.getDateStr());
    myFile.print(",");
    myFile.print(rtc.getTimeStr());
    myFile.print(",");
    myFile.print(temp_rtc);
    myFile.print(",");
    */

    //write TCS34725 data in the card (colorTemp, lux, r, g, b, c)
    myFile.print(colorTemp);
    myFile.print(",");
    myFile.print(lux);
    myFile.print(",");
    myFile.print(r);
    myFile.print(",");
    myFile.print(g);
    myFile.print(",");
    myFile.print(b);
    myFile.print(",");
    myFile.print(c);

    //write DHT22 data in the card (h, t, hic)
    myFile.print(h);
    myFile.print(",");
    myFile.print(t);
    myFile.print(",");
    myFile.println(hic);


    myFile.close(); // close the file
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening logfile.txt");
    }

  delay(10000); //wait 3 seconds to run loop again
}
