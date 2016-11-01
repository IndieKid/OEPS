#include "stm32l1xx.h"

uint8_t i = 0;

void TIM6_IRQHandler(void)
{
		TIM6->SR &= ~TIM_SR_UIF;
		if (i == 0) GPIOB->BSRRL |= GPIO_BSRR_BS_6;
		else GPIOB->BSRRH |= GPIO_BSRR_BS_6;
		i = ~i;
}
 
int main(void)
{
   GPIO_InitTypeDef port;
    
   /* RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);*/
	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
		NVIC_SetPriority(TIM6_IRQn, 1); 
		NVIC_EnableIRQ(TIM6_IRQn);
	
		RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
		GPIOB->MODER |= GPIO_MODER_MODER6_0;
		GPIOB->OTYPER &= ~GPIO_OTYPER_OT_6;
		GPIOB->PUPDR &= ~GPIO_PUPDR_PUPDR6;
		GPIOB->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR6;
	
		RCC->APB1ENR |= RCC_APB1ENR_TIM6EN; 
		TIM6->PSC = 0xFFFF; 
		TIM6->ARR = 0x000F;
		TIM6->DIER |= TIM_DIER_UIE; 
		TIM6->CR1 |= TIM_CR1_CEN;
		
	
	
    port.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    port.GPIO_Mode = GPIO_Mode_OUT;
    port.GPIO_OType = GPIO_OType_PP;
    port.GPIO_PuPd = GPIO_PuPd_NOPULL;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOB, &port);
		/*/////////////////////////////////////
    port.GPIO_Pin = GPIO_Pin_0;
    port.GPIO_Mode = GPIO_Mode_IN;
    port.GPIO_OType = GPIO_OType_PP;
    port.GPIO_PuPd = GPIO_PuPd_NOPULL;
    port.GPIO_Speed = GPIO_Speed_2MHz;
    
    GPIO_Init(GPIOA, &port);
		*/
		
    
    while(1)
    {
        GPIO_SetBits(GPIOB, GPIO_Pin_7);
    }
}
