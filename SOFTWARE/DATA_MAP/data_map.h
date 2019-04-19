
/***************************************************

		���ݵ��ڴ����
		��Ƭ����ǰ1KB�ڴ����������ڴ棬��������ͨ���ڴ��ȡָ�����޸ĺͶ�ȡ
		ÿ��cpu�ֳ���Ϊ��λ�洢


**************************************************/

#ifndef DATA_MAP_H__
#define DATA_MAP_H__


#define DATA_MAP ((data_map*)0x20000000)



typedef struct
	
{
	char devType[4];			//�豸����
	char softVersion[4];		//����汾
	char extType[4];			//��չ����
	u32 devAddr;
	u32 sysRunTime;
	float temperature;
	float humidity;
	float tvoc;
	float co2;
	float pm2_5;
}data_map;



void data_map_init(void);





#endif





