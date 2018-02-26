#include "switch.h"


extern volatile uint16_t DAC_Index;

void music_play(){
	Timer0A_Enable();
}

void music_pause(){
	Timer0A_Disable();
}

void music_reset(){
	music_pause();
	DAC_Index = 0;
}
