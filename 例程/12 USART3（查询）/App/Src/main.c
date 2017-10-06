/*************************718����������**********************

*   ��д��718����ʵ����
*		ƽ̨��STM32F103VET6�ƴ���ѵ������
*		˵����������ʹ�ùٷ�����б�д���������ߵ�ˮƽ���ޣ� 
*								���в���֮���� �����Ҽ���
*									�����Ҷ���������ֲᣬ��������Ⱥ�ʹ�ҽ�����

*************************************************************/
/*************************����˵��******************************
ͨ����������Խ���ͨ��
ʲô�Ǵ���:
https://baike.baidu.com/item/%E4%B8%B2%E8%A1%8C%E6%8E%A5%E5%8F%A3/2909564?fr=aladdin
����:
���ô���ʵ�ֵ����뵥Ƭ��,��Ƭ���뵥Ƭ��֮���ͨ��,��һ�ּ򵥵�ͨ��Э��
���ڳ�ʼ������:
�򿪹ܽ�ʱ�Ӻʹ���USARTģ��ʱ��(�൱���ܿ���)->
����GPIO�ܽ�->
����USART����ģ��->
ʹ�ܴ���
*************************����˵��******************************/

#include "include.h"
#include <stdio.h>																			//ʹ��printf������Ҫ������׼��
//�궨�� ����ʱ�� GPIOʱ�� ������
#define USART_CLK RCC_APB1Periph_USART3
#define USART_GPIO_CLK RCC_APB2Periph_GPIOB
#define USART_BAUDRATE 115200
#define USARTx USART3
#define USARTx_APBxClkCmd RCC_APB1PeriphClockCmd

//USART GPIO�ܽź궨��
#define USART_TX_GPIO_PORT GPIOB
#define USART_TX_GPIO_PIN GPIO_Pin_10
#define USART_RX_GPIO_PORT GPIOB
#define USART_RX_GPIO_PIN GPIO_Pin_11

void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

int main() {
	uint8_t ucTemp;	//ucTemp�������ڱ���UASRT���ջ�������ֵ
	
	/*��ʼ��USART ����ģʽΪ 115200 8-N-1��*/
  USART_Config();
	
	/*����һ���ַ�*/
	Usart_SendByte(USARTx,'*');
	/* ����һ���ַ��� */
	Usart_SendString( USARTx,"����һ�����ڽ��շ��ͳ���\n");	
	printf("718����ʵ����\n\n\n\n");	//ʹ��printf��������
		
while(1){
	
	if(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE) == 1){		//��ѯRXNE�����ռĴ����ǿ����Զ���һ��
			ucTemp = USART_ReceiveData(USARTx);					//��ȡ���ռĴ�����ֵ
			USART_SendData(USARTx,ucTemp);						//�ط����յ�������
	}
}

}
/*
�������� void USART_Config(void)
���ã� 		USART��ʼ��
������    void
���أ�		void
˵����		USART1 ʹ��APB2 ʱ�� ����ʹ��APB1ʱ�ӣ
					��ϸ���ÿɼ������ֲ�
*/
void USART_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;		//GPIO��ʼ���ṹ��
	USART_InitTypeDef USART_InitStructure;	//USART��ʼ���ṹ��
	//��GPIOʱ��
	RCC_APB2PeriphClockCmd(USART_GPIO_CLK,ENABLE);
	//�򿪴�������ʱ��
	USARTx_APBxClkCmd(USART_CLK,ENABLE);
	// ��USART Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);
  // ��USART Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);
// ���ô��ڵĹ�������
	// ���ò�����Ϊ115200
	USART_InitStructure.USART_BaudRate = USART_BAUDRATE;
	// ���� �������ֳ�Ϊ8λ
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ 1λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ ������
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������  ��
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(USARTx, &USART_InitStructure);
	//ʹ��USART
	USART_Cmd(USARTx,ENABLE);
}
/*
�������� void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
���ã� 		����һ���ֽ�
������    USART_TypeDef * pUSARTx�� uint8_t ch
���أ�		void
˵����		��ϸ˵���ɼ������ֲ�
*/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(pUSARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*
�������� void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
���ã� 		����һ��8λ����
������    USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num
���أ�		void
˵����		�������и���Ԫ�����η���
*/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET); //USART_FLAG_FCΪ������ɱ�־λ �������Ӳ���Զ���1
}
/*
�������� void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
���ã� 		�����ַ���
������    USART_TypeDef * pUSARTx, char *str
���أ�		void
˵����		
*/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* �ȴ�������� */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}
/*
�������� Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
���ã� 		����16λ����
������    USART_TypeDef * pUSARTx, uint16_t ch
���أ�		void
˵����		�ȷ��͸߰�λ���ٷ��͵Ͱ�λ Ȼ��ϳ�
*/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*
�������� int fputc(int ch, FILE *f)
���ã� 		�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
������    int ch, FILE *f
���أ�		ch
˵����		printf�ٷ���ʱ��Ҫ����fputc����  �˴����ú������¶���
*/
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USARTx, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/*
�������� int fgetc(FILE *f)
���ã� 		�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
������    FILE *f
���أ�		(int)USART_ReceiveData(USARTx)
˵����		scanf����ʱ��Ҫ����fputc����  �˴����ú������¶���
*/
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USARTx);
}

