#include <stdint.h>
#include <stdbool.h>
#include "../inc/tm4c123gh6pm.h"

#define CE		(*((volatile unsigned long *)0x40024004))
#define CSN		(*((volatile unsigned long *)0x40025020))
#define SCK		(*((volatile unsigned long *)0x40025010))
#define MISO	(*((volatile unsigned long *)0x40025004))
#define MOSI	(*((volatile unsigned long *)0x40025008))
#define IRQ		(*((volatile unsigned long *)0x40025040))


void SSI_Init(void);

void send_data(uint8_t data);

uint16_t receive_data(void);
