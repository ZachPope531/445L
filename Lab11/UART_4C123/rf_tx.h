/* rf_tx.h */


#include "ssi_tx.h"
#include "timer0.h"

#include <stdint.h>

//initialize module/s
void Tx_Init(void);

void Transmit(uint16_t data);

