//Jared Spadaro and Jarrett Sack
//CPE123 Section 5 10/17/12
//LAB3
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

int L;
int R;
int O;
int motor_speed;
int set_motor_speed(motor_number, speed){
	if (motor_number == 0){  //These commands
		L= 10*speed + 3000;
	}
	if (motor_number == 1) {
		R = 10*speed + 3000;
	}
	if(motor_speed == 2) {
		O = 10*speed + 3000;
	}
}

unsigned char state = 0;
ISR (TIMER1_COMPA_vect) {
  if (state == 0) {
    state++;
	PORTD|=(1<<PD3);
    OCR1A=L;      //set next interrupt for on time of left motor
  } else if (state == 1) {
    state++;
	PORTD &=~(1<<PD3);
	OCR1A = 12000-L;    //set next interrupt for off time of left motor
  } else if (state == 2) {
    state++;
	PORTD|=(1<<PD7);
	OCR1A = R; //set next interrupt for on time of right motor
  } else if (state == 3) {
    state++;
	PORTD&=~(1<<PD7);
	OCR1A = 12000 - R;
	
  
  
}   else if (state == 5) {
    state = 0;
    
  }
}
void initialize_timer(void) {
    TCCR1B = 2;                  //increment timer at 2MHz
    TIMSK1 |= (1 << OCIE1A); //enable output compare match
    sei();                   //enable global interrupts
    }

int main(void) {
  initialize_timer();
  //set direction and initialize timer
  unsigned char x;

  //accelerate
  for(x=0;x<100;x++) {
    set_motor_speed(0,x); //set left motor speed to x
    set_motor_speed(1,x); //set right motor speed to x
    _delay_ms(50);
	

  }
    for(x=100;x>0;x--) {
    set_motor_speed(0,x); //set left motor speed to x
    set_motor_speed(1,x); //set right motor speed to x
    _delay_ms(50);
	
	
  }  for(x=0;x>-100;x--) {
    set_motor_speed(0,x); //set left motor speed to x
    set_motor_speed(1,x); //set right motor speed to x
    _delay_ms(50);
	
	
  }  for(x=-100;x<0;x++) {
    set_motor_speed(0,x); //set left motor speed to x
    set_motor_speed(1,x); //set right motor speed to x
    _delay_ms(50);
	
	
  }
  

  

  return 0;
}