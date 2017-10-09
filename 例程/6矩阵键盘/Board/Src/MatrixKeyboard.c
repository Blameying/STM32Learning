#include "MatrixKeyboard.h"
void KeyInit(void) {

  GPIO_InitTypeDef GPIO_InitStructure;                   //����ṹ�����
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);  //����Ӧʱ��
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;  //���io������
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;          //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 				//�����������
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;  //���io������                                                
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;        //�������                                                  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 			//�����������
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin =GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;  //��������
  GPIO_Init(GPIOD, &GPIO_InitStructure);

}



char KeyClicked(void) {

  char key = 0;



  /*****������һ�а���******/

  GPIO_SetBits(GPIOB, GPIO_Pin_14);                // ���øߵ�ƽ

  GPIO_ResetBits(GPIOB, GPIO_Pin_15);              // �͵�ƽ

  GPIO_ResetBits(GPIOD, GPIO_Pin_9 | GPIO_Pin_8);  // �͵�ƽ

  if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13) == 1)		//��⵽�ߵ�ƽ֤������������
	{
      key = 11;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12) == 1) 
	{

      key = 21;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) == 1) 
	{
      key = 31;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 1)
	{
      key = 41;
  }


  /*****�����ڶ��а���******/

  GPIO_SetBits(GPIOB, GPIO_Pin_15);                

  GPIO_ResetBits(GPIOD, GPIO_Pin_8 | GPIO_Pin_9);  

  GPIO_ResetBits(GPIOB, GPIO_Pin_14);              

  if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13) == 1)
	{
      key = 12;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12) == 1) 
	{

      key = 22;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) == 1) 
	{
      key = 32;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 1)
	{
      key = 42;
  }

    /*****���������а���******/



  GPIO_SetBits(GPIOD, GPIO_Pin_8);    

  GPIO_ResetBits(GPIOD, GPIO_Pin_9);  

  GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);

  if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13) == 1)
	{
      key = 13;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12) == 1) 
	{

      key = 23;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) == 1) 
	{
      key = 33;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 1)
	{
      key = 43;
  }

 /*****���������а���******/

  GPIO_SetBits(GPIOD, GPIO_Pin_9);                   

  GPIO_ResetBits(GPIOD, GPIO_Pin_8);                 

  GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);  

  if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_13) == 1)
	{
      key = 14;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_12) == 1) 
	{

      key = 24;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_11) == 1) 
	{
      key = 34;
	} 
	else if (GPIO_ReadInputDataBit(GPIOD, GPIO_Pin_10) == 1)
	{
      key = 44;
  }
  return key;//���ذ������
}
