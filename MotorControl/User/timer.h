#ifndef __TIMER_H
#define __TIMER_H

#include "All_Include.h"

//void NVIC_Init(void);

void TIM1_Init(void);
void TIM2_Init(void);
void GPIO_Config(void);

u32 Motor1;
u32 Motor2;
u32 Motor3;
//void TIM2_IRQHandler(void);

#endif
