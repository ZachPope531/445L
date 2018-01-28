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
uint32_t ASCII_Offset = 48;

void ST7735_sDecOut2(int32_t n){
	if (n > 9999) {
		char error_str[6] = " **.**";
		ST7735_OutString(error_str);
		return;
	}
	if (n < -9999) {
		char error_str[6] = "-**.**";
		ST7735_OutString(error_str);
		return;
	}

	char str[6] = "";
	str[3] = '.';
	char buf[4] = { ' ', '0', '0', '0'	};

	int32_t i = n;
	if (i < 0) i = i * -1;
	uint32_t j = 3;
	while (i != 0) {
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
	char buf[5] = { ' ', ' ', '0', '0', '0' };

	uint32_t i = n * 100;
	i = i / 64;

	uint32_t j = 4;
	while (i != 0) {
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
	uint16_t x_coord;
	uint16_t y_coord;
	for(uint16_t i = 0; i < num; i++){
		if(bufX[i] < plot_minX || bufX[i] > plot_maxX || bufY[i] < plot_minY || bufY[i] > plot_maxY){
			continue;
		}
		x_coord = (uint16_t) (bufX[i] - plot_minX) * (120) / (plot_maxX - plot_minX) + 4;
		y_coord = (uint16_t) 120 - (bufY[i] - plot_minY) * (120) / (plot_maxY - plot_minY) + 36;
		ST7735_DrawPixel(x_coord, y_coord, 0x0000);
		ST7735_DrawPixel(x_coord + 1, y_coord, 0x0000);
		ST7735_DrawPixel(x_coord, y_coord + 1, 0x0000);
		ST7735_DrawPixel(x_coord + 1, y_coord + 1, 0x0000);
	}
}
