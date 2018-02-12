#include "timer.h"
#include "switch.h"

#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF1             (*((volatile uint32_t *)0x40025008))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

extern part time_part;
extern mode mode_status;
extern timemode time_status;
extern displaymode display_status;
extern alarm alarm_en;

//ADD BITS FOR OTHER BUTTONS
void EdgeCounter_Init(void){       
	uint32_t delay;
	
	SYSCTL_RCGCGPIO_R |= 0x00000020; // (a) activate clock for port F

  delay = SYSCTL_RCGCGPIO_R;

  GPIO_PORTF_LOCK_R = 0x4C4F434B; // unlock GPIO Port F

  GPIO_PORTF_CR_R = 0x1F;         // allow changes to PF4,0

  GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF4,0 in (built-in button)

  GPIO_PORTF_AFSEL_R &= ~0x1F;  //     disable alt funct on PF4,0

  GPIO_PORTF_DEN_R |= 0x1F;     //     enable digital I/O on PF4,0

  GPIO_PORTF_PCTL_R &= ~0x000FFFFF; //  configure PF4,0 as GPIO

  GPIO_PORTF_AMSEL_R &= ~0x1F;  //     disable analog functionality on PF4,0

  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF4,0

  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF4,PF0 is edge-sensitive

  GPIO_PORTF_IBE_R &= ~0x11;    //     PF4,PF0 is not both edges

  GPIO_PORTF_IEV_R &= ~0x11;    //     PF4,PF0 falling edge event

  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flags 4,0

  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF4,PF0

  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 3

  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
	
	/*
  SYSCTL_RCGCGPIO_R |= 0x00000022; // (a) activate clock for ports B and F
	delay = SYSCTL_RCGC2_R;
  GPIO_PORTF_DIR_R &= ~0x11;    // (c) make PF0/4 in (built-in button)
	GPIO_PORTB_DIR_R &= ~0x03;		//		 same stuff but with PB0/1
  GPIO_PORTF_AFSEL_R &= ~0x15;  //     disable alt funct on PF0/4
	GPIO_PORTB_AFSEL_R &= ~0x03;
  GPIO_PORTF_DEN_R |= 0x15;     //     enable digital I/O on PF0/4
	GPIO_PORTB_DEN_R |= 0x03;
  GPIO_PORTF_PCTL_R &= ~0x000F0F0F; //  configure PF0/4 as GPIO
	GPIO_PORTB_PCTL_R &= ~0x000000FF;
  GPIO_PORTF_AMSEL_R &= ~0x15;  //    disable analog functionality on PF0/4
	GPIO_PORTB_AMSEL_R &= ~0x03;
  GPIO_PORTF_PUR_R |= 0x11;     //     enable weak pull-up on PF0/4
	GPIO_PORTB_PUR_R |= 0x03;
  GPIO_PORTF_IS_R &= ~0x11;     // (d) PF0/4 is edge-sensitive
	GPIO_PORTB_IS_R &= ~0x03;
  GPIO_PORTF_IBE_R &= ~0x11;    //     PF0/4 is not both edges
	GPIO_PORTB_IBE_R &= ~0x03;
  GPIO_PORTF_IEV_R &= ~0x11;    //     PF0/4 falling edge event
	GPIO_PORTB_IEV_R &= ~0x03;
  GPIO_PORTF_ICR_R = 0x11;      // (e) clear flag0/4
	GPIO_PORTB_ICR_R = 0x03;
  GPIO_PORTF_IM_R |= 0x11;      // (f) arm interrupt on PF0/4
	GPIO_PORTB_IM_R |= 0x03;
  NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00A00000; // (g) priority 5
  NVIC_EN0_R = 0x40000000;      // (h) enable interrupt 30 in NVIC
  //EnableInterrupts();           // (i) Enable global Interrupt flag (I)
	*/
}

//CHECK WHICH BIT TO CLEAR
//BY CHECKING RIS?

void GPIOPortB_Handler(void){
	//delay?
	uint32_t trigger_check_b = GPIO_PORTB_RIS_R & 0x00FF;
	if (trigger_check_b == 0x0001){ //switch 3
		GPIO_PORTB_ICR_R = 0x01;
		if (mode_status == ALARM){
			if (alarm_en == ON) Alarm_Disable();
			else if (alarm_en == OFF) Alarm_Set();
		} 
		else if (mode_status == TIME) {
			if (time_part == HR) time_part = MIN;
			else if (time_part == MIN) time_part = HR;
		} 
		else if (mode_status == DISPLAY){
			//12/24
		}
	} 
	else if (trigger_check_b == 0x0002){ //switch 4
		GPIO_PORTB_ICR_R = 0x02;
		//call Snooze
	}
}

void GPIOPortF_Handler(void){
	//delay?
	uint32_t trigger_check_f = GPIO_PORTF_RIS_R & 0x00FF;
	if (trigger_check_f == 0x0001){ //button 1
		GPIO_PORTF_ICR_R = 0x01;
		if (mode_status == ALARM){
			Alarm_Change(1);
		} 
		else if (mode_status == TIME) {
			PF2 ^= 0x04;
			Time_Change(1);
		} 
		else if (mode_status == DISPLAY){
			if (display_status == ANALOG) display_status = DIGITAL;
			else if (display_status == DIGITAL) display_status = ANALOG;
		}
	} else if (trigger_check_f == 0x0010){ //button 2
		GPIO_PORTF_ICR_R = 0x10;      // acknowledge flag4
		if (mode_status == ALARM){
			Alarm_Change(-1);
		} 
		else if (mode_status == TIME) {
			PF1 ^= 0x02;
			Time_Change(-1);
		} 
		else if (mode_status == DISPLAY){
			//STYLE
		}
	}
}
