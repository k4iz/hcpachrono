
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
data | A1           | D4 (GPIO 2)
 
### I2C

* RTC DS3231 (Real Time Clock)
* TCS34725 (RGB Light Sensor)

desc | pin Arduino | pin NodeMCU
-----|-------------|--------------
SDA  | A4          | D2 (GPIO 4)
SCL  | A5          | D1 (GPIO 5)

## Installing Firmware

### With Arduino IDE

1. Copy all contents of the "lib/" directory to your "Arduino/libraries" folder.

2. Open the "hcpachrono/hcpachrono.ino" file with the Arduino IDE.

3. Select the board model on the IDE (ex: Arduino Uno).

4. Plug the USB cable with the board;

5. Select the port on the IDE (COMx on Windows or /dev/ttyACMx on Linux).

6. Click on the right arrow button (==>) to compile and upload (or simply Ctrl+U).

7. Open the serial monitor (Ctrl+Shift+M) for checking;

### With Platformio

1. Make sure commands "plaformio" and "make" are available on your terminal.

2. On the root of this repo there is a Makefile. Open it and configure your board and baud rate at the top variables.

3. Simply execute "make" to perform build & upload & monitor all at once.

4. You can execute individual targets, for instance "make monitor".

5. Use "make clean" to start fresh.

