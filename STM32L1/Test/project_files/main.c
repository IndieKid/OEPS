#include "stm32l1xx.h"

void delay(void) {
  volatile uint32_t i;
    for (i=1; i != 0xF000; i++);
  }

int main()
{
	GPIO_InitTypeDef port;
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

	port.GPIO_Pin = GPIO_Pin_6;
	port.GPIO_Mode = GPIO_Mode_AF;
	port.GPIO_OType = GPIO_OType_PP;
	port.GPIO_Speed = GPIO_Speed_2MHz;
	
	GPIO_Init(GPIOB, &port);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

	
	TIM4->CCER |= (TIM_CCER_CC1E|TIM_CCER_CC3E|TIM_CCER_CC4E);
	TIM4->CCMR1|=(TIM_CCMR1_OC2M_0| TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	TIM4->CCMR2|=(TIM_CCMR2_OC3M_0 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC4M_0 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2);
	
	
	TIM4->CR1 |= TIM_CR1_CEN;
	

	
	

  while(1)
  {
    
      TIM4->CCR2=13107; //0..65535
      
  }

}
