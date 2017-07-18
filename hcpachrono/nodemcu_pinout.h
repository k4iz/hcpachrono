/*-----------------------------------------------------------------------------
 *  Author: Nelso G. Jost (nelsojost@gmail.com)
 *  License: GPLv2
 *  Purpose: Mapping of NodeMCU pinout to real ESP GPIO numbers.
 *---------------------------------------------------------------------------*/
#ifndef NODEMCU_PINOUT_H
#define NODEMCU_PINOUT_H

#define  D0  16  // DEEP WAKE
#define  D1   5  // I2C Bus SCL (clock)
#define  D2   4  // I2C Bus SDA (data)
#define  D3   0  // FLASH
#define  D4   2  // LED_BUILTIN (inverted logic)
#define  D5  14  // SPI Bus SCK (clock)
#define  D6  12  // SPI Bus MISO
#define  D7  13  // SPI Bus MOSI
#define  D8  15  // SPI Bus SS (CS)
#define  D9   3  // RX0 (Serial)
#define  D10  1  // TX0 (Serial)

#endif

