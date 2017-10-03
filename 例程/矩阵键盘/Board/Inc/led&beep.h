/**********************718����ʵ���ҿ���������*********************
*  ��д��718����ʵ����
*  ƽ̨��STM32F103VET6
*  ˵�����������ߵ�ˮƽ���ޣ����в���֮�����������½⡣
*		 �����Ҷ࿴�������ֲᡣ     
******************************************************************/


#ifndef __LED&BEEP_H__
#define __LED&BEEP_H__

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"

typedef enum  //ö�ٶ���Ƶ����
{
	LED1,
	LED2,
	LED3,
	LED4,
	LED5,
	LED6
}LEDNumber;

typedef enum
{
	Power_ON,
	Power_OFF,
}PowerState;


extern void LEDInit();
extern void LEDPower(LEDNumber Number,PowerState State);
extern void BeepInit();
extern void BeepPower(PowerState State);

#endif
