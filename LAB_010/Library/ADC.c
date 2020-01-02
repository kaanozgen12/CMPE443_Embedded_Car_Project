#include "ADC.h"
#include "Wait.h"

uint32_t ADC_Last = 0;
uint32_t ADC_Right = 0;
uint32_t ADC_Left = 0;

uint32_t ADC_Potans = 0;

uint32_t counter = 0;



void ADC_Init() {
	//Change the function value of pin to ADC.
	ANALOG_PIN_IOCON_RIGHT &= ~(7);
	ANALOG_PIN_IOCON_RIGHT |= 1;
	
	//Change the mode value of pin to mode which should be selected if Analog mode is used.
	ANALOG_PIN_IOCON_RIGHT &= ~(3<<3);
	//Change Analog/Digital mode of pin to Analog.
	ANALOG_PIN_IOCON_RIGHT &= ~(1<<7);
	
	//Change the function value of pin to ADC.
	ANALOG_PIN_IOCON_LEFT &= ~(7);
	ANALOG_PIN_IOCON_LEFT |= 3;
	
	//Change the mode value of pin to mode which should be selected if Analog mode is used.
	ANALOG_PIN_IOCON_LEFT &= ~(3<<3);
	//Change Analog/Digital mode of pin to Analog.
	ANALOG_PIN_IOCON_LEFT &= ~(1<<7);
	
	//Change the function value of pin to ADC.
	ANALOG_PIN_IOCON_POTANS &= ~(7);
	ANALOG_PIN_IOCON_POTANS |= 1;
	
	//Change the mode value of pin to mode which should be selected if Analog mode is used.
	ANALOG_PIN_IOCON_POTANS &= ~(3<<3);
	//Change Analog/Digital mode of pin to Analog.
	ANALOG_PIN_IOCON_POTANS &= ~(1<<7);
	
	
	//Turn on ADC.
	PCONP |= 1<<12;
	//Set the CLKDIV and make the A/D converter operational without Burst mode.
	ADC->CR |= ADC_CLKDIV << 8;
	//Make the A/D converter operational
	ADC->CR |= 1<<21;
	//Make sure conversions are software controlled and require 31 clocks (Do not use Burst mode)
	ADC->CR &= ~(1<<16);
	//Configure CR SEL bits for sampled and converting corresponding pin.
	ADC->CR &= ~(0xFF);
	ADC->CR |= 1<<0;
	
	//Enable interrupt for corresponding pin.
	ADC->INTEN |= 1<<4;
	ADC->INTEN |= 1<<2;
	//ADC->INTEN |= 1<<1;Burasi artik ultrasonic için
	ADC->INTEN |= 1<<0;
	//Enable ADC_IRQn (Interrupt Request).
	NVIC_EnableIRQ(ADC_IRQn);
}

void ADC_Start () {
	//Write a code for starting A/D conversion on a rising edge on the TIMER 0 MATCH 1.
	
	ADC->CR |= 1<<24;
	
}

uint32_t ADC_GetLastValue() {	
	if (ADC_Left < ADC_Right){
		return ADC_Left;
	}else{
		return ADC_Right;
	}
}

uint32_t ADC_GetPotans(){
	return ADC_Potans;
}




void ADC_IRQHandler() {
	ADC->GDR &= ~((uint32_t)1 << 31);
	
	//Write the converted data (only the converted data) to ADC_	
	if((ADC->CR & 1<<24) == 0){
		ADC->CR |= 1<<24;
		counter = (counter+1)%3;
	}
	
	if(counter == 2){
		ADC_Left = ADC->DR[counter*2]>>4 & 0xFFF;
	}else if(counter == 1){
		ADC_Right = ADC->DR[counter*2]>>4 & 0xFFF;
	}else if(counter == 0){
		ADC_Potans = ADC->DR[counter*2]>>4 & 0xFFF;
	}
		
	ADC->CR &= ~(0xFF);
	ADC->CR |= 1<<(((counter+1)%3)*2);
	
	
	
	ADC->CR &= ~(7<<24);
}
