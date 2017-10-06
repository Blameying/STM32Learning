/*************************718����������**********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����

*************************************************************/

#include "stm32f10x.h"
#define  LED1_PORT 			GPIOC   
#define  LED1_PIN       GPIO_Pin_9
#define  LED1_PORT_RCC  RCC_APB2Periph_GPIOC

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	GPIO_InitTypeDef GPIO_InitStructure;//����ṹ�����
	
	RCC_APB2PeriphClockCmd(LED1_PORT_RCC,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=LED1_PIN;  //ѡ����Ҫ���õ�IO��
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;	 //�����������ģʽ
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;	  //���ô�������
	GPIO_Init(LED1_PORT,&GPIO_InitStructure); 	   //��ʼ��GPIO
	
	GPIO_SetBits(LED1_PORT,LED1_PIN);   //��LED�˿����ߣ�Ϩ������LED
	while(1);
}
