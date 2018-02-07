#include "screen.h"
#include <math.h>

#define CENTER_X 64
#define CENTER_Y 80

#define PI 3.14159265

volatile uint8_t OldMinute_X = 0;
volatile uint8_t OldMinute_Y = 0;
volatile uint8_t OldHour_X = 0;
volatile uint8_t OldHour_Y = 0;

void ST7735_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
	//Check bounds
	if(y1 > 160 || y2 > 160 || x1 > 128 || x2 > 128){
		return;
	}
	
	//Find start and end points
	uint16_t x = x1 <= x2 ? x1 : x2;
	uint16_t endX = x1 <= x2 ? x2 : x1;
	uint16_t y = y1 <= y2 ? y1 : y2;
	uint16_t endY = y1 <= y2 ? y2 : y1;
	
	/*
		Line drawing algorithm based off of 
		Bresenham's Line Generation Algorithm
		I flipped the usage of dx and dy
		because the screen has a larger height
		than width
	*/
	int16_t dx, dy;
	
	dx = endX - x;
	dy = endY - y;
	
	int16_t error = dy/2;
	
	for(; y <= endY; y++){
		//if(dy > dx){
			ST7735_DrawPixel(x, y, color);
		//} else {
			//ST7735_DrawPixel(y, x, color);
		//}
		
		error -= dx;
		
		if(error < 0){
			x++;
			error += dy;
		}
	}
}

void drawClock(void){
	//Draw circle
	
	//Draw numbers
}

void drawHands(uint8_t hour, uint8_t minute){
	//Convert hour and minute into angle
	uint16_t hourX = (uint16_t) CENTER_X + 27*cos(hour * PI / 6.0 + PI);
	uint16_t hourY = (uint16_t) CENTER_Y + 27*sin(hour * PI / 6.0 + PI);
	uint16_t minuteX = (uint16_t) CENTER_X + 54*cos((180/PI)*minute*6 - PI);
	uint16_t minuteY = (uint16_t) CENTER_Y + 54*sin((180/PI)*minute*6 - PI);
	
	//Erase old hour and minute lines
	ST7735_Line(CENTER_X, CENTER_Y, OldMinute_X, OldMinute_Y, 0x0000);
	ST7735_Line(CENTER_X, CENTER_Y, OldHour_X, OldHour_Y, 0x0000);
	
	//Draw new hour and minute lines
	ST7735_Line(CENTER_X, CENTER_Y, hourX, hourY, 0xFFFF);
	ST7735_Line(CENTER_X, CENTER_Y, minuteX, minuteY, 0xFFFF);
	
	//Update OldTime variables
	OldMinute_X = minuteX;
	OldMinute_Y = minuteY;
	OldHour_X = hourX;
	OldHour_Y = hourY;
}
