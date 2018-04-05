//main.c

#include <stdint.h>
#include "Timer0A.h"
#include "ST7735.h"
#include "ADCSWTrigger.h"
#include "UART.h"
#include "PLL.h"


int32_t data;
int32_t buffer[100];
int i;


int main (void){
	int i = 0;
	buffer = {0};
	PLL_Init(Bus80MHz);
	UART_Init();
	ADC0_InitSWTriggerSeq3_Ch9();
	Timer0A_Init(&Read_Data, 80000); //run Read_Data at timer interrupt
	                                 // (80MHz / 1000 Hz) = 80000
	while(1){
		if (i >= 1000){
			Send_Data(); //read buffer values use UART to send data
			break; //stop
		}
	}
}

void Read_Data(void){
	if (i < 1000){
		data = ADC0_InSeq3();
		buffer[i] = data;
		i++;
	}
}

void Send_Data(void){
	for (int j = 0; j < 1000; j++){
		UART_OutString("\n\rADC data =");
		int buff_val = buffer[j];
		UART_OutUDec(buff_val);
	}
}
	