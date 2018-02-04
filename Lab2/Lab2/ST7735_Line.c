#include "ST7735_Line.h"

void ST7735_Line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
	//Check bounds
	if(y1 > 160 || y2 > 160 || x1 > 128 || x2 > 128){
		return;
	}
	
	//Clear screen
	ST7735_FillScreen(0x0000);
	
	//Find start and end points
	uint16_t x = x1 <= x2 ? x1 : x2;
	uint16_t endX = x1 <= x2 ? x2 : x1;
	uint16_t y = y1 <= y2 ? y1 : y2;
	uint16_t endY = y1 <= y2 ? y2 : y1;
	
	while(x != endX && y != endY){
		ST7735_DrawPixel(x, y, color);
		if(x < endX) x++;
		if(y < endY) y++;
	}
}
