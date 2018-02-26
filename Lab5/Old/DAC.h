
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

/**
	Initialize the DAC output using SSI
	Inputs:		None
	Outputs:	None
*/
void DAC_Init(uint16_t data);


/**
	Send a single value to the DAC
	Inputs:		A 16-bit value between 0-2047
	Outputs:	None
*/
void DAC_Out(uint16_t data);
