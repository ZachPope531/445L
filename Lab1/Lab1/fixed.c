#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "fixed.h"

void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY){
	Output_Init();
}

void ST7735_XYplot(uint32_t num, int32_t bufX[], int32_t bufY[]){
	int32_t x_coord_32b;
	int32_t y_coord_32b;
	int16_t x_coord_16b;
	int16_t y_coord_16b;
	for(uint16_t i = 0; i < num; i++){
		x_coord_32b = bufX[i];
		y_coord_32b = bufY[i];
		//Have to convert fixed point decimal to something usable
		//Map the values to the 160x128 screen?
		ST7735_DrawPixel(x_coord_16b, y_coord_16b, 0xFFFF);
		ST7735_DrawPixel(x_coord_16b + 1, y_coord_16b, 0xFFFF);
		ST7735_DrawPixel(x_coord_16b, y_coord_16b + 1, 0xFFFF);
		ST7735_DrawPixel(x_coord_16b + 1, y_coord_16b + 1, 0xFFFF);
	}
}