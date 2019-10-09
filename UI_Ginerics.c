#include "UI_Ginerics.h"
//
// This porgram contains Generic UI functions
// It is intended to be resuable and help to simplify the creation of UI's


//
// Display a header that is as wide as the given span and includes the given string as the header msg
// The header string will be centerd and sandiched btween 2 lines of chars that are as long as the span
// Example
//************************************
//          Header mst Here
//************************************
void display_header(int span,char* string){
	display_charater_sequence(span,'*');
	char buffer[span];
	display_string(center_align(string,span,buffer));
	display_charater_sequence(span,'*');
	
}
//
// Builds and displays a sequence of characters
// The span is the number of chars to be included in the sequence
// the character is the carater that is used to built the sequence
// Example: span = 5 character = *
// display output = *****
void  display_charater_sequence(int span, char charater){
	char string[span+1];
	for(int i = 0; i <= span; i++){
		string[i] = charater;
	}
	string[span+1] = '\0';
	display_string(string);
}
//
// Display given string to UART
// Always includes return carage and new line
void display_string(char* string){
	uint8_t display_buffer[BUFFER_SIZE];
	int msg = sprintf((char *) display_buffer, "%s\r\n",string);
	USART_Write(USART2,display_buffer,msg);
}
//
// Center align the given string within the given span
// The original string is unaltered
// The new center aligned string is stored in buffer
// buffer size must be atleast as big as the ((span - length of sting) / 2 + the lenght of string + 1)
char* center_align(char* string, int span, char* buffer){
	int left_side_white_space = (span - strlen(string))/2;
	// Add white space
	for(int i = 0; i < left_side_white_space; i++){
		buffer[i] = ' ';
	}
	// Add string after white space
	for(int i = 0; i < strlen(string); i++){
		buffer[i + left_side_white_space] = string[i];
	}
	buffer[left_side_white_space + strlen(string)] = '\0';
	return buffer;
}
//
// Wait untill the user hits the enter key
// If any other keys are entered before enter
// Displayes msg and prompts for enter again
void wait_for_enter(void){
	int input_size = 2;
	char input[input_size];
	get_user_input(input,input_size);
	while(input[0] != 0x0D){
		display_string("No other input needed\n\rEnter to continue");
		get_user_input(input,input_size);
	}
}

