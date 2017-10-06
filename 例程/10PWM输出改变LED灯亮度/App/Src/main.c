/*************************718����������**********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����

*************************************************************/
/*************************����˵��******************************
ͨ����ʱ�����PWM�����ƵƵ����ȱ仯,Ҳ�����������Ƶ��ת��
ʲô��PWM��:
http://www.eepw.com.cn/article/272990.htm
****************************************************************/

/*************************˵��******************************
��ϸ������鿴TIM.h��TIM.c�ļ�
************************************************************/
#include "stm32f10x.h"
#include "TIM.h"

void LED_GPIO_Config(void)
{		
		/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*����LED��ص�GPIO����ʱ��*/
		RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;	

		/*��������ģʽΪͨ���������*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*������������Ϊ50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIO*/
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
		
		/*ѡ��Ҫ���Ƶ�GPIO����*/
		GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

		/*���ÿ⺯������ʼ��GPIOF*/
		GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);

		/* �ر�����led��	LED����*/  
	GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
	GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);
	GPIO_ResetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
}
void delayms(int a)
{
int i,j;
	for(i=a;i>=0;i--)
	for(j=12000;j>=0;j--)
	{
		;;
	}
}
int main(void)
{
	/* led �˿����� */ 
	LED_GPIO_Config();
	
	/* ��ʱ����ʼ�� */
	GENERAL_TIM_Init();
	GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);//��һ�������Ա�
  while(1)
  {      
		
		int a=0;
			TIM_SetCompare3(TIM8,0);	//ռ�ձ�Ϊ0  ��ֹ�������졣��
		for(a=0;a<=10;a++)//�ı�PWMֵ���ƵƵ�����
		{
		TIM_SetCompare4(TIM8,a);	
			delayms(10);
			
		}
		for(;a>=0;a--)
		{
		TIM_SetCompare4(TIM8,a);	
			delayms(10);
		}
	//	GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);//R
		//GPIO_ResetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);//G
	//	GPIO_ResetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);//B
		/*****************���ϸı�PWM����ռ�ձ�****************/
		
  }
}
