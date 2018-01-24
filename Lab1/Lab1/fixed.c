#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "fixed.h"

int32_t plot_minX;
int32_t plot_maxX;
int32_t plot_minY;
int32_t plot_maxY;

void ST7735_sDecOut2(int32_t n){
	return;
}

void ST7735_uBinOut6(uint32_t n){
	return;
}

void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY){
	Output_Init();
	ST7735_SetCursor(0,0);
	ST7735_OutString(title);
	ST7735_FillRect(4, 160-124, 120, 120, 0xFFFF);
	plot_minX = minX;
	plot_maxX = maxX;
	plot_minY = minY;
	plot_maxY = maxY;
}

void ST7735_XYplot(uint32_t num, int32_t bufX[], int32_t bufY[]){
	int32_t x_coord_32b;
	int32_t y_coord_32b;
	uint16_t x_coord_16b;
	uint16_t y_coord_16b;
	for(uint16_t i = 0; i < num; i++){
		x_coord_32b = bufX[i];
		y_coord_32b = bufY[i];
		if(x_coord_32b < plot_minX || x_coord_32b > plot_maxX || y_coord_32b < plot_minY || y_coord_32b > plot_maxY){
			continue;
		}
		x_coord_16b = (uint16_t) (x_coord_32b - plot_minX) * (128) / (plot_maxX - plot_minX);
		y_coord_16b = (uint16_t) (y_coord_32b - plot_minY) * (128) / (plot_maxY - plot_minY);
		ST7735_DrawPixel(x_coord_16b, y_coord_16b, 0x0000);
		ST7735_DrawPixel(x_coord_16b + 1, y_coord_16b, 0x0000);
		ST7735_DrawPixel(x_coord_16b, y_coord_16b + 1, 0x0000);
		ST7735_DrawPixel(x_coord_16b + 1, y_coord_16b + 1, 0x0000);
	}
}
