/* ssi.h */

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"

void SSI_Init(void);

void SSI1_Write(uint16_t data);

uint16_t SSI2_Read (void);