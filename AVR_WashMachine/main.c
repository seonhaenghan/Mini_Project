/*
 * washing_machine.c
 *
 * Created: 2022-08-13 오전 11:47:33
 * Author : seonhaeng han
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdio.h> // printf, scanf 등이 정의 되어 있다.
#include <string.h> // strcpy, strcat, strcmp 등이 들어 있음

void init_timer0();
void manual_mode();
void auto_mode();
void manual_mode_set();
void time_mode_set();
void speed_mode_set();
void motor_sq1(int time1,int speed);
void motor_sq2(int time1,int speed);
void motor_sq3(int time1,int speed);
void sq_choice(int a, int b, int c);
int speed_sq();
int time1_sq();

extern int get_BUTTON1();
extern int get_BUTTON2();
extern int get_BUTTON3();
extern int get_BUTTON4();

extern void motor_init();
extern void motor_mode1(int speed);
extern void motor_mode1(int speed);
extern void motor_stop();

extern void init_led(); 
extern void led_toggle1();
extern void led_toggle2();
extern void led_toggle3();

extern void init_fnd(void);
extern void display_fnd();
extern void set_fnd_data(uint16_t data);

extern void init_speaker(void);
extern void Music_Player(int *tone, int *Beats);
extern void Beep(void);
extern const int School_Bell_Tune[];
extern const int School_Bell_Beats[];
extern const int Elise_Tune[];
extern const int Elise_Beats[];

volatile uint32_t ms_cnt = 0;
volatile uint32_t ms_lcnt = 0;
volatile uint32_t s_cnt = 0;
volatile uint16_t time_cnt = 0; 



volatile int manual_auto_state = 0; 

int speed, time1 = 0;
int button_cnt = 1; 
int button_cnt2 = 1; 
int button_cnt3 = 1; 

extern int led_toggle; 




ISR(TIMER0_OVF_vect) // 인터럽트 루틴을 길게 짤 수록 output delay가 증가하여 원하는 시간에 출력이 나오지 않음
{
	TCNT0 = 6; // TCNT를 6~256 == > 정확히 1ms 를 유지하기 위해
	ms_cnt++;				// 1ms 마다 1씩증가
	ms_lcnt++;
	if(ms_cnt >= 1000)
	{
		ms_cnt=0;
		s_cnt++;			// 1000ms 마다 1씩 증가
		time_cnt--;  
		if(manual_auto_state == 0 || manual_auto_state == 1)
		{
			
			time_cnt = 0; 
		}
	}
	
	if(manual_auto_state == 2 )	
	{
		if(ms_cnt % 4)
		{
			display_fnd();
		}
	}
	
	
}

char sbuf[40];

int main(void)
{
   init_timer0();
   motor_init();
   init_led();
   I2C_LCD_init();
   init_fnd();
   init_speaker();
   sei();
   
	while(1)
	{

		if(manual_auto_state == 0)
		{
			
			led_toggle3();
		}
		else if (manual_auto_state == 1)
		{
			
			led_toggle1();
		}
		else if (manual_auto_state == 2)
		{
			
			led_toggle2();
		}
		
		if(manual_auto_state == 0)
		{
			
			manual_mode_set();
			speed_mode_set();
			time_mode_set();
			
		}
		
		if(manual_auto_state == 1)
		{
			
			led_toggle1();
			if(get_BUTTON4())	// 실행이 완료된 후 처음 화면으로
			{
				Music_Player(Elise_Tune, Elise_Beats);
				manual_auto_state = 0;
				
				init_fnd();
				
			}
		}
		
		int a = button_cnt;
		int c = button_cnt2;
		int b = button_cnt3;
		
		if(c == 1)
		{
			c = 110;
		}
		else if(c == 2)
		{
			c = 170;
		}
		else if(c == 3)
		{
			c = 250;
		}
		
		if(get_BUTTON4())
		{
			Music_Player(Elise_Tune, Elise_Beats);
			if(manual_auto_state ==0)
			{
				s_cnt = 0;
				// auto mode 시간 표시 
				if(button_cnt == 4)
				{
					time_cnt = 20;
				}
				else
				{
					time_cnt = b * 10;
				}
				
				manual_auto_state = 2; // start set
			}
			
		}
		
		if(manual_auto_state == 2)
		{
			I2C_LCD_write_string_XY(0,0, "                ");
			if(button_cnt == 1)
			{
				sprintf(sbuf,"only wash run!!");
			}
			else if(button_cnt == 2)
			{
				sprintf(sbuf,"only dry run!!");
			}
			else if(button_cnt == 3)
			{
				sprintf(sbuf,"wash + dry run!!");
			}
			else if(button_cnt == 4)
			{
				sprintf(sbuf,"Auto mode run!!");
			}
			I2C_LCD_write_string_XY(0,0,sbuf);
			I2C_LCD_write_string_XY(1, 0, "                ");
			sprintf(sbuf, "   stop = BT4");
			I2C_LCD_write_string_XY(1, 0, sbuf);
			
			sq_choice(a, b, c);
			if(manual_auto_state == 1)
			{
				init_fnd();
				
				I2C_LCD_write_string_XY(0,0, "                ");
				sprintf(sbuf," ===finish===");
				I2C_LCD_write_string_XY(0,0,sbuf);
				I2C_LCD_write_string_XY(1, 0, "                ");
				sprintf(sbuf, " RESET = BT4");
				I2C_LCD_write_string_XY(1, 0, sbuf);

			}
			
			if(get_BUTTON4()) // 실행 중 정지 
			{
				Music_Player(Elise_Tune, Elise_Beats);
				manual_auto_state = 0;
				motor_stop();
				init_fnd();
			
			}
		}
	}
}

void auto_mode()
{
	
		if(s_cnt < 10)
		{
			motor_mode1(speed);
		}
		else if(s_cnt >= 10 && s_cnt <13)
		{
			motor_mode2(speed);
		}
		else if(s_cnt >= 13 && s_cnt < 16)
		{
			motor_mode1(speed);
		}
		else if(s_cnt >= 16 && s_cnt <= 19)
		{
			motor_mode2(speed);
		}
		else if(s_cnt > 20)
		{
			
			motor_stop(speed);
			
			 manual_auto_state = 1;
			 init_fnd();
			 Music_Player(School_Bell_Tune, School_Bell_Beats);
			 
		}
	
}

void manual_mode_set()
{
	
	if(get_BUTTON1())
	{
		Music_Player(Elise_Tune, Elise_Beats);
		button_cnt++;
		if(button_cnt > 4 )
		{
			button_cnt = 1;
		}
		
		I2C_LCD_write_string_XY(0,0, "                ");
		if(button_cnt == 1)
		{
			sprintf(sbuf,"only wash");
		}
		else if(button_cnt == 2)
		{
			sprintf(sbuf,"only dry");
		}
		else if(button_cnt == 3)
		{
			sprintf(sbuf,"wash + dry");
		}
		else if(button_cnt == 4)
		{
			sprintf(sbuf,"Auto mode");
		}
		I2C_LCD_write_string_XY(0,0,sbuf);
		I2C_LCD_write_string_XY(1, 0, "                ");
		if(button_cnt == 4)
		{
			sprintf(sbuf, "pwr:%d  time:%d", 2, 20);
		}
		else
		{
			sprintf(sbuf, "pwr:%d  time:%d", button_cnt2, button_cnt3 * 10);
		}
		
		I2C_LCD_write_string_XY(1, 0, sbuf);
	}
	
}

void speed_mode_set()
{
	
		if(get_BUTTON2())
		{
			Music_Player(Elise_Tune, Elise_Beats);
			button_cnt2++;
			if(button_cnt2 > 3 )
			{
				button_cnt2 = 1;
			}
			I2C_LCD_write_string_XY(0,0, "                ");
			if(button_cnt == 1)
			{
				sprintf(sbuf,"only wash");
			}
			else if(button_cnt == 2)
			{
				sprintf(sbuf,"only dry");
			}
			else if(button_cnt == 3)
			{
				sprintf(sbuf,"wash + dry");
			}
			else if(button_cnt == 4)
			{
				sprintf(sbuf,"Auto mode");
			}
			I2C_LCD_write_string_XY(0,0,sbuf);
			I2C_LCD_write_string_XY(1, 0, "                ");
			if(button_cnt == 4)
			{
				sprintf(sbuf, "pwr:%d  time:%d", 2, 20);
			}
			else
			{
				sprintf(sbuf, "pwr:%d  time:%d", button_cnt2, button_cnt3 * 10);
			}
			
			I2C_LCD_write_string_XY(1, 0, sbuf);
		}
	
	
}

void time_mode_set()
{
	
		if(get_BUTTON3())
		{
			Music_Player(Elise_Tune, Elise_Beats);
			
			button_cnt3++;
			
			if(button_cnt3 > 5 )
			{
				button_cnt3 = 1;
			}
		}
		I2C_LCD_write_string_XY(0,0, "                ");
		if(button_cnt == 1)
		{
			sprintf(sbuf,"only wash");
		}
		else if(button_cnt == 2)
		{
			sprintf(sbuf,"only dry");
		}
		else if(button_cnt == 3)
		{
			sprintf(sbuf,"wash + dry");
		}
		else if(button_cnt == 4)
		{
			sprintf(sbuf,"Auto mode");
		}
		I2C_LCD_write_string_XY(0,0,sbuf);
		I2C_LCD_write_string_XY(1, 0, "                ");
		if(button_cnt == 4)
		{
			sprintf(sbuf, "pwr:%d  time:%d", 2, 20);
		}
		else
		{
			sprintf(sbuf, "pwr:%d  time:%d", button_cnt2, button_cnt3 * 10);
		}
		
		I2C_LCD_write_string_XY(1, 0, sbuf);
	
	
}

void init_timer0() // timer0 초기화
{
	DDRF = 0x01 + 0x02 + 0x04;
	
	PORTF |= 0x02;
	
	TCCR0 |= (1 << CS02) | (0 << CS01) | (0 << CS00);  //  분주비를 64로 설정
	
	TIMSK |= (1 << TOIE0);
	
	TCNT0 = 6;
}

void motor_sq1(int time1, int speed) // 세탁
{
	
	
		if(s_cnt <= time1) 
		{
			motor_mode1(speed);
			
		}

		else
		{
			motor_stop();
			
			  manual_auto_state = 1;
			  init_fnd();
			  Music_Player(School_Bell_Tune, School_Bell_Beats);
		}
}

void motor_sq2(int time1, int speed) // 탈수 
{
	
	int time2 = time1 / 5;
	
		if(s_cnt <= time2)
		{
			motor_mode1(speed);
		}
		
		else if(s_cnt > time2 && s_cnt <= time2*2)
		{
			motor_mode2(speed);
		}
		else if(s_cnt > time2*2 && s_cnt <= time2*3)
		{
			motor_mode1(speed);
		}
		else if(s_cnt > time2*3 && s_cnt <= time2*4)
		{
			motor_mode2(speed);
		}
		else if(s_cnt > time2*4 && s_cnt <= time2*5)
		{
			motor_mode1(speed);
		}
		else
		{
			motor_stop();	
			
			  manual_auto_state = 1;
			  init_fnd();
			  Music_Player(School_Bell_Tune, School_Bell_Beats);
		}
		
}

void motor_sq3(int time1, int speed)	// 세탁 + 탈수 
{
	time1 = time1 / 10; 
		if(s_cnt <= time1*5)
		{
			motor_mode1(speed);
		}
		
		else if(s_cnt > time1*5 && s_cnt <= time1*6)
		{
			motor_mode2(speed);	
		}
		else if(s_cnt > time1*6 && s_cnt <= time1*7)
		{
			motor_mode1(speed);
		}
		else if(s_cnt > time1*7 && s_cnt <= time1*8)
		{
			motor_mode2(speed);
		}
		else if(s_cnt > time1*8 && s_cnt <= time1*9)
		{
			motor_mode1(speed);
		}
		else if(s_cnt > time1*9 && s_cnt <= time1*10)
		{
			motor_mode2(speed);
		}
		else
		{
			motor_stop();
			
			manual_auto_state = 1; 
			init_fnd();
			Music_Player(School_Bell_Tune, School_Bell_Beats);
		}
}
void sq_choice(int a, int b, int c)
{
		
		
		if(a == 1)
		{
			motor_sq1(b*10, c);
		}
		else if(a == 2)
		{
			motor_sq2(b*10, c);
		}
		else if(a == 3)
		{
			motor_sq3(b*10, c);
		}
		else if(a == 4)
		{
			speed = 170;
			
			auto_mode();
		}
	
	
}