#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "screen.h"

int main(void){
	PLL_Init(Bus80MHz);
	ST7735_InitR(INITR_REDTAB);
	drawHands(1, 15);
	ST7735_FillScreen(0x0000);
	drawHands(2, 15);
	ST7735_FillScreen(0x0000);
	drawHands(3, 15);
	ST7735_FillScreen(0x0000);
	drawHands(4, 15);
	ST7735_FillScreen(0x0000);
}
