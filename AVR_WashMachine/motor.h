/*
 * motor.h
 *
 * Created: 2022-08-13 오전 11:55:06
 *  Author: seonhaeng han
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
extern volatile int ms_cnt;
extern volatile int s_cnt;
void motor_init();
void motor_time_speed_auto();
void motor_mode1(int speed);
void motor_mode2(int speed);
void motor_stop();



#endif /* MOTOR_H_ */