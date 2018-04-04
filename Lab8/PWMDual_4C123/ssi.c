/* ssi.c */

#include "ssi.h"

#define PB5 (*((volatile uint32_t *) 0x400005080))

void SSI_Init(void){
	SYSCTL_RCGCSSI_R |= 0x06;       // activate SSI1 and SSI2
  SYSCTL_RCGCGPIO_R |= 0x22;      // activate ports B, F
  while((SYSCTL_PRGPIO_R&0x01) == 0){};// ready?
  GPIO_PORTB_AFSEL_R |= 0xD0;     // enable alt funct on PB467
  GPIO_PORTB_DEN_R |= 0xF0;       // configure PB4657 as SSI
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0x00F0FFFF)+0x22020000;
  GPIO_PORTB_AMSEL_R = 0;         // disable analog functionality on PB
	GPIO_PORTB_DIR_R |= 0x20;				// PB5 out (!CS)
  PB5 = 0x20;                     // !CS = 1
	GPIO_PORTF_AFSEL_R |= 0x07;     // enable alt funct on PF012
  GPIO_PORTF_DEN_R |= 0x0F;       // configure PF0123 as SSI
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF000)+0x00000222;
  GPIO_PORTF_AMSEL_R = 0;         // disable analog functionality on PA
  SSI1_CR1_R = 0x00000000;        // disable SSI, master mode HOW MAKE SLAVE?
  SSI1_CPSR_R = 0x08;             // 2 MHz SSIClk 
  SSI1_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI1_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI1_CR1_R |= 0x00000002;       // enable SSI
	SSI2_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI2_CPSR_R = 0x08;             // 2 MHz SSIClk 
  SSI2_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI2_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI2_CR1_R |= 0x00000002;       // enable SSI

}