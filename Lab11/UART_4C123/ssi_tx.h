/* ssi_tx.h */

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "ST7735.h"
//#include "nrf24l01p.h"

void SSI_Tx_Init(void);

void SSI1_Write(uint16_t data);