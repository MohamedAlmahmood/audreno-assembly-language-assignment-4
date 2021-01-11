/*
 * Mohamed Almahmood
 * V00824909
 * CSC 230
 * Assignment 4
 * This program scrolls through two strings. 
 * If UP button is pressed the scrolling will stop and LEDs will stop blinking.
 * If DOWN button is pressed the scrolling will resume and LEDs will resume.
 * If RIGHT button is pressed the scrolling will speed up and LEDs will blink faster.
 * If LEFT button is pressed the scrolling will slow down and LEDs will blink slower.
 */ 

#include "CSC230.h"
#include <string.h>
#define  ADC_BTN_RIGHT 0x032
#define  ADC_BTN_UP 0x0C3
#define  ADC_BTN_DOWN 0x17C
#define  ADC_BTN_LEFT 0x22B
#define  ADC_BTN_SELECT 0x316

void setup(){
	lcd_init();
}
//This function is copied from lab09_show_adc_result.c
unsigned short poll_adc(){
	unsigned short adc_result = 0; //16 bits
	
	ADCSRA |= 0x40;
	while((ADCSRA & 0x40) == 0x40); //Busy-wait
	
	unsigned short result_low = ADCL;
	unsigned short result_high = ADCH;
	
	adc_result = (result_high<<8)|result_low;
	return adc_result;
}
int check_buttons()
{
	int adc_result = poll_adc();
	
	if(adc_result >= ADC_BTN_RIGHT && adc_result < ADC_BTN_UP)
	{
		return 8; // UP = 8
	}
	if(adc_result >= ADC_BTN_UP && adc_result < ADC_BTN_DOWN)
	{
		return 2; // DOWN = 2
	}
	if(adc_result >= ADC_BTN_DOWN && adc_result < ADC_BTN_LEFT) // LEFT = 4
	{
		return 4;
	}
	if(adc_result < ADC_BTN_RIGHT) // RIGHT = 6
	{
		return 6;
	}
	if(adc_result >= ADC_BTN_LEFT && adc_result < ADC_BTN_SELECT) // SELECT = 5
	{
		return 5;
	}
	return 0;
}

int main(void)
{
	lcd_init();
     char line1[17] = "";
	 char string1[100] = "I did dis! "; 
	 char line2[17] = "";
	 char string2[100] = "YOU are awesome! I wish you a Happy day and a Happy life. ";
	int j = 0;
	int k = 0;
	int a = 0;
	int b = 0;
	int delay_default = 60; //default delay value
	int delay_fast = 20;
	int delay_slow = 120;
	
	//ADC Set up
	ADCSRA = 0x87;
	ADMUX = 0x40;
	while(1)
	{
			j = k; //line 1
			a = b; //line 2
			
		//Loop for line 1:	
			for(int i=0; i<16; i++)
			{
			
				if(string1[j] != 0)
				{
					line1[i] = string1[j];
					j++;
				}
				else
				{
					j=0;
					line1[i] = string1[j];
					j++;
				}
			}
		
			//Loop for line 2:
			for (int i=0; i<16; i++)
			{
				if(string2[a] != 0)
				{
					line2[i] = string2[a];
					a++;
				}
				else
				{
					a=0;
					line2[i] = string2[a];
					a++;
				}
			}
		
			lcd_command( 0x01 );
			lcd_xy(0,0); //start at column 0, first row  
			lcd_puts(line1);
			lcd_xy(0,1);
			lcd_puts(line2);
		
			//Check buttons
			if(check_buttons() == 8)//UP
			{
				while(1)
				{
					if(check_buttons() == 2)//DOWN
					{
					break;
					}
				}
			}
		
			//Check for line 1:
			if(k < strlen (string1))
			{	
				k++;	
			}
			else
			{
				k=0;
			}
		
			//Check for line 2:
			if(b < strlen (string2))
			{
				if(check_buttons() == 6)// INCREASE SCROLLING SPEED IF RIGHT BUTTON IS HELD
				{
					PORTB = 2; //one light turns on for slow scrolling.
					_delay_ms(delay_fast);
					PORTB = 8;
					_delay_ms(delay_fast);
					PORTL = 2;
					_delay_ms(delay_fast);
					PORTL = 8;
					_delay_ms(delay_fast);
					PORTL = 32;
					_delay_ms(delay_fast);
					PORTL = 128;
					_delay_ms(delay_fast);
					PORTB = 0;
					PORTL = 0;

					
				}
				else if(check_buttons() == 4)// DECREASE SCROLLING SPEED IF LEFT BUTTON IS HELD
				{
					PORTB = 2; //one light turns on for slow scrolling.
					_delay_ms(delay_slow);
					PORTB = 8;
					_delay_ms(delay_slow);
					PORTL = 2;
					_delay_ms(delay_slow);
					PORTL = 8;
					_delay_ms(delay_slow);
					PORTL = 32;
					_delay_ms(delay_slow);
					PORTL = 128;
					_delay_ms(delay_slow);
					PORTB = 0;
					PORTL = 0;
				}else
				{
					PORTB = 2; //one light turns on for slow scrolling.
					_delay_ms(delay_default);
					PORTB = 8;
					_delay_ms(delay_default);
					PORTL = 2;
					_delay_ms(delay_default);
					PORTL = 8;
					_delay_ms(delay_default);
					PORTL = 32;
					_delay_ms(delay_default);
					PORTL = 128;
					_delay_ms(delay_default);
					PORTB = 0;
					PORTL = 0;
				}
			
				b++;
			}
			else
			{
				b=0;
			}
		
	
	
	}
}
