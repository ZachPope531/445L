/*
Zachary Pope and Ali Kedwaii
Saadallah Kassir

MW 3:30-5 PM

Lab 11
*/


// UARTTestMain.c
// Runs on LM4F120/TM4C123
// Used to test the UART.c driver
// Daniel Valvano
// May 30, 2014

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

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "UART.h"
#include "ADC.h"

void EnableInterrupts(void);

extern volatile uint16_t ADCa_In;
extern volatile uint16_t ADCb_In;

int main(void){

  PLL_Init(Bus80MHz);       // 80  MHz
	//ADC_Init();
  UART_Init();              // initialize UART
	//EnableInterrupts();
	
	while(1){
		//Take in ADC data from PE4 and PE5
		ADC_In89();
		int leftRight = ADCa_In;
		int upDown = ADCb_In;
		
		
		//Send these values through UART
		UART_OutChar((leftRight & 0x00FF));
		while((UART1_FR_R & 0x0020) != 0){}; //TXFF
		for(int i = 0; i < 1000000; i++){};
		UART_OutChar((leftRight & 0xFF00) >> 8);
		while((UART1_FR_R & 0x0020) != 0){}; //TXFF
		for(int i = 0; i < 1000000; i++){};
		UART_OutChar((upDown & 0x00FF));
		while((UART1_FR_R & 0x0020) != 0){}; //TXFF
		for(int i = 0; i < 1000000; i++){};
		UART_OutChar((upDown & 0xFF00) >> 8);
		while((UART1_FR_R & 0x0020) != 0){}; //TXFF
		for(int i = 0; i < 10000000; i++){};
		
	}
  
}
