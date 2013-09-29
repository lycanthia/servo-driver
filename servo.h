/*
 * Module responsible for setting PWM to drive servomotors
 */

#ifndef __H_SERVO_H__
#define __H_SERVO_H__


#define SERVO_LEFT      1010  //daje to 1ms
#define SERVO_CENTER    1500
#define SERVO_RIGHT     1990  //daje to 2ms

#define SERVO_ALL   0
#define SERVO_1     1
#define SERVO_2     2
#define SERVO_3     3
#define SERVO_4     4

#define SERVO_BASEQUANTUM   1



void servo_Init(void);
void servo_SetPosition(uint8_t servo, uint16_t position);
void servo_SetPercent(uint8_t servo, uint8_t percent);


#endif

