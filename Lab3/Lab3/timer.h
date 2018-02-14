/* timer.h */
/* 
  Zachary Pope zhp76
  Mohammad Kedwaii mak3799
  Feb 12 2018
*/

#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "screen.h"

/* values to modify in time mode */
typedef enum {
	HR,
	MIN,
	SEC //we ended up not using this
} part;

/* different modes */
typedef enum {
	TIME, //adjust time by minutes or hours
	ALARM, //adjust alarm time, enable/disable alarm
	DISPLAY //analog or digital, 12hr or 24hr
} mode;

/* 12 vs 24 hr */
typedef enum {
	AMPM,
	MILITARY
} timemode;

/* analog vs digital */
typedef enum {
	ANALOG,
	DIGITAL
} displaymode;

/* alarm enable/disable */
typedef enum {
	OFF,
	ON
} alarm;

//Initialize Timer 0, which updates clock
//1 Hz
//Input: none
//Output: none
void Timer0A_Init1HzInt(void);


//Draws clock and alarm on display
//Input: none
//Output: none
void Display_Time(void);

//Updates time variables
//Adds 1 second, carries as necessary
//Calls Display_Time
//Input: none
//Output: none
void Timer0A_Handler(void);

//Initalize Timer 1
//Checks ADC for mode change
//Input: none
//Output: none
void Timer1_Init(void);

//Checks ADC, sets mode
//Input: none
//Output: none
void Timer1A_Handler(void);

//Updates time value, updates display
//Input: val: +1 or -1, added to time
//Output: none
void Time_Change(int val);

//Updates alarm value, updates display
//Input: val: +1 or -1, added to alarm
//Output: none
void Alarm_Change(int val);

//Sets alarm time to clock time plus one minute
//Sets alarm status to ON
//Input: none
//Output: none
void Alarm_Set(void);

//Sets alarm status to OFF
//Input: none
//Output: none
void Alarm_Disable(void);

//Prints alarm hours and minutes to LCD
//Input: none
//Output: none
void Print_Alarm(void);
