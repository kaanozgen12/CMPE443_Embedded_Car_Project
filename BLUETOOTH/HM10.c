#include "HM10.h"
#include "LED.h"
uint8_t HM10CurrentBufferIndex = 0;
uint8_t HM10NewDataAvailable = 0;



char HM10Buffer[HM10BufferSize];

void HM10_Init() {
	HM10_UART_TX_PIN  &= 7;
	HM10_UART_RX_PIN  &= 7;
	HM10_UART_TX_PIN |= 0x02;
	HM10_UART_RX_PIN |= 0x02;
	
	PCONP |= 1 <<  25;
	
	HM10_UART->FCR =	1 << 0
						 |	0 << 1
						 |	0 << 2
						 |	0 << 6;
	
	HM10_UART->LCR |= (1 << 7);
	
	//Write correct DLM, DLL and FDR values for 9600 baudrate
	HM10_UART->DLM = 0x01;
	HM10_UART->DLL = 0x25; 
	HM10_UART->FDR = 0x01 << 0 | 0x03 << 4;


	HM10_UART->LCR &= ~(1 << 7);
	
	HM10_UART->LCR =	3 << 0
							| 0 << 2
							| 0 << 3
							| 0 << 4;
	
	//Enable the Receive Data Available Interrupt.
	HM10_UART->IER |= 3<<0;
	//Enable UART3_IRQn Interrupt.
	NVIC_EnableIRQ(UART3_IRQn);
	NVIC_SetPriority(UART3_IRQn, 5);
	//NVIC_ClearPendingIRQ(UART3_IRQn);
}

void HM10_SendCommand(char* command) {
	HM10_Write(command);
	EMBEDLED1_On();
	EMBEDLED2_On();
	EMBEDLED3_On();
	EMBEDLED4_On();
}

void HM10_ClearBuffer() {
	HM10CurrentBufferIndex = 0;
	strcpy(HM10Buffer,"");	
}

char HM10_ReadData() {
	while (!(HM10_UART->LSR & 0x01));
	return HM10_UART->RBR;
}

void HM10_WriteData(char data) {
	while (!(HM10_UART->LSR & 0x20));
	HM10_UART->THR = data;
}

void HM10_Write(char* data) {
	while(*data > 0)  {
		HM10_WriteData(*data++);
	}
}


void UART3_IRQHandler() {
	char data;
	data = HM10_ReadData();
	HM10Buffer[HM10CurrentBufferIndex] = data;
	HM10CurrentBufferIndex++;
	if(data == 10){
		HM10NewDataAvailable = 1;
	}
	

	
}
/*


void UART3_IRQHandler() {	
	uint32_t currentInterrupt = ((HM10_UART->IIR & (0x7 << 1)) >> 1);
	
	//First if statement is for Receive Data Available interrupt.
	//When Receive Data Available, the code will enter to the first if condition.
	if(currentInterrupt == 0x02) {
		serialReceivedCharacter = Serial_ReadData();
		serialNewDataAvailable = 1;
	}
	//Second if statement is for THRE interrupt
	//When THRE interrupt is handled, the code will enter to the second if condition.
	else if(currentInterrupt == 0x1) {
		if(*serialTransmitData > 0) {
			Serial_WriteData(*serialTransmitData++);
		}
		else {
			serialTransmitCompleted = 1;
		}
	}
}
*/

