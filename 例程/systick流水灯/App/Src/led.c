#include "led.h"

/**********************718����ʵ���ҿ���������*********************
*  ������:LED_Init
*  ����:��            
*  ����: led��ʼ��
*	 ʹ��ʾ��:LED_Init;
*******************************************************************/
void LED_Init(void)					//led��ʼ��									
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��PC,PD��ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 //LED1-->PC.9������
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOC, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC.0
 GPIO_SetBits(GPIOC,GPIO_Pin_9);						 //PC.9 �����

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	    		 //LED2-->PC.8 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_8); 						 //PC.8 ����� 
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	    		 //LED3-->PC.7 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_7); 						 //PC.2 ����� 

		
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	    		 //LED4-->PC.6 �˿�����, �������
 GPIO_Init(GPIOC, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOC,GPIO_Pin_6); 						 //PC.6 ����� 
 
 	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;	    		 //LED5-->PD.15 �˿�����, �������
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOD,GPIO_Pin_15); 						 //PCD.15 ����� 
 
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;	    		 //LED6-->PD.14 �˿�����, �������
 GPIO_Init(GPIOD, &GPIO_InitStructure);	  				 //������� ��IO���ٶ�Ϊ50MHz
 GPIO_SetBits(GPIOD,GPIO_Pin_14); 						 //PCD.14 ����� 
}
 