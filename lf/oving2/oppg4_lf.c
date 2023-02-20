// All references to USART1 replaced with USART3

#define F_CPU 4000000UL // changed from 3333333
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 *(float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

// Prototypes
void USART3_init(void);
void USART3_sendChar(char c);
void USART3_sendString(char *str);

void USART3_init(void)
{
	PORTB.DIRSET = PIN0_bm; //TX-pin as  output, changed from PORTC.DIR |= PIN0_bm;
	PORTB.DIRCLR = PIN1_bm; //RX-pin as  input, changed from PORTC.DIR &= ~PIN1_bm;

	USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600);
	USART3.CTRLB |= USART_TXEN_bm;
}

void USART3_sendChar(char c)
{
	while (!(USART3.STATUS & USART_DREIF_bm))	//wait while USART3 Data Register not empty
	{
		;
	}
	USART3.TXDATAL = c;	// Send c
}

void USART3_sendString(char *str)
{
	for(size_t i = 0; i < strlen(str); i++)	//Send each cahr in str using USART3_sendString()
	{
		USART3_sendChar(str[i]);
	}
}

int main(void)
{	
	USART3_init();	// Intit USART3

	while (1)
	{
		USART3_sendString("Hello World!\r\n");	//Send string
		_delay_ms(500);
	}
}
