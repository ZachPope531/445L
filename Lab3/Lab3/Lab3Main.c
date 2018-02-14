#include <stdio.h>
#include <stdint.h>
#include "ST7735.h"
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"
#include "screen.h"
#include "speaker.h"
#include "timer.h"
#include "switch.h"
#include "ADC.h"

extern volatile enum displaymode currentDisplay;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

int main(void){
	PLL_Init(Bus80MHz);
	ST7735_InitR(INITR_REDTAB);
	Timer0A_Init1HzInt();
	Timer1_Init();
	ADC0_InitSWTriggerSeq3_Ch9();
	EdgeCounter_Init();
	PortB_Init();
	Timer2_Init(181818);
	EnableInterrupts();
	
	//Alarm_On();
	while(1){
		static uint16_t blah = 1;
		blah++;
	}
}
