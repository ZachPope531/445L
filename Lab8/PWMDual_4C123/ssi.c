/* ssi.c */

#include "ssi.h"

#define PB5 (*((volatile uint32_t *) 0x40005080))
#define PE0 (*((volatile uint32_t *) 0x40024004))
#define PE1 (*((volatile uint32_t *) 0x40024008))
#define PF3 (*((volatile uint32_t *) 0x40025020))
	
#define U 0x55
#define D 0x44
#define L 0x4C
#define R 0x52

//Port F + SSI1 for transmitter
//Port B + SSI2 for receiver
//CSN/!CS = Fss
void SSI_Init(void){
	SYSCTL_RCGCSSI_R |= 0x06;       // activate SSI1 and SSI2
  SYSCTL_RCGCGPIO_R |= 0x32;      // activate ports B, E, F
  while((SYSCTL_PRGPIO_R&0x32) == 0){};// ready?
  GPIO_PORTB_AFSEL_R |= 0xD0;     // enable alt funct on PB467
  GPIO_PORTB_DEN_R |= 0xF0;       // configure PB4657 as SSI
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0x00F0FFFF)+0x22020000;
  GPIO_PORTB_AMSEL_R = 0;         // disable analog functionality on PB
	GPIO_PORTB_DIR_R |= 0x20;				// PB5 out (!CS)
	GPIO_PORTB_PDR_R |= 0x20;				// pull-down for CSN
  PB5 = 0x20;                     // !CS = 1
	GPIO_PORTE_DEN_R |= 0x03;				// PE0 and PE1 for CE1 and CE2
	GPIO_PORTE_AMSEL_R = 0;
	GPIO_PORTE_DIR_R |= 0x03;

	GPIO_PORTF_AFSEL_R |= 0x07;     // enable alt funct on PF012
  GPIO_PORTF_DEN_R |= 0x0F;       // configure PF0123 as SSI
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF000)+0x00000222;
  GPIO_PORTF_AMSEL_R = 0;         // disable analog functionality on PF
	GPIO_PORTF_DIR_R |= 0x08;       // PF3 out (!CS)
	GPIO_PORTF_PDR_R |= 0x08;
	PF3 = 0x08;
	
  SSI1_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI1_CPSR_R = 0x08;             // 2 MHz SSIClk 
  SSI1_CR0_R &= ~(0x0000FF70);    // SCR = 0, SPH = 1, SPO = 0 Freescale
  SSI1_CR0_R |= 0x0F;             // DSS = 16-bit data
	SSI1_CR0_R |= 0x0080;						// SPH = 1
  SSI1_CR1_R |= 0x00000002;       // enable SSI
	SSI2_CR1_R = 0x00000000;        // disable SSI, master mode
  SSI2_CPSR_R = 0x08;             // 2 MHz SSIClk 
  SSI2_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI2_CR0_R |= 0x0F;             // DSS = 16-bit data
	//SSI2_CR0_R |= 0x0080;						// SPH = 1
  SSI2_CR1_R |= 0x00000002;       // enable SSI
	
	//set config for transmitter
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}	//wait for transfer fifo empty
	SSI1_DR_R = 0x20;		//command to write to config register
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {} //wait for something in receiver fifo
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = 0x02;		//PWR_UP
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
		
	//set config for receiver
	while((SSI2_SR_R & SSI_SR_TFE) == 0) {}
	SSI2_DR_R = 0x20;		//command to write to config register
	while((SSI2_SR_R & SSI_SR_RNE) == 0) {}
	while((SSI2_SR_R & SSI_SR_TFE) == 0) {}
	SSI2_DR_R = 0x03;		//PWR_UP + PRIME_RX
	while((SSI2_SR_R & SSI_SR_RNE) == 0) {}
		
	PE0 = 0;		//CE1
	PE1 = 0x02; //CE2
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
	PE0 = 0x01; //CE ready to send
	PF3 = 0x08;		//CSN up, done with data transfer						
	return;
}

uint16_t SSI2_Read (void) {
	uint16_t data, dummy;
	PE1 = 0;											//CE ready to receive
  PB5 = 0; //CSN
	//flush
	while(SSI2_SR_R & SSI_SR_RNE) {
		dummy = SSI2_DR_R;
	}
	while((SSI2_SR_R & SSI_SR_TFE) == 0) {}
	SSI2_DR_R = 0x61;							//send R_RX_PAYLOAD command
	//SSI2_DR_R = 0x00;	
	while((SSI2_SR_R & SSI_SR_RNE) == 0) {}
	uint32_t status = SSI2_DR_R;	//check status returned by command
	ST7735_SetCursor(0, 2);				//print
	ST7735_OutUDec(status);
	while((SSI2_SR_R & SSI_SR_TFE) == 0) {}
	SSI2_DR_R = 0;								//meh
	while((SSI2_SR_R & SSI_SR_RNE) == 0) {}
	
	data = SSI2_DR_R;							//byte 1
	while((SSI2_SR_R & SSI_SR_TFE) == 0) {}
	SSI2_DR_R = 0;								
	while((SSI2_SR_R & SSI_SR_RNE) == 0) {}
	data = data + (SSI2_DR_R << 8);	//byte 2
	PE1 = 0x02;											//CE done receiving
	PB5 = 0x20;											//CSN, transfer done
	return data;
}