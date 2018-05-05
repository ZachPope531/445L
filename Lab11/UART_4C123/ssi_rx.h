/* ssi_rx.h */

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
//#include "nrf24l01p.h"

void SSI_Rx_Init(void);

uint16_t SSI1_Read(void);