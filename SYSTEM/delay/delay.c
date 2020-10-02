#include "delay.h"

static u8 fac_us = 0; 
static u16 fac_ms = 0; 

void delay_init()
{
#if SYSTEM_SUPPORT_OS //�����Ҫ֧��OS.
	u32 reload;
#endif
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK_Div8); //ѡ���ⲿʱ��  HCLK/8
	fac_us = SystemCoreClock / 8000000;					  //Ϊϵͳʱ�ӵ�1/8
#if SYSTEM_SUPPORT_OS									  //�����Ҫ֧��OS.
	reload = SystemCoreClock / 8000000;					  //ÿ���ӵļ������� ��λΪK
	reload *= 1000000 / delay_ostickspersec;			  //����delay_ostickspersec�趨���ʱ��
														  //reloadΪ24λ�Ĵ���,���ֵ:16777216,��72M��,Լ��1.86s����
	fac_ms = 1000 / delay_ostickspersec;				  //����OS������ʱ�����ٵ�λ

	SysTick->CTRL |= SysTick_CTRL_TICKINT_Msk; //����SYSTICK�ж�
	SysTick->LOAD = reload;					   //ÿ1/delay_ostickspersec���ж�һ��
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;  //����SYSTICK

#else
	fac_ms = (u16)fac_us * 1000; //��OS��,����ÿ��ms��Ҫ��systickʱ����
#endif
}

void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD = nus * fac_us;			  //ʱ�����
	SysTick->VAL = 0x00;					  //��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //��ʼ����
	do
	{
		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;		//�رռ�����
	SysTick->VAL = 0X00;							//��ռ�����
}

void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD = (u32)nms * fac_ms;		  //ʱ�����(SysTick->LOADΪ24bit)
	SysTick->VAL = 0x00;					  //��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk; //��ʼ����
	do
	{

		temp = SysTick->CTRL;
	} while ((temp & 0x01) && !(temp & (1 << 16))); //�ȴ�ʱ�䵽��
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;		//�رռ�����
	SysTick->VAL = 0X00;							//��ռ�����
}

