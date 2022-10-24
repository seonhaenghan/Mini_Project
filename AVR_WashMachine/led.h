/*
 * led.h
 *
 * Created: 2022-08-14 오전 1:26:55
 *  Author: seonhaeng han
 */ 


#ifndef LED_H_
#define LED_H_

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h> // printf, scanf 등이 정의 되어 있다.
#include <string.h> // strcpy, strcat, strcmp 등이 들어 있음
void init_led();
void led_toggle1();
void led_toggle2();
void led_toggle3();



#endif /* LED_H_ */