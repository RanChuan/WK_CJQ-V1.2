#include "kqm2801A.h"
#include "myiic.h"
#include "delay.h"
#include "data.h"
#include "sgp30.h"

u8 TvocValue[4]={0};   //���淵�ص��ĸ��ֽ�
u8 TVOCValue[4]={0};   //����TVOC����
u8 CO2Value[4]={0};		//������ֵ̼
//u8 a[4]={0};
float KQM2801_Value(char whatdo) //0x5F:TVOC
{
	float tvoc;
	u8 tmp1,tmp2;
	u16 ST;
	IIC_Init();
	delay_us(50);
	IIC_Start();  //������ʼ�ź�
	delay_us(50);
	IIC_Send_Byte(0x5F); //��������ַ   
	if(IIC_Wait_Ack()==0) //�ȴ�Ӧ���źŵ��� ����ֵ�� 1������Ӧ��ʧ�� 0�� ����Ӧ��ɹ�
	{
		delay_us(50);
	//IIC_Wait_Ack();
	TvocValue[0]= IIC_Read_Byte(1);    //��ȡ��λ����
	delay_us(100);
	TvocValue[1]= IIC_Read_Byte(1);   //��ȡ��λ����
	delay_us(100);
	TvocValue[2]=	IIC_Read_Byte(1);
	delay_us(100);
	TvocValue[3]= IIC_Read_Byte(1);
	delay_us(100);		
	IIC_Read_Byte(0);           
	delay_us(50);
	IIC_Stop();
	delay_us(50);
	if(TvocValue[1]==0xFF&&TvocValue[2]==0xFF)   //Ԥ��ʱ������ݸ�λ��λ����0xff
		return 0;
	
	ST = (TvocValue[1] << 8) | (TvocValue[2] << 0);
	
	if(whatdo==((char)0x5F))
	{
		tvoc = ST * 0.1;
		return (tvoc);
	} 
}
}
//SHT20 �����λ=========�ɲ���======================================
void SoftReset1(void) //������
{
	IIC_Init();
	IIC_Start();
	IIC_Send_Byte(0x80); //SHT20 ������ַ+write
	IIC_Send_Byte(0xfe);
	IIC_Stop();
} //���÷ֱ��ʣ� ���Բ��ã� Ĭ�Ͼ���
void Set_Resolution1(void)
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
/*********��ȡTVOC**********/

void Get_TVOC()
{
	f_to_u t={0};
	u16 ret=0;
	u16 tvoc=0;
	u16 co2=0;
	t.f=KQM2801_Value(0x5F);
	
	if(t.f==0)
	{
					//�ɰ�TVOC������û������|û�д�����
		ret=0;
		ret=sgp_measure_iaq_blocking_read(&tvoc,&co2);
		if (ret==0)
		{
			t.f=tvoc/1000.0;								//��Ϊ������2019.3.30
			if (t.f<0.1) t.f=0.1;
			TVOCValue[0]=t.u[0];
			TVOCValue[1]=t.u[1];
			TVOCValue[2]=t.u[2];
			TVOCValue[3]=t.u[3];
			DATA_MAP->tvoc=t.f;
			t.f=co2;
			CO2Value[0]=t.u[0];
			CO2Value[1]=t.u[1];
			CO2Value[2]=t.u[2];
			CO2Value[3]=t.u[3];
			DATA_MAP->co2=t.f;
		}
		else
		{
			TVOCValue[0]=0;
			TVOCValue[1]=0;
			TVOCValue[2]=0;
			TVOCValue[3]=0;
			CO2Value[0]=0;
			CO2Value[1]=0;
			CO2Value[2]=0;
			CO2Value[3]=0;
			DATA_MAP->tvoc=0;
			DATA_MAP->co2=0;
		}
	}
	else {															//��Ϊ������2019.3.30
		TVOCValue[0]=t.u[0];            
		TVOCValue[1]=t.u[1];  					
		TVOCValue[2]=t.u[2];            
		TVOCValue[3]=t.u[3];  					
		DATA_MAP->tvoc=t.f;
		CO2Value[0]=0;            
		CO2Value[1]=0;  					
		CO2Value[2]=0;            
		CO2Value[3]=0;  
		DATA_MAP->co2=0;
	}


}

