/*************************************
              ��������
���ڱ��깺����30Ԫ���´ι��򼴿ɷ���5�ǣ�
      ��50Ԫ���´ι��򼴿ɷ���1Ԫ��
     ��100Ԫ���´ι��򼴿ɷ���2Ԫ��
     ��150Ԫ���´ι��򼴿ɷ���4Ԫ��
      ��200Ԫ���´ι��򼴿�����
http://shop106001793.taobao.com/search.htm?spm=a1z10.5.w5002-3375901029.1.l1TXSl&search=y              
               V1.1
             2013.10.17
**************************************/
#include "delay.h"

#define BIT(x)	(1 << (x))


/****************************************************
�������ܣ�ϵͳʱ�ӳ�ʼ��
�����������
�����������
��    ע����
*****************************************************/		
void RCC_Config(void){
	ErrorStatus HSEStartUpStatus;
	RCC_DeInit();
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus = RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus == SUCCESS){
		RCC_HCLKConfig(RCC_SYSCLK_Div1);
		RCC_PCLK2Config(RCC_HCLK_Div1);
    RCC_PCLK1Config(RCC_HCLK_Div2);
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		while(RCC_GetSYSCLKSource() != 0x08);
  }
}

/****************************************************
�������ܣ�ms����ʱ
���������nms : ����
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/							    
void delay_ms(u16 nms)
{
   	SysTick->LOAD = (u32)fac_ms*nms-1;//����ʱ��ֵ
	  SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	  SysTick->CTRL |= BIT(0);//SysTickʹ��
	  while(!(SysTick->CTRL&(1<<16)));//�ж��Ƿ����0
	  SysTick->CTRL &=~BIT(0);//�ر�SysTick
}

/****************************************************
�������ܣ���ʱ��ʼ��
���������SYSCLK : ϵͳʱ��(72)MHZ
�����������
��    ע����
*****************************************************/
void Delay_Init(u8 SYSCLK)
{
   RCC_Config();
	 SysTick->CTRL &=~BIT(2);//ѡ���ⲿʱ��
	 SysTick->CTRL &=~BIT(1);//�رն�ʱ������0����ж�����
	 fac_us = SYSCLK/8;//�����SysTick����ֵ
	 fac_ms = (u16)fac_us*1000;	 
}

/****************************************************
�������ܣ�us����ʱ
���������nus : ΢��
�����������
��    ע�����ô˺���ǰ����Ҫ��ʼ��Delay_Init()����
*****************************************************/		    								   
void delay_us(u32 nus)
{		
	  SysTick->LOAD = (u32)fac_us*nus-1;//����ʱ��ֵ
	  SysTick->VAL = 1;//���д��ֵ��������ؼĴ�����ֵ
	  SysTick->CTRL |= BIT(0);//SysTickʹ��
	  while(!(SysTick->CTRL&(1<<16)));//�ж��Ƿ����0
	  SysTick->CTRL &=~BIT(0);//�ر�SysTick
}


