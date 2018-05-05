/* controller.c */

#include "controller.h"

#define U 0x55
#define D 0x44
#define L 0x4C
#define R 0x52

void Controller_Init(){
	ADC_Init();
}

uint16_t Get_Value(void){
	char dir;
	uint16_t data;
	//read ADCs
	uint32_t LR_in = ADCa_In();
	uint32_t UD_in = ADCb_In();
	//interpret values
	if (LR_in < 2000) dir = L;
	else if (LR_in > 2100) dir = R;
	else if (UD_in < 2000) dir = D;
	else if (UD_in > 2100) dir = U;
	
	switch (dir) {
		case L: data = (2000 - LR_in) / 20 ; break;
		case D: data = (2000 - UD_in) / 20 ; break;
		case R: data = (LR_in - 2100) / 20 ; break;
		case U: data = (UD_in - 2100) / 20 ; break;
		default: break;
	}
	uint16_t _dir = dir << 8;
	data = (data & 0x00FF) + (_dir & 0xFF00);	
	return data;
}