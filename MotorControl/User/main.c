#include "stm32f10x.h"
#include "timer.h"
#include "usart1.h"
#include "delay.h"
#include <stdio.h>

void Delay(u32 nCount);

int main()
{
	u16 step=0;
	Delay_Init(72);
	GPIO_Config();
	//NVIC_Init();
	TIM1_Init();  
	TIM2_Init();    
  
	//USART1_Config();
	//DMA_Config();
	//TIM1->CR1 &= 0x0000;	
	//TIM2->CR1 &= 0x0000;
	//Delay(0xFFFF);
	//printf("现在实验开始:\n");
	
	while (1)
	{
		 TIM_Cmd(TIM1,ENABLE);
		 TIM_Cmd(TIM2,ENABLE);
		 while(1){
			 TIM_SetCompare1(TIM1,4000);
			 TIM_SetCompare2(TIM1,0);
			 TIM_SetCompare3(TIM1,0);
			 TIM_SetCompare4(TIM1,3000);	
			 TIM_SetCompare1(TIM2,0);
			 TIM_SetCompare2(TIM2,1000);			 
		 }
	}
}



void Delay(u32 nCount)
{
   for(; nCount != 0; nCount--);
}
