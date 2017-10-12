/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ     
******************************************************************/
/*************************����˵��********************************
ͨ��stm32��RTC(real time clock)ģ��ʵ�ּ�ʱ���ܲ���ʾ���������
*************************����˵��********************************/

#include "stm32f10x.h"
#include "module_74hc595.h"
#include "rtc.h"
#include "systick.h"

RTCDate calendar;  //RTCDate�ṹ��,���ڱ���ʱ������

 /**********************718����ʵ���ҿ���������*********************
*  ������:RTC_IRQHandler
*  ����:   ��       
*  ����:RTCʱ���жϣ�ÿ�봥��һ��  
*  ʹ��ʾ��:
*******************************************************************/																
															 
void RTC_IRQHandler(void)
{		 
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)//�����ж�
	{							
		calendar=RTC_Get();//����ʱ��   
 	}			  								 
	RTC_ClearITPendingBit(RTC_IT_SEC|RTC_IT_OW);		//�������ж�
	RTC_WaitForLastTask();	  	    						 	   	 
}

 /**********************718����ʵ���ҿ���������*********************
*  ������:main
*  ����:   ��       
*  ����:������  
*  ʹ��ʾ��:
*******************************************************************/		

int main()
{
	
	
	
	RTCInit();					//ʱ�ӳ�ʼ��
	hc595_init();				//����ܳ�ʼ��
	
	while(1)
	{
		DisplayScan(0,data_table[calendar.hour/10]);		//��ʾʱ��
		DisplayScan(1,data_table[calendar.hour%10]);
		DisplayScan(3,data_table[calendar.min/10]);
		DisplayScan(4,data_table[calendar.min%10]);
		DisplayScan(6,data_table[calendar.sec/10]);
		DisplayScan(7,data_table[calendar.sec%10]);
		
	}
}
