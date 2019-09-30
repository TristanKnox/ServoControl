#include "UserInputHandler.h"



// Adds USART read chars to a string
// Continues untill enter key is detected
// max_input_size is the maximum number of char the user is alowed to enter
// If user inputs more chars than premited an error is displayed and user is prompted for input again
void get_user_input(char* input, int max_input_size){
	uint8_t buffer[BufferSize];
	char rxByte;
	int current_char;
	int index = 0;
	while(rxByte != 0x0D){
		if(index == max_input_size){
			over_flow_error(max_input_size);
			index = 0;
		}

		rxByte = USART_Read(USART2);
		current_char = sprintf((char *) buffer, "%c",rxByte);
		USART_Write(USART2,buffer,current_char);	
		input[index] = rxByte;
		index++;

		
	}
	input[index + 1] = '\0';	
}

// Display over flow error mesage 
// used when user tries to input more chars than input string can hold
void over_flow_error(int limit){
	uint8_t buffer[100];
	int msg = sprintf((char *) buffer, "\r\nExceeded char limit!\r\n");
	USART_Write(USART2,buffer,msg);
	msg = sprintf((char *) buffer, "Input may not exceed %d characters.\r\nPlease try again.\r\n",limit);
	USART_Write(USART2,buffer,msg);
}

