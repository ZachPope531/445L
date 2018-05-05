/* rf_tx.c */

#include "rf_tx.h"


//initialize module/s
void Tx_Init(void){
	SSI_Tx_Init();
	Timer0A_Init();
}

void Transmit(uint16_t data) {
	SSI1_Write(data);
}
