#define F_CPU 4000000UL // changed from 3333333
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 *(float)BAUD_RATE)) + 0.5)

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include "usart.h"

//#define DBG

int main(void)
{
	USART3_init();	// Init USART3

	uint8_t count = 0;
	while (1)
	{
		#ifdef DBG
			printf("Boring value is: 1\r\n");
		#endif
		printf("Counter value is: %d\r\n", count++);
		_delay_ms(500);
	}

}