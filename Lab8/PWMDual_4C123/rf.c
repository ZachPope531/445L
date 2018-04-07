/* rf.c */

#include "rf.h"


//initialize module/s
void Module_Init(void){
	SSI_Init();
	Timer0A_Init();
	Timer1A_Init();
}

void Transmit(uint16_t data) {
	SSI1_Write(data);
}

uint16_t Receive(void) {
  return SSI2_Read();
}