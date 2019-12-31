#ifndef GPIO_H
#define GPIO_H

#include "LPC407x_8x_177x_8x.h"

typedef struct
{
  volatile	uint32_t DIR;
						uint32_t RESERVED0[3];
  volatile	uint32_t MASK;
  volatile	uint32_t PIN;
  volatile	uint32_t SET;
  volatile  uint32_t CLR;
} GPIO_TypeDef;

typedef enum {
	INPUT = 0,
	OUTPUT = 1
} GPIO_Direction;

typedef enum {
	LOW = 0,
	HIGH = 1
} GPIO_Value;


#define GPIO_ADDRESS	0x20098000

#define PORT0	((GPIO_TypeDef*) PORT0_BASE)
#define PORT1	((GPIO_TypeDef*) PORT1_BASE)
#define PORT2	((GPIO_TypeDef*) PORT2_BASE)
#define PORT3	((GPIO_TypeDef*) PORT3_BASE)
#define PORT4	((GPIO_TypeDef*) PORT4_BASE)
#define PORT5	((GPIO_TypeDef*) PORT5_BASE)

#define PORT0_BASE		(GPIO_ADDRESS + 0x000)
#define PORT1_BASE		(GPIO_ADDRESS + 0x020)
#define PORT2_BASE		(GPIO_ADDRESS + 0x040)
#define PORT3_BASE		(GPIO_ADDRESS + 0x060)
#define PORT4_BASE		(GPIO_ADDRESS + 0x080)
#define PORT5_BASE		(GPIO_ADDRESS + 0x0A0)

//Write Correct Port and Mask values.
#define LED_RIGHT_FORWARD_PORT			PORT1
#define LED_RIGHT_FORWARD_MASK			((uint32_t) 1 << 11)

#define LED_RIGHT_BACKWARD_PORT			PORT1
#define LED_RIGHT_BACKWARD_MASK			((uint32_t) 1 << 7)

#define LED_LEFT_FORWARD_PORT			PORT0
#define LED_LEFT_FORWARD_MASK			((uint32_t) 1 << 4)

#define LED_LEFT_BACKWARD_PORT			PORT0
#define LED_LEFT_BACKWARD_MASK			((uint32_t) 1 << 5)

#define IN1A_PORT			PORT1
#define IN1A_MASK			((uint32_t) 1 << 23)

#define IN2A_PORT			PORT1
#define IN2A_MASK			((uint32_t) 1 << 20)

#define IN3B_PORT			PORT0
#define IN3B_MASK			((uint32_t) 1 << 3)

#define IN4B_PORT			PORT0
#define IN4B_MASK			((uint32_t) 1 << 2)


void GPIO_DIR_Write(GPIO_TypeDef* PORT,uint32_t MASK,uint8_t value);
void GPIO_PIN_Write(GPIO_TypeDef* PORT,uint32_t MASK,uint8_t value);

void LED_RIGHT_FORWARD_Init(void);
void LED_RIGHT_BACKWARD_Init(void);
void LED_LEFT_FORWARD_Init(void);
void LED_LEFT_BACKWARD_Init(void);

void IN1A_Init(void);
void IN2A_Init(void);
void IN3B_Init(void);
void IN4B_Init(void);

void LED_RIGHT_FORWARD_Off(void);
void LED_RIGHT_BACKWARD_Off(void);
void LED_LEFT_FORWARD_Off(void);
void LED_LEFT_BACKWARD_Off(void);

void IN1A_Off(void);
void IN2A_Off(void);
void IN3B_Off(void);
void IN4B_Off(void);

void LED_RIGHT_FORWARD_On(void);
void LED_RIGHT_BACKWARD_On(void);
void LED_LEFT_FORWARD_On(void);
void LED_LEFT_BACKWARD_On(void);

void IN1A_On(void);
void IN2A_On(void);
void IN3B_On(void);
void IN4B_On(void);

void go_forward(void);

void go_backward(void);

void turn_right(uint32_t);

void turn_left(uint32_t);

void stop(void);

#endif
