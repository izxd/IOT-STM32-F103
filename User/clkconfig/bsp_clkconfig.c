#include "bsp_clkconfig.h"

void HSE_SetSysClock(uint32_t RCC_PLLMul_x)
{
		ErrorStatus HSEStatus;
	
		// RCC寄存器复位
		RCC_DeInit();
	
	  // 使能HSE
    RCC_HSEConfig(RCC_HSE_ON);

		// 等待HSE启动稳定
		HSEStatus = RCC_WaitForHSEStartUp();
		if(HSEStatus == SUCCESS)
		{
			// flash使能预取指
			FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
			// 设置潜在因子
			FLASH_SetLatency(FLASH_Latency_2);
			
			// 三个总线分频因子
			RCC_HCLKConfig(RCC_SYSCLK_Div1);
			RCC_PCLK2Config(RCC_HCLK_Div1);
			RCC_PCLK1Config(RCC_HCLK_Div2);
			
			// 配置锁相环PLLCLK = HSE * RCC_PLLMul_x
			RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_x);
			// 使能PLL
			RCC_PLLCmd(ENABLE);
			
			// 等待PLL稳定
			while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
			{
			
			}
			
			// 选择系统时钟
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
