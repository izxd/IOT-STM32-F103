#ifndef __BSP_DH11_H
#define __BSP_DH11_H

#include "bsp_gpio.h"
#include "bsp_systick2.h"

char dht11_value(unsigned char * temp, unsigned char * humi);

#endif /* __BSP_DH11_H */
