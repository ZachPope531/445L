#include "DAC.h"

volatile uint16_t DAC_Index;


//********DAC_Init*****************
// Initialize 12-bit DAC
// inputs:  initial voltage output (0 to 4095)
// outputs: none
// assumes: system clock rate less than 20 MHz
void DAC_Init(uint16_t data){
  SYSCTL_RCGCSSI_R |= 0x04;       // activate SSI2
  SYSCTL_RCGCGPIO_R |= 0x02;      // activate port B
  while((SYSCTL_PRGPIO_R&0x01) == 0){};// ready?
  GPIO_PORTB_AFSEL_R |= 0xF0;     // enable alt funct on PB4,5,6,7
  GPIO_PORTB_DEN_R |= 0xF0;       // configure PA2,3,5 as SSI
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0x0000FFFF)+0x22220000;
  GPIO_PORTB_AMSEL_R = 0;         // disable analog functionality on PB
		
	/** LOOK AT THESE PARTS AND CHANGE THEM FOR SSI2 **/	
  SSI0_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI0_CPSR_R = 0x02;             // 8 MHz SSIClk 
  SSI0_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI0_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI0_DR_R = data;               // load 'data' into transmit FIFO
  SSI0_CR1_R |= 0x00000002;       // enable SSI

}

//********DAC_Out*****************
// Send data to 12-bit DAC
// inputs:  voltage output (0 to 4095)
// outputs: none
void DAC_Out(uint16_t data){   
  while((SSI2_SR_R&0x00000002)==0){};// SSI Transmit FIFO Not Full
  SSI2_DR_R = data;	// data out, no reply
}
