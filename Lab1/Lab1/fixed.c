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
	
}