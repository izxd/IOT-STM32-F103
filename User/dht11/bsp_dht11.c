#include "bsp_dht11.h"

unsigned char dht11_read_byte(void)
{
	unsigned char r_val = 0;
	unsigned char t_count = 0; // ��ʱ��, ����ʱ
	unsigned char i;
	
	for(i = 0; i < 8; i++)
	{
		t_count = 0;
		
		// �͵�ƽ50us��ʼһ������λ�Ķ�ȡ
		while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))
		{
			t_count++;
			if(t_count > 250) // ��ʱ
			return '4';
		}
		t_count = 0;
		
		SysTick_Delay_us2(32);
		
		// �ߵ�ƽ26-28us��ʾ'0',70us��ʾ'1'
		if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))	
		{
			r_val <<= 1;
			r_val |= 1;
		}else
		{
			r_val <<= 1;
			continue;
		}
		
		// �ȴ�dht11����������
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
	unsigned char t_count = 0; // ��ʱ��,����ʱ
	
	unsigned char h_i = 0, h_f = 0;
	unsigned char t_i = 0, t_f = 0;
	
	// GPIO������
	GPIO_Config();
	// GPIOB_Pin9��������
	// GPIO_SetBits(GPIOB,GPIO_Pin_9); // ��1����ߵ�ƽ
	GPIO_ResetBits(GPIOB,GPIO_Pin_9); // ��0����͵�ƽ
	
	SysTick_Delay_ms2(20); // �͵�ƽ����18ms����
	
	// ���������źţ���GPIO_B_Pin_9����ߵ�ƽ
	GPIO_SetBits(GPIOB,GPIO_Pin_9); // ��1����ߵ�ƽ
	
	// �����ȴ�20us~40us,��ȡdht11��Ӧ���
	SysTick_Delay_us2(30);
	
	// ���Ÿ�����
	GPIO_Config_In();
	
	// ��ȡ�������ŵĵ�ƽ 1����ʾ�ߵ�ƽ 2���͵�ƽ������������Ӧ���ź�
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9) == 1)
	{
		// ������
		return '1';
	}else{
		
		// ��������
	  while(!GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9))
		{	
			t_count++;
			
			if(t_count > 250) // ��ʱ
				return '3';
		}
		
		t_count = 0;
		
		SysTick_Delay_us2(50); // ��������80us 
		
		while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9)) // �ȴ�����
		{
			t_count++;
			
			if(t_count > 250) //��ʱ
				return '3';
		}
		
		h_i = dht11_read_byte(); //ʪ���������֣�
		h_f = dht11_read_byte(); //ʪ��С�����֣�
		t_i = dht11_read_byte(); //�¶��������֣�
		t_f = dht11_read_byte(); //�¶�С�����֣�
		
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
