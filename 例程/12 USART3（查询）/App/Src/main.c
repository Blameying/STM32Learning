/*************************718开发板例程**********************

*   编写：718创新实验室
*		平台：STM32F103VET6科创培训开发板
*		说明：该例程使用官方库进行编写，由于作者的水平有限， 
*								若有不足之处， 还请大家见谅
*									建议大家多查阅数据手册，多在新生群和大家交流。

*************************************************************/

#include "include.h"
#include <stdio.h>//printf函数需要包含此头文件 并在配置选项中勾选use microlib
//宏定义 总线时钟 GPIO时钟 波特率
#define USART_CLK RCC_APB2Periph_USART1
#define USART_GPIO_CLK RCC_APB2Periph_GPIOA
#define USART_BAUDRATE 115200
#define USARTx USART1
#define USARTx_APBxClkCmd RCC_APB2PeriphClockCmd

//USART GPIO管脚宏定义
#define USART_TX_GPIO_PORT GPIOA
#define USART_TX_GPIO_PIN GPIO_Pin_9
#define USART_RX_GPIO_PORT GPIOA
#define USART_RX_GPIO_PIN GPIO_Pin_10

void USART_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);

int main() {
	uint8_t ucTemp;	//ucTemp变量用于保存UASRT接收缓冲器的值
	
	/*初始化USART 配置模式为 115200 8-N-1，*/
  USART_Config();
	
	/*发送一个字符*/
	Usart_SendByte(USARTx,'*');
	/* 发送一个字符串 */
	Usart_SendString( USARTx,"这是一个串口接收发送程序\n");	
	printf("718创新实验室\n\n\n\n");	//使用printf函数发送
		
while(1){
	
	if(USART_GetFlagStatus(USARTx,USART_FLAG_RXNE) == 1){		//查询RXNE（接收寄存器非空则自动置一）
			ucTemp = USART_ReceiveData(USARTx);					//读取接收寄存器的值
			USART_SendData(USARTx,ucTemp);						//回发接收到的数据
	}
}

}
/*
函数名： void USART_Config(void)
作用： 		USART初始化
参数：    void
返回：		void
说明：		USART1 使用APB2 时钟 其他使用APB1时钟�
					详细设置可见数据手册
*/
void USART_Config(void){
	GPIO_InitTypeDef GPIO_InitStructure;		//GPIO初始化结构体
	USART_InitTypeDef USART_InitStructure;	//USART初始化结构体
	//打开GPIO时钟
	RCC_APB2PeriphClockCmd(USART_GPIO_CLK,ENABLE);
	//打开串口外设时钟
	USARTx_APBxClkCmd(USART_CLK,ENABLE);
	// 将USART Tx的GPIO配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = USART_TX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(USART_TX_GPIO_PORT, &GPIO_InitStructure);
  // 将USART Rx的GPIO配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = USART_RX_GPIO_PIN;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(USART_RX_GPIO_PORT, &GPIO_InitStructure);
// 配置串口的工作参数
	// 配置波特率为115200
	USART_InitStructure.USART_BaudRate = USART_BAUDRATE;
	// 配置 针数据字长为8位
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位 1位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位 不检验
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// 配置硬件流控制  无
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(USARTx, &USART_InitStructure);
	//使能USART
	USART_Cmd(USARTx,ENABLE);
}
/*
函数名： void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
作用： 		发送一个字节
参数：    USART_TypeDef * pUSARTx， uint8_t ch
返回：		void
说明：		详细说明可见数据手册
*/
void Usart_SendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到USART */
	USART_SendData(pUSARTx,ch);
		
	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*
函数名： void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
作用： 		发送一个8位数组
参数：    USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num
返回：		void
说明：		将数组中各个元素依次发送
*/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* 发送一个字节数据到USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* 等待发送完成 */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET); //USART_FLAG_FC为发送完成标志位 发送完成硬件自动置1
}
/*
函数名： void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
作用： 		发送字符串
参数：    USART_TypeDef * pUSARTx, char *str
返回：		void
说明：		
*/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
  do 
  {
      Usart_SendByte( pUSARTx, *(str + k) );
      k++;
  } while(*(str + k)!='\0');
  
  /* 等待发送完成 */
  while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET)
  {}
}
/*
函数名： Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
作用： 		发送16位的数
参数：    USART_TypeDef * pUSARTx, uint16_t ch
返回：		void
说明：		先发送高八位，再发送低八位 然后合成
*/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* 取出高八位 */
	temp_h = (ch&0XFF00)>>8;
	/* 取出低八位 */
	temp_l = ch&0XFF;
	
	/* 发送高八位 */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* 发送低八位 */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}
/*
函数名： int fputc(int ch, FILE *f)
作用： 		重定向c库函数printf到串口，重定向后可使用printf函数
参数：    int ch, FILE *f
返回：		ch
说明：		printf再发送时需要调用fputc函数  此处将该函数重新定义
*/
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(USARTx, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}
/*
函数名： int fgetc(FILE *f)
作用： 		重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
参数：    FILE *f
返回：		(int)USART_ReceiveData(USARTx)
说明：		scanf接收时需要调用fputc函数  此处将该函数重新定义
*/
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USARTx);
}

