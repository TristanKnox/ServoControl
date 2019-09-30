#include "UI.h"
//#include "Validation.h"
#include "DataColector.h"

#include <stdlib.h>

uint8_t buffer[BufferSize];
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


// Displays a welcom msg for the start of program
//void display_header(void){
//	int msg = sprintf((char *) buffer,"\r\n\n%s\r\n",build_header(80));
//	USART_Write(USART2,buffer,msg);
//	msg = sprintf((char *) buffer, "%27s%s%s\r\n","","Wlcome to our Timing Demo","");
//	USART_Write(USART2,buffer,msg);
//	msg = sprintf((char *) buffer,"%s\r\n",build_header(80));
//	USART_Write(USART2,buffer,msg);
//}



// Prompts user to aprove current limit settings
int is_limit_approved(void){
	display_limits();
	display_prompt("Would you like to use these limits? (Y/N):\r\n");
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
// Displays an invald msg
void invalid_YES_NO_prompt(void){
	char str[] = "Invalid input(Y/N):\r\n";
	USART_Write(USART2, (uint8_t *)str, strlen(str));
}



// Display the current limit settings
void display_limits(void){
	int msg = sprintf((char *) buffer, "\r\nCurrent limits\r\n==============\r\n%5s = %d\r\n%5s = %d\r\n\n","Lower",get_curent_limit(),"Upper",get_curent_limit()+100);
	USART_Write(USART2,buffer,msg);
}

// Prints out a number to the UART
void display_number(int number){
	int msg = sprintf((char *) buffer, "%d\r\n",number);
	USART_Write(USART2,buffer,msg);
}



// Validats that the limit value is a number
// Validates that the limit is within the accepted range
// Return 1 if true
// Return 0 if flase
int validate_limit_string(char* limit){
	if(!is_number(limit))
		return 0;
	int value = atoi(limit);
	range_t range = {50,9950};
	if(validate_within_range(value, range))
		return 1;
	return 0;
}



// Prompts the user for a new lower limit
// Validate the new limit and prompt for it again if not valid
// return the new limit as an int
int get_new_limit(void){
	display_prompt("\r\nThe upper limit will be 100 greater than the lower limit\r\nWhat would you like the lower limit to be?");
			int input_size = 6;
			char input[input_size];
			get_user_input(input, input_size);
			while(!validate_limit_string(input)){
				display_prompt("\r\nLimit must be a number between 50 and 9950");
				get_user_input(input,input_size);
			}
			return atoi(input);
}

// Promt the user to choose limit settings
// Will display current/default settings and ask user if this is desired
// Other wise prompt user for new limit unitll user is satified
void prompt_for_limit(void){
	int limit_aprooved = 0;
	while(!limit_aprooved){
		if(is_limit_approved())
			limit_aprooved = 1;
		else{
			int new_limit = get_new_limit();
			set_limit(new_limit);
			display_number(get_curent_limit());
		}
	}
	display_prompt("Limits Set");
	display_limits();
	display_string("Enter to continue...");
	wait_for_enter();
	display_prompt("Colecting data with curent limits.");
	display_charater_sequence(60,'-');
		
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
