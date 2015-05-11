#include "stm32f10x_lib.h"
#include "stm32f10x_it.h"

#define encoderlines 600 //600 lines incremental encoder

void Encoder_Configuration(void);
void TIM2_IRQHandler(void);
