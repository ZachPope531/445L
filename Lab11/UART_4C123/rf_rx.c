/* rf_rx.c */

#include "rf_rx.h"


//initialize module/s
void Rx_Init(void){
	SSI_Rx_Init();
	Timer1A_Init();
}

uint16_t Receive(void) {
  return SSI1_Read();
}