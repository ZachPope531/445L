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

void Alarm_On() {
	GPIO_PORTB_DATA_R |= 0x08;
}

void Snooze(){
	GPIO_PORTB_DATA_R &= ~0x08;
	alarm_en = OFF;
}
