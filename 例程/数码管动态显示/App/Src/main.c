/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ     
******************************************************************/
/*************************����˵��********************************
����ܶ�̬��ʾ
*************************����˵��********************************/

#include "stm32f10x.h"
#include "module_74hc595.h"


void main()
{
	hc595_init();				//����ܳ�ʼ��
	
	while(1)
	{
		DisplayScan(0,data_table[1]);		//��ʾʱ��
		DisplayScan(1,data_table[2]);
		DisplayScan(2,data_table[3]);
		DisplayScan(3,data_table[4]);
		DisplayScan(4,data_table[5]);
		DisplayScan(5,data_table[6]);
		DisplayScan(6,data_table[7]);
		DisplayScan(7,data_table[8]);
	}

	
}
