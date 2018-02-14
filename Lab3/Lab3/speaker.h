/* speaker.h */
/* 
  Zachary Pope zhp76
  Mohammad Kedwaii mak3799
  Feb 12 2018
*/

#include <stdio.h>
#include <stdint.h>
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"


//Initialize output for speaker
//1-bit output
//Input: none
//Output: none
void PortB_Init(void);

// Activate Timer2 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer2_Init(unsigned long period);

//Toggles speaker output
//Input: none
//Output: none
void Timer2A_Handler(void);

//Starts Timer 2 to start speaker
//Input: none
//Output: none
void Alarm_On(void);

//Disables timer, sets alarm status to OFF
//Accidentally just turned off alarm
//instead of temporarily disabling it
//Input: none
//Output: none
void Snooze(void);
