#include <avr/io.h>
#define F_CPU	4000000UL
#include "util/delay.h"

const int buttonPin_bm = PIN2_bm;  // the mask of the pushbutton pin
const int ledPin_bm = PIN3_bm;    // the number of the LED pin

int buttonState = 0;

int main(void)
{
	PORTB.DIRCLR = buttonPin_bm; //PORTB, pin 2 configured as input
	PORTB.PIN2CTRL = PORT_PULLUPEN_bm; //Enable Pullup resistor
	
	PORTB.DIRSET = ledPin_bm; //PORTB, pin 3 configured as output.
	while(1) {
		
		int buttonState = !(PORTB.IN & buttonPin_bm)

		if(buttonState) {
			PORTB.OUTSET = ledPin_bm;
		} else {
			PORTB.OUTCLR = ledPin_bm;
		}
	}
}