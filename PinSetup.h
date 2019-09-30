// Tristan Knox

#include "stm32l476xx.h"

#define SLEW_COMP (50)

typedef enum{
	INPUT,	//Input mode
	OUTPUT,	//Gerneral purpose output mode
	ALT,		//Alternate function mode
	ANALOG	//Analog mode
}mode_t;

typedef enum{
	A,B,C,D,E,F,G,H //Represent the GPIOx groups where x = A..H
}GPIO_group_t;

typedef enum{
	CLEAR,
	SET,
	EXTRACT
}mask_t;

typedef struct{
	GPIO_group_t group;
	int pin_number;
	mode_t mode;
}pin_t;

//function declarations
void init_pinX(pin_t pin);
int read_pinX(pin_t pin);
void monitor_pinX(pin_t pin);
void output_pinX_ON(pin_t pin);
void output_pinX_OFF(pin_t pin);


//helper functions
void enable_clock(GPIO_group_t group);
GPIO_TypeDef * get_GPIOx(GPIO_group_t group);
//int build_mask(int pin_number, mask_t type, int bit_clusterint, int culster_size);
int bit_mask(int pin_number, mask_t type);
int mode_mask(pin_t pin, mask_t type);

//int get_bit_cluster(mode_t mode);
int mode_bit_config(mode_t mode);
void time_delay(int duration);
