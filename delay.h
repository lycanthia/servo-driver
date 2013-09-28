/*
 * Module responsible for generating defined delays.
 */

#ifndef __H_DELAY_H__
#define __H_DELAY_H__



#define DELAY_MAXTIMERS 5

#define DEALY_TIMER0    0
#define DEALY_TIMER1    1
#define DEALY_TIMER2    2
#define DEALY_TIMER3    3
#define DEALY_TIMER4    4



void delay_Init(void);

void delay_ClearTimer(int timer);
unsigned long delay_GetTimer(int timer);

void delay_MsBlockWait(unsigned long time, int timer);
void delay_100usBlockWait(unsigned long time, int timer);



#endif

