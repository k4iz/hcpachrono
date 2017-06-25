/*All necessary libraries*/
#include <SD.h>
#include <SPI.h>
#include <RTClib.h>
#include <Wire.h>
#include <Adafruit_TCS34725.h>
#include <DHT.h>

#define  FILENAME           "logfile.txt"        // datafile name 
#define  SAMPLING_RATE      3                    // seconds (reading interval)

/*DS3231 parameters*/
RTC_DS3231 rtc; //defining object

/*TCS34725 parameters*/
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_700MS, TCS34725_GAIN_1X);

/*DHT22 parameters*/
#ifdef __AVR
    #define DHTPIN 2 // Pin 2 on Arduino Uno
#elif defined(ESP8266)
    #define DHTPIN 2 // GPIO 2 | D4 on Nodemcu
#endif

#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

/*SD card parameters*/
#ifdef __AVR
    const int pinCS = 4; // Pin 4 on Arduino Uno
#elif defined(ESP8266)
    const int pinCS = 15; // GPIO 15 | D8 on Nodemcu
#endif

File myFile; //defining object

/*Declaring necessary functions - C/C++ syntax*/
void printDateTime(File myFile);
void printTemperetureData(File myFile);
void printLightData(File myFile);


void setup() 
{

    /*Open serial communications and wait for port to open:*/
    Serial.begin(9600);
    while (!Serial) {};

    /*initializing SD card*/
    Serial.print("Initializing SD card...");
    if (!SD.begin(pinCS)) 
    {
        Serial.println("Card failed, or not present");
        while (1) { yield(); }; //if there is no SD card present, the program does nothing
    }
    Serial.println("SD Card initialized.");


    #ifndef ESP8266
        while (!Serial); // for Leonardo/Micro/Zero
    #endif
    /*initializing DS3231(rtc)*/
    Serial.println("DS3231 initialized");
    rtc.begin();
    
    /*setting time*/
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    Serial.println("RTC was set");
    
    /*initializing TCS34725*/
    if (tcs.begin()) 
    {
      Serial.println("TCS34725 initialized");
    } 
    else 
    {
        Serial.println("No TCS34725 found ... check your connections");
        while (1);
    }
    /*initializing DHT22*/
    Serial.println("DHT22 initialized");
    dht.begin();
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


void printDateTime(File myFile)
{
    /*DS3231*/
    Serial.println("DS3231:");

    DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('-');
    Serial.print(now.month(), DEC);
    Serial.print('-');
    Serial.print(now.day(), DEC);
    Serial.print(' ');
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    myFile.print(now.year(), DEC);
    myFile.print('-');
    myFile.print(now.month(), DEC);
    myFile.print('-');
    myFile.print(now.day(), DEC);
    myFile.print(' ');
    myFile.print(now.hour(), DEC);
    myFile.print(':');
    myFile.print(now.minute(), DEC);
    myFile.print(':');
    myFile.print(now.second(), DEC);
}


void printTemperetureData(File myFile)
{
    /*DHT22*/
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
    Serial.print(" %%\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print("Heat index: ");
    Serial.print(hic);
    Serial.println(" *C ");
    Serial.println(" ");

    //write DHT22 data in the card (h, t, hic)
    myFile.print(h);
    myFile.print(",");
    myFile.print(t);
    myFile.print(",");
    myFile.println(hic);
}


void printLightData(File myFile)
{ 

    /*TCS34725*/
    Serial.println("TCS34725:");

    tcs.setInterrupt(true);  //turn off LED

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
}