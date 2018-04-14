/* data.c */

#include "data.h"

int32_t ADC_buff[100];
int32_t fixed_buff[100];

int ASCII_Offset = 48;


void ADC_to_Temp(uint32_t * buff){
	for(int i = 0; i < 100; i++){
		*(ADC_buff + i) = buff[i];
		*(fixed_buff + i) = ((-9 * buff[i]) / 10) + 3836;
	}
}


void ST7735_sDecOut2(int32_t n){
	if (n > 9999) {
		char error_str[6] = " **.**";
		ST7735_OutString(error_str);
		return;
	}
	if (n < -9999) {
		char error_str[6] = "-**.**";
		ST7735_OutString(error_str);
		return;
	}

	char str[6] = "";
	str[3] = '.';
	char buf[4] = { ' ', '0', '0', '0'	};

	int32_t i = n;
	if (i < 0) i = i * -1;
	uint32_t j = 3;
	while (i != 0) {
		buf[j] = (i % 10) + ASCII_Offset;
		i = i / 10;
		j = j - 1;
	}

	str[5] = buf[3];
	str[4] = buf[2];
	str[2] = buf[1];
	str[1] = buf[0];
	str[0] = ' ';

	if (n < 0) {
		if (str[1] == ' ') str[1] = '-';
		else str[0] = '-';
	}

	ST7735_OutString(str);
	return;
}

void UART_sDecOut2(int32_t n){
	if (n > 9999) {
		char error_str[6] = " **.**";
		UART_OutString(error_str);
		return;
	}
	if (n < -9999) {
		char error_str[6] = "-**.**";
		UART_OutString(error_str);
		return;
	}

	char str[6] = "";
	str[3] = '.';
	char buf[4] = { ' ', '0', '0', '0'	};

	int32_t i = n;
	if (i < 0) i = i * -1;
	uint32_t j = 3;
	while (i != 0) {
		buf[j] = (i % 10) + ASCII_Offset;
		i = i / 10;
		j = j - 1;
	}

	str[5] = buf[3];
	str[4] = buf[2];
	str[2] = buf[1];
	str[1] = buf[0];
	str[0] = ' ';

	if (n < 0) {
		if (str[1] == ' ') str[1] = '-';
		else str[0] = '-';
	}

	UART_OutString(str);
	return;
}

void Print_Data(void){
	for (int i = 0; i < 100; i++){
		ST7735_SetCursor(0,0);
		ST7735_OutString("Temp = ");
		ST7735_sDecOut2(fixed_buff[i]);
		ST7735_OutString("C = ");
		ST7735_OutUDec(ADC_buff[i]);
	}
}

void UART_Print(void){
	for (int i = 0; i < 100; i++){
		UART_OutString("Temp = ");
		UART_sDecOut2(fixed_buff[i]);
		UART_OutString("C = ");
		UART_OutUDec(ADC_buff[i]);
		UART_OutString("\n");
	}
}

void Data_Process(int * data_dump){

	int i, j;
	for (i = 0; i < 100; i++){
		for (j = 0; j < i; j++) {
			if (data_dump[j] > data_dump[i]){
				int temp = data_dump[j];
				*(data_dump + j) = data_dump[i];
				*(data_dump + i) = temp;
			}
		}
	}
	
	ST7735_PlotClear(0, 159);
	
	uint32_t ADC = 2050;
	int y = 0;

	for (i = 0; i < 100; i++){
		if (data_dump[i] == ADC) y++;
		else if (data_dump[i] > ADC) {
				while(data_dump[i] > ADC){
				ST7735_PlotBar(y);
				ST7735_PlotNext();
				y = 0;
				ADC++;
			}
		}
	}

	return;
}