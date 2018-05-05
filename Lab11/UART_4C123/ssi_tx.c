/* ssi_tx.c */

#include "ssi_tx.h"

#define PE0 (*((volatile uint32_t *) 0x40024004))
#define PF3 (*((volatile uint32_t *) 0x40025020))
	
#define U 0x55
#define D 0x44
#define L 0x4C
#define R 0x52


void SSI_Tx_Init(void){
	//GPIO_PORTF_LOCK_R = 0x4C4F434B;	//Unlock PF
	SYSCTL_RCGCSSI_R |= 0x02;       // activate SSI1
  SYSCTL_RCGCGPIO_R |= 0x30;      // activate ports E, F
  while((SYSCTL_PRGPIO_R&0x30) == 0){};// ready? 
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x0F;
	GPIO_PORTE_DEN_R |= 0x01;				// PE0 for CE1
	GPIO_PORTE_AMSEL_R = 0;
	GPIO_PORTE_DIR_R |= 0x01;
	GPIO_PORTF_AFSEL_R |= 0x07;     // enable alt funct on PF012
  GPIO_PORTF_DEN_R |= 0x0F;       // configure PF0123 as SSI
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF000)+0x00000222;
  GPIO_PORTF_AMSEL_R = 0;         // disable analog functionality on PF
	GPIO_PORTF_DIR_R |= 0x08;       // PF3 out (!CS)
	GPIO_PORTF_PDR_R |= 0x08;
	PF3 = 0x08;
	
  SSI1_CR1_R = 0x00000000;        // disable SSI, master mode
  //SSI1_CPSR_R = 0x08;             // 2 MHz SSIClk 
	SSI1_CC_R = (SSI1_CC_R&~SSI_CC_CS_M)+SSI_CC_CS_PIOSC; //Configure for system clock
	SSI1_CPSR_R = (SSI1_CPSR_R&~SSI_CPSR_CPSDVSR_M)+64; //Configure for 16MHz (80MHz/5 = 16MHz)
  SSI1_CR0_R &= ~(0x0000FF70);    // SCR = 0, SPH = 1, SPO = 0 Freescale
  SSI1_CR0_R |= 0x0F;             // DSS = 16-bit data
	SSI1_CR0_R |= 0x0080;						// SPH = 1
  SSI1_CR1_R |= 0x00000002;       // enable SSI
	
	//set config for transmitter
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}	//wait for transfer fifo empty
	SSI1_DR_R = 0x20;		//command to write to config register
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {} //wait for something in receiver fifo
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = 0x02;		//PWR_UP
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
		
	PE0 = 0;		//CE1

//nrf24l01p_init();
//nrf24l01p_tx_mode();
}

void SSI1_Write(uint16_t data){
	PE0 = 0;		//Tx operation
	PF3 = 0; 		//!CS, start transfer
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = 0xA0;												//send WRITE_TX_PAYLOAD command
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = data & 0xFF;								//byte 1
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = (data >> 8) & 0xFF;					//byte 2
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
	PE0 = 0x01; 	//CE ready to send
	PF3 = 0x08;		//CSN up, done with data transfer						
	return;
//	char buff[2] = { (data & 0xFF) , ((data >> 8) & 0xFF) } ;
//	nrf24l01p_write(0xA0, &buff[0], 2);
}