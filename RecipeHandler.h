#include "stdint.h"
#include "UI_Ginerics.h"
#include "LED.h"
#include "stdio.h"
#include <stdlib.h>



#define MOV  0x20
#define WAIT 0x40
#define LOOP 0x80
#define END_LOOP 0xA0
#define RESTART 0xC0
#define RECIPE_END 0x00


typedef struct{
	unsigned char* recipe;
	int current_index;
	int loop_start_index;
	int loop_count;	
	int is_active;
}recipe_t;

typedef struct{
	uint8_t opcode;
	uint8_t value;
}command_t;


void init_recipe(recipe_t* recipe, unsigned char* recipe_array);
command_t get_next_command(recipe_t* recipe);
