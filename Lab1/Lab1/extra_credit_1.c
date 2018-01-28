#include "extra_credit_1.h"

// version 1: C floating point
// run with compiler options selected for floating-point hardware
volatile float T;    // temperature in C
volatile uint32_t N; // 12-bit ADC value
void Test1(void){
  for(N=0; N<4096; N++){
    T = 10.0+ 0.009768*N; 	
  }
}
