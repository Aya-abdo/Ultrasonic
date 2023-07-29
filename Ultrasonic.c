/*
 * Ultrasonic.c
 *
 * Created: 8/10/2022 11:39:19 PM
 *  Author: MSI
 */ 

#include "LCD.h"
#include "DIO.h"
#define F_CPU 1000000UL
#include <util/delay.h>
#include "STD_macros.h"
#include <avr/io.h>


int main(void)
{
	LCD_init();
	DIO_SET_DIR('D',0,1);
	LCD_send_string("Distance=");
    while(1)
    {
		
		LCD_move_cursor(1,10);
		unsigned short a=0,b=0,distance=0,high=0;
		TCCR1A=0;
		SET_BIT(TIFR,ICF1);
		
		DIO_WRITE('D',0,1);
		_delay_ms(50);
		DIO_WRITE('D',0,0);
        TCCR1B=0xc1;
		while(IS_BIT_CLR(TIFR,ICF1));
		a=ICR1;
		SET_BIT(TIFR,ICF1);
		TCCR1B=0x81;
		while(IS_BIT_CLR(TIFR,ICF1));
	    b=ICR1;
		SET_BIT(TIFR,ICF1);
		TCNT1=0;
		TCCR1B=0;
		
		high=b-a;
	    distance=((high*34600)/(F_CPU*2));
		if (distance<=80)
		{
			
			LCD_send_char((distance/10)+'0');
			LCD_send_char((distance%10)+'0');
			_delay_ms(500);
			
			
		}
		else
		{
			LCD_clear();
			LCD_send_string("wrong range");
			_delay_ms(500);
			LCD_clear();
			LCD_send_string("Distance=");
		}
		
		
		
		
		
    }
}