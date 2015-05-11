#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include "stm32f10x_gpio.h"

u32 Motor1=2000;
u32 Motor2=2000;
u32 Motor3=2000;


/*******************************************************
	控制方案概述：
	1.速度控制：使用TIM1的CH1-4，TIM2的CH1-2共2个定时器实现PWM输出
	
*******************************************************/



/*void NVIC_init(void)
{
	NVIC_InitTypeDef    NVIC_InitStructure;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}*/
void GPIO_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;       //??GPIO(???PWM,?????)
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;            //??GPIO?????????
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;          //?????????50MHz
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void TIM1_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM1_TimeBaseStructure; 
	TIM_OCInitTypeDef  TIM1_OCInitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);   	   
  TIM_DeInit(TIM1);
  TIM1_TimeBaseStructure.TIM_Prescaler = 7;//8????
  TIM1_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//??????
  TIM1_TimeBaseStructure.TIM_Period = 4000;//???????4000
  TIM1_TimeBaseStructure.TIM_ClockDivision = 0x0;//??????1
	TIM1_TimeBaseStructure.TIM_RepetitionCounter = 0; 

  TIM_TimeBaseInit(TIM1,&TIM1_TimeBaseStructure);

  TIM_OCStructInit(&TIM1_OCInitStructure);         
  TIM1_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //?????4???1?PWM1??
  
	/*Motor 1*/
	TIM1_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;     
	TIM1_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;	
  TIM1_OCInitStructure.TIM_Pulse = Motor1;  
  TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	//???????
  TIM_OC1Init(TIM1,&TIM1_OCInitStructure);	 
  TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

  /*Motor 1R*/
  TIM1_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM1_OCInitStructure.TIM_Pulse = Motor1; 
	TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OC2Init(TIM1, &TIM1_OCInitStructure);
  TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable); 

  /*Motor 2*/
  TIM1_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM1_OCInitStructure.TIM_Pulse = Motor2; 
	TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OC3Init(TIM1, &TIM1_OCInitStructure);
  TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable); 

  /*Motor 2R*/
  TIM1_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM1_OCInitStructure.TIM_Pulse = Motor2;
  TIM1_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
  TIM_OC4Init(TIM1, &TIM1_OCInitStructure);
  TIM_OC4PreloadConfig(TIM1, TIM_OCPreload_Enable); 
	
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	
	TIM1->BDTR |= 1<<15;  
	
	TIM_Cmd(TIM1,ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE); 
}

void TIM2_Init(void)
{
	TIM_TimeBaseInitTypeDef  TIM2_TimeBaseStructure; 
	TIM_OCInitTypeDef  TIM2_OCInitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);   	   
  TIM_DeInit(TIM2);
  TIM2_TimeBaseStructure.TIM_Prescaler = 7;//8????
  TIM2_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//??????
  TIM2_TimeBaseStructure.TIM_Period = 4000;//???????4000
  TIM2_TimeBaseStructure.TIM_ClockDivision = 0x0;//??????1

  TIM_TimeBaseInit(TIM2,&TIM2_TimeBaseStructure);

  TIM_OCStructInit(& TIM2_OCInitStructure);         
  TIM2_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //?????4???1?PWM1??
  
	/*Motor 3*/
	TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;           
  TIM2_OCInitStructure.TIM_Pulse = Motor3;  
  TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	//???????
  TIM_OC1Init(TIM2,&TIM2_OCInitStructure);	 
  TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);

  /*Motor 3R*/
  TIM2_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM2_OCInitStructure.TIM_Pulse = Motor3; 
	TIM2_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;	
  TIM_OC2Init(TIM2, &TIM2_OCInitStructure);
  TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable); 
	
	TIM_ARRPreloadConfig(TIM2, ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);
}






