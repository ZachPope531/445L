// PWMtest.c
// Runs on TM4C123
// Use PWM0/PB6 and PWM1/PB7 to generate pulse-width modulated outputs.
// Daniel Valvano
// March 28, 2014

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   Program 6.8, section 6.3.2

   "Embedded Systems: Real-Time Operating Systems for ARM Cortex M Microcontrollers",
   ISBN: 978-1466468863, Jonathan Valvano, copyright (c) 2015
   Program 8.4, Section 8.3

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
#include <stdint.h>
#include <stdbool.h>
#include "PLL.h"
#include "PWM.h"
#include "Tachometer.h"
#include "Timer0A.h"
#include "ST7735.h"
#include "LCD.h"
#include "Switch.h"

void DisableInterrupts(void);
void EnableInterrupts(void);

extern uint32_t desiredRPS;
extern uint16_t newDuty;
extern volatile bool printSpeedFlag;

void WaitForInterrupt(void);  // low power mode

int main(void){
  PLL_Init(Bus80MHz);               // bus clock at 80 MHz
	newDuty = 30000;
	desiredRPS = 20;
  PWM0B_Init(40000, 30000);         // initialize PWM0, 1000 Hz, 75% duty
	for(int i = 0; i < 1000000; i++);
	Timer0A_Init(&Proportional_Integral, 80000000); //Set for every second
	ST7735_InitR(INITR_REDTAB);
	Switch_Init();
	PortE_Init();

  while(1){
		WaitForInterrupt();
  }
}
