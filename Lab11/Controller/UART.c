// UART.c
// Runs on LM4F120/TM4C123
// Provide functions that setup and interact with UART
// Last Modified: 4/12/2016 
// Student names: change this to your names or look very silly
// Last modification date: change this to the last modification date or look very silly

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// UART initialization function 
// Input: none
// Output: none
void UART_Init(void){
	//Turn on port C
	unsigned volatile long delay;
	SYSCTL_RCGCGPIO_R |= 0x0004;
	delay = SYSCTL_RCGCGPIO_R;
	//DO NOT TOUCH PC0-PC3, you can't flash without those
	GPIO_PORTC_DEN_R |= 0x30;
	GPIO_PORTC_AMSEL_R &= ~0x30;
	GPIO_PORTC_AFSEL_R |= 0x30;
	GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000; //Enable UART functionality on PC4-5
	
	//Turn on UART1
	SYSCTL_RCGCUART_R |= 0x0002;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	//Disable UART1 for the intialization
	UART1_CTL_R &= ~0x0001;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	//Set the Baud rate
	UART1_IBRD_R = 50; //(80MHz*(16*100kbps)=50
	UART1_FBRD_R = 0; //Nothing to round
	//Set the frame size
	UART1_LCRH_R = 0x70;
	
	//Turn on the ISR
	UART1_IM_R |= UART_IM_RXIM; //Arm the Rx bit, not Tx
	UART1_IFLS_R |= 0x10;
	//See online chapter 12.3 for this crap
	NVIC_PRI1_R |= 0x00800000; //Set bits 21-23 for the priority
	NVIC_EN0_R |= 1<<6; //Enable bit 6 to choose UART1
	
	//Turn on UART1
	UART1_CTL_R |= 0x0301;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;
	delay = SYSCTL_RCGCGPIO_R;

}

//------------UART_InChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
// *** Need not be busy-wait if you know when to call
char UART_InChar(void){
  return ((uint8_t) (UART1_DR_R & 0xFF));
}

//------------UART_OutChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
void UART_OutChar(char data){  
	while((UART1_FR_R & 0x0020) != 0){}; //TXFF
	UART1_DR_R = data;
}
