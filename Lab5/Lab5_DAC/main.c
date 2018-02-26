
#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include "PLL.h"
#include "timer.h"
#include "DAC.h"


void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

const unsigned short Wave[32] = {
	1024,1122,1215,1302,1378,1440,1486,1514,1524,1514,1486,
	1440,1378,1302,1215,1122,1024,926,833,746,670,608,
	562,534,524,534,562,608,670,746,833,926
};

void PlayNext(void){
  static uint8_t index = 0;        // counting index of output sequence
  DAC_Out(Wave[index]);         // output next value in sequence
  index = (index + 1)&0x1F;        // increment counter
}

int main(void){ 
  PLL_Init(Bus16MHz);              // bus clock at 16 MHz
	
	DAC_Init(0x1000);
	uint16_t frequency = 1136;
	Timer0A_Init(&PlayNext, 1136);
	
	while(1){
		Timer0A_ChangeFrequency(frequency);
		frequency -= 10;
		for(int i = 0; i < 363630; i++){
		}
		if(frequency < 20){
			frequency = 500000/523;
		}
	}
}
