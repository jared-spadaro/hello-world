//Jared Spadaro and Carmen Dang
//CPE 123 Lab 3
//10/22/12 Section 5
#include <avr/io.h>
#include <util/delay.h>
#include <interrupt.h>

//call this first to enable the analog-to-digital converter
void initialize_adc(void) {
  ADCSRA |= (1<<ADPS2) |  (1<<ADPS1) |  (1<<ADPS0);  //set prescalar
  ADMUX |= (1<<REFS0);  //set reference voltage
  ADMUX |= (1<<ADLAR);  //left align data
  ADCSRA |= (1<<ADEN);  //enable ADC
}

//call this to read one of the analog input pins
//example:   readADC(0);   --read input 0 and return the 8-bit digital number
unsigned char readADC(unsigned char num) {
  unsigned char temp;
  ADMUX = (ADMUX & 0xE0) | num; //set ADC input
  ADCSRA = ADCSRA | 0x40;       //start analog to digital conversion
  while (ADCSRA & (1<<ADSC));   //wait for conversion to finish
  temp = ADCH;                  //read upper 8bits
  return temp;
}

int main (void) {
	DDRD|=(1<<PD0);  //Turn pins to output
	DDRD|=(1<<PD1);
	DDRD|=(1<<PD2);
	initialize_adc();  //Enables analog-to-digital coverter
	while(1){ //Begins loop
		unsigned char x;
		if ((x=readADC(1))<<25){  //Commands led1 to turn on if the sensor reads less than 25 light on a 0-255 scale
			PORTD|=(1<<PD1);
			}else{
				PORTD&=~(1<<PD1); //Commands led1 to turn off if the sensor reads more than 25 light on a 0-255 scale
			}
		}
	return 0;
}
			
			
