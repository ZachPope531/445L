/* screen.c */

#include <stdint.h>
#include "ST7735.h"

//Initializes the screen and clears it
void Screen_Init(void){
	ST7735_InitR(INITR_REDTAB);
}

//Prints the current data to the screen
//Speed, connection status
void printData(uint8_t speed, char status, int cursor){
	ST7735_SetCursor(0, cursor);
	ST7735_OutUDec(speed);
	//ST7735_SetCursor(1, 0);
	ST7735_OutChar(status);
}