#ifndef __BSP_USART2_H
#define __BSP_USART2_H

#include "stm32f10x.h"
#include <stdio.h>

void USART2_Config( void );
extern void USART2_printf(USART_TypeDef* USARTx, char *Data, ...);

#endif /* __BSP_USART2_H */
