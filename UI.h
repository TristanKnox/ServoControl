#include "stm32l476xx.h"
#include "userInputHandler.h"
#include "UART.h"
#include "UI_Ginerics.h"
#include <stdio.h>
#include <string.h>

void display_formated_msg(int msg);
//void display_header(void);
void display_limits(void);
void display_prompt(char* string);
int try_again_promt(char* string);



void prompt_for_limit(void);

char * build_header(int size);
