//CPE123 - Fall 2012
//Lab 1 - part 3
//Jared Spadaro and Ryan Gelston
//This program will cause 3 LED lights connected to Port D pins 0, 1, and 2 to light up 
//in such a way that they will count in binary from 0 to 7 and back to 0, and so on in an 
//endless loop.

#include <avr/io.h>  //This includes the compiler into the function
#include <util/delay.h>  //This includes the delay function into the program

int main (void) {  //Begins main program
	
	while (1){    //This sets everything within the bracket into an infinite loop
		
		DDRD = DDRD | (1<<PD0);  //Sets pin 0 on Port D to output
		DDRD = DDRD | (1<<PD1);  //Sets pin 1 on Port D to output
		DDRD = DDRD | (1<<PD2);  //Sets pin 2 on Port D to output
	
		PORTD = PORTD | (1<<PD0);  //Sets pin 0 on Port D to high for 1 second
		PORTD = PORTD & ~(1<<PD1); //Sets pin 1 to low for 1 second
		PORTD = PORTD & ~(1<<PD2); //Sets pin 2 to low for 1 second
		_delay_ms(1000);
	
		PORTD = PORTD & ~(1<<PD0); //Sets pin 0 on Port D to low for 1 second
		PORTD = PORTD | (1<<PD1);  //Sets pin 1 on Port D to high for 1 second
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
		
		//half rotation
	
		PORTD = PORTD | (1<<PD1);   //Sets pin 1 to high for 1 second
		PORTD = PORTD | (1<<PD2);   //Sets pin 2 to high for 1 second
		PORTD = PORTD & ~(1<<PD0);  //Sets pin 0 to low for 1 second
		_delay_ms(1000);
	
		PORTD = PORTD & ~(1<<PD1);  //Sets pin 1 to low for 1 second
		PORTD = PORTD | (1<<PD0);   //Sets pin 0 to high for 1 second
		PORTD = PORTD | (1<<PD2);   //Sets pin 2 to high for 1 second
		_delay_ms(1000);
	
		PORTD = PORTD & ~(1<<PD0);  //Sets pin 0 to low for 1 second
		PORTD = PORTD & ~(1<<PD1);  //Sets pin 1 to low for 1 second
		PORTD = PORTD | (1<<PD2);   //Sets pin 2 to high for 1 second
		_delay_ms(1000);
	
		PORTD = PORTD & ~(1<<PD2); //Sets pin 2 to low for 1 second
		PORTD = PORTD | (1<<PD0);  //Sets pin 0 to high for 1 second
		PORTD = PORTD | (1<<PD1);  //Sets pin 1 to high for 1 second
		_delay_ms(1000);
	
		PORTD = PORTD & ~(1<<PD0); //Sets pin 0 to low for 1 second
		PORTD = PORTD | (1<<PD1);  //Sets pin 1 to high for 1 second
		PORTD = PORTD & ~(1<<PD2); //Sets pin 2 to low for 1 second
		_delay_ms(1000);
		
		PORTD = PORTD | (1<<PD0);  //Sets pin 0 to high for 1 second
		PORTD = PORTD & ~(1<<PD1); //Sets pin 1 to low for 1 second
		PORTD = PORTD & ~(1<<PD2); //Sets pin 2 to low for 1 second
		_delay_ms(1000);
		
		PORTD = PORTD & ~(1<<PD0);  //This paragraph sets all pins to low
		PORTD = PORTD & ~(1<<PD1);
		PORTD = PORTD & ~(1<<PD2);
		_delay_ms(1000);
		
	}
	return 0;  //End program
}
	
	