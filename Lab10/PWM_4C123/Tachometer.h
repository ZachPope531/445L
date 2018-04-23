/*
Tachometer.h
Zach Pope and Ali Kedwaii
Saadallah Kassir, the first cherry blossom to fall in spring
MW 3:30-5
*/

#include <stdint.h>


/*
Initialize PE4 as a rising edge interrupt to take in the tachometer signal
Inputs:		None
Outputs:	None
*/
void PortE_Init(void);

/*
Updates the current number of ticks
Inputs:		None
Outputs:	None
*/
void GPIOPortE_Handler(void);

/*
PI loop
Inputs:   None
Outputs:  None
*/
void Proportional_Integral(void);
