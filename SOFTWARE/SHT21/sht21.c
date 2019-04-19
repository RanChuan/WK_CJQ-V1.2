#include "sht21.h"
#include "myiic.h"
#include "delay.h"
#include "data.h"

u8 TempAndHumi[8]={0};
float SHT2X_MeasureNHM(char whatdo) //0xF3:�¶Ȳ����� 0xF5:ʪ�Ȳ����� ���Ƿ�����
{
	float Humidity,Temperature;
	u8 tmp1,tmp2;
	u16 ST;
	IIC_Init();
	delay_us(50);
	IIC_Start();
	IIC_Send_Byte(0x80); //��������ַ   
	if(IIC_Wait_Ack()==0)
	{
		IIC_Send_Byte(whatdo);
		if(IIC_Wait_Ack()==0)
		{
			do
			{
			delay_us(50);
			IIC_Start();
			}while(IIC_Send_Byte(0x81),IIC_Wait_Ack()==1); //�м��Ƕ��������    �����������һ������Ľ��
		}
	}//�˴�����ȴ�Ӧ�� ��������ʱ���棬 �����޷������� ���� 128 �������ݴ���
	delay_us(50);
	tmp1= IIC_Read_Byte(0);
	delay_us(50);
	tmp2= IIC_Read_Byte(0);
	IIC_Read_Byte(0);
	IIC_Stop();
	delay_us(50);
	if(tmp1==0xFF&&tmp2==0xFF)
		return 0;
	ST = (tmp1 << 8) | (tmp2 << 0);
	ST &= ~0x0003;	
	if(whatdo==((char)0xF3))
	{
		Temperature = ((float)ST * 0.00268127) - 46.85;
		return (Temperature);
	} 
	else //����Ĭ����һ�־��Ƿ�����ʪ�Ȳ����� ����Ҫ��������ģʽ���Լ����
	{
		Humidity = ((float)ST * 0.00190735) - 6;
		return (Humidity);
	}
}
//SHT20 �����λ=========�ɲ���======================================
void SoftReset(void) //������
{
	IIC_Init();
	IIC_Start();
	IIC_Send_Byte(0x80); //SHT20 ������ַ+write
	IIC_Send_Byte(0xfe);
	IIC_Stop();
} //���÷ֱ��ʣ� ���Բ��ã� Ĭ�Ͼ���
void Set_Resolution(void)
{
	IIC_Start();
	IIC_Send_Byte(0x80); //����д����
	if(IIC_Wait_Ack()==0)
	{
		IIC_Send_Byte(0xE6); //д�û��Ĵ���
		if(IIC_Wait_Ack()==0)
		{
			if(IIC_Send_Byte(0x83),IIC_Wait_Ack()==0)
				; //11bit RH%; 11bit temp
		}
	}
}




#include "data_map.h"
/*********��ȡ��ʪ��
  * �������ֽڷ��¶�
  * �������ֽڷ�ʪ��
  */
void Get_TempAmdHumi()
{
	f_to_u t={0};
	
	t.f=SHT2X_MeasureNHM(0xF3);		//�ϴ�������2019.3.30
	TempAndHumi[0]=t.u[0];
	TempAndHumi[1]=t.u[1];
	TempAndHumi[2]=t.u[2];
	TempAndHumi[3]=t.u[3];
	DATA_MAP->temperature=t.f;
	
	t.f=SHT2X_MeasureNHM(0xF5);
	TempAndHumi[4]=t.u[0];
	TempAndHumi[5]=t.u[1];
	TempAndHumi[6]=t.u[2];
	TempAndHumi[7]=t.u[3];
	DATA_MAP->humidity=t.f;
}

