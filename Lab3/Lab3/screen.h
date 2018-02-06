#include "ST7735.h"

void ST7735_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);

//Draws the circle starting from (10, 80) and with a radius of 54 pixels
//Places numbers around the circle like a clock
void drawClock(void);

void drawHands(uint8_t hour, uint8_t minute);