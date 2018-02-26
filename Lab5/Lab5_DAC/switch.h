#include <stdint.h>
#include "timer0.h"
#include "timer1.h"


void Switch_Init(void);

void GPIOPortF_Handler(void);

typedef enum {
	OFF,
	ON
} status;



/**
	Starts playing the sound from its current spot
	Picks up from where DAC_Index is currently set
	Inputs:		None
	Outputs:	None
*/
void play(void);

/**
	Stops playing the sound at its current spot
	Doesn't change DAC_Index to 0
	Inputs:		None
	Outputs:	None
*/
void pause(void);


/**
	Pauses the music and sets DAC_Index to 0
	Inputs:		None
	Outputs:	None
*/
void reset(void);
