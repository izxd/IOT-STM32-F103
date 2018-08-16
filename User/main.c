#include "stm32f10x.h"
#include "bsp_led.h"
#include "bsp_key.h"
#include "bsp_exti.h"
#include "bsp_clkconfig.h"
#include "bsp_SysTick.h"
#include "bsp_usart.h"

void Delay(uint32_t count)
{
	for(;count != 0; count--);
}

int main(void)
{
	/* 初始化USART配置模式为。。。 */
	
	//USART_Config();
	
	//Usart_SendString(DEBUG_USARTx, "this is string .\n");
	
	//HSE_SetSysClock(RCC_PLLMul_9);
	//LED_GPIO_Config();
	//GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
	
	//Key_GPIO_Config();
	// EXIT_Key_Config();
	while(1)
	{
		// nesting vector interrupt
//		if(Key_Scan(KEY1_GPIO_PORT, KEY1_GPIO_PIN) == KEY_ON)
//		{
//			LED_G(OFF);
//		}
//		
//		if(Key_Scan(KEY2_GPIO_PORT, KEY2_GPIO_PIN) == KEY_ON)
//		{
//			LED_G(ON);
//		}
		
		//LED_G(OFF);
		//SysTick_Delay_ms(500);
		//Delay(0xFFFFFF);
		//LED_G(ON);
		//SysTick_Delay_ms(500);
		//Delay(0xFFFFFF);
		
		// GPIO_SetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
		
		//GPIO_ResetBits(LED_G_GPIO_PORT, LED_G_GPIO_PIN);
		
	}
	
	
}

