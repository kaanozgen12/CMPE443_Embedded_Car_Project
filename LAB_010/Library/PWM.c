#include "PWM.h"

void PWM_Init() {
	//Change the function of the pin in here:
	IOCON_MOTOR_SPEED_A &= ~(7);
	IOCON_MOTOR_SPEED_A |= 3;

	IOCON_MOTOR_SPEED_B &= ~(7);
	IOCON_MOTOR_SPEED_B |= 3;
	
	
	PCONP |= (1 << 5 | 1 << 6);
	
	//Enable PWM output for corresponding pin.
	PWM0->PCR |= (1 << 9 | 1<<10);
	// Reset The PWM Timer Counter and The PWM Prescale Counter on the Next Positive Edge of PCLK
	PWM0->TCR = 1 << 1;
	

	
	//Configure MR0 register for a period of 20 ms
	PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000.0) * 20 * 1000;
	// Reset TC, when MR0 matches TC.
	PWM0->MCR = 1 << 1;
	// Enable PWM Match 0 Latch.
	PWM0->LER |= 1 << 0;
	// Enable Counter and PWM and Clear Reset on the PWM
	PWM0->TCR &= ~(1 << 1);
	PWM0->TCR |= (1 << 0 | 1 << 3);
	
}

void PWM_Cycle_Rate(uint32_t period_In_Cycles) {
	//Write a formula that changes the MR0 register value for a given parameter.
	PWM0->MR0 = (PERIPHERAL_CLOCK_FREQUENCY / 1000000) * period_In_Cycles * 1000;
	
	PWM0->LER |= 1 << 0;
}

void PWM_Write(uint32_t T_ON,uint32_t number) {	
	if(T_ON > 100) {
		T_ON = 100;
	}
	
	T_ON =(uint32_t)((( PWM0->MR0 ) * T_ON ) / 100.0);

	if (T_ON == PWM0->MR0) {
		T_ON++;
	}
	
	//Write a formula to calculate the match register of the PWM pin.
	if(number == 1){
		PWM0->MR1 = T_ON;
	
	}else if(number == 2){
		PWM0->MR2 = T_ON;
		
	}
	//Enable PWM Match Register Latch.
	PWM0->LER = 1<<number;
}
