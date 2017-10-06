/*************************718����������**********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����

*************************************************************/
/*************************����˵��******************************
��һ�仰д��flash(�൱�ڵ����ϵ�Ӳ��)��,�ٽ���仰��ȡ������ʾ
flash��д����:
	д��:
		����flash->ɾ��flash��ԭ�е��ļ�->��flash��д������->���¸�flash����
	��ȡ:
		����flash->��ȡflash�ϵ�����->���¸�flash����

1.flash������Ҫ��Ϊ�˷�ֹ���������д
2.flash��ȡ��д���ʱ��Ҫ2���ֽڻ���4���ֽڵĶ�ȡ,��������
3.��Ƭ����ĳ�������ݶ��Ǵ洢��flash���,��дflashһ��Ҫ����,
	�������׳������صĹ���
****************************************************************/
#include "stm32f10x_it.h"			//stm32�ײ��ͷ�ļ�
#include "stm32f10x_flash.h"	//flash������ص�ͷ�ļ�
#include "Spi-OLED.h"					//OLED��Ļ�������ͷ�ļ�


#define FLASH_ADDRESS ((u32)0x08006000)		//flashд��ĵ�ַ,�����������ַ����д����

unsigned char DataToWrite[]={"Welcome To 718! "}; //׼��д���һ�仰
unsigned char DataToRead[20];											//׼��������仰������

/*============================================
��������main()
���ã�������,��������
==========================================*/

int main()
{
	unsigned int counter=0;
	OLED_Init();													//��ʼ��OLED��Ļ
	OLED_Print(0,0,"Flash Test");					//��OLED��Ļ����(0,0)дһ�仰
  FLASH_Unlock();												//flash����
	FLASH_ClearFlag(FLASH_FLAG_BSY | FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPRTERR);//���flash��־λ(��һ��Ҳ���Բ�Ҫ)
	while(FLASH_ErasePage(FLASH_ADDRESS)!=FLASH_COMPLETE);			//�ȴ�flash���֮ǰ�������
	
	for(counter=0;counter<15;counter+=2)	//flashд��
	{
		uint16_t temp=(uint16_t)(DataToWrite[counter]<<8|DataToWrite[counter+1]);
		FLASH_ProgramHalfWord(counter+FLASH_ADDRESS,(uint16_t)(temp));
	}
  FLASH_Lock();													//flash����
	OLED_Print(0,2,"Flash Write OK");			//OLED��ʾд�����
/***************************д�����******************************/
	FLASH_Unlock();												//flash����
	for(counter=0;counter<15;counter+=2)	//��ȡflash
	{
		int16_t temp = *(int16_t*)(counter+FLASH_ADDRESS);
		int16_t temp2=temp>>8;
		DataToRead[counter]=(char)temp2;
		DataToRead[counter+1]=(char)temp;
	}
	FLASH_Lock();		
	OLED_Print(0,4,"Flash Read OK");			//��ʾ��ȡ�ɹ�
	OLED_Print(0,6,DataToRead);						//��Ļ�������ȡ��������
	/***************************��ȡ���******************************/
}
