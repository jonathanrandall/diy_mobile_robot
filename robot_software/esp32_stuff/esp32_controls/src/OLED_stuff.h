#ifndef OLED_STUFF_
#define OLED_STUFF_

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSans9pt7b.h>
// #include "wifi_stuff.h"

#define SCREEN_WIDTH 128 //128 // OLED width,  in pixels
#define SCREEN_HEIGHT 64 // OLED height, in pixels
#define OLED_RESET -1

// create an OLED display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


//Adafruit_SSD1306 display(OLED_RESET);



#endif