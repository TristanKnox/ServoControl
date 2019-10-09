#include "Validation.h"

// Validats Yes/No input
// Only handles chars and will not validate full strings
int validate_Yes_No(char* input){
	switch(input[0]){
		case 'Y':
		case 'y':
		case 'N':
		case 'n':
			return 1;
		default:
			return 0;
	}
}

int validate_input(char* input)
{
	switch(input[0])
	{
		default:
			return 0;
	}
}

// Check if the given value is within the given range
// Return 1 if in range
// Return 0 if not in range
int validate_within_range(int value, range_t range){
	if(value >= range.min && value <= range.max)
		return 1;
	return 0;
}

// Determines if a string of characters is a valid number
// Return 0 if not a number
// Return 1 if a valid number
int is_number(char* number){
	for(int i = 0; number[i] != '\0'; i++){	// Check each char untill the null terminator is reached
		if(number[i] < 48 && number[i] >57){// If ever this is true, not a number
			return 0;
		}
	}
	return 1; // If we get to here it must be a number
}
