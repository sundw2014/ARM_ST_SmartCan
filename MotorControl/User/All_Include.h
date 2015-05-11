#ifndef _ALL_INCLUDE_H

#define _ALL_INCLUDE_H


/*声明头文件区域*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_usart.h"
#include "stm32f10x_dma.h"
#include "stm32f10x_it.h"

#include "timer.h"
#include "usart1.h"
#include "delay.h"
#include <stdarg.h>
#include <stdio.h>


/*引用声明全局变量区域*/
u16 fac_ms;
u8 fac_us;

u32 Motor1=2000;
u32 Motor2=2000;
u32 Motor3=2000;



#endif