/* MotorControl.h
Controls the H-Bridge for the motors
Uses PB4-7's PWM function
PB2,3 are GPIO for enable
*/

//Initialize PB4-7 as PWM and PB2,3 as GPIO
void PortB_Init(void);

//Sets the duty cycle for the PWMs
//Chooses motor 0 or 1
//Speed from 0-100
void changeSpeed(uint8_t motor, uint8_t speed);

//Chooses motor 0 or 1
//0 for forward, 1 for backward
void setDirection(uint8_t motor, uint8_t dir);