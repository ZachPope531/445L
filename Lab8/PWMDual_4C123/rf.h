/* rf.h */
/* Initialize module, send data and receive data */


//imports

//initialize Port F
void PortF_Init(void);

//init timer for checking/sending data
void Timer0A_Init(void);

//check for data transmission
void Timer0A_Handler(void);