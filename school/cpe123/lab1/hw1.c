//CPE123 - Fall 2012
//Jared Spadaro
#include <avr/io.h>
#include <util/delay.h>

int main (void)   {
	
	while (1) {
	
		DDRD = DDRD | (1<<PD0);  
		DDRD = DDRD | (1<<PD1);  
		DDRD = DDRD | (1<<PD2);
		
		PORTD = PORTD | (1<<PD0);
		PORTD = PORTD & ~ (1<<PD1);
		_delay_ms(1000);
		
		PORTD = PORTD & ~(1<<PD0);
		PORTD = PORTD | (1<<PD1);
		_delay_ms(1000);
		
		PORTD = PORTD & ~ (1<<PD1);
		PORTD = PORTD | (1<<PD2);
		_delay_ms(1000);
		
		PORTD = PORTD & ~ (1<<PD2);
		PORTD = PORTD | (1<<PD1);
		_delay_ms(1000);
		
		
		
	}

	return 0;
	
}