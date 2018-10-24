/*
 * motor-switch-led-avr-atmega32.c
 *
 * Created: 10/21/2018 12:14:29 PM
 * Author : ashumeow
 */ 
#include <avr/io.h>
#define get_bit(reg,bitnum) ((reg & (1<<bitnum))>>bitnum)
int main(void)
{
	DDRD=0b11111000; // set the first 3 pins of PORTD to be inputs to read from the push buttons
	DDRB=0b11111111; // ensure that Pin3 in POrt B is output as this is the OC0 pin that will produce the PWM
	PORTD=0b00000000; // Initialize PORTD to zeros
	TCCR0=0b01110101; //Configure TCCR0
	TIMSK=0b00000000;
	DDRC = 0x00; //Makes PORTC as Output
	OCR0=255; // Set OCR0 to 255 so that the duty cycle is initially 0 and the motor is not rotating
	while (1)
	{
		if (get_bit(PIND,0)==1)
		{
			DDRC= 0xFF; //Turns ON LED
			OCR0=102; //duty cycle=60%
			} else if(get_bit(PIND,0)==0) {
			DDRC= 0x00; //Turns OFF LED
			OCR0=255;
			} else {
			// do nothing
		}
	}
}

