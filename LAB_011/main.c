#include "LPC407x_8x_177x_8x.h"

#include <stdio.h> 
#include <string.h> 
#include "Library/HM10.h"
#include "Library/Serial.h"
#include "Library/HM10.h"
#include "Library/GPIO.h"
#include "Library/PWM.h"
#include "Library/Joystick.h" 
#include "Library/LED.h"
#include "Library/Wait.h"
#include "Library/Ultrasonic.h"
//Define IOCON registers of GPIO pins
#define IOCON_GPIO1		*((volatile uint32_t*)(0x4002C0DC))  //P6_p1.23
#define IOCON_GPIO2		*((volatile uint32_t*)(0x4002C0D0))   //p7_p1.20
#define IOCON_GPIO3		*((volatile uint32_t*)(0x4002C008))  //P9_p0.2
#define IOCON_GPIO4		*((volatile uint32_t*)(0x4002C00C))   //p_p0.3


char characters[128] = ""; 

void motor_command(uint32_t command){
	if(command == 0){
		//FORWARD
		PORT1->PIN &= ~(1<<23 | 1<<20);
		PORT1->PIN |= 1<<23;
		PORT0->PIN &= ~(1<<2 | 1<<3);
		PORT0->PIN |= (1<<3);
		LED2_Off();LED3_Off();LED1_On();LED4_On();
		PWM_Write(100,1);PWM_Write(100,2);
	}else if(command == 1){
		//BACKWARD
		PORT1->PIN &= ~(1<<23 | 1<<20);
		PORT1->PIN |= 1<<20;
		PORT0->PIN &= ~(1<<2 | 1<<3);
		PORT0->PIN |= (1<<2);
		LED2_On();LED3_On();LED1_Off();LED4_Off();
		PWM_Write(100,1);PWM_Write(100,2);
	}else if(command == 2){
		//TURN RIGHT
		//TODO: Implement Blinking PWM
		PORT1->PIN &= ~(1<<23 | 1<<20);
		PORT1->PIN |= 1<<23;
		PORT0->PIN &= ~(1<<2 | 1<<3);
		PORT0->PIN |= (1<<2);
		LED2_On();LED3_Off();LED1_On();LED4_Off();
		PWM_Write(100,1);PWM_Write(70,2);
	}else if(command == 3){
		//TURN LEFT
		PORT1->PIN &= ~(1<<23 | 1<<20);
		PORT1->PIN |= 1<<20;
		PORT0->PIN &= ~(1<<2 | 1<<3);
		PORT0->PIN |= (1<<3);
		LED2_Off();LED3_On();LED1_Off();LED4_On();
		PWM_Write(70,1);PWM_Write(100,2);
	}
}
void init() {	
	//IOCON FOR DIRECTION PINS
	IOCON_GPIO1 &= ~(7);
	IOCON_GPIO2 &= ~(7);
	IOCON_GPIO3 &= ~(7);
	IOCON_GPIO4 &= ~(7);
	PORT1->DIR |= (1<<20 | 1<<23);
	PORT0->DIR |= (1<<2 | 1<<3);
	
	//PORT1->PIN &= ~(1<<20);
	Joystick_Init();
	PWM_Init();
	LED_Init();
	EMBEDLED_Init();
	Ultrasonic_Init();
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	Ultrasonic_Start_Trigger_Timer();
	//motor_command(0);
	HM10_Init();
	
	EMBEDLED1_Off();
	EMBEDLED2_Off();
	EMBEDLED3_Off();
	EMBEDLED4_Off();
	HM10_SendCommand("AT+NAMEbaris_demir");
	HM10_SendCommand("AT+RESET");
	


	/*
	Serial_Init();

	HM10_Init();
	*/
}
int  value = 0;

void update() {
	/* serialTransmitData= "Hello World";
	Serial_WriteData(*serialTransmitData++);
  while(!serialTransmitCompleted); */
	
	
	
}


int main() {
	init();
	
	while(1) {
		update();
	}
}


