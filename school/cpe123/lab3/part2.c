//Jared Spadaro and Carmen Dang
//CPE123 Section 5 10/29/12
//LAB3
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>

void initialize_adc(void) {
  ADCSRA |= (1<<ADPS2) |  (1<<ADPS1) |  (1<<ADPS0);  //set prescalar
  ADMUX |= (1<<REFS0);  //set reference voltage
  ADMUX |= (1<<ADLAR);  //left align data
  ADCSRA |= (1<<ADEN);  //enable ADC
}

unsigned char readADC(unsigned char num) {
  unsigned char temp;
  ADMUX = (ADMUX & 0xE0) | num; //set ADC input
  ADCSRA = ADCSRA | 0x40;       //start analog to digital conversion
  while (ADCSRA & (1<<ADSC));   //wait for conversion to finish
  temp = ADCH;                  //read upper 8bits
  return temp;
}

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
	PORTD|=(1<<PD2);
    OCR1A=L;      //set next interrupt for on time of left motor
  } else if (state == 1) {
    state++;
	PORTD &=~(1<<PD2);
	OCR1A = 12000-L;    //set next interrupt for off time of left motor
  } else if (state == 2) {
    state++;
	PORTD|=(1<<PD3);
	OCR1A = R; //set next interrupt for on time of right motor
  } else if (state == 3) {
    state++;
	PORTD&=~(1<<PD3);
	OCR1A = 12000 - R;
	
  
  
}   else if (state == 4) {
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
  initialize_adc();   //set direction and initialize timer
  DDRD|=(1<<PD3);     //set pins 3-5 to output
  DDRD|=(1<<PD4);
  DDRD|=(1<<PD5);
  while (1) {
	char var1;
	char var2;
	var1=readADC(0);  //Sets variables 1 and 2 to represent the light intake of the sensors
	var2=readADC(1);
	unsigned char error;
	error=((var1-var2)*25/255);  //Sets error to the difference between the sensors' light intake times a constant
	set_motor_speed(0,20-error); //Sets motor speed depending on the amount of error the sensors read
	set_motor_speed(1,-20-error);
	
  }
  
  

  

  return 0;
}