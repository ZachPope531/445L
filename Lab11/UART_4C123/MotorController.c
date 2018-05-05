#include <stdint.h>
#include ".\inc\tm4c123gh6pm.h"
#include "MotorController.h"

#define PWM_0_GENA_ACTCMPAD_ONE 0x000000C0  // Set the output signal to 1
#define PWM_0_GENA_ACTLOAD_ZERO 0x00000008  // Set the output signal to 0
#define PWM_0_GENB_ACTCMPBD_ONE 0x00000C00  // Set the output signal to 1
#define PWM_0_GENB_ACTLOAD_ZERO 0x00000008  // Set the output signal to 0

#define SYSCTL_RCC_USEPWMDIV    0x00100000  // Enable PWM Clock Divisor
#define SYSCTL_RCC_PWMDIV_M     0x000E0000  // PWM Unit Clock Divisor
#define SYSCTL_RCC_PWMDIV_2     0x00000000  // /2

#define PB7       (*((volatile uint32_t *)0x40005200))
#define PB6       (*((volatile uint32_t *)0x40005100))
#define PB5       (*((volatile uint32_t *)0x40005080))
#define PB4       (*((volatile uint32_t *)0x40005040))
	
uint8_t Motor0Direction;
uint8_t Motor1Direction;
	
//Initialize PB4-7 as PWM and PB2,3 as GPIO
void PortB_Init(uint16_t period, uint16_t duty1, uint16_t duty2){
	SYSCTL_RCGCPWM_R |= 0x01;             // 1) activate PWM0
  SYSCTL_RCGCGPIO_R |= 0x02;            // 2) activate port B
  while((SYSCTL_PRGPIO_R&0x02) == 0){};
  GPIO_PORTB_AFSEL_R |= 0xF0;           // enable alt funct on PB7-4
  GPIO_PORTB_PCTL_R &= ~0xFFFF0000;     // configure PB7-4 as PWM
  GPIO_PORTB_PCTL_R |= 0x44440000;      // PB7-4 PWM
  GPIO_PORTB_AMSEL_R &= ~0xF0;          // disable analog functionality on PB7/6
  GPIO_PORTB_DIR_R |= 0xF0;             // PB7, PB6 output
  GPIO_PORTB_DEN_R |= 0xF0;             // enable digital I/O on PB7/6
  SYSCTL_RCC_R = 0x001A0000 |           // 3) use PWM divider 
      (SYSCTL_RCC_R & (~0x000E0000));   //    configure for /64 divider
  PWM0_0_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_0_GENA_R = 0xC8;                 // low on LOAD, high on CMPA down
  // PB7/6 goes low on LOAD
  // PB7/6 goes high on CMPA down
  PWM0_0_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM0_0_CMPA_R = duty1 - 1;             // 6) count value when output rises
  PWM0_0_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x00000003;          // enable PB6/7/M0PWM0
		
		
	PWM0_1_CTL_R = 0;                     // 4) re-loading down-counting mode
  PWM0_1_GENA_R = 0xC8;                 // low on LOAD, high on CMPA down
  // PB4 goes low on LOAD
  // PB4 goes high on CMPA down
  PWM0_1_LOAD_R = period - 1;           // 5) cycles needed to count down to 0
  PWM0_1_CMPA_R = duty2 - 1;             // 6) count value when output rises
  PWM0_1_CTL_R |= 0x00000001;           // 7) start PWM0
  PWM0_ENABLE_R |= 0x0000000C;          // enable PB4/M0PWM1A is PWM2
	
	//Initialize the direction to forward
	Motor0Direction = Motor1Direction = 0;
	
}

//Sets the duty cycle for the PWMs
//Chooses motor 0, 1, or both 2
//Speed from 0-100
void changeSpeed(uint8_t motor, uint8_t speed){
	switch(motor){
		case 0:
			if(Motor0Direction == 0){
				PWM0_0_CMPA_R = 124*speed;
				PWM0_1_CMPA_R = 12400;
			} else {
				PWM0_1_CMPA_R = 12500-124*speed;
				PWM0_0_CMPA_R = 0;
			}
		case 1:
			
		case 2:
			
		default:
			break;
	}
}

//Chooses motor 0 or 1
//0 for forward, 1 for backward
void setDirection(uint8_t motor, uint8_t dir){
	if(motor == 0){
		Motor0Direction = dir;
	} else {
		Motor1Direction = dir;
	}
}
