// PWMDualTest.c
// Runs on TM4C123
// Use PWM0/PB6 and PWM1/PB7 to generate two square waves with 50% duty cycle
// and 180 degrees out of phase.  These two signals plus two digital logic
// inverters are used to drive a stepper motor.  The stepper motor has 200
// steps per revolution and needs to be driven between 1 and 100 revolutions
// per minute.
// 1 rev   1 min    200 step   0.25 pulse   0.83333 pulse
// ----- * ------ * -------- * ---------- = -------------
// 1 min   60 sec    1 rev       1 step         1 sec    
// Daniel Valvano
// September 10, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to ARM Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 6.7, section 6.3.2

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
#include "PLL.h"
#include "MotorController.h"
#include "Screen.h"
#include "rf.h"


void WaitForInterrupt(void);  // low power mode

int main1(void){
  PLL_Init(Bus80MHz);           // bus clock at 80 MHz
	PortB_Init(12500, 12500-500, 500);
	setDirection(0,0);
	changeSpeed(0, 50);
  while(1){
    WaitForInterrupt();
  }
}

int main(void){
	PLL_Init(Bus80MHz);
	Module_Init();
	screenInit();
	while(1){
		WaitForInterrupt();
	}
}
