#include "GPIO.h"

void GPIO_DIR_Write(GPIO_TypeDef* PORT,uint32_t MASK,uint8_t value) {
	if(value == 0) {
		PORT->DIR &= ~MASK;
	}
	else {
		PORT->DIR |= MASK;
	}
}

void GPIO_PIN_Write(GPIO_TypeDef* PORT,uint32_t MASK,uint8_t value) {
	if(value == 0) {
		PORT->PIN &= ~MASK;
	}
	else {
		PORT->PIN |= MASK;
	}
}

void LED_RIGHT_FORWARD_Init() {
	//Write code for initializing LED_RIGHT_FORWARD.
	GPIO_DIR_Write(LED_RIGHT_FORWARD_PORT,LED_RIGHT_FORWARD_MASK,OUTPUT);
}

void LED_RIGHT_BACKWARD_Init() {
	//Write code for initializing LED_RIGHT_BACKWARD.
	GPIO_DIR_Write(LED_RIGHT_BACKWARD_PORT,LED_RIGHT_BACKWARD_MASK,OUTPUT);
}

void LED_LEFT_FORWARD_Init() {
	//Write code for initializing LED_LEFT_FORWARD.
	GPIO_DIR_Write(LED_LEFT_FORWARD_PORT,LED_LEFT_FORWARD_MASK,OUTPUT);
}

void LED_LEFT_BACKWARD_Init() {
	//Write code for initializing LED_LEFT_BACKWARD.
	GPIO_DIR_Write(LED_LEFT_BACKWARD_PORT,LED_LEFT_BACKWARD_MASK,OUTPUT);
}

void IN1A_Init() {
	//Write code for initializing IN1A.
	GPIO_DIR_Write(IN1A_PORT,IN1A_MASK,OUTPUT);
}

void IN2A_Init() {
	//Write code for initializing IN2A.
	GPIO_DIR_Write(IN2A_PORT,IN2A_MASK,OUTPUT);
}

void IN3B_Init() {
	//Write code for initializing IN3B.
	GPIO_DIR_Write(IN3B_PORT,IN3B_MASK,OUTPUT);
}

void IN4B_Init() {
	//Write code for initializing IN4B.
	GPIO_DIR_Write(IN4B_PORT,IN4B_MASK,OUTPUT);
}

void LED_RIGHT_FORWARD_Off() {
	//Write code for turning off LED_RIGHT_FORWARD.
	GPIO_PIN_Write(LED_RIGHT_FORWARD_PORT,LED_RIGHT_FORWARD_MASK,LOW);
}

void LED_RIGHT_BACKWARD_Off() {
	//Write code for turning off LED_RIGHT_BACKWARD.
	GPIO_PIN_Write(LED_RIGHT_BACKWARD_PORT,LED_RIGHT_BACKWARD_MASK,LOW);
}

void LED_LEFT_FORWARD_Off() {
	//Write code for turning off LED_LEFT_FORWARD.
	GPIO_PIN_Write(LED_LEFT_FORWARD_PORT,LED_LEFT_FORWARD_MASK,LOW);
}

void LED_LEFT_BACKWARD_Off() {
	//Write code for turning off LED_LEFT_BACKWARD.
	GPIO_PIN_Write(LED_LEFT_BACKWARD_PORT,LED_LEFT_BACKWARD_MASK,LOW);
}

void IN1A_Off() {
	//Write code for turning off LED_RIGHT_FORWARD.
	GPIO_PIN_Write(IN1A_PORT,IN2A_MASK,LOW);
}

void IN2A_Off() {
	//Write code for turning off LED_RIGHT_BACKWARD.
	GPIO_PIN_Write(IN2A_PORT,IN2A_MASK,LOW);
}

void IN3B_Off() {
	//Write code for turning off LED_LEFT_FORWARD.
	GPIO_PIN_Write(IN3B_PORT,IN3B_MASK,LOW);
}

void IN4B_Off() {
	//Write code for turning off LED_LEFT_BACKWARD.
	GPIO_PIN_Write(IN4B_PORT,IN4B_MASK,LOW);
}

void LED_RIGHT_FORWARD_On() {
	//Write code for turning on LED_RIGHT_FORWARD.
	GPIO_PIN_Write(LED_RIGHT_FORWARD_PORT,LED_RIGHT_FORWARD_MASK,HIGH);
}

