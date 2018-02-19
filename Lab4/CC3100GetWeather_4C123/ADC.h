/* ADC.h */
/* 
  Zachary Pope zhp76
  Mohammad Kedwaii mak3799
  Feb 12 2018
*/

//Initializes ADC on PE3
//Input: none
//Output: none
void ADC0_InitSWTriggerSeq3_Ch9(void);

// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
unsigned int ADC0_InSeq3(void);
