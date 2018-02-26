#include <stdint.h>


/**
	Starts playing the sound from it's current spot
	Picks up from where DAC_Index is currently set
	Inputs:		None
	Outputs:	None
*/
void play(void);

/**
	Stops playing the sound at it's current spot
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