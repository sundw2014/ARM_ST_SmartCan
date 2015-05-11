#ifndef __DELAY_H
#define __DELAY_H

#include "All_Include.h"

void RCC_Config(void);
void delay_ms(u16 nms);
void delay_us(u32 nus);
void Delay(u32 count);
void Delay_Init(u8 SYSCLK);

#endif

