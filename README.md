# hcpachrono

Datalogger for measuring Light and temperature

## Wiring 

### Micro SD card

desc | pin Arduino | pin NodeMCU
-----|-------------|--------------
CLK  | 13          | D5 (GPIO 14)
MIS0 | 12		   | D6 (GPIO 12)
M0SI | 11	       | D7 (GPIO 13)
CS   | 4           | D8 (GPIO 15)

### DHT22 (temperature + humidity)

desc | pin Arduino | pin NodeMCU
-----|-------------|--------------
data | 2           | D4 (GPIO 2)
 
### I2C

* RTC DS3231 (Real Time Clock)
* TCS34725 (RGB Light Sensor)

desc | pin Arduino | pin NodeMCU
-----|-------------|--------------
SDA  | A4          | D2 (GPIO 4)
SCL  | A5          | D1 (GPIO 5)
