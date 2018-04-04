/* timer1.h */

#include <stdint.h>
#include "..//inc//tm4c123gh6pm.h"

#ifndef __TIMER1AINTS_H__ // do not include more than once
#define __TIMER1AINTS_H__

//init timer for checking/sending data
void Timer1A_Init(void(*task)(void));

//check for data transmission
void Timer1A_Handler(void);

#endif // __TIMER0AINTS_H__