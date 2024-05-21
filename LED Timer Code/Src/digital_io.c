// digital_io.c

#include <digital_io.h>
#include <stdint.h>
#include "stm32f303xc.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

void (*timer_overflow)() = 0x00;  // Moved the declaration of the timer_overflow pointer

// Global variable
volatile uint8_t led_pattern_flag = 1;

// Moved functions
void timer_set(uint16_t delay_in_milliseconds){
    timer_info timer_x_info = delay_set(delay_in_milliseconds);
    timer_initialisation(&timer_x_info);
}

timer_info delay_set(uint16_t delay_in_milliseconds){
    timer_info timer_x_info;
    uint16_t psc_value = 0x1F3F;
    set_max_count(&timer_x_info, delay_in_milliseconds);
    set_psc_value(&timer_x_info, psc_value);
    return timer_x_info;
}

void set_max_count(timer_info *s, uint16_t max_count_value){
    s->max_count = max_count_value;
}

void set_psc_value(timer_info *s, uint16_t psc_int){
    s->psc_value = psc_int;
}

void LED_on(){
    uint8_t *LED_output_register = ((uint8_t*)&(GPIOE->ODR)) + 1;
    uint8_t LED_pattern = 0xFF;
    *LED_output_register = LED_pattern;
}

void chase_led() {
    uint8_t *LED_output_register = ((uint8_t*)&(GPIOE->ODR)) + 1;

    if (*LED_output_register == 0b11111111) {
        led_pattern_flag = 0; // Start turning LEDs off
    }

    if (led_pattern_flag == 0) {
        uint8_t LED_right_shift = *LED_output_register >> 1;
        *LED_output_register = LED_right_shift;
        // Check if all LEDs are off and if so, set the final pattern
        if (*LED_output_register == 0x00) {
        	timer_set(0x64);
            led_pattern_flag = 2; // Use a new state to indicate flashing pattern
            *LED_output_register = 0x55; // Set the initial pattern to 0x01010101 (0b01010101)
        }
    } else if (led_pattern_flag == 2) {
        // Toggle the pattern between 0x01010101 (0x55) and 0x10101010 (0xAA)
        if (*LED_output_register == 0x55) {
            *LED_output_register = 0xAA; // Change to 0x10101010 (0b10101010)
        } else {
            *LED_output_register = 0x55; // Change back to 0x01010101 (0b01010101)
        }
    }
}


void TIM2_IRQHandler(){
    if (timer_overflow != 0x00) {
        timer_overflow();
    }
    reset_UIF();
}

int enable_clocks(){

	RCC->AHBENR |= RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOCEN | RCC_AHBENR_GPIOEEN; //enable GPIOA, GPIOC, GPIOE

	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; //store a 1 into the TIM2 enable flag to enable the timer
}

void initialise_board() {

	// get a pointer to the second half word of the MODER register (for outputs pe8-15)
	uint16_t *led_output_registers = ((uint16_t *)&(GPIOE->MODER)) + 1;
	*led_output_registers = 0x5555;
}


void reset_timer() {

	TIM2->EGR |= TIM_EGR_UG;

}

void reset_UIF(){

	TIM2->SR &= ~TIM_SR_UIF;

}

void max_count_value(timer_info *s) {

	uint16_t max_count = s->max_count;
	TIM2->ARR = max_count;

}

void start_timer() {

	TIM2->CR1 |= TIM_CR1_CEN;

}

void set_prescaler(timer_info *s){

	uint16_t psc_value = s->psc_value;
	TIM2->PSC = psc_value;

}

void general_initialisation() {

	enable_clocks();
	initialise_board();

}

void timer_initialisation(timer_info *s){

	__disable_irq();

	max_count_value(s);
	start_timer();
	set_prescaler(s);
	reset_timer();
	reset_UIF();

	__enable_irq();

}

void enable_interrupt(){

	__disable_irq();

	__NVIC_SetPriority(TIM2_IRQn,2);
	__NVIC_EnableIRQ(TIM2_IRQn);

	TIM2->DIER |= TIM_DIER_UIE;

	__enable_irq();
}
