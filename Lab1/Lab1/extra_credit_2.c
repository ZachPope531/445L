#include "extra_credit_2.h"
/*
// version 2: C fixed-point
volatile uint32_t T;    // temperature in 0.01 C
volatile uint32_t N;    // 12-bit ADC value
void Test2(void){
  for(N=0; N<4096; N++){
    T = 1000+ ((125*N+64)>>7); 	
  }
}

*/
