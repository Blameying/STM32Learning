/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ     
******************************************************************/
/*************************����˵��******************************
	ͨ��forѭ��Ӳ��ʱʵ����˸LED��
	��ϸ��led&beep.h
****************************************************************/

#include "stm32f10x.h"
#include "led&beep.h"


void DELAY()							//����forѭ��Ӳ��ʱ
{
	int i=0,j=0;
	for(i=0;i<10000;i++)
	{
		for(j=0;j<100;j++);
	}
}

void main()
{

	LED_Init();										//led��ʼ��

	while(1)
	{
		LEDPower(LED1,Power_ON);
		LEDPower(LED2,Power_ON);
		LEDPower(LED3,Power_ON);
		LEDPower(LED4,Power_ON);
		LEDPower(LED5,Power_ON);
		LEDPower(LED6,Power_ON);
		
		DELAY();
		LEDPower(LED1,Power_OFF);
		LEDPower(LED1,Power_OFF);
		LEDPower(LED2,Power_OFF);
		LEDPower(LED3,Power_OFF);
		LEDPower(LED4,Power_OFF);
		LEDPower(LED5,Power_OFF);
		LEDPower(LED6,Power_OFF);
		
		DELAY();
	}
	
}