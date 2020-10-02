#include "timer.h"


/***********************************

Function : timer_init
Description : 定时器初始化 5ms定时中断
Input : 
Output :
Version : 1.0
Others : 
Author : LF

***********************************/
void BSP_timer_init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 7200 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ARRPreloadConfig(TIM2, ENABLE);

	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

	//TIM_Cmd(TIM2, ENABLE);
}

/***********************************

Function : TIM2_IRQHandler
Description : 定时用定时器中断处理
Input : 
Output :
Version : 1.0
Others : 
Author : LF

***********************************/
u16 s_counter=0;
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
	{
		s_counter++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
