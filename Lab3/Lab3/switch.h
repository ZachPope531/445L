/* switch.h */
/* 
  Zachary Pope zhp76
  Mohammad Kedwaii mak3799
  Feb 12 2018
*/

//From ST7735 file
//Counts for n milliseconds
//Input: 32 bit value, counts for n ms
//Output: none
void Delay1millisecond(uint32_t n);

//Initializes switches on Port F to respond to falling edges
//Input: none
//Output: none
void EdgeCounter_Init(void);

//Switch interrupt
//Checks which switch triggered
//Calls function or changes status variable based on switch and mode
//Input: none
//Output: none
void GPIOPortF_Handler(void);
