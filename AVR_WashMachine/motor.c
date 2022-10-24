/*
 * motor.c
 *
 * Created: 2022-08-13 오전 11:54:55
 *  Author: seonhaeng han
 */ 
#include "motor.h"

 // orginal 
// ENA : PORTE.5 (OCR3B(PE5) <=== PORTE.4 (Dc motor driver pin)
// IN1 : PORTE.0 (정회전/ 역회전)
// IN2 : PORTE.2 (속도)

void motor_init()
{
	
	// 모드5 : 8비트고속PWM모드 timer 3
	TCCR3A |= (1 << WGM30);
	TCCR3B |= (1 << WGM32);
	
	// 비반전 모드 TOP: 0xff 비교일치값 : OCR3C : PE5
	TCCR3A |= (1 << COM3C1);
	// 분주비 64  16000000/64  ==> 250000HZ(250KHZ)
	// 256 / 250000 ==> 1.02ms
	// 127 / 250000 ==> 0.5ms
	TCCR3B |= ( 1 << CS31)  | (1 << CS30);   // 분주비 64
	// 1600000HZ / 64분주 ==> 250000HZ (250KHZ)
	// 
	OCR3C=0;  // PORTE.5 
	
	DDRE |= ( 1 << 0) | ( 1 << 2) | ( 1 << 5);  // PE.0 PE.2 PE5 출력 모드로 설정
}

// ENA : PORTE.5 (OCR3B(PE5) <=== PORTE.4
// IN1 : PORTE.0
// IN2 : PORTE.2

void motor_mode1(int speed)
{
	// 정회전 : PE2:0 | PE0 1
	PORTE &= 0b11111011;  // 모터정지 : PE0:1 | PE2:0
	PORTE |= 0b00000001;
	OCR3C = speed;
		
    
}
void motor_mode2(int speed)
{
	// 역회전 : PE2:1 PE0 0
	PORTE &= 0b11111110;
	PORTE |= 0b00000100;
	OCR3C = speed;
}

void motor_stop()
{
	OCR3C=0;
	PORTE |= 0b00000101;  // 모터정지 : PE0:1 PE2:1
}






