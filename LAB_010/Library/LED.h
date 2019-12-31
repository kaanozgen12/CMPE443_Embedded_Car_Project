#ifndef LED_H
#define LED_H

#include "LPC407x_8x_177x_8x.h"
#include "GPIO.h"

#define LED1_PORT			PORT1
#define LED1_MASK			((uint32_t) 1 << 11)

#define LED2_PORT			PORT1
#define LED2_MASK			((uint32_t) 1 << 12)

#define LED3_PORT			PORT0
#define LED3_MASK			((uint32_t) 1 << 4)

#define LED4_PORT			PORT0
#define LED4_MASK			((uint32_t) 1 << 5)


#define EMBEDLED1_PORT			PORT1
#define EMBEDLED1_MASK			((uint32_t) 1 << 18)

#define EMBEDLED2_PORT			PORT0
#define EMBEDLED2_MASK			((uint32_t) 1 << 13)

#define EMBEDLED3_PORT			PORT1
#define EMBEDLED3_MASK			((uint32_t) 1 << 13)

#define EMBEDLED4_PORT			PORT2
#define EMBEDLED4_MASK			((uint32_t) 1 << 19)

void LED_Init(void);
void LED1_Init(void);
void LED2_Init(void);
void LED3_Init(void);
void LED4_Init(void);

void LED_ON(void);
void LED1_On(void);
void LED2_On(void);
void LED3_On(void);
void LED4_On(void);

void LED_OFF(void);
void LED1_Off(void);
void LED2_Off(void);
void LED3_Off(void);
void LED4_Off(void);


void EMBEDLED_Init(void);

void EMBEDLED1_On(void);
void EMBEDLED2_On(void);
void EMBEDLED3_On(void);
void EMBEDLED4_On(void);

void EMBEDLED1_Off(void);
void EMBEDLED2_Off(void);
void EMBEDLED3_Off(void);
void EMBEDLED4_Off(void);

void EMBEDLED_ALL_On(void);
void EMBEDLED_ALL_Off(void);

#endif
