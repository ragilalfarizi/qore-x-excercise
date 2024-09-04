# PIN OUT

| Function | GPIO |
| -------- | ---- |
| LCD_DC   | IO27 |
| LCD_CS   | IO25 |
| LCD_SCLK | IO18 |
| LCD_MOSI | IO23 |
| LCD_BKL  | IO13 |



---
```cpp
#define ST7789_DRIVER      // Full configuration option, define additional parameters below for this display
#define TFT_WIDTH  240 // ST7789 240 x 240 and 240 x 320
#define TFT_HEIGHT 320 // ST7789 240 x 320
// #define TFT_BL   32            // LED back-light control pin

// For NodeMCU - use pin numbers in the form PIN_Dx where Dx is the NodeMCU pin designation
#define TFT_MISO  PIN_D6  // Automatically assigned with ESP8266 if not defined
#define TFT_MOSI  PIN_D7  // Automatically assigned with ESP8266 if not defined
#define TFT_SCLK  PIN_D5  // Automatically assigned with ESP8266 if not defined

#define TFT_CS    PIN_D8  // Chip select control pin D8
#define TFT_DC    PIN_D3  // Data Command control pin
#define TFT_RST   PIN_D4  // Reset pin (could connect to NodeMCU RST, see next line)

//#define TOUCH_CS 21     // Chip select pin (T_CS) of touch screen

#define SPI_FREQUENCY  27000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000
```