#include "timer.h"
#include "ADC.h"
#include "ST7735.h"

#define PF1             (*((volatile uint32_t *)0x40025008))
	
volatile int16_t hours;
volatile int16_t minutes;
volatile int16_t seconds;
volatile int16_t aHr, aMin, aSec;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode



//enum part {
//	HR,
//	MIN,
//	SEC
//};


//enum mode {
//	TIME,
//	ALARM,
//	DISPLAY
//};

//enum timemode {
//	AMPM,
//	MILITARY
//};

//enum displaymode {
//	ANALOG,
//	DIGITAL
//};


//enum alarm {
//	OFF,
//	ON
//};

extern int isChanged;

part time_part;
mode mode_status;
timemode time_status;
displaymode display_status;
alarm alarm_en;


void Timer0A_Init1HzInt(void){
  volatile uint32_t delay;
  DisableInterrupts();
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER0_TAILR_R = 79999999;         // start value for 1 Hz interrupts
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 1
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x20000000; // top 3 bits
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
	
	seconds = 0;
	minutes = 0;
	hours = 0;
	

	time_part = MIN;
	mode_status = TIME;
	time_status = MILITARY;
	display_status = DIGITAL;
	alarm_en = OFF;
}

void Display_Time(void) {
	if (isChanged == 1){
		Output_Clear();
		if (display_status == ANALOG) drawClock();
		isChanged = 0;
	}
	if (display_status == ANALOG){
		drawHands(hours, minutes, seconds);
	} else if (display_status == DIGITAL) {
		digitalClock(hours, minutes, seconds);
	}
}

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
  seconds++;
	if (seconds >= 60) {
		seconds = 0;
		minutes++;
	}
	if (minutes >= 60) {
		minutes = 0;
		hours++;
	}
	if (hours >= 24) {
		hours = 0;
	}

	Display_Time();
	if (alarm_en == ON){
		if (aHr == hours && aMin == minutes && aSec == seconds){
			//Alarm_Sound(); //in speaker
		}
	}
}
 
void Timer1_Init(void){
  SYSCTL_RCGCTIMER_R |= 0x02;   // 0) activate TIMER1
  //PeriodicTask = task;          // user function
  TIMER1_CTL_R = 0x00000000;    // 1) disable TIMER1A during setup
  TIMER1_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER1_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER1_TAILR_R = 799999;    // 4) reload value
  TIMER1_TAPR_R = 0;            // 5) bus clock resolution
  TIMER1_ICR_R = 0x00000001;    // 6) clear TIMER1A timeout flag
  TIMER1_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI5_R = (NVIC_PRI5_R&0xFFFF00FF)|0x00004000; // 8) priority 2
// interrupts enabled in the main program after all devices initialized
// vector number 37, interrupt number 21
  NVIC_EN0_R = 1<<21;           // 9) enable IRQ 21 in NVIC
  TIMER1_CTL_R = 0x00000001;    // 10) enable TIMER1A
}

void Timer1A_Handler(void){
  TIMER1_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER1A timeout
  //check and set mode
	uint32_t ADC_val = ADC0_InSeq3();
	if (ADC_val < 1365) mode_status = ALARM;
	else if (ADC_val >= 1365 && ADC_val <= 2730) mode_status = TIME;
	else if (ADC_val > 2730) mode_status = DISPLAY;

}

void Time_Change(int val){
	if (time_part == HR) {
		if(hours+val >= 0){
			hours = (hours + val) % 24;
		} else {
			hours = 23;
		}
	}
	
	if (time_part == MIN) {
		if(minutes+val >= 0){
			minutes = (minutes + val) % 60;
		} else {
			minutes = 59;
		}
	}
	Display_Time();
}

void Alarm_Change(int val){
	aMin += val;
	if (aMin >= 60) {
		aMin = 0;
		aHr = (aHr + 1) % 24;
	}
	else if (aMin < 0) {
		aMin = 59;
		aHr = (aHr - 1) % 24;
		if (aHr < 0) aHr = 23;
	}
	//update alarm if displayed
}

void Alarm_Set(void) {
	aSec = seconds;
	aMin = (minutes + 1) % 60;
	aHr = hours;
	alarm_en = ON;
}

void Alarm_Disable(void) {
	alarm_en = OFF;
}

