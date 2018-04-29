#include "nRF42L01+.h"

void Init(){
	GPIO_PORTF_LOCK_R = 0x4C4F434B;	//Unlock PF
	SYSCTL_RCGCSSI_R |= 0x02;	//Initialize SSI1
	SYSCTL_RCGCGPIO_R |= 0x30; //Enable PF and PortE
	while((SYSCTL_PRGPIO_R&0x0030) == 0){}; //Ready?
		
	//Enable CSN and CE
	GPIO_PORTF_DIR_R |= 0x18; //Make PF3,4 out (CSN, IRQ)
	GPIO_PORTF_AFSEL_R &= ~0x18; //Disable alternate function on PF3,4 (CSN, IRQ)
	GPIO_PORTF_DEN_R |= 0x18; //Enable digital I/O on PF3,4 (CSN, IRQ)
	GPIO_PORTE_DIR_R |=0x01; //Make PE0 out (CE)
	GPIO_PORTE_AFSEL_R &= ~0x01; //Disable alternate function on PE0 (CE)
	GPIO_PORTE_DEN_R |= 0x01;	//Enable digital I/O on PE0 (CE);
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0x000FF000)+0x00000000; //Configure PF3,4 as GPIO
	GPIO_PORTE_PCTL_R = (GPIO_PORTE_PCTL_R&0x0000000F)+0x00000000; //Configure PE0 as GPIO
		
	//Enable SCK, MISO, and MOSI
	GPIO_PORTF_AFSEL_R |= 0x07; //Enable alternate functions on PF0,1,2 (MISO, MOSI, SCK)
	GPIO_PORTF_DEN_R &= ~0x07; //Disable digital I/O on PF0,1,2 (MISO, MOSI, SCK)
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0x00000FFF) + 0x000000222; //Configure PF0,1,2 as SSI
	
	SSI1_CR1_R &= ~SSI_CR1_SSE; //Disable SSI
	SSI1_CR1_R &= ~SSI_CR1_MS; //Master mode

	//MAYBE THIS IS THE WRONG CLOCK SPEED? 16MHz ON THE CRYSTAL
	SSI1_CC_R = (SSI1_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_SYSPLL; //Configure for system clock
	SSI1_CPSR_R = (SSI1_CPSR_R&~SSI_CPSR_CPSDVSR_M)+5; //Configure for 16MHz (80MHz/5 = 16MHz)
	
	//From ST7735.c:
//	SSI0_CC_R = (SSI0_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_SYSPLL;
//                                        // clock divider for 3.125 MHz SSIClk (50 MHz PIOSC/16)
//  SSI0_CPSR_R = (SSI0_CPSR_R&~SSI_CPSR_CPSDVSR_M)+16;
                                        // clock divider for 8 MHz SSIClk (80 MHz PLL/24)
                                        // SysClk/(CPSDVSR*(1+SCR))
                                        // 80/(10*(1+0)) = 8 MHz (slower than 4 MHz)
//	SSI0_CPSR_R = (SSI0_CPSR_R&~SSI_CPSR_CPSDVSR_M)+10; // must be even number

	SSI1_CR0_R &= ~(SSI_CR0_SCR_M |	//SCR = 0 (8 Mbps data rate) ???Supposed to be 250kbps???
									SSI_CR0_SPH |	//Phase = 0
									SSI_CR0_SPO);	//Polarity = 0
									
	SSI1_CR0_R = (SSI1_CR0_R&~SSI_CR0_FRF_M)+SSI_CR0_FRF_MOTO; //Freescale
	
	SSI1_CR0_R = (SSI1_CR0_R&~SSI_CR0_DSS_M)+SSI_CR0_DSS_16; //16-bit data
	SSI1_DR_R = 0x0000; //Clear data
	SSI1_CR1_R |= SSI_CR1_SSE;	//Enable SSI
	
	
}

void send_data(uint8_t data){
	//https://github.com/maniacbug/RF24/blob/master/RF24.h
	
	//PWR_UP = 1
	//PRIM_RX = 0
	CE = 0x01; //Set CE high
	while((SSI1_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};	//Wait until SSI1 TX not busy
  SSI1_DR_R = 0b0010 0000; //Write to PWR_UP
	while((SSI1_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};	//Wait until SSI1 TX not busy
	SSI1_DR_R = 0b0010 0000; //Write to PRIM_RX
	while((SSI1_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};	//Wait until SSI1 TX not busy
	SSI1_DR_R = data;

	while((SSI1_SR_R&SSI_SR_BSY)==SSI_SR_BSY){};	//Wait until SSI1 TX not busy
}

void receive_data(uint16_t data){
	//PWR_UP = 1
	//PRIM_RX = 1
	//CE = 1
	
}
