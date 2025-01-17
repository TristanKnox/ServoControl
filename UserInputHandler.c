#include "UserInputHandler.h"

int current_index = 0;

// Adds USART read chars to a string
// Continues untill enter key is detected
// max_input_size is the maximum number of char the user is alowed to enter
// If user inputs more chars than premited an error is displayed and user is prompted for input again
int get_user_input(char* input, int max_input_size){
	uint8_t ui_buffer[BUFFER_SIZE];
	char rxByte;
	int current_char;
	if(current_index == max_input_size){
			over_flow_error(max_input_size);
			current_index = 0;
			
		}
		if(USART2->ISR & USART_ISR_RXNE){
			rxByte = (uint8_t)(USART2->RDR & 0xFF);
			current_char = sprintf((char *) ui_buffer, "%c",rxByte);
			USART_Write(USART2,ui_buffer,current_char);	
			input[current_index] = rxByte;
			if(rxByte == 0x08){ // Backspace
				if(current_index > 0)
				{
					current_index--;
				}
				return 0;
			}
			current_index++;
		}
		if(rxByte == 0x0D){
			input[current_index - 1] = '\0';
			current_index = 0;
			return 1;
		}
	return 0;
}

// Display over flow error mesage 
// used when user tries to input more chars than input string can hold
void over_flow_error(int limit){
	uint8_t overflow_buffer[OVERFLOW_BUFFER_SIZE];
	int msg = sprintf((char *) overflow_buffer, "\r\nExceeded char limit!\r\n");
	USART_Write(USART2,overflow_buffer,msg);
	msg = sprintf((char *) overflow_buffer, "Input may not exceed %d characters.\r\nPlease try again.\r\n",limit);
	USART_Write(USART2,overflow_buffer,msg);
}

