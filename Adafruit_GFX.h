/***********************************
This is a our graphics core library, for all our displays. 
We'll be adapting all the
existing libaries to use this core to make updating, support 
and upgrading easier!

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above must be included in any redistribution
****************************************/

/*
 *  Modified by Neal Horman 7/14/2012 for use in LPC1768
 */

#ifndef _ADAFRUIT_GFX_H_
#define _ADAFRUIT_GFX_H_

static inline void swap(int16_t &a, int16_t &b)
{
    int16_t t = a;
    
    a = b;
    b = t;
}

#ifndef _BV
#define _BV(bit) (1<<(bit))
#endif

#define BLACK 0
#define WHITE 1

class Adafruit_GFX : public Stream
{
 public:
    Adafruit_GFX(int16_t w, int16_t h)
        : _rawWidth(w)
        , _rawHeight(h)
        , _width(w)
        , _height(h)
        , cursor_x(0)
        , cursor_y(0)
        , textcolor(WHITE)
        , textbgcolor(BLACK)
        , textsize(1)
        , rotation(0)
        , wrap(true)
        {};

    // this must be defined by the subclass
    virtual void drawPixel(int16_t x, int16_t y, uint16_t color) = 0;
    // this is optional
    virtual void invertDisplay(bool i) {};
    
    // Stream implementation - provides printf() interface
    // You would otherwise be forced to use writeChar()
    virtual int _putc(int value) { return writeChar(value); };
    virtual int _getc() { return -1; };

#ifdef WANT_ABSTRACTS
    // these are 'generic' drawing functions, so we can share them!
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    virtual void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color);
    virtual void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t color);
    virtual void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    virtual void fillScreen(uint16_t color);

    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint16_t color);

    void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void drawRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
    void fillRoundRect(int16_t x0, int16_t y0, int16_t w, int16_t h, int16_t radius, uint16_t color);
#endif

    void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint16_t color);
    void drawChar(int16_t x, int16_t y, unsigned char c, uint16_t color, uint16_t bg, uint8_t size);
    size_t writeChar(uint8_t);

    int16_t width(void) { return _width; };
    int16_t height(void) { return _height; };

    void setCursor(int16_t x, int16_t y) { cursor_x = x; cursor_y = y; };
    void setTextSize(uint8_t s) { textsize = (s > 0) ? s : 1; };
    void setTextColor(uint16_t c) { textcolor = c; textbgcolor = c; }
    void setTextColor(uint16_t c, uint16_t b) { textcolor = c; textbgcolor = b; };
    void setTextWrap(bool w) { wrap = w; };

    void setRotation(uint8_t r);
    uint8_t getRotation(void) { rotation %= 4; return rotation; };

protected:
    int16_t  _rawWidth, _rawHeight;   // this is the 'raw' display w/h - never changes
    int16_t  _width, _height; // dependent on rotation
    int16_t  cursor_x, cursor_y;
    uint16_t textcolor, textbgcolor;
    uint8_t  textsize;
    uint8_t  rotation;
    bool  wrap; // If set, 'wrap' text at right edge of display
};

#endif
