/*Screen.h
Sets up the screen to display connection status, speed, etc
*/

#include "ST7735.h"

//Initializes the screen and clears it
void screenInit(void);

//Prints the current data to the screen
//Speed, connection status
void printData(uint8_t speed, const char *status);