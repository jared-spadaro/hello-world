//CPE123 - Fall 2012
//Lab 1 - part 2
//Jared Spadaro and Ryan Gelston
//This program will cause 3 LED lights connected to Port D pins 0, 1, and 2 to light up 
//in such a way that they will "count" 1 to 7 in binary.
#include <avr/io.h> //Includes compiler into program
#include <util/delay.h> //Includes delay function into program
int main (void) { //Begins main program
	
	DDRD = DDRD | (1<<PD0);  //Sets pin 0 on Port D to output
	DDRD = DDRD | (1<<PD1);  //Sets pin 1 on Port D to output
	DDRD = DDRD | (1<<PD2);  //Sets pin 2 on Port D to output
	
	PORTD = PORTD | (1<<PD0);  //Sets pin 0 to high for 1 second
	PORTD = PORTD & ~(1<<PD1); //Sets pin 1 to low for 1 second
	PORTD = PORTD & ~(1<<PD2); //Sets pin 2 to low for 1 second
	_delay_ms(1000);
	
	
	PORTD = PORTD & ~(1<<PD0); //Sets pin 0 to low for 1 second
	PORTD = PORTD | (1<<PD1);  //Sets pin 1 to high for 1 second
	PORTD = PORTD & ~(1<<PD2); //Sets pin 2 to low for 1 second
	_delay_ms(1000);
	
	PORTD = PORTD | (1<<PD0);  //Sets pin 0 to high for 1 second
	PORTD = PORTD | (1<<PD1);  //Sets pin 1 to high for 1 second
	_delay_ms(1000);
	
	PORTD = PORTD & ~(1<<PD0);  //Sets pin 0 to low for 1 second
	PORTD = PORTD & ~(1<<PD1);  //Sets pin 1 to low for 1 second
	PORTD = PORTD | (1<<PD2);   //Sets pin 2 to high for 1 second
	_delay_ms(1000);
	
	PORTD = PORTD | (1<<PD0);   //Sets pin 0 to high for 1 second
	PORTD = PORTD | (1<<PD2);   //Sets pin 2 to high for 1 second
	_delay_ms(1000);
	
	PORTD = PORTD | (1<<PD1);   //Sets pin 1 to high for 1 second
	PORTD = PORTD | (1<<PD2);   //Sets pin 2 to high for 1 second
	PORTD = PORTD & ~(1<<PD0);  //Sets pin 0 to low for 1 second
	_delay_ms(1000);
	
	PORTD = PORTD | (1<<PD0);   //Sets pin 0 to high for 1 second
	PORTD = PORTD | (1<<PD1);   //Sets pin 1 to high for 1 second
	PORTD = PORTD | (1<<PD2);   //Sets pin 2 to high for 1 second
	_delay_ms(1000);
	
	
	
	return 0;  //Ends program.
}