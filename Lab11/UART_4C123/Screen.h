/*Screen.h
Sets up the screen to display connection status, speed, etc
*/

#include "ST7735.h"
#include <stdint.h>

//Initializes the screen and clears it
void Screen_Init(void);

//Prints the current data to the screen
//Speed, connection status
void printData(uint8_t speed, char status, int cursor);