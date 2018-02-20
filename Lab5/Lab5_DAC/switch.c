#include "switch.h"

extern volatile uint16_t DAC_Index;

void music_play(){
	
}

void music_pause(){
	
}

void music_reset(){
	music_pause();
	DAC_Index = 0;
}