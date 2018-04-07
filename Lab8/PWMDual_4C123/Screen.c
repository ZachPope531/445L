/* screen.c */

//Initializes the screen and clears it
void screenInit(void){
	ST7735_InitB();
}

//Prints the current data to the screen
//Speed, connection status
void printData(uint8_t speed, const char *status){
	ST7735_SetCursor(0, 0);
	ST7735_OutUDec(speed);
	ST7735_SetCursor(1, 0);
	ST7735_DrawChar(status);
}