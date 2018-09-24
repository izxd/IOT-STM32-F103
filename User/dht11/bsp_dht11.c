#include "bsp_dht11.h"

unsigned char dht11_read_byte(void)
{
	unsigned char r_val = 0;
	unsigned char t_count = 0; // 计时器, 防超时
	unsigned char i;
	
	for(i = 0; i < 8; i++)
	{
		t_count = 0;
		
		// 低电平50us后开始一个数据位的读取
		while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))
		{
			t_count++;
			if(t_count > 250) // 超时
			return '4';
		}
		t_count = 0;
		
		SysTick_Delay_us2(32);
		
		// 高电平26-28us表示'0',70us表示'1'
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))	
		{
			r_val <<= 1;
			r_val |= 1;
		}else
		{
			r_val <<= 1;
			continue;
		}
		
		// 等待dht11数据输出结果
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))
		{	
			t_count++;
			if(t_count > 250)
			{
				return '4';
			}
		}
	}
	
	return r_val;
}


char dht11_value(unsigned char * temp, unsigned char * humi)
{
	unsigned char t_count = 0; // 计时器,防超时
	
	unsigned char h_i = 0, h_f = 0;
	unsigned char t_i = 0, t_f = 0;
	
	// GPIO口配置
	GPIO_Config();
	// GPIOB_Pin9引脚配置
	// GPIO_SetBits(GPIOB,GPIO_Pin_9); // 置1输出高电平
	GPIO_ResetBits(GPIOB,GPIO_Pin_9); // 置0输出低电平
	
	SysTick_Delay_ms2(20); // 低电平保持18ms以上
	
	// 主机结束信号，即GPIO_B_Pin_9输出高电平
	GPIO_SetBits(GPIOB,GPIO_Pin_9); // 置1输出高电平
	
	// 主机等待20us~40us,读取dht11响应输出
	SysTick_Delay_us2(30);
	
	// 引脚改输入
	GPIO_Config_In();
	
	// 读取输入引脚的电平 1：表示高电平 2：低电平，即传感器响应了信号
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1)
	{
		// 不处理
		return '1';
	}else{
		
		// 处理事情
	  while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))
		{	
			t_count++;
			
			if(t_count > 250) // 超时
				return '3';
		}
		
		t_count = 0;
		
		SysTick_Delay_us2(50); // 拉高总线80us 
		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)) // 等待接收
		{
			t_count++;
			
			if(t_count > 250) //超时
				return '3';
		}
		
		h_i = dht11_read_byte(); //湿度整数部分；
		h_f = dht11_read_byte(); //湿度小数部分；
		t_i = dht11_read_byte(); //温度整数部分；
		t_f = dht11_read_byte(); //温度小数部分；
		
		temp[0] = t_i/10+0x30;
		temp[1] = t_i%10+0x30;
		temp[2] = t_f/10+0x30;
		temp[3] = t_f%10+0x30;
		
		humi[0] = h_i/10+0x30;
		humi[1] = h_i%10+0x30;
		humi[2] = h_f/10+0x30;
		humi[3] = h_f%10+0x30;
		
		return '0';
	}
	
}
