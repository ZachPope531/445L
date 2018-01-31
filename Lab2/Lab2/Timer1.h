#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

void Timer1_Init(void(*task)(void), uint32_t period);

void Timer1A_Handler(void);