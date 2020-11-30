//CPE123 Section 5 - Fall 2012
//Lab 4 - Part 2
//Jared Spadaro and Leah Pichay

/*
 Robot drives using the controls Volume Up (18), Volume Down (19), Channel Up (16), and Channel Down (17)

 Note: 2000 cycles = 1 ms
 For TNCT0 ~63 cyc = 1 ms
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#define SENSOR PD6
#define LED PD7
#define LEFT_MOTOR PD2
#define RIGHT_MOTOR PD3
#define TIME 100

int L;
int R;
unsigned int state = 0;

// enter a number from -100 to 100 to output 2000 to 4000 
int set_motor_speed(motor_number, speed){
	if (motor_number==0){  //left motor
		L=10*speed + 3000;  //speed of left motor
	} else if (motor_number==1){  //right motor
		R=10*speed + 3000;  //speed of right motor
	}
}

void initialize_timer(void){
 	TCCR1B = 2;                  	// Increment timer at 2MHz
	TIMSK1 |= (1 << OCIE1A);	// Enable output compare match
	sei();                  	// Enable global interrupts
}

void lab4_initialize_timer0(void){
  TCCR0B |= (1 << CS02);   //set timer 0 to increment at 62.5KHz
}

// allows the motors to run, defining the speed
ISR(TIMER1_COMPA_vect){
	if(state==0){
		PORTD |= (1<<LEFT_MOTOR);
		OCR1A+=L;
		state = 1;
	}
	else if(state==1){
		PORTD &= ~(1<<LEFT_MOTOR);
		OCR1A+=12000-L;
		state = 2;
	}
	else if(state==2){
		PORTD |= (1<<RIGHT_MOTOR);
		OCR1A+=R;
		state = 3;
	}
	else{
		PORTD &= ~(1<<RIGHT_MOTOR);
		OCR1A+=12000-R;
		state = 0;
	}
}

int main(void){
	DDRD |= (11111<<LEFT_MOTOR);  //set Port D Pin 3 to an output
	lab4_initialize_timer0();  //incorporates the initialize_timer function for timer
	initialize_timer();

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
	int reading;
	
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
		int y = 20;  //speed of motors
		int z;
		reading = 0;  //number value of databits
		for(z=0;z<7;z++){
			if(data[z]==1){ 
				reading |= (1 << z);
			}
		}
		if(reading==19){  //Volume Down
			set_motor_speed(0,-y);
			set_motor_speed(1,y);
		} else if(reading==18){  //Volume Up
			set_motor_speed(0,y);
			set_motor_speed(1,-y);
		} else if(reading==17){  //Channel Down
			set_motor_speed(0,0);
			set_motor_speed(1,y);
		} else if(reading==16){  //Channel Up
			set_motor_speed(0,y);
			set_motor_speed(1,0);
		}
	}
	return 0;  //end program
}