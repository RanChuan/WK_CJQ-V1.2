#include "collect.h"
#include "sht21.h"
#include "interruptdef.h"
#include "crc8_16.h" 
#include "flash.h"
#include "deal.h"
#include "usart1.h"
#include "kqm2801A.h"
#include "usart3.h"
#include "key.h"
#include "data_map.h"



u8 collectNumber=1;	//�ɼ���������
u8 centerNumber=1;	//������������
u8 controlNumber=1;	//������������
u8 collectData[COLLECTSIZE];
u16 collectId=2;  //�ɼ�����     ͨ�����ø�


void addressIdinit(void)
{
	u16 t;
	flash_Read(FLASH_SAVE_ADDR,&t,1);
	if((t&0XFFFF)!=0xFFFF)  //�ж��Ƿ����ù�   ���ù�  flash��û�����ݵ�ʱ����0xff
	{
		collectId=t;
	}
	else 
	{
		Nothing();
	}
	DATA_MAP->devAddr=collectId; 
}


void collectdeal(void)
{
	u8 err=0;
	if(time3_count>=5)//ÿ5��ɼ�һ������
	{
		Get_TempAmdHumi();         //��ʪ�Ȼ�ȡ
		Get_TVOC();
		get_data();
		time3_count=0;
		
		if ((TempAndHumi[0]==0&&TempAndHumi[1]==0&&TempAndHumi[2]==0&&TempAndHumi[3]==0)&&
			(TempAndHumi[4]==0)&&(TempAndHumi[5]==0)&&(TempAndHumi[6]==0)&&(TempAndHumi[7]==0))
		{
			err++;
		}
		if ((TVOCValue[0]==0&&TVOCValue[1]==0)&&(TVOCValue[2]==0&&TVOCValue[3]==0))
		{
			err++;
		}
		if (err==0)
		{
			LED=0;
		}

	}
}



void Nothing(void)
{
	dataBuffer[0]=2;
	collectId=dataBuffer[0];
}

















