#include "ST7735_Line.h"

#define CENTER_X 64
#define CENTER_Y 80

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
	
	if(dy == 0){
		if(endX > CENTER_X){
			ST7735_DrawFastHLine(CENTER_X, CENTER_Y, 40, 0xFFFF);
		} else {
			ST7735_DrawFastHLine(CENTER_X-40, CENTER_Y, 40, 0xFFFF);
		}
		return;
	} else if(dx == 0){
		if(endY > CENTER_Y){
			ST7735_DrawFastVLine(CENTER_X, CENTER_Y, 40, 0xFFFF);
		} else {
			ST7735_DrawFastVLine(CENTER_X, CENTER_Y-40, 40, 0xFFFF);
		}
		return;
	}
	
	for(; y <= endY; y++){
		ST7735_DrawPixel(x, y, color);
		
		error -= dx;
		
		if(error < 0){
			x++;
			error += dy;
		}
	}
}
