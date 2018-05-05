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
#include "rf_tx.h"
#include "rf_rx.h"
//#include "UART.h"
#include "controller.h"
#include "timer0.h"
#include "timer1.h"
#include "UART1.h"
#include "ADC.h"


#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define fresh     1  
#define stale     0
uint32_t Data;      // 12-bit ADC
uint32_t Position;  // 32-bit fixed-point 0.001 cm
int32_t TxCounter = 0, RxCounter = 0;
uint32_t ADC_Mailbox, ADC_Status;
uint32_t GlobalError = 0;
char chardata;
uint32_t char_data;

char ArrayTx[8] = {0x02, 0, 0x2E, 0, 0, 0, 0x0D, 0x03};


void WaitForInterrupt(void);  // low power mode
void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts

void SysTick_Init(void){
	NVIC_ST_CTRL_R = 0;
	NVIC_ST_RELOAD_R = 0x001EB47F;
	NVIC_ST_CURRENT_R = 0;
	NVIC_ST_CTRL_R = 0x00000007;
}

// Get fit from excel and code the convert routine with the constants
// from the curve-fit
uint32_t Convert(uint32_t input){
	uint32_t pos;
	pos = ((input*30)>>6) + 23;
  return pos;
}

int main1(void){
  PLL_Init(Bus80MHz);           // bus clock at 80 MHz
	PortB_Init(12500, 12500-500, 500);
	setDirection(0,0);
	changeSpeed(0, 50);
  while(1){
    WaitForInterrupt();
  }
}

int main2(void){
	PLL_Init(Bus80MHz);
	Controller_Init();
	//Tx_Init();
	SysTick_Init();
	UART1_Init();
	//Timer0A_Init();
	EnableInterrupts();
	while(1){
		WaitForInterrupt();
	}
}

int main(void){
	PLL_Init(Bus80MHz);
	Screen_Init();
	SysTick_Init();
	//ST7735_OutUDec(5);
	//Rx_Init();
	UART1_Init();
	//PortB_Init(12500, 12500-500, 500);
	//setDirection(0,0);
	//changeSpeed(0, 50);
	//Timer1A_Init();
	EnableInterrupts();
	while(1){
		while(FiFo_Get(&chardata)==0){}
		ST7735_SetCursor(0,0);
		/*char_data = 0;
		for (uint32_t i = 0; i < 8; i++){
			FiFo_Get(&chardata);
			if(i==1){
				char_data = (((chardata-0x30)&0xFF)*1000);
			}
			if(i==3){
				char_data += (((chardata-0x30)&0xFF)*100);
			}
			if(i==4){
				char_data += (((chardata-0x30)&0xFF)*10);
			}
			if(i==5){
				char_data += (chardata-0x30)&0xFF;
			}
		}
		LCD_OutFix(char_data);*/
		for(uint32_t i=1; i<=5; i++){
			FiFo_Get(&chardata);
			ST7735_OutChar(chardata);
		}
		FiFo_Get(&chardata);
		FiFo_Get(&chardata);
		ST7735_OutString(" cm");
	}
}

void SysTick_Handler(void){ // every 25 ms
 //Similar to Lab9 except rather than grab sample and put in mailbox
 //        format message and transmit 
	PF2 ^= 0x04;
	ADC_Mailbox = ADCa_In();
	ADC_Status = fresh;
	PF2 ^= 0x04;
	Position = Convert(ADC_Mailbox);
	ArrayTx[5] = (Position%10) + 0x30;
	ArrayTx[4] = ((Position/10)%10) + 0x30;
	ArrayTx[3] = ((Position/100)%10) + 0x30;
	ArrayTx[1] = (Position/1000) + 0x30;
	for (uint32_t i = 0; i < 8; i++){
		UART1_OutChar(ArrayTx[i]);
	}
	TxCounter++;
	PF2 ^= 0x04;
	return;
}

//-----------UART1_Handler------------
void UART1_Handler(void){
	PF1 ^= 0x02;
	PF1 ^= 0x02;
	while((UART1_FR_R&0x10) == 0){
		uint32_t n = FiFo_Put(UART1_InChar());
		if(n == 0){
			GlobalError++;
			return;
		}
	}
	RxCounter++;
	UART1_ICR_R |= 0x10;
	PF1 ^= 0x02;
	return;
}
