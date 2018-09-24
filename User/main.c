#include "stm32f10x.h"
#include "bsp_dht11.h"
#include "bsp_systick2.h"
#include "bsp_usart.h"
#include "bsp_led.h"

int main(void)
{
	unsigned char temp[4],humi[4];
	unsigned char prints[9];
	
	USART_Config();
	
	while(1){
		
	  dht11_value(temp,humi);
		
		prints[0] = temp[0];
		prints[1] = temp[1];
		prints[2] = temp[2];
		prints[3] = temp[3];
		
		prints[4] = humi[0];
		prints[5] = humi[1];
		prints[6] = humi[2];
		prints[7] = humi[3];
		
	  Usart_SendString(DEBUG_USARTx, prints);
		
		SysTick_Delay_ms2(1000);
	}
	
}

