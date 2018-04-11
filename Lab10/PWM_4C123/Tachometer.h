#include <stdint.h>

int currentTicks;
int currentRPM;

/*
Initialize PF2 as a rising edge interrupt to take in the tachometer signal
Inputs:		None
Outputs:	None
*/
void PortF_Init(void);

/*
Updates the current number of ticks
Inputs:		None
Outputs:	None
*/
void PortF_Handler(void);

/*
PI loop here?
*/
