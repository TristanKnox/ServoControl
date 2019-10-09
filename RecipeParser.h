#include "stdint.h"
#include "UI_Ginerics.h"

#define MAX_CMD_SIZE 11
typedef struct{
	char* recipe;
	int current_index;
	int number_of_loops;
}loop_t;

typedef struct{
	char* recipe;
	int current_index;
	loop_t loop_recipe;
	int loop_count;
	char cmd_string[MAX_CMD_SIZE];
	int cmd_index;
}recipe_t;

typedef struct{
	uint8_t opcode;
	int value;
}command_t;

typedef enum{
	MOV,WAIT,LOOP,END_LOOP,RECIPE_END
}mnemonic_t;

void init_recipe(recipe_t* recipe, char* recipe_string);
void init_loop(loop_t* loop, char* recipe_string, int num_loop_cycles);
command_t* get_next(recipe_t* recipe);
