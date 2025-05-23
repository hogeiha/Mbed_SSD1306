/*********************************************************************
This is a library for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

These displays use SPI to communicate, 4 or 5 pins are required to  
interface

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

/*
 *  Modified by Neal Horman 7/14/2012 for use in LPC1768
 */

#ifndef _ADAFRUIT_SSD1306_H_
#define _ADAFRUIT_SSD1306_H_

#include "mbed.h"
#include "Adafruit_GFX.h"

/*=========================================================================
    SSD1306 Displays
    -----------------------------------------------------------------------
    The driver is used in multiple displays (128x64, 128x32, etc.).
    Select the appropriate display below to create an appropriately
    sized framebuffer, etc.

    SSD1306_128_64  128x64 pixel display

    SSD1306_128_32  128x32 pixel display

    You also need to set the LCDWIDTH and LCDHEIGHT defines to an 
    appropriate size

    -----------------------------------------------------------------------*/
#define SSD1306_128_64
//#define SSD1306_128_32
/*=========================================================================*/

#if defined SSD1306_128_64 && defined SSD1306_128_32
    #error "Only one SSD1306 display can be specified at once in SSD1306.h"
#endif
#if !defined SSD1306_128_64 && !defined SSD1306_128_32
    #error "At least one SSD1306 display must be specified in SSD1306.h"
#endif

#if defined SSD1306_128_64
    #define SSD1306_LCDWIDTH 128
    #define SSD1306_LCDHEIGHT 64
#endif
#if defined SSD1306_128_32
    #define SSD1306_LCDWIDTH 128
    #define SSD1306_LCDHEIGHT 32
#endif

#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF
#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA
#define SSD1306_SETVCOMDETECT 0xDB
#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9
#define SSD1306_SETMULTIPLEX 0xA8
#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10
#define SSD1306_SETSTARTLINE 0x40
#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8
#define SSD1306_SEGREMAP 0xA0
#define SSD1306_CHARGEPUMP 0x8D
#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// an DigitalOut sub-class that provides a constructed default state
class DigitalOut2 : public DigitalOut
{
public:
    DigitalOut2(PinName pin, bool active = false) : DigitalOut(pin) { write(active); };
    DigitalOut2& operator= (int value) { write(value); return *this; };
    DigitalOut2& operator= (DigitalOut2& rhs) { write(rhs.read()); return *this; };
    operator int() { return read(); };
};

class Adafruit_SSD1306 : public Adafruit_GFX
{
 public:
    Adafruit_SSD1306(SPI &spi, PinName DC, PinName RST, PinName CS);
    void begin(uint8_t switchvcc = SSD1306_SWITCHCAPVCC);
    void ssd1306_command(uint8_t c);
    void ssd1306_data(uint8_t c);
    
    void clearDisplay(void);
    virtual void invertDisplay(bool i);
    void display();
    
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color);
    
private:
    DigitalOut2 rst,cs,dc;
    SPI &mspi;
    // the memory buffer for the LCD
    uint8_t buffer[SSD1306_LCDHEIGHT * SSD1306_LCDWIDTH / 8];
};

#endif
