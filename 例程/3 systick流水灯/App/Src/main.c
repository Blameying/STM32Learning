/*************************718����������**********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����

*************************************************************/

/*************************����˵��******************************
ͨ��systick��ʱ����ʱʵ����ˮ��Ч��
****************************************************************/

/*************************˵��******************************
��ϸ������鿴systick.c��systick.h�ļ�
************************************************************/
#include "stm32f10x.h"
#include "led&beep.h"
#include "systick.h"

int main()
{
		LED_Init();		        //��ʼ��LED�˿�
	while(1)
	{											//ledΪ�������ĵ�·��IO��Ϊ�ߵ�ƽ��ʱ����
			GPIO_ResetBits(GPIOC,GPIO_Pin_9);  //LED1��Ӧ����GPIOC9���ͣ���  
			Delay_ms(100);
			GPIO_ResetBits(GPIOC,GPIO_Pin_8);  //LED2��Ӧ����GPIOC8���ͣ���  
			Delay_ms(100);
			GPIO_ResetBits(GPIOC,GPIO_Pin_7);  //LED3��Ӧ����GPIOC7���ͣ���  
			Delay_ms(100);
			GPIO_ResetBits(GPIOC,GPIO_Pin_6);  // ����
			Delay_ms(100);
			GPIO_ResetBits(GPIOD,GPIO_Pin_15); 
			Delay_ms(100);
			GPIO_ResetBits(GPIOD,GPIO_Pin_14);    
			Delay_ms(100);
		
			GPIO_SetBits(GPIOC,GPIO_Pin_9);   //LED1��Ӧ����GPIOC9���ߣ���
			Delay_ms(100);
			GPIO_SetBits(GPIOC,GPIO_Pin_8);   //LED2��Ӧ����GPIOC8���ߣ���
			Delay_ms(100);
			GPIO_SetBits(GPIOC,GPIO_Pin_7);   //LED3��Ӧ����GPIOC7���ߣ���
			Delay_ms(100);
			GPIO_SetBits(GPIOC,GPIO_Pin_6);  //����
			Delay_ms(100);
			GPIO_SetBits(GPIOD,GPIO_Pin_15); 
			Delay_ms(100);
			GPIO_SetBits(GPIOD,GPIO_Pin_14);   
			Delay_ms(100);
	
	
	}
}
