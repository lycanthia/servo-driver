/*
 * Servo driver controled by USB. It uses STM32 microcontroller to controll
 * up to 8 servomotors.
 *
 * Author: Pawel Polawski
 * Email: pawel.polawski@gmail.com
 *
 * */

#include "stm32f10x.h"

#include "portio.h"
#include "delay.h"



void main_Init();

int main(void)
{
    uint8_t i = 0;
    int8_t e = -10;

    main_Init();    //init everything

    if (e == -10)
    for ( i = 0; i < 20; ++i) {
        portio_Led(PORTIO_LED_R, PORTIO_ON);
        portio_Led(PORTIO_LED_G, PORTIO_ON);
        delay_MsBlockWait(100, DEALY_TIMER0);

        portio_Led(PORTIO_LED_R, PORTIO_OFF);
        portio_Led(PORTIO_LED_G, PORTIO_OFF);
        delay_MsBlockWait(100, DEALY_TIMER0);
    }

    //chcking for input
    while(1) {
    	if(portio_CheckButton(PORTIO_BUTTON1) && portio_CheckButton(PORTIO_BUTTON2)) {
			portio_Led(PORTIO_LED_G, PORTIO_ON);
			portio_Led(PORTIO_LED_R, PORTIO_OFF);
    	} else {
    		portio_Led(PORTIO_LED_G, PORTIO_OFF);
    		portio_Led(PORTIO_LED_R, PORTIO_ON);
    	}
    }

    while(1);
    return 0;
}



void main_Init(void)
{
    portio_Init();
    delay_Init();
}

