#ifndef _COLLECT_H
#define _COLLECT_H
#include "stm32f10x.h"

#define COLLECTSIZE 128

extern u16 collectId; //�ɼ������

//typedef struct 
//{
//	u8 numId;
//	u8 id1;  //������
//	u8 id2;  //�ɼ������
//	u8 id3;  //������
//	u8 tempNumH;  //�¶�����λ
//	u8 tempNumL;  //�¶�С��λ
//	u8 humiNumH;   //ʪ������
//	u8 humiNumL;
//	u8 tvocH;     //tvoc����
//	u8 tvocL;
//	u8 pm2_5_bai;  //pm2.5��λ
//	u8 pm2_5_h;    //pm2.5ʮλ�͸�λ
//	u8 pm2_5_l;    //pm2.5С��
//	
//}CollectData;

void collectdeal(void);

void returnEnvironmentData(u8 address);

void addressIdinit(void);

void Nothing(void);
//��ȡTVOC
void get_tvoc(void);


#endif
