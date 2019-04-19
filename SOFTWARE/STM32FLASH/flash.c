#include "flash.h"

//��FLASHд�������(2���ֽ�)
void flash_Write(u32 flashAddr,u16 buf[],u8 len)
{
	u8 i;
	FLASH_Unlock();
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	FLASH_ErasePage(flashAddr);
	for(i=0;i<len;i++)	
	{
			FLASH_ProgramHalfWord(flashAddr+i*2,buf[i]);
	}
	FLASH_ClearFlag(FLASH_FLAG_BSY|FLASH_FLAG_EOP|FLASH_FLAG_PGERR|FLASH_FLAG_WRPRTERR);
	FLASH_Lock();
}
//��FLASH���������(2���ֽ�)
void flash_Read(u32 flashAddr,u16 buf[],u8 len)
{
	u8 i;
	for(i=0;i<len;i++)
	{
		buf[i]=*((u32*)(flashAddr+i*2));
	}
}


