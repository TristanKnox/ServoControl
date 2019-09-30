//Tristan Knox
// This program is inteded to povide Gineric GPIO pin set up and use functionality
// It includes a Pin type def struct to represent various pins and allows the creation of pin's that can be passed into
// the various functions (set up, read, turn on, turn off)

//#include "stm32l476xx.h"
#include "PinSetup.h"
#include "LED.h"



// Turn on the peripheral clock for GPIOx where x = A..H = group
// and set Pxy to be mode where
		// x = A..H = group
		// y = 0..15 = pin_number
		// mode = INPUT, OUTPUT, ALT, or ANALOG
void init_pinX(pin_t pin){
	//TODO add pin_number validation(0 >= pin_number <= 15)
	enable_clock(pin.group);
	GPIO_TypeDef * GPIOx = get_GPIOx(pin.group);
	
	int mask;// = build_mask(pin.pin_number, CLEAR, 3,2);
	mask = mode_mask(pin, CLEAR);
	GPIOx->MODER &= 0x00;	//Clear the 2 bits associated with mode

	mask = mode_mask(pin, SET);
	GPIOx->MODER |= mask;	// Set the mode for the pin
}
	
// Read given pinX to see if it is set to High or Low
// Where x = 0..15 = pin_number
// return 1 if High
// return 0 if Low
int read_pinX(pin_t pin){
	int value;
	GPIO_TypeDef * GPIOx = get_GPIOx(pin.group);
	int mask = bit_mask(pin.pin_number, EXTRACT);
	if(pin.mode == INPUT){
		value = GPIOx->IDR & mask;
	}
	else if(pin.mode == OUTPUT){
		value = GPIOx->ODR & mask;
	}
	value >>= pin.pin_number;	// Shift value back to ensure a return value of 1 or 0
	return value;
	
}

// For testing
void monitor_pinX(pin_t pin){
	if( read_pinX(pin) ){
		Red_LED_On();
	}
	else{
		Red_LED_Off();
	}
}

// Set Given output pinX to High
// Where x = 0..15 = pin_number
void output_pinX_ON(pin_t pin){
	GPIO_TypeDef * GPIOx = get_GPIOx(pin.group);
	//int mask = build_mask(pin.pin_number, SET,1,1);
	int mask = bit_mask(pin.pin_number, SET);
	GPIOx->ODR |= mask;
	time_delay(SLEW_COMP);
}

// Set given output pin to Low
// Where x = 0..15 = pin_number
void output_pinX_OFF(pin_t pin){
	GPIO_TypeDef * GPIOx = get_GPIOx(pin.group);
	//int mask = build_mask(pin.pin_number,CLEAR,1,1);
	int mask = bit_mask(pin.pin_number, CLEAR);
	GPIOx->ODR &= mask;
	time_delay(SLEW_COMP);
}


// Returns the bit configruation needed to set the MODER regester
// mode is a pin_mode
int mode_bit_config(mode_t mode){
	switch(mode){
		case INPUT:
			return 0;	//00
		case OUTPUT:
			return 1;	//01
		case ALT:
			return 2;	//10
		case ANALOG:
			return 3;	//11
		default:
			return 0;
	}
}


// Creats a mask for a single bit
// Used for reading a spicific pin current value
// Or turning on or off a spicific ouput pin
int bit_mask(int pin_number, mask_t type){
	switch(type){
		case SET:
			return 1 << pin_number;
		case CLEAR:
			return ~(1 << pin_number);
		case EXTRACT:
			return 1 << pin_number;
		default:
			return 0;
	}
}
// Creats mask used for setting up MODER regester
int mode_mask(pin_t pin, mask_t type){
	int base_mask = mode_bit_config(pin.mode);	// The base mask is defigned by what the MODER regester need for the specified mode
	int shift_value = pin.pin_number *2;	//The MODER register assigns 2 bits for every pin. Therfor by multiplying the pin_number by 2 we get the apropreat shift value
	switch(type){
		case SET:
			return base_mask << shift_value;
		case EXTRACT:
			return base_mask << shift_value;
		case CLEAR:
			return ~(3 << shift_value); // Shift 3 (bits 11) over then Invert the mask to protect all other bits
		default:
			return 0;
	}
}

// Enable clock for GPIOx where x = A..H = group
void enable_clock(GPIO_group_t group){
	switch(group){
		case A:
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			break;
		case B:
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			break;
		case C:
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
			break;
		case D:
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIODEN;
			break;
		case E:
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
			break;			
		case F:
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOFEN;
			break;			
		case G:
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOGEN;
			break;			
		case H:
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOHEN;
			break;
	}
}

// Grabs the GPIOx where x = A..H = group
GPIO_TypeDef * get_GPIOx(GPIO_group_t group){
	switch(group){
		case A:
			return GPIOA;
		case B:
			return GPIOB;
		case C:
			return GPIOC;
		case D:
			return GPIOD;
		case E:
			return GPIOE;			
		case F:
			return GPIOF;			
		case G:
			return GPIOG;			
		case H:
			return GPIOH;
		default:
			return 0;
	}
}
//
// Counts for given duration to waist time
void time_delay(int duration){
	int i;
	for(i = 0; i < duration; i++);
}
