/* 
  Zachary Pope zhp76
  Mohammad Kedwaii mak3799
  Mar 02 2018
	
	Lab: MW 330-5
	TA: Saadallah Kassir the unstoppable force, the immovable object
*/

#include "Switch.h"

extern uint32_t desiredRPS;

void Switch_Init(){
	unsigned long volatile delay;
  SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port F
  delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x11;         // allow changes to PF4,0
  GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF4,0 in (built-in button)
  GPIO_PORTF_AFSEL_R &= ~0x11;  //     disable alt funct on PF4,0
  GPIO_PORTF_DEN_R |= 0x11;     //     enable digital I/O on PF4,0
  GPIO_PORTF_PCTL_R &= ~0x000F000F; //  configure PF4,0 as GPIO
  GPIO_PORTF_AMSEL_R &= ~0x11;  //     disable analog functionality on PF4,0
  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4,0
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4,PF0 is edge-sensitive
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4,PF0 is not both edges
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4,PF0 falling edge event
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flags 4,0
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4,PF0
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00400000; // (g) priority 2
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
}

//DEBOUNCE BETTER
void GPIOPortF_Handler(){
	//Delay1millisecond(15); //Still doesn't work 100%
	if(GPIO_PORTF_RIS_R&0x01){  // PF0 touch
    GPIO_PORTF_ICR_R = 0x01;  // acknowledge flag0
		desiredRPS -= 5;
  }

  if(GPIO_PORTF_RIS_R&0x10){  // PF4 touch
    GPIO_PORTF_ICR_R = 0x10;  // acknowledge flag4
		desiredRPS += 5;
  }
}