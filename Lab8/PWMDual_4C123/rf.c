/* rf.c */

#include "rf.h"

//initialize module/s
void Module_Init(void){
	SSI_Init();
	Timer0A_Init(*Transmit());
	Timer1A_Init(*Receive());
}

void Transmit(void){}

void Receive(void){}