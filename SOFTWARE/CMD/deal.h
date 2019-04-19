#ifndef __DEAL_H
#define __DEAL_H

#include "stdio.h"
#include "sys.h"



//ģʽ2�еĴ������Ͷ���

#define ERR_SUCCESS         0x0000			//�ɹ�
#define ERR_FAIL						0x0001			//δ֪����
#define ERR_DATAVALE				0x0002			//���ݴ���
#define ERR_DATALENGTH			0x0003			//���ݳ��ȴ���
#define ERR_WANTLENGTH			0x0004			//��Ҫ��ȡ�����ݳ��ȴ���
#define ERR_NULLCMD					0x0005			//��֧�ֵ��������ͣ�
#define ERR_NOCONNECT				0x0006			//û�����ӣ�һ�в�����Ҫ��ͨ�ſ�ʼ֮��
#define ERR_NOCJADDR				0x0007			//�ɼ����ĵ�ַ���Ǳ����󶨵Ĳɼ�����ַ
#define ERR_CANNOTCFG				0x0008			//�ڲ��ǿ�����״̬���յ�����������
#define ERR_NOTMYTYPE				0x0009			//��Ҫ���Ƶ��豸�뱾������
#define ERR_TIMEOUT					0x000a   //��ʱ




extern u16 dataBuffer[20];
#define FLASH_SAVE_ADDR  (0x08000000+62*1024) 				//����FLASH �����ַ(����Ϊż��)
//#define FLASH_SAVE_ALLOCTIONARR  (0x08000000+62*1024) 				//����FLASH �����ַ(����Ϊż��)

#define SIZE sizeof(dataBuffer/2)	 			  	//���鳤��

void cmd_0x01 (u8 *recv);
void cmd_0x04 (u8 *recv);
void cmd_0x06 (u8 *buff);
void cmd_0x07 (u8 *buff);
void cmd_0x09 (u8 *buff);
void deal(void);
void Return_NEW (u8 cmd,u16 err);


#endif
