/* controls.h */
/* Inits and handlers for buttons and joystick */
/* Different launchpad than motor/car */

//import ADC.h from old lab

//init joystick/ADCs
void PortE_Init(void);

//init switches
void PortF_Init(void);

//switch functions
void PortF_Handler(void);