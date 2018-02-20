#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "DAC.h"
#include "timer.h"

int main(void){
	PLL_Init(Bus80MHz);
	DAC_Init();
}
