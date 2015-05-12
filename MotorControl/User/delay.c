/*************************************
              今明电子
凡在本店购买满30元，下次购买即可返还5角；
      满50元，下次购买即可返还1元；
     满100元，下次购买即可返还2元；
     满150元，下次购买即可返还4元；
      满200元，下次购买即可免邮
http://shop106001793.taobao.com/search.htm?spm=a1z10.5.w5002-3375901029.1.l1TXSl&search=y              
               V1.1
             2013.10.17
**************************************/
#include "delay.h"

#define BIT(x)	(1 << (x))


/****************************************************
函数功能：系统时钟初始化
输入参数：无
输出参数：无
备    注：无
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
函数功能：ms级延时
输入参数：nms : 毫秒
输出参数：无
备    注：调用此函数前，需要初始化Delay_Init()函数
*****************************************************/							    
void delay_ms(u16 nms)
{
   	SysTick->LOAD = (u32)fac_ms*nms-1;//加载时间值
	  SysTick->VAL = 1;//随便写个值，清除加载寄存器的值
	  SysTick->CTRL |= BIT(0);//SysTick使能
	  while(!(SysTick->CTRL&(1<<16)));//判断是否减到0
	  SysTick->CTRL &=~BIT(0);//关闭SysTick
}

/****************************************************
函数功能：延时初始化
输入参数：SYSCLK : 系统时钟(72)MHZ
输出参数：无
备    注：无
*****************************************************/
void Delay_Init(u8 SYSCLK)
{
   RCC_Config();
	 SysTick->CTRL &=~BIT(2);//选择外部时钟
	 SysTick->CTRL &=~BIT(1);//关闭定时器减到0后的中断请求
	 fac_us = SYSCLK/8;//计算好SysTick加载值
	 fac_ms = (u16)fac_us*1000;	 
}

/****************************************************
函数功能：us级延时
输入参数：nus : 微秒
输出参数：无
备    注：调用此函数前，需要初始化Delay_Init()函数
*****************************************************/		    								   
void delay_us(u32 nus)
{		
	  SysTick->LOAD = (u32)fac_us*nus-1;//加载时间值
	  SysTick->VAL = 1;//随便写个值，清除加载寄存器的值
	  SysTick->CTRL |= BIT(0);//SysTick使能
	  while(!(SysTick->CTRL&(1<<16)));//判断是否减到0
	  SysTick->CTRL &=~BIT(0);//关闭SysTick
}


