#define F_CPU 4000000UL
#define USART3_BAUD_RATE(BAUD_RATE) ((float)(F_CPU * 64 / (16 *(float)BAUD_RATE)) + 0.5)

#define MAX_COMMAND_LEN 9
#define NUMBER_OF_COMMANDS 4

#define CR 0x0D	// '\r'
#define LF 0x0A // '\n'

#define LED1_PIN_bm PIN0_bm
#define LED2_PIN_bm PIN1_bm

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include <stdio.h>
#include <string.h>

//Prototypes
void USART3_init(void);
void USART3_sendChar(char c);
static int USART3_printChar(char c, FILE *stream);
void USART3_sendString(char *str);
uint8_t USART3_read();
uint8_t compareCommands(char* src);

// Setting up FDEV_SETUP_STREAM to use USART3_printChar
static FILE USART_stream = FDEV_SETUP_STREAM(USART3_printChar, NULL, _FDEV_SETUP_WRITE);

// Array of commands to compare to
static char commands[NUMBER_OF_COMMANDS][MAX_COMMAND_LEN] = {
	"ledon 1",
	"ledon 2",
	"ledoff 1",
	"ledoff 2"
};

// Init function
void USART3_init(void)
{
	PORTB.DIRSET = PIN0_bm; // Set TX pin to output
	PORTB.DIRCLR = PIN1_bm; // Set RX pin to input

	USART3.BAUD = (uint16_t)USART3_BAUD_RATE(9600);	// Set Baud rate 9600
	USART3.CTRLB |= USART_TXEN_bm | USART_RXEN_bm;
	
	stdout = &USART_stream;	//Replacing output stream
}

// Function to send char
void USART3_sendChar(char c)
{
	while (!(USART3.STATUS & USART_DREIF_bm)) //while data register not empty
	{
		;
	}
	USART3.TXDATAL = c;
}
// Wrapping USART3_sendChar in a function computable with FDEV_SETUP_STREAM
static int USART3_printChar(char c, FILE *stream)
{
	USART3_sendChar(c);
	return 0;
}

// Function to send string
void USART3_sendString(char *str)
{
	for(size_t i = 0; i < strlen(str); i++)
	{
		USART3_sendChar(str[i]);
	}
}

// Function to read received char
uint8_t USART3_read()
{
	while (!(USART3.STATUS & USART_RXCIF_bm))
	{
		;
	}
	uint8_t src = USART3.RXDATAL;
	USART3_sendChar(src);
	return src;
}

uint8_t compareCommands(char* src)
{
	// Return index of command received or 255 if none
	for(uint8_t i = 0; i < NUMBER_OF_COMMANDS; i++){
		if(strcmp(src, commands[i]) == 0){
			return i;
		}
	}
	return 255;
}

// Function to exicute command using switc case
void executeCommand(uint8_t command_number)
{
	switch(command_number)
	{
		case 0:
			PORTD.OUTSET = PIN0_bm;
			printf("ledon 1 \r\n");
		break;
		
		case 1:
			PORTD.OUTSET = PIN1_bm;
			printf("ledon 2 \r\n");
		break;
		
		case 2:
			PORTD.OUTCLR = PIN0_bm;
			printf("ledoff 1 \r\n");
		break;
		
		case 3:
			PORTD.OUTCLR = PIN1_bm;
			printf("ledoff 2 \r\n");
		break;
		
		default:
			printf("unknown command\r\n");
	}
}


int main(void)
{
	char command[MAX_COMMAND_LEN];
	uint8_t index = 0;
	char c;

	/* Set the LED pins as output. */
	PORTD.DIRSET = LED1_PIN_bm | LED2_PIN_bm; 

	USART3_init();
	
	/* This delay invalidates the initial noise on the TX line, after device reset. */
	_delay_ms(10);
	
	while (1)
	{
		c = USART3_read();
		if(c != LF && c != CR){	// If received \r or \n
			command[index++] = c;
			if(index > MAX_COMMAND_LEN)
			{
				printf("\r\n");
				index = 0;
			}
		}
		if(c == CR){	// if recived \r
			command[index] = 0;
			index = 0;
			printf("Received command: ");
			executeCommand(compareCommands(command));
		}
	}
}