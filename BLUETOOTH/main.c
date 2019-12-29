#include "LPC407x_8x_177x_8x.h"

#include <stdio.h> 
#include <string.h> 
#include "Library/HM10.h"
#include "Library/Serial.h"
#include "Library/GPIO.h"
#include "Library/PWM.h"
#include "Library/Joystick.h" 
#include "Library/LED.h"
#include "Library/Wait.h"
#include "Library/Ultrasonic.h"

#include "Library/ADC.h"
#include "Library/Timer.h"

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
		PWM_Write(100,1);PWM_Write(30,2);
	}else if(command == 2){
		//TURN RIGHT
		//TODO: Implement Blinking PWM
		PORT1->PIN &= ~(1<<23 | 1<<20);
		PORT1->PIN |= 1<<23;
		PORT0->PIN &= ~(1<<2 | 1<<3);
		PORT0->PIN |= (1<<2);
		LED2_On();LED3_Off();LED1_On();LED4_Off();
		PWM_Write(100,1);PWM_Write(40,2);
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
	//Joystick_Init();
	//PWM_Init();
	LED_Init();
	EMBEDLED_Init();
	//Ultrasonic_Init();
	//Ultrasonic_Trigger_Timer_Init();
	//Ultrasonic_Capture_Timer_Init();
	//Ultrasonic_Start_Trigger_Timer();
	//motor_command(1);
	HM10_Init();
	Serial_Init();
	EMBEDLED1_Off();
	EMBEDLED2_Off();
	EMBEDLED3_Off();
	EMBEDLED4_Off();
	
	//ADC_Init();
	//Timer_Init();
	//ADC_Start();

	
	


	/*
	Serial_Init();

	HM10_Init();
	*/
}
int value = 0;
uint32_t count=0;
char temp;
void update() {
	
	while(!serialNewDataAvailable);
	serialNewDataAvailable = 0;
	temp = serialReceivedCharacter;
	if (temp != 13){
		characters[count] = temp;
		count++;
	}
	else{
		characters[count] = '\r';
		characters[count+1] = '\n';
		characters[count+2] = '\0';
		characters[count+3] = 13;
		HM10_SendCommand("name\r\n");
		//HM10_ClearBuffer();
		strcpy(characters, "");
		count=0;
		
	}

	/*
	serialTransmitData= "Hello World";
	Serial_WriteData(*serialTransmitData);
  while(!serialTransmitCompleted); 
	*/
	
	/*SERIAL FULL CALISAN
	while(!serialNewDataAvailable);
	serialNewDataAvailable = 0;
	temp = serialReceivedCharacter;
	if (temp != 13){
		characters[count] = temp;
		count++;
	}
	else{
		characters[count] = '\0';
		serialTransmitData= characters;
		Serial_WriteData(*serialTransmitData++);
		while(!serialTransmitCompleted); 
		strcpy(characters, "");
		count=0;
		
	}
	*/
	 
}


int main() {
	init();
	
	while(1) {
		update();
	}
}


