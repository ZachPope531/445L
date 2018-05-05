// UART1.c
// Runs on LM4F120/TM4C123
// Provide functions that setup and interact with UART


#include "UART1.h"

// UART initialization function 
// Input: none
// Output: none
void UART1_Init(void){ 
	// Assumes a 80 MHz bus clock, creates 100000 baud rate
  SYSCTL_RCGCUART_R |= 0x0002; // activate UART1
  SYSCTL_RCGCGPIO_R |= 0x0004; // activate port C
  UART1_CTL_R &= ~0x0001;      // disable UART
  UART1_IBRD_R = 50; 
// IBRD=int(80000000/(16*100,000)) = int(50)
  UART1_FBRD_R = 0;  
// FBRD = round(0 * 64) = 0
  UART1_LCRH_R = 0x0070;  // 8-bit length, enable FIFO
  UART1_CTL_R = 0x0301;   // enable RXE, TXE and UART
  GPIO_PORTC_AFSEL_R |= 0x030; // alt funct on PC5-4
  GPIO_PORTC_PCTL_R = 
            (GPIO_PORTC_PCTL_R&0xFFFFFF00)+0x00220000;
  GPIO_PORTC_DEN_R |= 0x30;   // digital I/O on PC5-4
  GPIO_PORTC_AMSEL_R &= ~0x30; // No analog on PC5-4
	UART1_IM_R |= 0x10;
	UART1_IFLS_R |= 0x10; //1/2 full
	NVIC_PRI1_R |= 0x00D00000;  // bits 21-23
	NVIC_EN0_R |= 0x40; // enable interrupt 6 in NVIC
	FiFo_Init();
}

//------------UART_InChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
// *** Need not be busy-wait if you know when to call
char UART1_InChar(void){  
	while((UART1_FR_R&0x0010) != 0){} // wait until RXFE is 0
  return((uint8_t)(UART1_DR_R&0xFF));
}

//------------UART_OutChar------------
// Wait for new input,
// then return ASCII code
// Input: none
// Output: char read from UART
void UART1_OutChar(char data){
	while ((UART1_FR_R&0x0020) != 0){} //wait until TXFF is 0
	UART1_DR_R = data;
}

