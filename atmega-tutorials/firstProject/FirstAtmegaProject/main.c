/*
 * FirstAtmegaProject.c
 *
 * Created: 19-09-2022 19:49:34
 * Author : keshav
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

//int main(void)
//{
	//DDRD = DDRD | (1<<3);		/* Make PD3 as output pin */
	//DDRD = DDRD & (~(1<<0));		/* Make PD2 as input pin */
	//PORTD = PORTD | (1<<0);		/* Enable pull-up on PD2 by writing 1 to it */
	//int pin_status;
	//while(1)
	//{
		//pin_status = PIND & (1<<0);	/*Read status of pin PD2 */
		//if(pin_status)			/* Transmit status of pin PD2 on to pin PD3 to drive LED. */
		//{
			//PORTD = PORTD | (1<<3);	/* Switch is open, pin_status = 1, LED is ON */
		//}
		//else
		//{
			//PORTD = PORTD & (~(1<<3));	/* Switch is closed, pin_status = 0, LED is OFF */
		//}
	//}
	//return 0;
//}

int main(void)
{
	DDRD = DDRD | 0b00100000;
	DDRD = DDRD & 0b11111110;
	PORTD = PORTD | 0b00000001;
	/* Replace with your application code */
	while (1)
	{
		if((PIND & 0b00000001) > 0) {
			_delay_ms(100);
			PORTD = PORTD & 0b11011111;
			} else {
			_delay_ms(100);
			PORTD = PORTD | 0b00100000;
		}
	}
}