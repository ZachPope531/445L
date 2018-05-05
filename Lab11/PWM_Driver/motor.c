#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Timer0APWM.h"

#define PB2		(*((volatile unsigned long *)0x40005010))
#define PB3		(*((volatile unsigned long *)0x40005020))
#define PB4		(*((volatile unsigned long *)0x40005040))
#define PB5		(*((volatile unsigned long *)0x40005080))
#define PB6		(*((volatile unsigned long *)0x40005100))
#define PB7		(*((volatile unsigned long *)0x40005200))

void enable_PB_control(void){
	volatile unsigned long delay;
	SYSCTL_RCGCGPIO_R |= 0x02;
	delay = SYSCTL_RCGCGPIO_R;
	GPIO_PORTB_DIR_R |= (0x04 | 0x08 | 0x10 | 0x80);
	GPIO_PORTB_DEN_R |= (0x04 | 0x08 | 0x10 | 0x80);
	GPIO_PORTB_AFSEL_R &= ~(0x04 | 0x08 | 0x10 | 0x80);
	PB2 = 0x00; //Enable right motor
	PB3 = 0x00;	//Enable left motor
	PB4 = 0x00; //Left motor direction control
	PB7 = 0x00; //Right motor direction control
}

void motor_init(){
	enable_PB_control();
	Right_PWM_Init(16000, 5);
	Left_PWM_Init(16000, 5);
}

void right_motor_speed(uint8_t dir, uint8_t speed){
		if(speed >= 100){
		speed = 99;
	} else if(speed == 0){
		PB2 = 0x00; //Disable right motor
		return;
	}
	if(!dir){
		PB2 = 0x04; //Enable right motor
		
		PB7 = 0x00; //A2
		Right_PWM_Duty(speed*160);
	} else if(dir){
		PB2 = 0x04; //Enable right motor
		
		PB7 = 0x80; //A2
		Right_PWM_Duty(16000 - speed*160);
	}
}

void left_motor_speed(uint8_t dir, uint8_t speed){
	if(speed >= 100){
		speed = 99;
	} else if(speed == 0){
		PB3 = 0x00;
		return;
	}
	if(!dir){
		PB3 = 0x08; //Enable left motor
		
		PB4 = 0x00; //A4
		Left_PWM_Duty(speed*160);
	} else if(dir){
		PB3 = 0x08; //Enable left motor
		
		PB4 = 0x10; //A4
		Left_PWM_Duty(16000 - speed*160);
	}
}
