#ifndef _KQM2801A_H
#define _KQM2801A_H

#include "stm32f10x.h"

extern u8 TvocValue[4];
extern u8 TVOCValue[4];   //����TVOC����

float KQM2801_Value(char whatdo);
void Get_TVOC(void );
void SoftReset1(void); //������
void Set_Resolution1(void);

#endif


