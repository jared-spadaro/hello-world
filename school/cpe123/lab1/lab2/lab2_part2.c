//CPE123 - Fall 2012

//Lab 2 - part 1

//Jarrett Sack and Jared Spadaro

//Turns the LED on and off 5 times after button is pressed.
#include <avr/io.h>
#include <util/delay.h>
int x = 0;     // variable for reading the button status

int main(void){
	DDRD = DDRD |(1 <<PD4); //Sets Output
	
	while(1){
		if((PIND & (1 << PD3)) != (1 << PD3)){ //If button is pressed executes code below
			for (x = 0; x < 5; x++){ //For loop that sets x equal to 0, adds one to x, and then continues until x = 5
				PORTD = PORTD | (1<<PD4); //Turns LED on
				_delay_ms(1000);//Delays for 1 second
				PORTD = PORTD & ~(1 << PD4); //Turns led off
				_delay_ms(1000); //Delays for 1 second
				}
			}
		}
    return 0;
}
