// digital_io.h

#ifndef INITIALISE_H
#define INITIALISE_H

#include <stdint.h>
#include "stm32f303xc.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

typedef struct {
    uint16_t max_count;
    uint16_t psc_value;
} timer_info;

// Existing declarations
int enable_clocks();
void initialise_board();
void reset_timer();
void reset_UIF();
void max_count_value(timer_info *s);
void start_timer();
void set_prescaler(timer_info *s);
void general_initialisation();
void timer_initialisation(timer_info *s);
void enable_interrupt();

// New declarations
void timer_set(uint16_t delay_in_milliseconds);
timer_info delay_set(uint16_t delay_in_milliseconds);
void set_max_count(timer_info *s, uint16_t max_count_value);
void set_psc_value(timer_info *s, uint16_t psc_int);
void LED_on();
void chase_led();
void TIM2_IRQHandler();

#endif /* INITIALISE_H */
