#include "RecipeParser.h"


#define BUFFER_SIZE 8
// HELPER FUNCTIONS //
void get_next_in_loop(loop_t* loop);


void init_recipe(recipe_t* recipe, char* recipe_string){
	recipe->current_index = 0;
	recipe->recipe = recipe_string;
	recipe->loop_count = 0;
}
void init_loop(loop_t* loop, char* recipe_string, int num_loop_cycles){
	loop->current_index = 0;
	loop->number_of_loops = num_loop_cycles;
	loop->recipe = recipe_string;
}
command_t* get_next(recipe_t* recipe){
	char current_char = recipe->recipe[recipe->current_index++];
	int index = recipe->cmd_index++;
	if(current_char == 0x0A){
		recipe->cmd_string[index] = '\0';
		recipe->cmd_index = 0;
		display_string(recipe->cmd_string);
	}
	else
		recipe->cmd_string[index] = current_char;
	return 0;
	
}


