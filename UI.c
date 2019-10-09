#include "UI.h"

#include <stdlib.h>

uint8_t buffer[BUFFER_SIZE];
//char RxComByte = 0;

// Function Declaration
void invalid_YES_NO_prompt(void);
int is_limit_approved(void);


char string[100];


// Prints a string to the UART
void display_prompt(char * string){
	int msg = sprintf((char *) buffer,"%s\r\n",string);
	USART_Write(USART2,buffer,msg);
}

void display_formated_msg(int msg){
	USART_Write(USART2,buffer,msg);
}






// Displays an invald msg
void invalid_YES_NO_prompt(void){
	char str[] = "Invalid input(Y/N):\r\n";
	USART_Write(USART2, (uint8_t *)str, strlen(str));
}





// Prints out a number to the UART
void display_number(int number){
	int msg = sprintf((char *) buffer, "%d\r\n",number);
	USART_Write(USART2,buffer,msg);
}










void wiat_for_enter(void){
	
}
//
// Generic function to promp with a given string
// Then accept user input as Y/N
// Includes validation to ensure that only 'y','Y','n','N  are accepted
// return 1 if yes
// return 0 if no
int try_again_promt(char* string){
	display_string(string);
	int input_size = 2;
	char input[input_size];
	get_user_input(input,input_size);
	while(!validate_Yes_No(input)){
		display_prompt("Invalid input(Y/N):\r\n");
		get_user_input(input,input_size);
	}
	if(input[0] == 'y' || input[0] == 'Y')
		return 1;
	return 0;
	
}

char * build_char_sequence(int size, char character){
	for(int i = 0; i < size; i++){
		string[i] = character;
	}		
	string[size] = '\0';
	return &string[0];
}
