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
void PortE_Handler(void);

/*
PI loop here?
*/
