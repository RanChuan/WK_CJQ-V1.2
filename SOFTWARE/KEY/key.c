#include "key.h"




u8 AllocationFlag=0;



void Key_Init (void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;//KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15

	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);//KEY1
	EXTI_InitStructure.EXTI_Line=EXTI_Line15;	
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
	NVIC_Init(&NVIC_InitStructure); 
	
}
     

void EXTI15_10_IRQHandler(void)
{
		delay_ms(10);//����

	if(EXTI_GetITStatus(EXTI_Line15)!=RESET)//KEY1
	{

		if(KEY==0)
		{
//			GPIO_ResetBits(GPIOB,GPIO_Pin_2);						 //PB.2 �����
//			LED=!LED;
			AllocationFlag=!AllocationFlag;
		}
		EXTI_ClearFlag(EXTI_Line15);
		
	}
	
}
