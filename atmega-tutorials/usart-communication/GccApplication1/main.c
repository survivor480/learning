/*
 * GccApplication1.c
 *
 * Created: 26-09-2022 16:42:14
 * Author : kesha
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CHAR_BUFF_SIZE  20
#define BAUD_RATE		19200


void serial_init(unsigned short ubrr){
	UBRR0H = 0;					// Set high bit as 0
	UBRR0L = ubrr;				// Set low bit from input
	UCSR0B |= (1 << TXEN0);		// Turn on transmitter
	UCSR0B |= (1 << RXEN0);		// Turn on receiver
	UCSR0C |= (3 << UCSZ00);	// Set for aync. operation, no parity
}								// one stop bit, 8 data bits

unsigned long serial_initialise(unsigned long baud_rate) {
	unsigned long temp_1 = F_CPU / 16;
	unsigned long temp_2 = temp_1 / baud_rate;
	unsigned long ubrr = temp_2 - 1;
	return ubrr;
}

void serial_out(char ch){
	while(( UCSR0A & ( 1 << UDRE0 )) == 0);
	UDR0 = ch;
}

char serial_in() {
	while(!(UCSR0A & (1 << RXC0)));
	return UDR0;
}

void serial_print_string(char *character){
	int length = strlen(character);
	for(int i=0; i<length; i++){
		serial_out(character[i]);
	}
}

void serial_print_int(long num){
	char string_print[50];
	sprintf(string_print, "%ld", num);
	int num_length = strlen(string_print);
	for(int i=0; i<num_length; i++){
		serial_out(string_print[i]);
	}
}

static char * _float_to_char(float x, char *p) {
	char *s = p + CHAR_BUFF_SIZE; // go to end of buffer
	uint16_t decimals;  // variable to store the decimals
	int units;  // variable to store the units (part to left of decimal place)
	if (x < 0) { // take care of negative numbers
		decimals = (int)(x * -100) % 100; // make 1000 for 3 decimals etc.
		units = (int)(-1 * x);
		} else { // positive numbers
		decimals = (int)(x * 100) % 100;
		units = (int)x;
	}

	*--s = (decimals % 10) + '0';
	decimals /= 10; // repeat for as many decimal places as you need
	*--s = (decimals % 10) + '0';
	*--s = '.';

	while (units > 0) {
		*--s = (units % 10) + '0';
		units /= 10;
	}
	if (x < 0) *--s = '-'; // unary minus sign for negative numbers
	return s;
}

void serial_print_float(float x){
	char *temp="";
	char *print_float = _float_to_char(x, temp);
	serial_print_string(print_float);
}


int main(void)
{
	char *serial_show;
    /* Replace with your application code */
	DDRD = DDRD & 0b00000111;
	PORTD = PORTD | 0b11111000;
	
	serial_init(serial_initialise(BAUD_RATE));
	
    while (1) 
    {
		if((PIND & 0b00001000) > 0){
			serial_show = "LED 0 is active\n";
			serial_print_string(serial_show);
		}
		if((PIND & 0b00010000) > 0){
			serial_show = "LED 1 is active\n";
			serial_print_string(serial_show);
		}
		if((PIND & 0b00100000) > 0){
			serial_show = "LED 2 is active\n";
			serial_print_string(serial_show);
		}
		if((PIND & 0b01000000) > 0) {
			serial_show = "LED 3 is active\n";
			serial_print_string(serial_show);
		}
		if((PIND & 0b10000000) > 0){
			serial_show = "LED 4 is active\n";
			serial_print_string(serial_show);
		}
		
		serial_show = "\n\n\n\n\n\n";
		serial_print_string(serial_show);
		_delay_ms(2000);
    }
}

