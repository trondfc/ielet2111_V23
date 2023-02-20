#include <avr/io.h>
#define F_CPU 4000000UL
#include "util/delay.h"

const int LED_PIN = 0b00001000;
const int BTN_PIN = 0b00000100;

int main(void)
{    
	PORTB.DIRSET = LED_PIN; // Set pin 2 on port B as output.
	PORTB.DIRCLR = BTN_PIN; // Set pin 2 on port B as input.
	PORTB.PIN2CTRL = PORT_PULLUPEN_bm;
	
	while(1) // Main loop 
	{
		PORTB.OUT = (PORTB.IN << 1);
	}
}