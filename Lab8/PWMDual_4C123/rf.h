/* rf.h */
/* Initialize module, send data and receive data */


#include "ssi.h"
#include "timer0.h"
#include "timer1.h"

#include <stdint.h>

//initialize module/s
void Module_Init(void);

void Transmit(uint16_t data);

uint16_t Receive(void);

