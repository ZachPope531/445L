// UART1.h
// Runs on LM4F120/TM4C123
// Provide functions that setup and interact with UART


#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "FiFo.h"

// UART initialization function 
// Input: none
// Output: none
void UART1_Init(void);

//------------UART_InChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
// *** Need not be busy-wait if you know when to call
char UART1_InChar(void);

//------------UART_OutChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
void UART1_OutChar(char data);
