/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ     
******************************************************************/
/*************************����˵��********************************
ͨ���ⲿ�ж�ʵ�ְ�������led����
*************************����˵��********************************/

#include "stm32f10x.h"
#include "led&beep.h"

void Key_Init()
{
	EXTI_InitTypeDef EXTI_InitStructure;													//�ⲿ�ж�������Ϣ�ṹ��
	NVIC_InitTypeDef NVIC_InitStructure;													//�ж����ȼ����ýṹ��
	GPIO_InitTypeDef GPIO_InitStructure;													//gpio���ƽṹ��
	//ʹ���õ���GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);					//GPIOB
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;                    //�ܽ�12
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;									//GPIO����Ϊ��������
  //����������Ϣ�ṹ�壬��ʼ���ܽ�
  GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);   						//���ȼ�����2:2
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);          //ʹ�ܹܽŸ���ʱ��
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource12);  //���жϺ�GPIO����
	
	//�ж��ߺ��жϳ�ʼ������
	EXTI_InitStructure.EXTI_Line = EXTI_Line12;										//��Ϊ������GPIO15��ʹ��15���ж���
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;						//����ģʽΪ�ж�
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;				//�½��ش����ж�
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;											//ʹ���ж�����
	EXTI_Init(&EXTI_InitStructure);                               //�����ж���Ϣ����ʼ��
	
	//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;					//ʹ�ܰ����ⲿ�ж�ͨ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2;				//��ռ���ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;						//�����ȼ�Ϊ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ������
	NVIC_Init(&NVIC_InitStructure);																//����������Ϣ����ʼ��
}

int main()
{
	LED_Init();																										//��ʼ��led��
	Key_Init();																										//��ʼ������
	
	while(1)
  {
      LEDPower(LED1,Power_ON);//һֱ��led��,���ж���ر�
  }

}

void delay()					//��ʱ
{
	int i,j;
	for(i=0;i<1000;i++)
	for(j=0;j<1000;j++);
	
	
}

void EXTI15_10_IRQHandler ()			//�ⲿ�ж�
{
	if(EXTI_GetITStatus(EXTI_Line12) != RESET)	//�ж��ǲ���12�������ж�
	{
		
		LEDPower(LED1,Power_OFF);									//�ص�
		delay();
		EXTI_ClearITPendingBit(EXTI_Line12);			//����жϱ�־λ
	}
}
