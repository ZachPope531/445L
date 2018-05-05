// ADC.c
// Runs on LM4F120/TM4C123
// Provide functions that initialize ADC1
// Last Modified: 3/6/2015 
// Student names: Zach Pope and John Lee
// Last modification date: 14 April 2016

#include "ADC.h"

// ADC initialization function 
// Input: none
// Output: none
void ADC_Init(void){
		volatile unsigned long delay;
		SYSCTL_RCGCGPIO_R |= 0x10;					// Turn on port E
		while((SYSCTL_PRGPIO_R&0x10) == 0){};
		GPIO_PORTE_DIR_R &= ~0x0C;      // 2) make PE2 and PE3 input
		GPIO_PORTE_AFSEL_R |= 0x0C;     // 3) enable alternate function on PE2 and PE3
		GPIO_PORTE_DEN_R &= ~0x0C;      // 4) disable digital I/O on PE2 and PE3
		GPIO_PORTE_AMSEL_R |= 0x0C;     // 5) enable analog function on PE2 and PE3
		SYSCTL_RCGCADC_R |= 0x03;       // 6) activate ADC0 and ADC1
		delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
		delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
		delay = SYSCTL_RCGCADC_R;       // extra time to stabilize
		delay = SYSCTL_RCGCADC_R;
		ADC0_PC_R = 0x01;               // 7) configure for 125K 
		ADC0_SSPRI_R = 0x0123;          // 8) Seq 3 is highest priority
		ADC0_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
		ADC0_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
		ADC0_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+1;  // 11) Ain1 (PE2)
		ADC0_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
		ADC0_IM_R &= ~0x0008;           // 13) disable SS3 interrupts
		ADC0_ACTSS_R |= 0x0008;         // 14) enable sample sequencer 3
			
		ADC1_PC_R = 0x01;               // 7) configure for 125K 
		ADC1_SSPRI_R = 0x0123;          // 8) Seq 3 is highest priority
		ADC1_ACTSS_R &= ~0x0008;        // 9) disable sample sequencer 3
		ADC1_EMUX_R &= ~0xF000;         // 10) seq3 is software trigger
		ADC1_SSMUX3_R = (ADC0_SSMUX3_R&0xFFFFFFF0)+0;  // 11) Ain0 (PE3)
		ADC1_SSCTL3_R = 0x0006;         // 12) no TS0 D0, yes IE0 END0
		ADC1_IM_R &= ~0x0008;           // 13) disable SS3 interrupts
		ADC1_ACTSS_R |= 0x0008;         // 14) enable sample sequencer 3
			
		ADC0_SAC_R = ADC_SAC_AVG_64X;
		ADC1_SAC_R = ADC_SAC_AVG_64X;

}

//------------ADC_In------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
uint32_t ADCa_In(void){  
	unsigned long result;
	ADC0_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC0_RIS_R&0x08)==0){};   // 2) wait for conversion done
  result = ADC0_SSFIFO3_R&0xFFF;   // 3) read result
  ADC0_ISC_R = 0x0008;             // 4) acknowledge completion
  return result;
}

uint32_t ADCb_In(void){  
	unsigned long result;
	ADC1_PSSI_R = 0x0008;            // 1) initiate SS3
  while((ADC1_RIS_R&0x08)==0){};   // 2) wait for conversion done
  result = ADC1_SSFIFO3_R&0xFFF;   // 3) read result
  ADC1_ISC_R = 0x0008;             // 4) acknowledge completion
  return result;
}


