#include "stm32f10x.h"
#include "stm32f10x_conf.h"
#include "portio.h"


void portio_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    
    //init for diodesh
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    //init for external buttons
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;

	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

void portio_Led(unsigned short number, char status)
{
    if(status)
        GPIO_SetBits(GPIOA, number);
    else
        GPIO_ResetBits(GPIOA, number);
}

char portio_CheckButton(unsigned short number)
{
    if(GPIO_ReadInputDataBit(GPIOB, number))
    	return 0;
    else
    	return 1;
}

