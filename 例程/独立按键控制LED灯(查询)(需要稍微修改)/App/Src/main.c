/*************************718����������**********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����

*************************************************************/
#include "include.h"
/*********������عܽ�******/
#define KEY_GPIO_CLK   RCC_APB2Periph_GPIOD			
#define KEY_GPIO_PORT 	GPIOD
#define KEY1_GPIO_PIN	GPIO_Pin_14
#define KEY2_GPIO_PIN	GPIO_Pin_15


#define LED_GPIO_PORT GPIOC
#define LED_GPIO_CLK   RCC_APB2Periph_GPIOC	
#define LED1_GPIO_PIN GPIO_Pin_6
#define LED2_GPIO_PIN GPIO_Pin_7
#define LED3_GPIO_PIN GPIO_Pin_8
#define LED4_GPIO_PIN GPIO_Pin_9

void Delay_ms(u16 time);			//��ʱ
void Key_gpio_init(void);					//key��ʼ��
void Led_init(void);//LED��ʼ��
void Led_on(void);	//LED��
void Led_off(void);	//LED��

int main() {
  Key_gpio_init();			
  Led_init();
	
  while(1){
		
/************����1���� LED�� ����2���� LED��***********************/
/**************����1***************************/
	if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY1_GPIO_PIN) == 0){	//��ⰴ������
	  Delay_ms(10);											//��ʱ����
	  if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY1_GPIO_PIN) == 0){		//ȷʵ�м�����
		Led_on();
		while(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY1_GPIO_PIN) == 0);		
	  }	
	}
	
/************����2**********************************/
	if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY2_GPIO_PIN) == 0){	
	  Delay_ms(10);		//��ʱ����	
	  if(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY2_GPIO_PIN) == 0){	
		Led_off();
		while(GPIO_ReadInputDataBit(KEY_GPIO_PORT,KEY2_GPIO_PIN) == 0);		
	  }	
	}	
  };
  
}
/*
�������� Delay_ms(u16 time)
���ã� 		��ʱ
������    u16 time
���أ�		void
˵����		������ʱ ��׼ȷ ���е�i�Ȳ�������������� 
					���ع��ھ���
*/
void Delay_ms(u16 time) {        
  u16 i=0;      
  while(time--){       
	i=12000;        
	while(i--);      
  } 
}
/*
�������� void Key_gpio_init(void)
���ã� 		����GPIO��ʼ��
������    void
���أ�		void
˵����		����������ֲἰԭ��ͼ
*/
void Key_gpio_init(void){
  GPIO_InitTypeDef GPIO_InitStructure;	//GPIO��ʼ���ṹ��							
  RCC_APB2PeriphClockCmd(KEY_GPIO_CLK, ENABLE);		//��GPIOʱ��		
  GPIO_InitStructure.GPIO_Pin = KEY1_GPIO_PIN|KEY2_GPIO_PIN;//ѡ��GPIO����				
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 			//����Ϊ��������
  GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);				//����ṹ�� 	��ɳ�ʼ��
}
/*
�������� Led_init(void)��
���ã� 		LED GPIO��ʼ��
������    void
���أ�		void
˵����		����������ֲἰԭ��ͼ
*/
void Led_init(void){
	GPIO_InitTypeDef GPIO_InitStructure;			//GPIO��ʼ���ṹ��					
  RCC_APB2PeriphClockCmd(LED_GPIO_CLK, ENABLE);			//��GPIOʱ��	
  GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN|LED2_GPIO_PIN|LED3_GPIO_PIN|LED4_GPIO_PIN;			//ѡ��GPIO����	
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //����Ϊ�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//���ùܽ��������Ϊ50MHZ
  GPIO_Init(LED_GPIO_PORT, &GPIO_InitStructure);			//��ɳ�ʼ��
}
/*
�������� void Led_on(void)
���ã� 		LED ��
������    void
���أ�		void
˵����		�μ�ԭ��ͼ  �˿���1ʱ  ��LED
*/
void Led_on(void){
	GPIO_SetBits(LED_GPIO_PORT,LED1_GPIO_PIN|LED2_GPIO_PIN|LED3_GPIO_PIN|LED4_GPIO_PIN);	//�˿���1 ��LED
}
/*
�������� void Led_off(void)
���ã� 		LED ��
������    void
���أ�		void
˵����		�μ�ԭ��ͼ  �˿���0ʱ  ��LED
*/
void Led_off(void){
	GPIO_ResetBits(LED_GPIO_PORT,LED1_GPIO_PIN|LED2_GPIO_PIN|LED3_GPIO_PIN|LED4_GPIO_PIN);	//�˿���0 �ر�LED
}


