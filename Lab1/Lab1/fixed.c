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
	if (n > 9999) {
		char error_str[6] = " **.**";
		ST7735_OutString(error_str);
		return;
	}
	if (n < -9999) {
		char error_str[6] = "-**.***";
		ST7735_OutString(error_str);
		return;
	}

	char str[6] = "";
	str[3] = '.';
	char buf[4] = { ' ', 0, 0, 0 };

	int32_t i = n;
	uint32_t j = 3;
	while (i != 0 || j < 0) {
		buf[j] = (i % 10) + ASCII_Offset;
		i = i / 10;
		j = j - 1;
	}

	str[5] = buf[3];
	str[4] = buf[2];
	str[2] = buf[1];
	str[1] = buf[0];
	str[0] = ' ';

	if (n < 0) {
		if (str[1] == ' ') str[1] = '-';
		else str[0] = '-';
	}

	ST7735_OutString(str);
	return;
}

void ST7735_uBinOut6(uint32_t n){
	if (n > 63999) {
		char error_str[6] = "***.**";
		ST7735_OutString(error_str);
		return;
	}

	char str[6] = "";
	str[3] = '.';
	char buf[5] = { ' ', ' ', 0, 0, 0 };

	uint32_t i = n * 100;
	i = i / 64;

	uint32_t j = 4;
	while (i != 0 || j < 0) {
		buf[j] = (i % 10) + ASCII_Offset;
		i = i / 10;
		j = j - 1;
	}

	str[5] = buf[4];
	str[4] = buf[3];
	str[2] = buf[2];
	str[1] = buf[1];
	str[0] = buf[0];

	ST7735_OutString(str);
	return;
}

void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY){
	Output_Init();
	ST7735_SetCursor(0,0);
	ST7735_OutString(title);
	ST7735_FillRect(4, 36, 120, 120, 0xFFFF);
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
		x_coord_16b = (uint16_t) (x_coord_32b - plot_minX) * (120) / (plot_maxX - plot_minX) + 4;
		y_coord_16b = (uint16_t) 120 - (y_coord_32b - plot_minY) * (120) / (plot_maxY - plot_minY) + 36;
		ST7735_DrawPixel(x_coord_16b, y_coord_16b, 0x0000);
		ST7735_DrawPixel(x_coord_16b + 1, y_coord_16b, 0x0000);
		ST7735_DrawPixel(x_coord_16b, y_coord_16b + 1, 0x0000);
		ST7735_DrawPixel(x_coord_16b + 1, y_coord_16b + 1, 0x0000);
	}
}
