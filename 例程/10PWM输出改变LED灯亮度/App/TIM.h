#ifndef __TIM_H
#define __TIM_H


/************ͨ�ö�ʱ��TIM�������壬ֻ��TIM2��3��4��5************/
// ��ʹ�ò�ͬ�Ķ�ʱ����ʱ�򣬶�Ӧ��GPIO�ǲ�һ���ģ����Ҫע��
// ��������Ĭ��ʹ��TIM3

#define            GENERAL_TIM                   TIM8
#define            GENERAL_TIM_APBxClock_FUN     RCC_APB2PeriphClockCmd
#define            GENERAL_TIM_CLK               RCC_APB2Periph_TIM8 
#define            GENERAL_TIM_Period            10
#define            GENERAL_TIM_Prescaler         71

// TIM3 ����Ƚ�ͨ��3
#define            GENERAL_TIM_CH3_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            GENERAL_TIM_CH3_PORT          GPIOC
#define            GENERAL_TIM_CH3_PIN           GPIO_Pin_8

// TIM3 ����Ƚ�ͨ��4
#define            GENERAL_TIM_CH4_GPIO_CLK      RCC_APB2Periph_GPIOC
#define            GENERAL_TIM_CH4_PORT          GPIOC
#define            GENERAL_TIM_CH4_PIN           GPIO_Pin_9





#define LED1_GPIO_PORT    	GPIOC			              
#define LED1_GPIO_CLK 	    RCC_APB2Periph_GPIOC		
#define LED1_GPIO_PIN	    	GPIO_Pin_7			       


#define LED2_GPIO_PORT    	GPIOC			              
#define LED2_GPIO_CLK 	    RCC_APB2Periph_GPIOC		
#define LED2_GPIO_PIN		GPIO_Pin_8			        


#define LED3_GPIO_PORT    	GPIOC			              
#define LED3_GPIO_CLK 	    RCC_APB2Periph_GPIOC		
#define LED3_GPIO_PIN		GPIO_Pin_9			        


/** the macro definition to trigger the led on or off 
  * 1 - off
  *0 - on
  */
#define ON  0
#define OFF 1




/* ������ɫ������߼��÷�ʹ��PWM�ɻ��ȫ����ɫ,��Ч������ */


void LED_GPIO_Config(void);
/**************************��������********************************/

void GENERAL_TIM_Init(void);


#endif	/* __BSP_GENERALTIME_H */
