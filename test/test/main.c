/*
 * test.c
 *
 * Created: 29/10/2023 11:48:52
 * Author : Ambrose
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif


int main(void)
{
	
    /* Replace with your application code */
    while (1) 
    {
		
		initUART();
		// call the virtual terminal function
		virtualTerminal();
    }
}


// Initialize UART for ATmega2560
void initUART()
{
	// Set baud rate to 9600 (for 16 MHz frequency)
	UBRR0H = 0;
	UBRR0L = 103;

	// Enable transmitter and receiver
	UCSR0B = (1 << TXEN0) | (1 << RXEN0);

	// Set frame format: 8 data bits, 1 stop bit, no parity
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

	// Debug message
	sendString("UART Initialized at 9600 bps\r\n");
}

// Transmit a character via UART
void sendChar(char data)
{
	// Wait until buffer is empty
	while (!(UCSR0A & (1 << UDRE0)))
	;
	// Put data into buffer, sends the data
	UDR0 = data;
}

// Transmit a string via UART
void sendString(const char *str)
{
	// Loop through each character in the string and send it
	while (*str != '\0')
	{
		sendChar(*str);
		str++;
	}
}

void virtualTerminal()
{
	// Send the sentence over UART
	sendString("Hello, ATmega2560!\r\n");
	_delay_ms(1000); // Delay for 1 second
}

