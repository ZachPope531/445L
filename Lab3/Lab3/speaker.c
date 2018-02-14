#include "speaker.h"
#include "timer.h"

#define PB3             (*((volatile uint32_t *)0x4000541C))
	
extern alarm alarm_en;

void PortB_Init(){
	//initialize PB3
	int delay;
	SYSCTL_RCGCGPIO_R |= 0x00000002;
	delay = SYSCTL_RCGCGPIO_R;
	//lock?
	GPIO_PORTB_AMSEL_R = 0x00;
	GPIO_PORTB_PCTL_R = 0x00000000;
	GPIO_PORTB_AFSEL_R = 0x00;
	GPIO_PORTB_DIR_R = 0x08;
	GPIO_PORTB_DEN_R = 0x0F;
	
	GPIO_PORTB_DATA_R &= ~0x08;
}

// Activate Timer2 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer2_Init(unsigned long period){
  SYSCTL_RCGCTIMER_R |= 0x04;   // 0) activate timer2
  TIMER2_CTL_R = 0x00000000;    // 1) disable timer2A during setup
  TIMER2_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER2_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER2_TAILR_R = period-1;    // 4) reload value
  TIMER2_TAPR_R = 0;            // 5) bus clock resolution
  TIMER2_ICR_R = 0x00000001;    // 6) clear timer2A timeout flag
  TIMER2_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0x00FFFFFF)|0x20000000; // 8) priority 1
// interrupts enabled in the main program after all devices initialized
// vector number 39, interrupt number 23
  NVIC_EN0_R = 1<<23;           // 9) enable IRQ 23 in NVIC
  //TIMER2_CTL_R = 0x00000001;    // 10) enable timer2A
}

void Timer2A_Handler(void){
  TIMER2_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER2A timeout
	GPIO_PORTB_DATA_R ^= 0x08;
}



void Alarm_On() {
	TIMER2_CTL_R = 0x00000001;
}

void Snooze(){
	TIMER2_CTL_R = 0x00000000;
	alarm_en = OFF;
}