void LED_RIGHT_BACKWARD_On() {
	//Write code for turning on LED_RIGHT_BACKWARD.
	GPIO_PIN_Write(LED_RIGHT_BACKWARD_PORT,LED_RIGHT_BACKWARD_MASK,HIGH);
}

void LED_LEFT_FORWARD_On() {
	//Write code for turning on LED_LEFT_FORWARD.
	GPIO_PIN_Write(LED_LEFT_FORWARD_PORT,LED_LEFT_FORWARD_MASK,HIGH);
}

void LED_LEFT_BACKWARD_On() {
	//Write code for turning on LED_LEFT_BACKWARD.
	GPIO_PIN_Write(LED_LEFT_BACKWARD_PORT,LED_LEFT_BACKWARD_MASK,HIGH);
}
	
void IN1A_On() {
	//Write code for turning on LED_RIGHT_FORWARD.
	GPIO_PIN_Write(IN1A_PORT,IN1A_MASK,HIGH);
}

void IN2A_On() {
	//Write code for turning on LED_RIGHT_BACKWARD.
	GPIO_PIN_Write(IN2A_PORT,IN2A_MASK,HIGH);
}

void IN3B_On() {
	//Write code for turning on LED_LEFT_FORWARD.
	GPIO_PIN_Write(IN3B_PORT,IN3B_MASK,HIGH);
}

void IN4B_On() {
	//Write code for turning on LED_LEFT_BACKWARD.
	GPIO_PIN_Write(IN4B_PORT,IN4B_MASK,HIGH);
}

void go_forward(){
	IN1A_On();
	IN2A_Off();
	
	IN3B_On();
	IN4B_Off();
	
	LED_RIGHT_FORWARD_On();
	LED_LEFT_FORWARD_On();
	
	LED_RIGHT_BACKWARD_Off();
	LED_LEFT_BACKWARD_Off();
	
}

void go_backward(){
	IN1A_Off();
	IN2A_On();
	
	IN3B_Off();
	IN4B_On();
	
	LED_RIGHT_BACKWARD_On();
	LED_LEFT_BACKWARD_On();
	
	LED_LEFT_FORWARD_Off();
	LED_RIGHT_FORWARD_Off();
	
}

void turn_right(uint32_t maneuver){
	uint32_t temp ;
	temp = 0;
	IN1A_On();
	IN2A_Off();
	IN3B_Off();
	IN4B_On();
	LED_RIGHT_FORWARD_On();
	LED_RIGHT_BACKWARD_On();
	LED_LEFT_FORWARD_Off();
	LED_LEFT_BACKWARD_Off();
	if(maneuver == 0){
			//This corresponds to test maneuver
		for(;temp<1500000;temp++){
			if((temp/100000)%2==0){
				LED_RIGHT_FORWARD_On();
				LED_RIGHT_BACKWARD_On();
			}
			else{
				LED_RIGHT_FORWARD_Off();
				LED_RIGHT_BACKWARD_Off();
			}
		}
		stop();
	}else if(maneuver == 1){
		for(;temp<150000;temp++){
			;
		}
		go_forward();
	}
	
	
}


void turn_left(uint32_t maneuver){
	uint32_t temp ;
	temp = 0;
	
	IN1A_Off();
	IN2A_On();
	
	IN3B_On();
	IN4B_Off();
	
	LED_RIGHT_BACKWARD_Off();
	LED_RIGHT_FORWARD_Off();
	
	LED_LEFT_FORWARD_On();
	LED_LEFT_BACKWARD_On();
	
	for(;temp<1500000;temp++){
		if((temp/100000)%2==0){
			LED_LEFT_FORWARD_On();
			LED_LEFT_BACKWARD_On();
		}
		else{
			LED_LEFT_FORWARD_Off();
			LED_LEFT_BACKWARD_Off();
		}
	}
	stop();
	
	
}


void stop(){
	IN1A_Off();
	IN2A_Off();
	
	IN3B_Off();
	IN4B_Off();
	
	LED_RIGHT_BACKWARD_Off();
	LED_LEFT_FORWARD_Off();
	LED_RIGHT_FORWARD_Off();
	LED_LEFT_BACKWARD_Off();
}
