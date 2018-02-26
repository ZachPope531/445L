/* music.c */

#include "music.h"

const unsigned short Flute[32] = {  	
  1007,1252,1374,1548,1698,1797,1825,1797,1675,1562,1383,	
  1219,1092,1007,913,890,833,847,810,777,744,674,	
  598,551,509,476,495,533,589,659,758,876	
};  

song song1 = {
	.waveform = {  	
  1007,1252,1374,1548,1698,1797,1825,1797,1675,1562,1383,	
  1219,1092,1007,913,890,833,847,810,777,744,674,	
  598,551,509,476,495,533,589,659,758,876	
	},
	.pitches = {
		C6, C6, G5, G5, F5, F5, D6, D6, C6, C6, G5, G5, F5, F5, D6, D6, Eb6, Eb6, D6, D6, G6, G6, F6, G6, F6, F6, Eb6, Eb6, D6, D6, C6, C6, Bb5, Bb5,
		C6, C6, G5, G5, F5, F5, D6, D6, C6, C6, G5, G5, F5, F5, D6, D6, Eb6, Eb6, D6, D6, G6, G6, F6, G6, F6, F6, Eb6, Eb6, D6, D6, C6, C6, G6, G6,
		C5, C5, G4, G4, F4, F4, D5, D5, C5, C5, G4, G4, F4, F4, D5, D5, Eb5, Eb5, D5, D5, G5, G5, F5, G5, F5, F5, Eb5, Eb5, D5, D5, C5, C5, Bb4, Bb4,
		C5, C5, G4, G4, F4, F4, D5, D5, C5, C5, G4, G4, F4, F4, D5, D5, Eb5, Eb5, D5, D5, G5, G5, F5, G5, F5, F5, Eb5, Eb5, D5, D5, C5, C5, G5, G5,
		C5, D5, Bb4, C5, G5, F5, G5, Ab5, Bb5, G5, F5, G5, C5, D5, Bb4, C5, G5, F5, Eb5, D5, C5, G5, C6, G5, F5, Eb5,
		C6, D6, Bb5, C6, G6, F6, G6, Ab6, Bb6, G6, F6, G6, C6, D6, Bb5, C6, G6, F6, Eb6, D6, C6, G6, C7, G6, F6, Eb6,
		C6, G5, F5, D5, C5, G4, F4, D4, Ab2, Eb3, Ab3, Bb3, C4, Eb4, Ab4, Bb4, C5, 0
	},
	.lengths = {
		12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 2, 2, 8, 4, 12, 4, 12, 4, 12, 4, 12, 4,
		12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 2, 2, 8, 4, 12, 4, 12, 4, 12, 4, 12, 4,
		12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 2, 2, 8, 4, 12, 4, 12, 4, 12, 4, 12, 4,
		12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 12, 4, 2, 2, 8, 4, 12, 4, 12, 4, 12, 4, 12, 4,
		48, 8, 8, 16, 32, 16, 48, 8, 8, 8, 8, 48, 48, 8, 8, 16, 32, 16, 8, 8, 32, 16, 16, 28, 10, 10,
		48, 8, 8, 16, 32, 16, 48, 8, 8, 8, 8, 48, 48, 8, 8, 16, 32, 16, 8, 8, 32, 16, 16, 28, 10, 10,
		16, 16, 16, 16, 16, 16, 16, 16, 8, 8, 8, 8, 8, 8, 8, 8, 64, 128
	}
};

//song song2 = {
//  .waveform = {
//	1024,1122,1215,1302,1378,1440,1486,1514,1524,1514,1486,
//	1440,1378,1302,1215,1122,1024,926,833,746,670,608,
//	562,534,524,534,562,608,670,746,833,926
//	},
//	.pitches = {
//		C3, D3, E3, F3, G3, A3, B3, C4
//	},
//	.lengths = {
//		16, 8, 8, 8, 8, 8, 8, 16
//	}
//};
