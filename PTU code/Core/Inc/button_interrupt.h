/*
 * button_interrupt.h
 *
 *  Created on: May 15, 2024
 *      Author: nataliebrown
 */

#ifndef INC_BUTTON_INTERRUPT_H_
#define INC_BUTTON_INTERRUPT_H_

#include <stdint.h>
#include "stm32f303xc.h"

void enable_interrupt();

void EXTI0_IRQHandler(void);

void button_init(void(*fp)(void));


uint8_t get_ptu_state();


void pause_ptu();



#endif /* INC_BUTTON_INTERRUPT_H_ */
