#include <avr/io.h>
#define F_CPU	4000000UL
#include "util/delay.h"

int main(void)
{
	PORTB.DIRCLR = PIN2_bm; //Innstilt som inngang
	
	PORTB.PIN2CTRL = PORT_PULLUPEN_bm; //Aktivert Pullup-motstand
	
	PORTE.DIRSET = 0b00000111; //Port E, pin 0, 1, og 2 innstilt som utganger
	while(1) {
		
		if(!(PORTB.IN & PIN2_bm)) {
			for(int i=0; i<3; i++) {
				PORTE.OUT |= (1<<i);
				_delay_ms(200);
				PORTE.OUT &= ~(1<<i);
			}
		}
		
	}
}