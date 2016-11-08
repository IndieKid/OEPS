#include "stm32l1xx.h"

void TIM2_IRQHandler(void)
{
	TIM2->SR &= ~TIM_SR_UIF;
	GPIOB->ODR ^= GPIO_OTYPER_ODR_6;
}

int main()
{
	GPIO_InitTypeDef port;
	
	NVIC_SetPriority(TIM2_IRQn, 1);
  NVIC_EnableIRQ(TIM2_IRQn);
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
	
	port.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
  port.GPIO_Mode = GPIO_Mode_OUT;
  port.GPIO_OType = GPIO_OType_PP;
  port.GPIO_PuPd = GPIO_PuPd_NOPULL;
  port.GPIO_Speed = GPIO_Speed_2MHz;
	
  GPIO_Init(GPIOB, &port);
	
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); //RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->PSC = 2096;
  TIM2->ARR = 500;
  TIM2->DIER |= TIM_DIER_UIE;
  TIM2->CR1 |= TIM_CR1_CEN;
	
	GPIO_SetBits(GPIOB, GPIO_Pin_6);
	GPIO_SetBits(GPIOB, GPIO_Pin_7);
	
	while (1)
	{
		
	}
}
