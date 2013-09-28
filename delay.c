#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "delay.h"


volatile unsigned long delay_timer[DELAY_MAXTIMERS];



void delay_Init(void)
{
    int i = 0;

    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
   
    //clearing timers
    for (i = 0; i < DELAY_MAXTIMERS; i++)
        delay_timer[i] = 0;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);
   
    //NVIC
    NVIC_InitStructure.NVIC_IRQChannel = TIM1_CC_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    
    NVIC_Init(&NVIC_InitStructure);
    
    TIM_TimeBaseStructure.TIM_Period = 99;  //1kHz
    TIM_TimeBaseStructure.TIM_Prescaler = 36;
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
    
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_Timing;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = 49;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM1,&TIM_OCInitStructure);
    
    TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);

    TIM_ITConfig(TIM1,TIM_IT_CC1,ENABLE);
    
    TIM_Cmd(TIM1,ENABLE);
}

void delay_ClearTimer(int timer)
{
    delay_timer[timer] = 0;
}

unsigned long delay_GetTimer(int timer)
{
    return delay_timer[timer];
}

void delay_MsBlockWait(unsigned long time, int timer)
{
    delay_timer[timer] = 0;

    while (delay_timer[timer] < (time * 10));
}

void delay_100usBlockWait(unsigned long time, int timer)
{
    delay_timer[timer] = 0;

    while (delay_timer[timer] < time);
}



void TIM1_CC_IRQHandler(void)
{
    int i = 0;

    if(TIM_GetITStatus(TIM1,TIM_IT_CC1) == SET)
    {
        TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
        
        for (i = 0; i < DELAY_MAXTIMERS; i++) {
            delay_timer[i]++;
    
            if(delay_timer[i] > 9999999)
                delay_timer[i] = 9999999;
        }
        
        // if(test)
        // {
            // test = 0;
            // portio_Led(PORTIO_LEDG,PORTIO_OFF);
        // }
        // else
        // {
            // test = 1;
            // portio_Led(PORTIO_LEDG,PORTIO_ON);
        // }
        //----------------------------------------------------
        //TIM_SetCompare1(TIM1,TIM_GetCapture1(TIM1) + DELAY_PULSE);
        //----------------------------------------------------
    }
}

