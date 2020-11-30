//Jared Spadaro and Jarrett Sack
//CPE123 Section 5 10/17/12
//LAB3
#include <avr/io.h>         //Includes compiler
#include <util/delay.h>     //Includes delay function
#include <avr/interrupt.h>  //Includes interrupt function

int led_status = 0;
int x = 0;
int fade_on = 1;
int led = 0;

ISR (TIMER1_COMPA_vect) {
	
	if(led_status==0) {
		
		PORTD|= (1<<led);
		led_status = 1;
		OCR1A+= x;
		
		
	} else if (led_status==1) {
	     PORTD&=~(1<<led);
		 led_status= 0;
		 OCR1A+= 2000-x;
		if (fade_on==1){	
			x+=1;
			if(x==1990) {
				fade_on=0;
			}
		} else {
			x-=1;
			if (x==15) {
				led++;
				if (led==3) {
					led=0;
				}
				fade_on=1;
			}
		}
	}
}

void initialize_timer(void) {
    TCCR1B = 2;                  //increment timer at 2MHz
    TIMSK1 |= (1 << OCIE1A); //enable output compare match
    sei();                   //enable global interrupts
    }
int main (void) {       //Begins main program
	initialize_timer();
	DDRD|= (1<<PD0);  //Sets pin 0 to output
	DDRD|= (1<<PD1);  //Sets pin 1 to output
	DDRD|= (1<<PD2);  //Sets pin 2 to output
	while (1) {}
	
	
	return 0;
}
	
	