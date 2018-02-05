// ADCTestMain.c
// Runs on TM4C123
// This program periodically samples ADC channel 0 and stores the
// result to a global variable that can be accessed with the JTAG
// debugger and viewed with the variable watch feature.
// Daniel Valvano
// September 5, 2015

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// center of X-ohm potentiometer connected to PE3/AIN0
// bottom of X-ohm potentiometer connected to ground
// top of X-ohm potentiometer connected to +3.3V 
#include <stdint.h>
#include "ADCSWTrigger.h"
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "Timer1.h"
#include "ST7735_Line.h"

#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF1             (*((volatile uint32_t *)0x40025008))
#define SIZE 1000
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

volatile uint32_t ADCvalue;

volatile uint32_t time_dump[SIZE];
volatile uint32_t data_dump[SIZE];
volatile uint16_t dump_index;
extern volatile uint32_t time;

volatile int ready;

// This debug function initializes Timer0A to request interrupts
// at a 100 Hz frequency.  It is similar to FreqMeasure.c.
void Timer0A_Init100HzInt(void){
  volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER0_TAILR_R = 799999;         // start value for 100 Hz interrupts
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 2
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; // top 3 bits
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
	
	dump_index = 0;
}


void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
  PF2 ^= 0x04;                   // profile
  PF2 ^= 0x04;                   // profile
  ADCvalue = ADC0_InSeq3();
  PF2 ^= 0x04;                   // profile
	
	
	//Time and data dump
	if(dump_index < SIZE){
		Timer1A_Handler();
		time_dump[dump_index] = time;
		data_dump[dump_index] = ADCvalue;
		ready = 0;
		
		dump_index++;
	} else {
		//Set a breakpoint here
		ready = 1;
		//dump_index = dump_index;
		//dump_index = 0;
	}
	
}

void Time_Process(void){
	//return jitter or make global?
	uint32_t jitter;
	int32_t min, max;
	min = time_dump[1] - time_dump[0];
	max = time_dump[1] - time_dump[0];
	int i;
	for (i = 2; i < SIZE; i++){
		int32_t diff = time_dump[i] - time_dump[i-1];
		if (max < diff) max = diff;
		if (min > diff) min = diff;
	}
	jitter = max - min;
	
	return;
}

void Data_Process(void){
	// how to plot?
	int32_t range;
	uint32_t min;
	uint32_t max;
	int i, j;
	for (i = 0; i < SIZE; i++){
		for (j = 0; j < i; j++) {
			if (data_dump[j] > data_dump[i]){
				int temp = data_dump[j];
				data_dump[j] = data_dump[i];
				data_dump[i] = temp;
			}
		}
	}
	
	min = data_dump[0];
	max = data_dump[SIZE-1];
	
	ST7735_PlotClear(0, 159);
	
	uint32_t ADC = 1950;
	int y = 0;
	
// check min and max
//	ST7735_OutUDec(min);
//	ST7735_OutChar(' ');
//	ST7735_OutUDec(max);
	
	for (i = 0; i < SIZE; i++){
		if (data_dump[i] == ADC) y++;
		else if (data_dump[i] > ADC) {
				while(data_dump[i] > ADC){
				ST7735_PlotBar(y);
				ST7735_PlotNext();
				y = 0;
				ADC++;
			}
		}
	}

	//arrange data into plottable form

	//ST7735_OutUDec(range);
	
	return;
}

int main(void){
  PLL_Init(Bus80MHz);                   // 80 MHz	
  SYSCTL_RCGCGPIO_R |= 0x20;            // activate port F
  ADC0_InitSWTriggerSeq3_Ch9();         // allow time to finish activating
  Timer0A_Init100HzInt();               // set up Timer0A for 100 Hz interrupts
	
	//Add Timer1 for debug purposes
	//Reads time in 12.5 ns intervals
	Timer1_Init();
	
  GPIO_PORTF_DIR_R |= 0x06;             // make PF2, PF1 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x06;          // disable alt funct on PF2, PF1
  GPIO_PORTF_DEN_R |= 0x06;             // enable digital I/O on PF2, PF1
                                        // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF
  PF2 = 1;                      				// turn on LED
	ST7735_InitR(INITR_REDTAB);						// Turn on the screen
  EnableInterrupts();
  while(1){
    PF1 ^= 0x02;  // toggles when running in main
		if (ready == 1) {
			Time_Process();
			Data_Process();
			ready = 0;
			dump_index = 0;
		}
  }
}


