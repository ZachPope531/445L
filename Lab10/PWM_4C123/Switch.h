/* 
  Zachary Pope zhp76
  Mohammad Kedwaii mak3799
  Mar 02 2018
	
	Lab: MW 330-5
	TA: Saadallah Kassir the unstoppable force, the immovable object
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
