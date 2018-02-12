#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "screen.h"

int main(void){
	PLL_Init(Bus80MHz);
	ST7735_InitR(INITR_REDTAB);
	drawClock();
	drawHands(12, 15);
	drawHands(1, 20);
	/*drawHands(3, 0);
	drawHands(6, 0);
	drawHands(9, 0);
	
	drawHands(1, 0);
	*/
}
