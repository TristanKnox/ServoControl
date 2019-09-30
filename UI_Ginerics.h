#include "UART.h"
#include "Validation.h"
#include "UserInputHandler.h"
#include <string.h>


void display_header(int span,char* string);
void display_string(char* string);
char* center_align(char* string, int span, char* buffer);
void wait_for_enter(void);
void  display_charater_sequence(int span, char charater);
