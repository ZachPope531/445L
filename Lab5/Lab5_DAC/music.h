/* music.h */

#include "notes.h"
//#include "timer0.h"

typedef struct {
	int waveform[32];
	int pitches[206]; //34 + 34 + 34 + 34 + 26 + 26 + 17
	int lengths[206];
} song;
