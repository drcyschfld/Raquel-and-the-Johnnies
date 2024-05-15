///*
// * pause_ptu.h
// *
// *  Created on: May 9, 2024
// *      Author: nataliebrown
// */
//
#ifndef INC_PAUSE_PTU_H_
#define INC_PAUSE_PTU_H_

#include <stdint.h>
#include "stm32f303xc.h"

// Function prototypes
uint8_t get_ptu_state();

void EXTI0_IRQHandler(void);

void enable_interrupt() ;

void button_initialise(void (*fp)());

void pause_ptu();

void chase_led();

#endif /* INC_PAUSE_PTU_H_ */
