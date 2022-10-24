/*
 * fnd.h
 *
 * Created: 2022-08-14 오전 1:28:12
 *  Author: seonhaeng han
 */ 


#ifndef FND_H_
#define FND_H_

#define FND_DATA_DDR   DDRC
#define FND_DATA_PORT  PORTC

#define FND_DIGHT_DDR  DDRA
#define FND_DIGHT_PORT PORTA
#define FND_DIGHT_D1   4
#define FND_DIGHT_D2   5
#define FND_DIGHT_D3   6
#define FND_DIGHT_D4   7

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

typedef struct _time // 사용자 정의
{
	uint8_t hour;
	uint8_t min;
	uint8_t sec; // unsigned char sec; 와 동일함
}TIME; // TIME이라는 이름으로 재정의 한다.

TIME time_clock = {0, 0, 0};

void display_fnd(void);
void init_fnd(void);
void set_fnd_data(uint16_t data);
uint16_t get_fnd_data(void);

void set_time_clock(TIME time);
void get_time_clock(TIME *time);
void watch_reset();
extern volatile uint16_t time_cnt;
extern manual_auto_state; 

#endif /* FND_H_ */