/**********************718创新实验室开发板例程*********************
*  编写：718创新实验室
*  平台：STM32F103VET6
*  说明：由于作者的水平有限，若有不足之处，还请大家谅解。
*		 建议大家多看看数据手册。     
******************************************************************/

#include "stm32f10x.h"
#include "iic.h"


/************************************************************
*模拟IIC引脚初始化函数
*初始化IIC用到的各个IO口
************************************************************/
void IIC_GPIO_Configuration( GPIO_TypeDef * GPIOx_SDA , uint16_t SDA_Pin , GPIO_TypeDef * GPIOx_SCL , uint16_t SCL_Pin )
{
	GPIO_InitTypeDef GPIO_InitStructure;															//声明GPIO配置结构体
	uint32_t RCC_GPIOx_SDA = 0;																				
	uint32_t RCC_GPIOx_SCL = 0;

	//得到滤波后的引脚端口
	RCC_GPIOx_SDA = GPIO_Filter( GPIOx_SDA );													
	RCC_GPIOx_SCL = GPIO_Filter( GPIOx_SCL );
	
	//使能时钟
  RCC_APB2PeriphClockCmd(RCC_GPIOx_SDA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_GPIOx_SCL,ENABLE);

	//配置引脚
	GPIO_InitStructure.GPIO_Pin = SDA_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_Init(GPIOx_SDA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = SCL_Pin;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_Init(GPIOx_SCL, &GPIO_InitStructure);

	//初始化ICC的模式
	SET_SDA;
	SET_SCL;  
}


/************************************************************/
//IIC延时函数
/************************************************************/
void IIC_Delay(void)
{
	u32 i = 5;
	while( i-- );
}

/*******************************************************************
TWI_START
发送启动数据
*******************************************************************/
u8 IIC_Start(void)
{
	SET_SDA;
	IIC_DELAY;

	SET_SCL;
	IIC_DELAY;

	if( IIC_SDA_STATE == RESET )
	{
		return IIC_BUS_BUSY;
	}

	RESET_SDA;
	IIC_DELAY;

	RESET_SCL;
	IIC_DELAY;

	if( IIC_SDA_STATE == SET )
	{
		return IIC_BUS_ERROR;
	}

	return IIC_BUS_READY;
}

/*******************************************************************
TWI_STOP
发送停止数据
*******************************************************************/
void IIC_Stop(void)
{
	RESET_SDA;
	IIC_DELAY;

	SET_SCL;
	IIC_DELAY;

	SET_SDA;
	IIC_DELAY;
}

/*******************************************************************************
* 函数名称:IIC_SendNACK                                                                     
* 描    述:收到数据,发送NACK                                                                                                                                       
 *******************************************************************************/
void IIC_SendNACK(void)
{
	RESET_SDA;
	IIC_DELAY;
	SET_SCL;
	IIC_DELAY;
	RESET_SCL; 
	IIC_DELAY; 
}

/*******************************************************************************
* 函数名称:IIC_SendACK                                                                     
* 描    述:收到数据,发送ACK                                                                                                                                        
*******************************************************************************/
void IIC_SendACK(void)
{
	SET_SDA;
	IIC_DELAY;
	SET_SCL;
	IIC_DELAY;
	RESET_SCL; 
	IIC_DELAY;
}

/*******************************************************************************
 * 函数名称:IIC_SendByte                                                                     
 * 描    述:发送一个字节                                                                                                                                      
 *******************************************************************************/
u8 IIC_SendByte(u8 Data)
{
	 u8 i;
	 RESET_SCL;
	 for(i=0;i<8;i++)
	 {  
		//---------数据建立----------
		if(Data&0x80)
		{
			SET_SDA;
		}
		else
		{
			RESET_SDA;
		} 
		Data<<=1;
		IIC_DELAY;
		//---数据建立保持一定延时----
		//----产生一个上升沿[正脉冲] 
		SET_SCL;
		IIC_DELAY;
		RESET_SCL;
		IIC_DELAY;//延时,防止SCL还没变成低时改变SDA,从而产生START/STOP信号
		//---------------------------   
	 }
	 //接收从机的应答 
	 SET_SDA; 
	 IIC_DELAY;
	 SET_SCL;
	 IIC_DELAY;   
	 if(IIC_SDA_STATE)
	 {
		RESET_SCL;
		return IIC_NACK;
	 }
	 else
	 {
		RESET_SCL;
		return IIC_ACK;  
	 }    
}

/*******************************************************************************
 * 函数名称:IIC_ReceiveByte                                                                     
 * 描    述:接收一个字节                                                                                                                                       
 *******************************************************************************/
u8 IIC_RecvByte(void)
{
	 u8 i,Dat = 0;
	 SET_SDA;
	 RESET_SCL; 
	 Dat=0;
	 for(i=0;i<8;i++)
	 {
		SET_SCL;//产生时钟上升沿[正脉冲],让从机准备好数据 
		IIC_DELAY; 
		Dat<<=1;
		if(IIC_SDA_STATE) //读引脚状态
		{
			Dat|=0x01; 
		}   
		RESET_SCL;//准备好再次接收数据  
		IIC_DELAY;//等待数据准备好         
	 }
	 return Dat;
}

/************************************************
*函数名称:Single_Write_IIC
*参数:SlaveAddress从机地址，REG_Address寄存器地址，REG_data数据
*功能:单字节写入
*************************************************/

void Single_Write_IIC(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{
    IIC_Start();                  //起始信号
    IIC_SendByte(SlaveAddress);   //发送设备地址+写信号
    IIC_SendByte(REG_Address);    //内部寄存器地址， //请参考中文pdf22页 
    IIC_SendByte(REG_data);       //内部寄存器数据， //请参考中文pdf22页 
    IIC_Stop();                   //发送停止信号
}

/************************************************
*函数名称:Single_Read_IIC
*参数:SlaveAddress从机地址，REG_Address寄存器地址，REG_data数据
*功能:单字节读取
*************************************************/
u8 Single_Read_IIC(u8 SlaveAddress, u8 REG_Address)
{  
	u8 REG_data;
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress);           //发送设备地址+写信号
    IIC_SendByte(REG_Address);            //发送存储单元地址，//从0开始	
    IIC_Start();                          //起始信号
    IIC_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data = IIC_RecvByte();              //读出寄存器数据
	IIC_SendACK();   
	IIC_Stop();                           //停止信号
    return REG_data; 
}


/************************************************
*函数名称:GPIO_Filter
*参数:GPIO地址
*功能:选定初始化时钟
*************************************************/
uint16_t GPIO_Filter( GPIO_TypeDef * GPIOx )
{	 
	uint32_t RCC_GPIOx = 0; 

	if( GPIOx == GPIOA )
	{
		RCC_GPIOx = RCC_APB2Periph_GPIOA;
	}
	else if( GPIOx == GPIOA )
	{
		RCC_GPIOx = RCC_APB2Periph_GPIOA;
	}
	else if( GPIOx == GPIOB )
	{
		RCC_GPIOx = RCC_APB2Periph_GPIOB;
	}
	else if( GPIOx == GPIOC )
	{
		RCC_GPIOx = RCC_APB2Periph_GPIOC;
	}
	else if( GPIOx == GPIOD )
	{
		RCC_GPIOx = RCC_APB2Periph_GPIOD;
	}
	else if( GPIOx == GPIOE )
	{
		RCC_GPIOx = RCC_APB2Periph_GPIOE;
	}
	else if( GPIOx == GPIOF )
	{
		RCC_GPIOx = RCC_APB2Periph_GPIOF;
	}
	else if( GPIOx == GPIOG )
	{
		RCC_GPIOx = RCC_APB2Periph_GPIOG;
	}
	return RCC_GPIOx;
}

