/* 
  Zachary Pope zhp76
  Mohammad Kedwaii mak3799
  Mar 02 2018
	
	Lab: MW 330-5
	TA: Saadallah Kassir the unstoppable force, the immovable object
*/

/* Timer1.c*/

#include "timer0.h"
#include "timer1.h"
#include "music.h"

extern song song1;
extern volatile uint16_t Note_Index;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode
//void (*PeriodicTask)(void);   // user function


//Taken from Valvano himself
void Delay1millisecond(uint32_t n){
	uint32_t volatile time;
  while(n){
    time = 16000;  // 1msec, tuned at 16 MHz DOUBLE CHECK THIS VALUE
    while(time){
      time--;
    }
    n--;
  }
}


void Timer1A_Init(void){long sr;
  sr = StartCritical(); 
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER1
  //PeriodicTask = task;          // user function
  TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = 15999999;    // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear TIMER1A timeout flag
  TIMER1_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF)|0x0000A000; // 8) priority 5
// interrupts enabled in the main program after all devices initialized
// vector number 37, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
  TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER1A
  EndCritical(sr);
}

void Timer1A_Handler(void){
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge timer1A timeout
  //(*PeriodicTask)();                // execute user task
	
	//this is a pretty crude way to separate notes
	//you can tell but after a long time the music might be delayed
	if (song1.pitches[Note_Index] == song1.pitches[Note_Index + 1]){
		Timer0A_Disable();
		Delay1millisecond(1);
		Timer0A_Enable();
	}
	Note_Index = (Note_Index + 1) % 206;
	Timer0A_ChangeFrequency(song1.pitches[Note_Index]);
	Timer1A_ChangeTime(song1.lengths[Note_Index]);
}

void Timer1A_ChangeTime(uint32_t time){
	TIMER1_CTL_R = 0x00000000;
	TIMER1_TAILR_R = 1000000*time; //1M - 1/16 s
	TIMER1_CTL_R = 0x00000001;
}

void Timer1A_Disable(void){
	TIMER1_CTL_R = 0x00000000;
}

void Timer1A_Enable(void){
	TIMER1_CTL_R = 0x00000001;
	//Timer1A_ChangeTime(song1.lengths[Note_Index]);
}
