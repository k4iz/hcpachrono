#ifndef MYSENSORS_H
#define MYSENSORS_H

/*Declaring necessary functions - C/C++ syntax*/
void initializeSDCard(void);
void initializeRTC(void);
void initializeDHT22(void);
void initializeTCS34725(void);   

void printDateTime(File myFile);
void printTemperetureData(File myFile);
void printLightData(File myFile);

#endif
