#include "ST7735.h"

//Draws a line between (x1, y1) and (x2, y2)
//Input:	x1	The first x coordinate
//				y1	The firsy y coordinate
//				x2	The second x coordinate
//				y2	The second y coordinate
//				color is the hex color value
//				minuteOrHour is 0 if we're drawing a minute hand, 1 for hour
//Ouput:	None
void ST7735_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color, uint8_t minuteOrHour);

//Draws a BMP image of the clock
void drawClock(void);


//Erases the old hands and redraws the new hands
//Input:	hour		Number between 0-24
//				minute	Number between 0-59
//Ouput:	None
void drawHands(uint8_t hour, uint8_t minute);

//Displays the digital clock
//Input:	none
//Output:	none
void digitalClock(void);

//Shows the time until the next alarm
//Input:	none
//Output:	none
void timeUntilAlarm(void);
