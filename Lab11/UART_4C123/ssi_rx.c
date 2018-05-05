/* ssi_rx.c */

#include "ssi_rx.h"

#define PE0 (*((volatile uint32_t *) 0x40024004))
#define PF3 (*((volatile uint32_t *) 0x40025020))
	
#define U 0x55
#define D 0x44
#define L 0x4C
#define R 0x52

//Port F + SSI1 for transmitter
//Port B + SSI2 for receiver
//CSN/!CS = Fss
void SSI_Rx_Init(void){
	//GPIO_PORTF_LOCK_R = 0x4C4F434B;	//Unlock PF
	SYSCTL_RCGCSSI_R |= 0x02;       // activate SSI
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
  SSI1_CR0_R &= ~(0x0000FFF0);    // SCR = 0, SPH = 0, SPO = 0 Freescale
  SSI1_CR0_R |= 0x0F;             // DSS = 16-bit data
  SSI1_CR1_R |= 0x00000002;       // enable SSI

			
	//set config for receiver
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = 0x20;		//command to write to config register
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = 0x03;		//PWR_UP + PRIME_RX
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
		
	PE0 = 0;		//CE1

//nrf24l01p_init();
//nrf24l01p_rx_mode();
}

uint16_t SSI1_Read (void) {
	uint16_t data, dummy;
	PE0 = 0;											//CE ready to receive
  PF3 = 0; //CSN
	//flush
	while(SSI1_SR_R & SSI_SR_RNE) {
		dummy = SSI1_DR_R;
	}
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = 0x61;							//send R_RX_PAYLOAD command
	//SSI2_DR_R = 0x00;	
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
	uint32_t status = SSI1_DR_R;	//check status returned by command
	ST7735_SetCursor(0, 2);				//print
	ST7735_OutUDec(status);
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = 0;								//meh
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
	
	data = SSI1_DR_R;							//byte 1
	while((SSI1_SR_R & SSI_SR_TFE) == 0) {}
	SSI1_DR_R = 0;								
	while((SSI1_SR_R & SSI_SR_RNE) == 0) {}
	data = data + (SSI1_DR_R << 8);	//byte 2
	PE0 = 0x02;											//CE done receiving
	PF3 = 0x08;											//CSN, transfer done
//	char buff[2] = { 0 , 0 } ;
//	nrf24l01p_read(0x61, &buff[0], 2);
//	data = buff[0];
//	data = data << 8;
//	data = data + buff[1];
	return data;
}