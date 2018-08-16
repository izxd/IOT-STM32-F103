#include "bsp_clkconfig.h"

void HSE_SetSysClock(uint32_t RCC_PLLMul_x)
{
		ErrorStatus HSEStatus;
	
		// RCC�Ĵ�����λ
		RCC_DeInit();
	
	  // ʹ��HSE
    RCC_HSEConfig(RCC_HSE_ON);

		// �ȴ�HSE�����ȶ�
		HSEStatus = RCC_WaitForHSEStartUp();
		if(HSEStatus == SUCCESS)
		{
			// flashʹ��Ԥȡָ
			FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
			// ����Ǳ������
			FLASH_SetLatency(FLASH_Latency_2);
			
			// �������߷�Ƶ����
			RCC_HCLKConfig(RCC_SYSCLK_Div1);
			RCC_PCLK2Config(RCC_HCLK_Div1);
			RCC_PCLK1Config(RCC_HCLK_Div2);
			
			// �������໷PLLCLK = HSE * RCC_PLLMul_x
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
			// ʹ��PLL
			RCC_PLLCmd(ENABLE);
			
			// �ȴ�PLL�ȶ�
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
			{
			
			}
			
			// ѡ��ϵͳʱ��
			RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
			
			while(RCC_GetSYSCLKSource() != 0x08)
			{
			
			}
			
			
		}else{
			while(1)
			{
				
			}
		}
}
