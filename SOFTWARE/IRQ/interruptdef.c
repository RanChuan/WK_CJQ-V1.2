#include "interruptdef.h"
#include "delay.h"
#include "collect.h"
#include "sht21.h"
//#include "zph_01.h"
u16 time3_count=0;		//time3��ʱ���жϽ������
u8 time3_flag=0;
u8 controlId=0;


////time2��ʱ��
//void time2_init(u8 config,u16 ms)			//config:ENABLE ʹ��   DISABLE ʧ��
//{
//	NVIC_InitTypeDef NVIC_InitStructure;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//	
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,config);
//	
                                                                                                                                                       
//	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
//	TIM_TimeBaseStructure.TIM_Period = ms*2;   //��ʱ1s   count��0�ӵ�2000Ϊ1s   72000000/36000
//	TIM_TimeBaseStructure.TIM_Prescaler = 36000-1;		
//	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
//	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	                                       
//	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
//	TIM_Cmd(TIM2,config);
//	TIM_ITConfig(TIM2,TIM_IT_Update,config);
//		 
//	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; 	//��time2��ȫ���ж�
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�Ϊ0
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;		  //��Ӧ���ȼ�Ϊ3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = config; 		  //ʹ��
//	NVIC_Init(&NVIC_InitStructure); 	
//	
//}

//time3��ʱ��
void time3_init(u8 config,u16 ms)			//config:ENABLE ʹ��   DISABLE ʧ��
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,config);
	

	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	TIM_TimeBaseStructure.TIM_Period = ms*2;   //��ʱ1s   count��0�ӵ�2000Ϊ1s   72000000/36000
	TIM_TimeBaseStructure.TIM_Prescaler = 36000-1;		
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, & TIM_TimeBaseStructure);
	TIM_Cmd(TIM3,config);
	TIM_ITConfig(TIM3,TIM_IT_Update,config);
	
 
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn; 	//��time3��ȫ���ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; //��ռ���ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		  //��Ӧ���ȼ�Ϊ3
	NVIC_InitStructure.NVIC_IRQChannelCmd = config; 		  //ʹ��
	NVIC_Init(&NVIC_InitStructure); 	
	
}



#include "data_map.h"



//time3�ж�
void TIM3_IRQHandler(void)
{
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
	DATA_MAP->sysRunTime++;
 	time3_count++;
	time3_flag++;
	
}


void SYSTIME_STOP (void)
{
	
	TIM_Cmd(TIM3,DISABLE); 	
	
}


void SYSTIME_START (void)
{
	TIM_Cmd(TIM3,ENABLE); 	
}





