/* Tachometer.c */

#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PWM.h"
#include "Tachometer.h"

uint32_t currentTicks;
uint32_t currentRPS;
uint32_t desiredRPS;
uint16_t newDuty;

void PortE_Init(){
	unsigned long volatile delay;
  SYSCTL_RCGCGPIO_R |= 0x00000010; // (a) activate clock for port E
  delay = SYSCTL_RCGCGPIO_R;
  GPIO_PORTE_DIR_R &= ~0x10;    // (c) make PE4 in (built-in button)
  GPIO_PORTE_AFSEL_R &= ~0x10;  //     disable alt funct on PE4
  GPIO_PORTE_DEN_R |= 0x10;     //     enable digital I/O on PE4
  GPIO_PORTE_PCTL_R &= ~0x000F0000; //  configure PE4 as GPIO
  GPIO_PORTE_AMSEL_R &= ~0x10;  //     disable analog functionality on PE4
  GPIO_PORTE_IS_R &= ~0x10;     // (d) PE4	is edge-sensitive
  GPIO_PORTE_IBE_R &= ~0x10;    //     PE4 is not both edges
  GPIO_PORTE_IEV_R |= 0x10;    //     PE4 rising edge event
  GPIO_PORTE_ICR_R = 0x10;      // (e) clear flags 4
  GPIO_PORTE_IM_R |= 0x10;      // (f) arm interrupt on PE4
  NVIC_PRI1_R = (NVIC_PRI1_R&0xFFFFFF00)|0x00000040; // (g) priority 2 NVIC_PRI1_R bits 7 � 5
  NVIC_EN0_R = 0x00000010;      // (h) enable interrupt 4 in NVIC
	currentTicks = 0;
}

void GPIOPortE_Handler() {
	currentTicks += 1;
}

void Proportional_Integral(){
	currentRPS = currentTicks / 6; //check tick #
	int32_t error = desiredRPS - currentRPS;
  newDuty = newDuty + (3 * error) / 64;
	if (newDuty < 100) newDuty = 100;
	if (newDuty > 39900) newDuty = 39900;
	PWM0A_Duty(newDuty);
	currentTicks = 0;
}
