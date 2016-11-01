#include "stm32l1xx.h"
 
int main(void)
{
    GPIO_InitTypeDef port;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
    
    port.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    port.GPIO_Mode = GPIO_Mode_OUT;
    port.GPIO_OType = GPIO_OType_PP;
    port.GPIO_PuPd = GPIO_PuPd_NOPULL;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOB, &port);
    /////////////////////////////////////
    port.GPIO_Pin = GPIO_Pin_0;
    port.GPIO_Mode = GPIO_Mode_IN;
    port.GPIO_OType = GPIO_OType_PP;
    port.GPIO_PuPd = GPIO_PuPd_NOPULL;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOA, &port);
    
    while(1)
    {
        if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == 1)
        {
            GPIO_SetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7);
        }
        else
        {
            GPIO_ResetBits(GPIOB, GPIO_Pin_6 | GPIO_Pin_7);
        }
    }
}
