/*
 * led.c
 *
 * Created: 2022-08-14 오전 1:26:47
 *  Author: seonhaeng han
 */ 
#include "led.h"


void init_led()
{
	DDRF |= 0x0f;
	PORTF &= 0xf0; 
	
}
int led_toggle = 0; 
void led_toggle1()
{

			PORTF = 0x08;
		
		
}
void led_toggle2()
{
	
		
			PORTF = 0x04;
		
	
}
void led_toggle3()
{
	
			PORTF = 0x02;
	
}