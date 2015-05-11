#ifndef __TIMER_H
#define __TIMER_H

extern u32 Motor1;
extern u32 Motor2;
extern u32 Motor3;

//void NVIC_Init(void);
void TIM1_Init(void);
void TIM2_Init(void);
void GPIO_Config(void);

//void TIM2_IRQHandler(void);

#endif
