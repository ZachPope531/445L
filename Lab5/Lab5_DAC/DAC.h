#include <stdint.h>
#include <stdbool.h>
#include "../driverlib/ssi.h"

/**
	Initialize the DAC output using SSI
	Inputs:		None
	Outputs:	None
*/
void DAC_Init(void);


/**
	Send a single value to the DAC
	Inputs:		A 16-bit value between 0-2047
	Outputs:	None
*/
void DAC_Out(uint16_t data);
