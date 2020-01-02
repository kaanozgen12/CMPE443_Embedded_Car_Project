#ifndef ADC_H
#define ADC_H

#include "LPC407x_8x_177x_8x.h"

#include "SystemStructures.h"


typedef struct {
  volatile	uint32_t CR;
  volatile	uint32_t GDR;
						uint32_t RESERVED0;
  volatile	uint32_t INTEN;
  volatile	uint32_t DR[8];
  volatile	uint32_t STAT;
  volatile	uint32_t TRM;
} ADC_TypeDef;

#define ADC_CLOCK_FREQUENCY 1000000

//Write the IOCON address of Analog Pin
#define	ANALOG_PIN_IOCON_ADDRESS_RIGHT	0x4002C064
#define ANALOG_PIN_IOCON_RIGHT	*((volatile uint32_t*)(ANALOG_PIN_IOCON_ADDRESS_RIGHT))

#define	ANALOG_PIN_IOCON_ADDRESS_LEFT	0x4002C0F8
#define ANALOG_PIN_IOCON_LEFT	*((volatile uint32_t*)(ANALOG_PIN_IOCON_ADDRESS_LEFT))
	
#define	ANALOG_PIN_IOCON_ADDRESS_POTANS	0x4002C05C
#define ANALOG_PIN_IOCON_POTANS	*((volatile uint32_t*)(ANALOG_PIN_IOCON_ADDRESS_POTANS))

//Write the max value of ADC.
#define ADC_MAX_VALUE 0xFFF

//Define a ADC_CLKDIV variable for given ADC_CLOCK_FREQUENCY.
#define ADC_CLKDIV 59

#define ADC_BASE	0x40034000
#define ADC	((ADC_TypeDef*) ADC_BASE)

extern uint32_t ADC_Last;
extern uint32_t ADC_Right;
extern uint32_t ADC_Left;

extern uint32_t ADC_Potans;


extern uint32_t counter;

void ADC_Init(void);
void ADC_Start(void);
void ADC_Stop(void);
uint32_t ADC_GetLastValue(void);
uint32_t ADC_GetPotans(void);

#endif
