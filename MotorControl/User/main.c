#include "All_Include.h"

void Delay(u32 nCount);
int main()
{
	Delay_Init(72);
	GPIO_Config();
	TIM1_Init();
	TIM2_Init();
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
