#include "External.h"


void External_Init() {
	//Change the functionality of the push button as EINT0
	IOCON_PUSH_BUTTON &= ~(7<<0);
	IOCON_PUSH_BUTTON |= (1<<0);
	
	//IOCON_PUSH_BUTTON &= ~(3<<3);

	
	//Change the External interrupt mode as Edge Sensitive
	EXT->EXTMODE |= 1<<0;
	//Change polarity of the External Interrupt as Low-active
	EXT->EXTPOLAR |= (1<<0);
	//Enable interrupt for EINT0_IRQn
	NVIC_EnableIRQ(EINT0_IRQn);
  //EXT->EXTINT |= 1<<0;

}

