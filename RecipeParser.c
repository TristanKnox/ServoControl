//#include "RecipeParser.h"


//#define BUFFER_SIZE 8
//// HELPER FUNCTIONS //
//void get_next_in_loop(loop_t* loop);
//int pars_recipe_string(recipe_t* recipe, char* recipe_string, command_t* comands);
//int isEqual(char* str1, char* str2);
//int get_opcode(char* mnemonic);
//void transfer_temp_commands(command_t* commands, command_t* temp, int num_commands);
//	
////////////////////////////////////////////////////////////////////

//void init_recipe(recipe_t* recipe, char* recipe_string){
//	command_t temp_commands[strlen(recipe_string)];
//	int num_commands = pars_recipe_string(recipe, recipe_string, temp_commands);
//	command_t* commands;
//	recipe->commands = (command_t*) malloc(num_commands * sizeof(command_t));
//	transfer_temp_commands(recipe->commands, temp_commands, num_commands);
//	//recipe->commands = commands;
//	recipe->current_index = 0;
//	recipe->is_active =1;
//}

//command_t get_next(recipe_t* recipe){
//	command_t command = {0,0};
//	if(recipe->is_active){
//		int recipe_index = recipe->current_index++;
//		int index = recipe_index * sizeof(command_t);
//		command = recipe->commands[index];
//		if(command.opcode == 0){
//			free(recipe->commands);
//			recipe->is_active = 0;
//		}
//		return command;
//	}
//	return command;
//}


//int pars_recipe_string(recipe_t* recipe, char* recipe_string, command_t* commands){
//	//int total_commands = 0;
//	int command_index = 0;
//	char mnemonic[11];
//	char cmd_value[3];
//	for(int i = 0; i < strlen(recipe_string);){
//		char current_char = recipe_string[i++];
//		int index = 0;
//		while(current_char != '+'&& current_char != 0){
//			mnemonic[index++] = current_char;
//			current_char = recipe_string[i++];
//		}
//		mnemonic[index] = '\0';
//		index = 0;
//		current_char = recipe_string[i++];
//		while(current_char != 0x0A && current_char != 0){
//			cmd_value[index++] = current_char;
//			current_char = recipe_string[i++];
//		}
//		cmd_value[index] = '\0';
//		index = 0;
//		display_string(mnemonic);
//		display_string(cmd_value);
//		command_t command;
//		command.opcode = get_opcode(mnemonic);
//		command.value = atoi(cmd_value);
//		commands[command_index++] = command;
//	}
//	return command_index;
//}

//void transfer_temp_commands(command_t* commands, command_t* temp, int num_commands){
//	int index;
//	for(int i = 0; i < num_commands; i++){
//		int size = sizeof(command_t);
//		index = i*size;
//		command_t command = temp[i];
//		commands[i*sizeof(command_t)] = command;
//	}
//}

//int get_opcode(char* mnemonic){
//	if(isEqual(mnemonic, "MOV"))
//		return 1; //0b001
//	else if(isEqual(mnemonic, "WAIT"))
//		return 2; //0b010
//	else if(isEqual(mnemonic, "LOOP"))
//		return 3; //0b100
//	else if(isEqual(mnemonic, "END_LOOP"))
//		return 4; //0b101
//	else if(isEqual(mnemonic, "END_RECIPE"))
//		return 0; //0b000
//	return 0;
//	
//}

//int isEqual(char* str1, char* str2){
//	if(strlen(str1) != strlen(str2))
//		return 0;
//	for(int i = 0; i < strlen(str1); i++){
//		if(str1[i] != str2[i])
//			return 0;
//	}
//	return 1;
//}


