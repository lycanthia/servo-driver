/*
 * Module rsponsible for handling buttons and diodes
 */

#ifndef __H_PORTIO_H__
#define __H_PORTIO_H__

#include "stm32f10x.h"
#include "stm32f10x_conf.h"

#define PORTIO_OFF      0
#define PORTIO_ON       1

#define PORTIO_LED_R GPIO_Pin_0
#define PORTIO_LED_G GPIO_Pin_1

#define PORTIO_BUTTON1  GPIO_Pin_8
#define PORTIO_BUTTON2  GPIO_Pin_9



void portio_Init(void);
void portio_Led(uint16_t, int8_t status);
int8_t portio_CheckButton(uint16_t number);



#endif

