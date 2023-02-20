#include <avr/io.h>
#define F_CPU 4000000UL
#include "util/delay.h"

const int builtin_led_mask = PIN3_bm;

int main(void)
{    
	PORTB.DIRSET = builtin_led_mask; // Pins on PORTB configured as outputs.
	
	while(1) // Main loop 
	{       
		PORTB.OUTSET = builtin_led_mask;
		_delay_ms(1000);
		PORTB.OUTCLR = builtin_led_mask;
		_delay_ms(1000);

		//Alternative solution:
		/*
		PORTB.OUT |= 1 << 0b0001000;
		_delay_ms(1000);
		PORTB.OUT &= ~(1 << 0b0001000);
		_delay_ms(1000);
		*/

	}
}
