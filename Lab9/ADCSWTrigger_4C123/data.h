/* data.h 
Zachary Pope and Ali Kedwaii
Saadallah Kassir, the brightest star in the darkest night
MW 3:30-5 Section
*/

#include <stdint.h>
#include "ST7735.h"
#include "UART.h"

void ADC_to_Temp(uint32_t * buff);

void ST7735_sDecOut2(int32_t n);

void UART_sDecOut2(int32_t n);

void Print_Data(void);

void UART_Print(void);

void Data_Process(int * data_dump);