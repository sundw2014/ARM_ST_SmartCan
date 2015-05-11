#include "encoder.h"

#define LED_ON GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define LED_OFF GPIO_SetBits(GPIOB,GPIO_Pin_0)

s32 steps = 0; //4*600steps/round
s32 prev_steps = 0; //previous record on steps, to calculate wire's velocity
float cur_velocity;//unit:mm/sec
//s32 length = 0;

extern s32 stepper_pulse_count; //everytime when there is a pulse on encoder, stepper_pulse_count get reset.

//u32 goalICWidth;
//s8 dir = 1;
//s32 temp = 0;
//u8  timOverflowCNT = 0;
//u32 timPrevIC1Value = 0;
//u32 timCurIC1Value = 0;
//u32	timIC1Width = 0;

const float encoder_constant = 3.14159*6.5*2/(4*encoderlines);	//PI*2*encoder wheel radius/(4*encoder resolution)




void Encoder_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_BaseInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE); //PB0 LED for indication of encoder's rotation
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //push-pull
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	LED_OFF;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_PartialRemap2_TIM2, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //input pull up
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	
	TIM_DeInit(TIM2);     
	
  TIM_BaseInitStructure.TIM_Prescaler = (u16) (72000000 / 10000) - 1; //定时器周期：10us       
  TIM_BaseInitStructure.TIM_ClockDivision = 0;     
  TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_BaseInitStructure.TIM_Period = 20; //get into update interrupt at 500Hz frequency
  TIM_TimeBaseInit(TIM2, &TIM_BaseInitStructure); 
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_3; 		   
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; 
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	TIM_ICInitStructure.TIM_ICFilter = 0x0;     
	TIM_ICInit(TIM2, &TIM_ICInitStructure); 

	TIM_ICInitStructure.TIM_Channel = TIM_Channel_4; 		   
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising; 
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI; 
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1; 
	TIM_ICInitStructure.TIM_ICFilter = 0x0;     
	TIM_ICInit(TIM2, &TIM_ICInitStructure); 
	
	TIM_Cmd(TIM2, ENABLE);											 //使能定时器
	
	TIM_ClearFlag(TIM2, TIM_FLAG_CC3);
	TIM_ClearFlag(TIM2, TIM_FLAG_CC4);
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	
	TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQChannel;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;				 //使能中断
	NVIC_Init(&NVIC_InitStructure);
}


void TIM2_IRQHandler(void) //encoder timer
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		TIM_ITConfig(TIM2, TIM_IT_Update, DISABLE);
		
		cur_velocity=(float)(steps-prev_steps)*encoder_constant*500; //unit:mm/sec, out direction:velocity>0, in direction:velocity<0
		prev_steps=steps;
		if((cur_velocity>20)||(cur_velocity<-20))//encoder seems to be working properly, so reset the stepper pulse count to not activate the encoder failsafe function
		{
			stepper_pulse_count=0;
		}
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	}
	
	if(TIM_GetITStatus(TIM2, TIM_IT_CC3) == SET)	  
	{
		//----------------------------------------------------------
		LED_ON;
		//------------------------------------------------------------
		TIM_ITConfig(TIM2, TIM_IT_CC3, DISABLE);
		if(!(TIM2->CCER & 0x0200)) //CC3发生的是一个上升沿触发
		{
			//timOverflowCNT = 0;
			
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
			{
				steps--;	
			}
			else
			{
				steps++; 	
			}
			
			TIM2->CCER |= 0x0200;			//CC3改成下降沿触发
		}
		else											//CC3发生的是一个下降沿触发
		{
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11))
			{
				steps++;
			}
			else
			{
				steps--;
			}
					
			TIM2->CCER &= 0xfdff;			//CC3改成上升沿触发
		}
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC3);
		TIM_ITConfig(TIM2, TIM_IT_CC3, ENABLE);
	}
	
	else if(TIM_GetITStatus(TIM2, TIM_IT_CC4) == SET)	  
	{
		//----------------------------------------------------------
		LED_ON;
		//------------------------------------------------------------
		TIM_ITConfig(TIM2, TIM_IT_CC4, DISABLE);
		if(!(TIM2->CCER & 0x2000)) //CC4发生的是一个上升沿触发
		{
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
			{
				steps++;
			}
			else
			{
				steps--;
			}	
			TIM2->CCER |= 0x2000;				//CC4改成下降沿触发
		}
		else												//CC4发生的是一个下降沿触发
		{
			if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10))
			{
				steps--;
			}
			else
			{
				steps++;
			}

			TIM2->CCER &= 0xdfff;				//CC4改成上升沿触发

			
		}
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC4);
		TIM_ITConfig(TIM2, TIM_IT_CC4, ENABLE);
	}
	
	//----------------------------------------------------------
	LED_OFF;
	//------------------------------------------------------------

}

