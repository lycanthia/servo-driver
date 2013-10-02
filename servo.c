#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "servo.h"



void servo_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    TIM_OCInitTypeDef TIM_OCInitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);    //clock for GPIOA i AFIO
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);    //clock for GPIOB i AFIO
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);     //clock for TIM3
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
    //----------------------------------------------------------------
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);  //PA6, PA7

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(GPIOB, &GPIO_InitStructure);  //PB0, PB1

    //GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
    //----------------------------------------------------------------
    TIM_TimeBaseStructure.TIM_Period = 1999;
    TIM_TimeBaseStructure.TIM_Prescaler = 32;
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    //----------------------------------------------------------------
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = SERVO_CENTER;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC1Init(TIM3, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
    //-----
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = SERVO_CENTER;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
    //-----
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = SERVO_CENTER;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC3Init(TIM3, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
    //-----
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_Pulse = SERVO_CENTER;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;

    TIM_OC4Init(TIM3, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
    //----------------------------------------------------------------
    TIM_ARRPreloadConfig(TIM3, ENABLE);
    TIM_Cmd(TIM3, ENABLE);
}

void servo_SetPosition(uint8_t servo, uint16_t position)
{
    uint16_t servoPosition;
    servoPosition = position;

    if(servoPosition > SERVO_RIGHT)
        servoPosition = SERVO_RIGHT;
    if(servoPosition < SERVO_LEFT)
        servoPosition = SERVO_LEFT;

    switch(servo)
    {
    case 0: //all motors
        TIM_SetCompare1(TIM3, servoPosition);
        TIM_SetCompare2(TIM3, servoPosition);
        TIM_SetCompare3(TIM3, servoPosition);
        TIM_SetCompare4(TIM3, servoPosition);
        break;

    case 1: //motor 1
        TIM_SetCompare1(TIM3, servoPosition);
        break;

    case 2: //motor 2
        TIM_SetCompare2(TIM3, servoPosition);
        break;

    case 3: //motor 3
        TIM_SetCompare3(TIM3, servoPosition);
        break;

    case 4: //motor 4
        TIM_SetCompare4(TIM3, servoPosition);
        break;
    }
}

void servo_SetPercent(uint8_t servo, uint8_t percent)
{
    uint8_t tmp = percent;

    if(tmp > 100)
        tmp = 100;
    
    servo_SetPosition(servo, SERVO_LEFT + tmp);
}
