#include  "include.h"


/*---------------------------*/
/*--------�˺�������---------*/
/*���--------PB5
  ����--------PB1
  �̵�--------PB0*/
void LED_GPIO_Config(void)
	{
GPIO_InitTypeDef GPIO_InitStructure;//�½�GPIO��ʼ���ṹ��

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//����GPIOBͨ��ʱ��

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//�ܽ�����

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ�������

GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���Ƶ��50M


		 GPIO_Init(GPIOB, &GPIO_InitStructure);    //��ʼ��GPIOB
		///
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;//�ܽ�����

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ�������

GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���Ƶ��50M
GPIO_Init(GPIOB, &GPIO_InitStructure);    //��ʼ��GPIOB
		///
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//�ܽ�����

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//���ģʽ�������

GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//���Ƶ��50M
GPIO_Init(GPIOB, &GPIO_InitStructure);    //��ʼ��GPIOB
////
		GPIO_SetBits(GPIOB,GPIO_Pin_5);//�رպ�ɫ��
		GPIO_SetBits(GPIOB,GPIO_Pin_0);//�ر���ɫ��
		GPIO_SetBits(GPIOB,GPIO_Pin_1);//�ر���ɫ��

}
	/*typedef enum colour {
		chi,
		cheng,
		huang,
		lv,
		lan,
		dian,
		zi,
}colour;
	
void  colourselect(colour C)
{
	
}*/
void Colour_Red()
	{
			GPIO_ResetBits(GPIOB,GPIO_Pin_5);
		GPIO_SetBits(GPIOB,GPIO_Pin_0);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
	}
void Colour_Green()
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		GPIO_ResetBits(GPIOB,GPIO_Pin_0);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);
}
void Colour_Blue()
{
		GPIO_SetBits(GPIOB,GPIO_Pin_5);
		 GPIO_SetBits(GPIOB,GPIO_Pin_0);
		 GPIO_ResetBits(GPIOB,GPIO_Pin_1); 
}
void Delay_ms(int a)
{
	int i,k;
		for(i=a;i>0;i--)
		for(k=72000;k>0;k--)
		{
			__nop;
		};
}