/*
 * ielet2111_function_demo.c
 *
 * Created: 25.01.2023 11:52:46
 * Author : crfosse
 */ 

#define F_CPU 4000000UL

#include <avr/io.h>
#include <util/delay.h>

void light_led(int pin);
void unlight_led(int pin);

int main(void)
{
	PORTE.DIR = 0b00000111;
    /* Replace with your application code */
    while (1) 
    {
		int led_pin = 1;
		
		light_led(0);
		_delay_ms(100);
		unlight_led(0);
		_delay_ms(100);
    }
}

void light_led(int pin) {
	
	PORTE.OUTSET = (1 << pin) | (1 << (pin+1));
		
}

void unlight_led(int pin) {
	
	PORTE.OUTCLR = (1 << pin) | (1 << (pin+1));
	
}
