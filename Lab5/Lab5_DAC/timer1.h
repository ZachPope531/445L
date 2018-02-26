/* Timer1.h */

#include <stdint.h>
#include "..//inc//tm4c123gh6pm.h"

#ifndef __TIMER1AINTS_H__ // do not include more than once
#define __TIMER1AINTS_H__

//Taken from Valvano himself
void Delay1millisecond(uint32_t n);

void Timer1A_Init(void);

void Timer1A_ChangeTime(uint32_t time);

void Timer1A_Disable(void);

void Timer1A_Enable(void);

#endif // __TIMER1AINTS_H__
