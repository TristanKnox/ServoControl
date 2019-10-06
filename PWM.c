# include "PWM.h"

// HELPER FUNCTIONS //
void set_PWM_mode(channel_t channel, PWM_mode_t mode);
void set_PWM_preload_enable(channel_t channel);
void set_PWM_output_enable(channel_t channel);

//////////////////////

// Set the puls width for given channel based on the count
void set_puls_width(channel_t channel, int count){
	switch(channel){
		case CHAN1:
			TIM2->CCR1 = count;
			break;
		case CHAN2:
			TIM2->CCR2 = count;
			break;
		case CHAN3:
			TIM2->CCR3 = count;
			break;
		case CHAN4:
			TIM2->CCR4 = count;
			break;
	}
}

// initiat and start the clock
void init_clock(void){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;
	// Counting direction: 0 = Up-counting, 1 = Down-counting
	TIM2->CR1 &= ~TIM_CR1_DIR; //up_counting
	// Start the clock
	TIM2->CR1 |= TIM_CR1_CEN;
}

// Initiat the PWM with initial output channel
void init_PWM(int pre_scalar, int count, channel_t channel, PWM_mode_t mode, pin_t pin){
	init_clock();
	set_PSC_and_count(pre_scalar,count);
	enable_channel(channel,mode);
	set_output_pin(pin);
}

// Enable given channel 
// channel = CHAN1, CHAN2, CHAN3, OR CHAN4
// mode = MODE_1 or MODE_2 where 
// MODE_1 In upcounting, channel 1 is active as long as TIMx_CNT<TIMx_CCR1 else inactive. In downcounting, channel 1 is inactive (OC1REF=‘0) as long as TIMx_CNT>TIMx_CCR1 else active
// MODE_2 In upcounting, channel 1 is inactive as long as TIMx_CNT<TIMx_CCR1 else active. In downcounting, channel 1 is active as long as TIMx_CNT>TIMx_CCR1 else inactive.
void enable_channel(channel_t channel, PWM_mode_t mode){
	set_PWM_mode(channel, mode);
	set_PWM_preload_enable(channel);
	set_PWM_output_enable(channel);
}

// Initiat given pin and set its alt function
void set_output_pin(pin_t pin){
	init_pinX(pin);
	set_ALT_function(pin);
}

// set up output channel and its pin
void add_output_channel(channel_t channel, PWM_mode_t mode, pin_t pin){
	enable_channel(channel,mode);
	set_output_pin(pin);
}

// Calebrate the given channel to the given mode
void set_PWM_mode(channel_t channel, PWM_mode_t mode){
	int mode_bits;
	if(mode == MODE_1)
		mode_bits = 6; // 0110;
	else if(mode == MODE_2)
		mode_bits = 7; // 0111
	switch(channel){
		case CHAN1:
			TIM2->CCMR1 &= ~TIM_CCMR1_OC1M; // Clear OC1M bits
			TIM2->CCMR1 |= (mode_bits << 1 * 4);
			break;
		case CHAN2:
			TIM2->CCMR1 &= ~TIM_CCMR1_OC2M;
			TIM2->CCMR1 |= (mode_bits << 3 * 4);
			break;
		case CHAN3:
			TIM2->CCMR2 &= ~TIM_CCMR2_OC3M;
			TIM2->CCMR2 |= (mode_bits << 1 *4);
			break;
		case CHAN4:
			TIM2->CCMR2 &= ~TIM_CCMR2_OC4M;
			TIM2->CCMR2 |= (mode_bits << 3 * 4);
			break;
	}
}

// Enable PWM preload for given channel
void set_PWM_preload_enable(channel_t channel){
	switch(channel){
		case CHAN1:
			TIM2->CCMR1 |= TIM_CCMR1_OC1PE;
			break;
		case CHAN2:
			TIM2->CCMR1 |= TIM_CCMR1_OC2PE;
			break;
		case CHAN3:
			TIM2->CCMR2 |= TIM_CCMR2_OC3PE;
			break;
		case CHAN4:
			TIM2->CCMR2 |= TIM_CCMR2_OC4PE;
			break;
	}
}

// Enable PWM ouput for given channel
void set_PWM_output_enable(channel_t channel){
	switch(channel){
		case CHAN1:
			TIM2->CCER |= TIM_CCER_CC1E;
			break;
		case CHAN2:
			TIM2->CCER |= TIM_CCER_CC2E;
			break;
		case CHAN3:
			TIM2->CCER |= TIM_CCER_CC3E;
			break;
		case CHAN4:
			TIM2->CCER |= TIM_CCER_CC4E;
			break;
	}
}

// Set the prescalar and the count 
// where count is the count of the clock before clock resets
void set_PSC_and_count(int pre_scalar, int count){
	// Set prescalar
	TIM2->PSC = pre_scalar -1;
	TIM2->ARR = count;
}
