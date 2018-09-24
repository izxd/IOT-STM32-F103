#include "bsp_systick_wifi.h"

static __IO u32 TimingDelay = 0;

void SysTick_Init(void)
{
	if(SysTick_Config(SystemCoreClock / 1000)){
		while(1);
	}
	
	SysTick->CTRL &=~ SysTick_CTRL_ENABLE_Msk;
}

void Delay_ms(__IO u32 nTime)
{
	TimingDelay = nTime;
	
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	
	while(TimingDelay != 0);
}

void TimingDelay_Decrement(void)
{

	if(TimingDelay != 0x00){
		TimingDelay --;
	}
}


