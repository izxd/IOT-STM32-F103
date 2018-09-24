#include "bsp_systick2.h"

void SysTick_Delay_us2(uint32_t us)
{
	uint32_t i;
	SysTick_Config(72);
	
	for(i=0; i<us; i++)
	{
		while( !((SysTick->CTRL) & (1<<16)));
	}	
	
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

void SysTick_Delay_ms2(uint32_t ms)
{
	uint32_t i;
	SysTick_Config(72000);
	
	for(i=0; i<ms; i++)
	{
		while( !((SysTick->CTRL) & (1<<16)));
	}	
	
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
