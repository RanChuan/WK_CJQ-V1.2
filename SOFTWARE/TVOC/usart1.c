#include "usart1.h"	
#include "delay.h"

u8 usart1_buf[256]={0};		//��Ļusart1���ݻ���
u8 buf_len=0;						//��Ļusart1���ݳ���
u8 flag_rxusart1=0;
u8 IsRecived;
u8 ReviceFlat=0;
u8 MaxLenth=0;
u8 Nowcount=0;


void usart1_init(u32 bound)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    /* config USART2 clock */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //���
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
   // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //��������
		GPIO_InitStructure.GPIO_Mode =GPIO_Mode_IPU;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    USART_InitStructure.USART_BaudRate = bound;   //������
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;   //���ݳ�8λ
    USART_InitStructure.USART_StopBits = USART_StopBits_1;   //1λֹͣλ
    USART_InitStructure.USART_Parity = USART_Parity_No ;   //��У��
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //ʧ��Ӳ����
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;   //�������պͷ���ģʽ
    USART_Init(USART1, &USART_InitStructure);  //��ʼ������1
    USART_Cmd(USART1, ENABLE);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		USART_ClearFlag(USART1,USART_FLAG_TC );
		
    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;  //�򿪴���1��ȫ���ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ�0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;  //��Ӧ���ȼ���3
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;  //ʧ�ܲ��ô����жϣ�ֱ���ô��ڷ���ģʽ
    NVIC_Init(&NVIC_InitStructure);
}


void usart1_sendData(unsigned char *dat,u8 len) 
{
	u8 i;
	//GPIO_SetBits(GPIOB,usart1_CONFIG);	//����Ϊ����ģʽ
	for(i=0;i<len;i++)
	{
		USART_SendData(USART1,*(dat+i));
		while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);  //USART_FLAG_TXE�������ݼĴ�����־λ  
	}
	while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		//USART_FLAG_TC������ɱ�־λ
	buf_len=0;
	//GPIO_ResetBits(GPIOB,usart1_CONFIG);	//����Ϊ����ģʽ
}


//��������
void usart1_receiveData(u8 rxdat[],u8 *data_len)
{
	u8 i,rxlen_t;
	rxlen_t=buf_len;
	*data_len=0;
	delay_ms(10);
	
	if((buf_len==rxlen_t)&&buf_len)		//�ж�10MS��������������
	{
			//GPIO_ResetBits(GPIOB,GPIO_Pin_5);		
		flag_rxusart1=1;
		for(i=0;i<rxlen_t;i++)
		{
			rxdat[i]=usart1_buf[i];
		}
		*data_len=buf_len;
		buf_len=0;
	}
}

void USART1_IRQHandler(void)                	
{
		u8 k;
		USART_ClearFlag(USART1,USART_FLAG_TC );
	
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)//���ָ����USART�жϷ������	
	{
	//	 USART_ClearITPendingBit(USART1, USART_IT_RXNE);
		k=USART_ReceiveData(USART1);  //�ѽ��ջ��������ݱ��浽������
		if(k==0xf0){	//��Ч���ݵ�ͷ  
			usart1_buf[0]=k;   //�ѽ��ջ��������ݷŵ�������
			Nowcount=1; 
			return;
		}
		
		if(k==0xfe)
		{
			Nowcount=2;
			usart1_buf[1]=k;
			IsRecived=1;
			ReviceFlat=0;
			return ;
		}
		
		if(IsRecived){   //�Ƿ������õ�����   0:����  1������  ����ǣ��ͷŵ����ջ�����
			Nowcount++;   //���ջ��������ݻ�ŵ����������������Ĵ�С
			usart1_buf[Nowcount-1]=k;
			
		if(Nowcount==4)    //�ж�buf��������ǲ�����Ч����
				{
					if(usart1_buf[3]==0x03)
					{
							MaxLenth=10;
					}
					else if(usart1_buf[2]==0xff)
					{
							MaxLenth=10;
					}
				}
			if(Nowcount==MaxLenth){   //������ݽ�����
				IsRecived=0;   
				ReviceFlat=1;   //���ݽ����Ƿ���ɱ�־λ   1�����ݽ�����
				Nowcount=0;
			}
		}

	}
}
