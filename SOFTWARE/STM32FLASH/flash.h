#ifndef _flash_H
#define _flash_H
#include "stm32f10x.h"

//stm32f103RCT6 flash
//#define SCREEN_START_ADDR (0x08000000+127*2048)	//������Ļ���ݵ�ַ
//#define ICO_START_ADDR (0x08000000+126*2048)		//������Ļͼ�걣���ַ
#define SCREEN_START_ADDR (0x08000000+63*1024)	//������Ļ���ݵ�ַ
#define ICO_START_ADDR (0x08000000+62*1024)		//������Ļͼ�걣���ַ
void flash_Write(u32 flashAddr,u16 buf[],u8 len);
void flash_Read(u32 flashAddr,u16 buf[],u8 len);
#endif
