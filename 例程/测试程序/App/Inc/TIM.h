#ifndef __TIM_H__
#define __TIM_H__
#define            BASIC_TIM_Period            1000-1   //��ʱ����
#define            BASIC_TIM_Prescaler         72-1     //��Ƶ����  ����Ϊ71  ��Ƶ��Ϊ71+1=72
#define						 BASIC_TIM									 TIM6      //��ʱ��
#define            BASIC_TIM_IRQ               TIM6_IRQn   //��ʱ���жϺ�
static void BASIC_TIM_Mode_Config(void);
static void BASIC_TIM_NVIC_Config(void);
void BASIC_TIM_IRQHandler (void);
extern void BASIC_TIM_Init(void);












#endif