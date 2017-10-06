#include "stm32f10x.h"
#include "GeneralTIM.h"  
#include "module_74hc595.h"
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
	

int main(void)
{
	uint32_t time;
	// TIM ������������ʱ��
	uint32_t TIM_PscCLK = 72000000 / (GENERAL_TIM_PSC+1);
	
	
	/* ��ʱ����ʼ�� */
	GENERAL_TIM_Init();
	/*����ܳ�ʼ��*/
	hc595_init();
	
	
	while(1)
	{
		if(TIM_ICUserValueStructure.Capture_FinishFlag == 1)
		{
			// ����ߵ�ƽʱ��ļ�������ֵ
			time = TIM_ICUserValueStructure.Capture_Period * (GENERAL_TIM_PERIOD+1) + 
			      (TIM_ICUserValueStructure.Capture_CcrValue+1);

						//�����������ʾ�ߵ�ƽ����ʱ��
			Dispaly_M(time/TIM_PscCLK,time%TIM_PscCLK);
			
			
			TIM_ICUserValueStructure.Capture_FinishFlag = 0;			
		}		
	}
}
