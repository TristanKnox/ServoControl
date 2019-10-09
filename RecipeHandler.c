#include "RecipeHandler.h"

#define OPCODE_MASK 0xE0
#define CMD_PARAM_MASK ~OPCODE_MASK
command_t build_command(recipe_t* recipe_p);
int validat_opcode(command_t* command);

void init_recipe(recipe_t* recipe, unsigned char* recipe_array){
	recipe->current_index = 0;
	recipe->loop_count = 0;
	recipe->loop_start_index = 0;
	recipe->recipe = recipe_array;
	recipe->is_active = 1;
}

command_t get_next_command(recipe_t* recipe_p){
	command_t command = build_command(recipe_p);
	if(command.opcode == LOOP){
		if(recipe_p->loop_count > 0){
			Red_LED_On();
			recipe_p->is_active = 0;
			command.opcode = RECIPE_END;
			return command;
		}
		recipe_p->loop_start_index = recipe_p->current_index;
		recipe_p->loop_count = command.value;
		command = build_command(recipe_p);
	}
	if(command.opcode == END_LOOP){
		if(recipe_p->loop_count > 0){
			recipe_p->current_index = recipe_p->loop_start_index;
			recipe_p->loop_count--;
		}
		command = build_command(recipe_p);
	}
	if(command.opcode == RECIPE_END){
		recipe_p->is_active = 0;
	}
	
	return command;
}

command_t build_command(recipe_t* recipe_p){
	unsigned char current_command_value = recipe_p->recipe[recipe_p->current_index++];
	uint8_t opcode = current_command_value & OPCODE_MASK;
	uint8_t cmd_param = current_command_value & CMD_PARAM_MASK;
	command_t command;
	command.opcode = opcode;
	command.value = cmd_param;
	if(!validat_opcode(&command)){
		recipe_p->is_active = 0;
		command.opcode = RECIPE_END;
		Red_LED_On();
	}
	return command;
}

int validat_opcode(command_t* command){
	switch(command->opcode){
		case MOV:
		case WAIT:
		case LOOP:
		case END_LOOP:
		case RECIPE_END:
		case RESTART:
			return 1;
		default:
			return 0;
	}
}


