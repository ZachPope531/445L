#include <stdio.h>
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "screen.h"

typedef enum {
	HR,
	MIN,
	SEC
} part;

typedef enum {
	TIME,
	ALARM,
	DISPLAY
} mode;

typedef enum {
	AMPM,
	MILITARY
} timemode;

typedef enum {
	ANALOG,
	DIGITAL
} displaymode;

typedef enum {
	OFF,
	ON
} alarm;

extern part time_part;
extern mode mode_status;
extern timemode time_status;
extern displaymode display_status;
extern alarm alarm_en;

void Timer0A_Init1HzInt(void);

void Display_Time(void);

void Timer0A_Handler(void);

void Timer1_Init(void);

void Timer1A_Handler(void);

void Time_Change(int val);

void Alarm_Change(int val);

void Alarm_Set(void);

void Alarm_Disable(void);

