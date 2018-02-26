/* music.h */

#include "notes.h"
#include "timer0.h"

typedef struct {
	int waveform[32];
	int pitches[100];
	int lengths[100];
} song;
