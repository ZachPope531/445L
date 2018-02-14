/* ADC.h */
/* 
  Zachary Pope zhp76
  Mohammad Kedwaii mak3799
  Feb 12 2018
*/

#include <stdio.h>
#include <stdint.h>
#include "PLL.h"
#include "../inc/tm4c123gh6pm.h"

//Initializes ADC on PE4
//Potentiometer used to change mode
//Input: none
//Output: none
void ADC0_InitSWTriggerSeq3_Ch9(void);

// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADC0_InSeq3(void);
