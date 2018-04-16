#include "LCD.h"
#include "Tachometer.h"

void printSpeed(){
	ST7735_SetCursor(0,0);
	ST7735_OutString("Current RPS: ");
	ST7735_OutUDec(currentRPS);
	ST7735_SetCursor(0,1);
	ST7735_OutString("Desired RPS: ");
	ST7735_OutUDec(desiredRPS);
}