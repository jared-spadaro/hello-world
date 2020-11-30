//CPE123 Section 5 - Fall 2012
//Lab 4 - Part 1
//Jared Spadaro and Leah Pichay

/*
 Make LED1 blink 1 time on a Volume Up (18)
 Make LED1 blink 2 times on a Volume Down (19)
 Make LED1 blink 3 times on a Channel Up (16)
 Make LED1 blink 4 times on a Channel Down (17)

 Note: 2000 cycles = 1 ms
 For TNCT0 ~63 cyc = 1 ms
 */

#include <avr/io.h>
#include <util/delay.h>
#define SENSOR PD2
#define LED PD3
#define TIME 500

void lab4_initialize_timer0(void){
  TCCR0B |= (1 << CS02);   //set timer 0 to increment at 62.5KHz
}

int main(void){
	DDRD |= (1<<LED);  //set Port D Pin 3 to an output
	lab4_initialize_timer0();  //incorporates the initialize_timer function for timer

	char timeout;
	TCNT0 = 0;     //reset the timer
	unsigned char timeout_delay;  //represents time given for condition to be met
	timeout = 1;   //assume we will get a timeout / if condition not met, reset
	
	char start;  //defines the startbit
	int falling_edge;  //defines whether a bit is high or low
	char current;  //current reading of sensor
	char previous;  //previous reading of sensor
	char data[7];  //databits received from remote
	data[0] = 0;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = 0;
	data[6] = 0;
	data[7] = 0;
	
	while(1){
		if(start==0){  //if start bit is not detected
			previous = 0;  //set previous to 0
			falling_edge = 0;
			while(falling_edge==0){  //if no falling edge is found
				current=(PIND & (1<<SENSOR));  //read sensor
				if(current==0 && previous!=0){  //if current reading differs from previous reading
					falling_edge = 1;  //falling edge is found
				}
				previous = current;  //set previous to current for the the next iteration of the loop
			}
			TCNT0 = 0;  //reset timer
			timeout_delay = 157;  //2.4 ms
			timeout = 1;  //defaults timeout at 1
			while (TCNT0 < timeout_delay){  //gives loop time limit of 2.4 ms
				if(current==0 && previous!=0){  //if current differs from previous
					timeout = 0;  //if it is high, set to no timeout
					timeout_delay = 0;  //break out of this loop
				}
			}
			if(timeout==1){  //if there is a timeout
				start = 1;  //startbit is found, read databits
			} else {  //if there is a timeout
				start = 0;  //find a startbit
			}
		} else {  //when startbit is found
			//PORTD |= (1<<PD3);
			int i;
			for(i=0; i<7; i++){  //runs loop 7 times
				TCNT0 = 0;  //resets timer
				timeout_delay = 75;  //1.2 ms
				timeout = 1;  //defaults timeout at 1
				while (TCNT0 < timeout_delay){  //gives loop time limit of 1.2 ms
					current=(PIND & (1<<SENSOR));  //read sensor
					if(current==0 && previous!=0){  //if current differs from previous reading
						timeout=0;  //if it is high, set to no timeout
						timeout_delay = 0;  //break out of this loop
					}
					previous = current;  //set previous to current for the next iteration
				}
				if(timeout==1){  //if there is a timeout
					start = 0;  //find a startbit
					char x;
					for(x=0;x<7;x++){
						data[x]=0;  //reset databits
					}
				} else if(timeout==0){  //if no timeout is found
					int timeout2 = 1;  //default second timeout to 1
					TCNT0 = 0;  //reset timer
					timeout_delay = 57;  //0.9 ms
					while (TCNT0 < timeout_delay){  //gives loop time limit of 0.9 ms
						current = (PIND & (1<<SENSOR));  //read sensor
						if(current==0 && previous!=0){  //if current differs from previous reading
							start = 0;  //find a startbit
							timeout2 = 0;  //set to no timeout
							char x;
							for(x=0;x<7;x++){
								data[x] = 0;  //reset databits
							}
						}
						previous = current;  //set previous to current for the next iteration
					}
					if(timeout2==1){  //if second timeout is found
						current=(PIND & (1<<SENSOR));  //read sensor
						if(current==0){  //if current reading is 0
							data[i] = 1;  //read which bits are 1
						}
					}
				}
			}
		}
		// blink 2 times
		if( (data[0])==1 && (data[1])==1 && (data[4])==1 ){  //Volume Down
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			
		// blink 1 time
		} else if ( (data[1])==1 && (data[4])==1 ){  //Volume Up
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			
		// blink 4 times
		} else if ( (data[0])==1 && (data[4])==1 ){  //Channel Down
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			
		// blink 3 times
		} else if ( (data[4])==1 ){  //Channel Up
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
			PORTD |= (1<<LED);
			_delay_ms(TIME);
			PORTD &= ~(1<<LED);
			_delay_ms(TIME);
		}
	}
	return 0;  //end program
}