#include "LPC407x_8x_177x_8x.h"

#include <stdio.h> 
#include <string.h> 
#include "Library/HM10.h"
#include "Library/Serial.h"
#include "Library/ADC.h"
#include "Library/GPIO.h"
#include "Library/Timer.h"
#include "Library/PWM.h"
#include "Library/Ultrasonic.h"
#include "Library/LED.h"


#define IOCON_GPIO1		*((volatile uint32_t*)(0x4002C0DC))  //P6_p1.23
#define IOCON_GPIO2		*((volatile uint32_t*)(0x4002C0D0))   //p7_p1.20
#define IOCON_GPIO3		*((volatile uint32_t*)(0x4002C008))  //P9_p0.2
#define IOCON_GPIO4		*((volatile uint32_t*)(0x4002C00C))   //p_p0.3


uint32_t LDR_VALUES[500] = {0};

uint32_t TEST_MODE = 0;
uint32_t AUTO_MODE = 0;
uint32_t START = 0;
uint32_t FINISH= 0;




const char empten[255]= {'\0'};
char last_behaviour[255] = {'\0'};
char characters[128] = ""; 

void motor_command(char* command){
		
	

	if(strcmp(command, "FORWARD\r\n") == 0){
		//FORWARD
		go_forward();
		
		PWM_Write(100,1);
		PWM_Write(100,2);
		memset(last_behaviour, 0, 255);
		strcpy(last_behaviour, "FORWARD\r\n");
		HM10_SendCommand("FORWARD\r\n");
		
	}else if(strcmp(command, "BACK\r\n") == 0){
		//BACKWARD
		go_backward();
		
		PWM_Write(100,1);
		PWM_Write(100,2);
		memset(last_behaviour, 0, 255);
		strcpy(last_behaviour, "BACK\r\n");
		HM10_SendCommand("BACKWARD\r\n");
		
	}else if(strcmp(command, "RIGHT\r\n") == 0){
		//TURN RIGHT
		//TODO: Implement Blinking PWM
		turn_right(0);
		
		PWM_Write(100,1);
		PWM_Write(100,2);
		memset(last_behaviour, 0, 255);
		strcpy(last_behaviour, "RIGHT\r\n");
		HM10_SendCommand("RIGHT\r\n");
		
	}else if(strcmp(command, "LEFT\r\n") == 0){
		//TURN LEFT
		//TODO: Implement Blinking PWM
		turn_left(0);
		
		PWM_Write(100,1);
		PWM_Write(100,2);
		memset(last_behaviour, 0, 255);
		strcpy(last_behaviour, "LEFT\r\n");
		HM10_SendCommand("LEFT\r\n");
		
	}else if(strcmp(command, "STOP\r\n") == 0){
		stop();
		HM10_SendCommand("STOP\r\n");
		
	}else{
	}
}

void init() {
	
//IOCON FOR DIRECTION PINS

	IOCON_GPIO1 &= ~(7);
	IOCON_GPIO2 &= ~(7);
	IOCON_GPIO3 &= ~(7);
	IOCON_GPIO4 &= ~(7);
	
	IN1A_Init();
	IN2A_Init();
	IN3B_Init();
	IN4B_Init();
	
	
	
	LED_RIGHT_FORWARD_Init();
	LED_RIGHT_BACKWARD_Init();
	LED_LEFT_FORWARD_Init();
	LED_LEFT_BACKWARD_Init();
	
	LED_RIGHT_FORWARD_On();
	LED_RIGHT_BACKWARD_On();
	LED_LEFT_FORWARD_On();
	LED_LEFT_BACKWARD_On();
	EMBEDLED_Init();
	PWM_Init();
	
	
	
	ADC_Init();
	Timer_Init();
	ADC_Start();
	
	HM10_Init();
	
	Ultrasonic_Init();
	Ultrasonic_Trigger_Timer_Init();
	Ultrasonic_Capture_Timer_Init();
	Ultrasonic_Start_Trigger_Timer();
	
	//motor_command("FORWARD\r\n");
	
	
}

uint32_t potans_value = 0;

uint32_t ldr_value = 0;
uint32_t ldr_value_sum = 0;
uint32_t count=0;
uint32_t distance =0;
uint32_t previous_distance =0;
char temp;

void update() {
	
	distance = ultrasonic_get_distance();
	if(distance >= 400){
	distance = previous_distance;
	}
	previous_distance = distance;
	if (distance <10){
		EMBEDLED_ALL_Off();
		EMBEDLED1_On();
		EMBEDLED3_On();
		if(AUTO_MODE)
			turn_right(1);
	}else{
		EMBEDLED_ALL_Off();
	}
	
	potans_value = ADC_GetPotans();
	
	PWM_Write(potans_value/40, 2);
	
	if(count < 500){
		LDR_VALUES[count] = ADC_GetLastValue();
		ldr_value_sum = ldr_value_sum + LDR_VALUES[count];
		count = count+1;
	}else {
		count = 0;
		ldr_value = ldr_value_sum / 500;
		ldr_value_sum = 0;
	}		
	
	 
	
	/*
	if(HM10NewDataAvailable && strcmp(HM10Buffer, "STATUS\r\n") == 0){
		HM10NewDataAvailable = 0;
		HM10_ClearBuffer();
		HM10_SendCommand("STATUS\r\n");
		//DIST, LEFT LIGHT, RIGHT LIGHT, OP MODE
		HM10_SendCommand("{\"distance\":5, }");
	}
	
	*/
	
	
	if(ldr_value < 1800 && !FINISH){
		
		FINISH = 1;
		stop();
		HM10_SendCommand("FINISH\r\n");
		
	}else if(FINISH && ldr_value > 2050) {
		FINISH = 0;
		motor_command(last_behaviour);
	}
	
	
	if(!AUTO_MODE){
		
		if(HM10NewDataAvailable){
				HM10NewDataAvailable = 0;
			if(strcmp(HM10Buffer, "TEST\r\n") == 0){
				HM10_ClearBuffer();
				TEST_MODE = 1;
				AUTO_MODE = 0;
				HM10_SendCommand("TESTING\r\n");
				
				
			}else if(strcmp(HM10Buffer, "AUTO\r\n") == 0){
				HM10_ClearBuffer();
				TEST_MODE = 0;
				AUTO_MODE = 1;
				HM10_SendCommand("AUTONOMOUS\r\n");
			
			}else{
				if(TEST_MODE){
					motor_command(HM10Buffer);
				}
				HM10_ClearBuffer();
			}
		}
		
	}else{
			
			if(HM10NewDataAvailable){
					HM10NewDataAvailable = 0;
				if(strcmp(HM10Buffer, "TEST\r\n") == 0){
					
					TEST_MODE = 1;
					AUTO_MODE = 0;
					HM10_SendCommand("TESTING\r\n");
					
				}else if(!START && strcmp(HM10Buffer, "START\r\n") == 0){
				  START = 1;
					HM10_SendCommand("START\r\n");
				}else{
					HM10_ClearBuffer();
				}
			}else{
				if(START){
					//READ SENSOR DATA in this section use median filter to avoid noise in the data
				}
			}
	
	}
	
	
}

int main() {
	
		init();
	
	while(1) {
		update();

	}
}

