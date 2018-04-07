/* screen.c */

#include <stdint.h>
#include "ST7735.h"

//Initializes the screen and clears it
void screenInit(void){
	ST7735_InitR(INITR_REDTAB);
}

//Prints the current data to the screen
//Speed, connection status
void printData(uint8_t speed, char status){
	ST7735_SetCursor(0, 0);
	ST7735_OutUDec(speed);
	ST7735_SetCursor(1, 0);
	ST7735_OutChar(status);
}