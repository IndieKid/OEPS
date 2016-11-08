#include "stm32l1xx.h"

//http://visualgdb.com/tutorials/arm/stm32/pwm/

void InitializeLEDs()
{
		GPIO_InitTypeDef gpioStructure;
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    gpioStructure.GPIO_Pin = GPIO_Pin_6;
    gpioStructure.GPIO_Mode = GPIO_Mode_AF;
    gpioStructure.GPIO_Speed = GPIO_Speed_40MHz;
    GPIO_Init(GPIOB, &gpioStructure);
}

void InitializeTimer(int period)
{
		TIM_TimeBaseInitTypeDef timerInitStructure;
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    timerInitStructure.TIM_Prescaler = 0;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = period;
		//timerInitStructure.TIM_RepetitionCounter = 0;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInit(TIM4, &timerInitStructure);
    TIM_Cmd(TIM4, ENABLE);
}

void InitializePWMChannel()
{
    TIM_OCInitTypeDef outputChannelInit = {0,};
    outputChannelInit.TIM_OCMode = TIM_OCMode_PWM1;
    outputChannelInit.TIM_Pulse = 1000;
    outputChannelInit.TIM_OutputState = TIM_OutputState_Enable;
    outputChannelInit.TIM_OCPolarity = TIM_OCPolarity_High;
 
    TIM_OC1Init(TIM4, &outputChannelInit);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
 
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
}

int main()
{
	int i,j;
	InitializeLEDs();
	InitializeTimer(500);
	InitializePWMChannel();
	
	for (;;)
    {
			for (i=0;i<=800;i++) //brightness 0..1000
			{
				TIM4->CCR1 = i;
				for(j=0;j<1000;j++);
			}
    }
}
