#include <stdio.h>
#include <stdint.h>
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"

void PortB_Init(void);

void Timer2_Init(unsigned long period);

void Timer2A_Handler(void);

void Alarm_On(void);

void Snooze(void);
