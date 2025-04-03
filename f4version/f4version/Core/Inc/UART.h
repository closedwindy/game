
#ifndef __UART_H
#define __UART_H

#include "usart.h"
#include "math.h"



typedef union
{
    float fdata;
    unsigned long ldata;
}FloatLongType;




void JustFloat_Send(float * fdata,uint16_t fdata_num,USART_TypeDef *Usart_choose);


#endif


