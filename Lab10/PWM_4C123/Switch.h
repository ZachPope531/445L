/*
Switch.h
Zach Pope and Ali Kedwaii
Saadallah Kassir, the first cherry blossom to fall in spring
MW 3:30-5
*/

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

/*
	Initializes PF0 and PF4's switches
*/
void Switch_Init(void);

/*
	Changes the desiredRPS values between 20-60 rps
*/
void GPIOPortF_Handler(void);
