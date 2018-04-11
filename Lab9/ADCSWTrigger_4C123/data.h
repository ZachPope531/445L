/* data.h */

#include <stdint.h>
#include "ST7735.h"

void ADC_to_Temp(uint32_t * buff);

void ST7735_sDecOut2(int32_t n);

void Print_Data(void);

void Data_Process(int * data_dump);